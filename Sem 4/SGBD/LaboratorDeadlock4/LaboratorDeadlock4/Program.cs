namespace LaboratorDeadlock4
{
    using System;
    using System.Data.SqlClient;

    internal abstract class Program
    {
        private static void Main()
        {
            const string connectionString = @"
                                            Server=DESKTOP-V5HRAR8\SQLEXPRESS;Database=ManagementPlati;
                                                    Integrated Security=true;TrustServerCertificate=true;
                                            ";

            var retryCount = 0;
            var success = false;

            while (!success && retryCount < 3)
            {
                Console.WriteLine("Retry count: " + retryCount);

                var thread1 = new Thread(() =>
                {
                    Console.WriteLine("Thread1 is running!");

                    using var connection = new SqlConnection(connectionString);
                    connection.Open();

                    using (var setTransactionLevelUncommited = connection.CreateCommand())
                    {
                        setTransactionLevelUncommited.CommandText = "SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED";
                        setTransactionLevelUncommited.ExecuteNonQuery();
                    }
                    
                    using (var transaction = connection.BeginTransaction())
                    {
                        try
                        {
                            using (var command = connection.CreateCommand())
                            {
                                command.Transaction = transaction;

                                // Update statement 1
                                command.CommandText = "UPDATE Bonusuri SET procent = 90 WHERE BonusuriId = 2";
                                command.ExecuteNonQuery();

                                // Delay for 7 seconds
                                Thread.Sleep(7000);

                                // Update statement 2
                                command.CommandText = "UPDATE Deductii SET procent = 90 WHERE DeductiiId = 2";
                                command.ExecuteNonQuery();
                            }

                            // Commit the transaction
                            transaction.Commit();
                            Console.WriteLine("Transaction committed successfully.");
                            success = true;
                        }
                        catch (SqlException ex)
                        {
                            if (ex.Number == 1205)
                            {
                                Console.WriteLine("Deadlock occurred. Retrying...");

                                transaction.Rollback();
                                Console.WriteLine("Transaction rolled back.");
                                retryCount++;
                            }
                            else
                            {
                                Console.WriteLine("Error occurred: " + ex.Message);
                                transaction.Rollback();
                                Console.WriteLine("Transaction rolled back.");
                            }
                        }
                    }
                });

                var thread2 = new Thread(() =>
                {
                    Console.WriteLine("Thread2 is running!");
                    using var connection = new SqlConnection(connectionString);
                    connection.Open();

                    using (var setTransactionLevelUncommited = connection.CreateCommand())
                    {
                        setTransactionLevelUncommited.CommandText = "SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED";
                        setTransactionLevelUncommited.ExecuteNonQuery();
                    }

                    using var transaction = connection.BeginTransaction();
                    try
                    {
                        using (var command = connection.CreateCommand())
                        {
                            command.Transaction = transaction;


                            command.CommandText = "UPDATE Deductii SET procent = 90 WHERE DeductiiId = 2";
                            command.ExecuteNonQuery();

                            Thread.Sleep(7000);
                            
                            command.CommandText = "UPDATE Bonusuri SET procent = 90 WHERE BonusuriId = 2";
                            command.ExecuteNonQuery();
                        }
                        
                        transaction.Commit();
                        Console.WriteLine("Transaction committed successfully.");
                        success = true;
                    }
                    catch (SqlException ex)
                    {
                        if (ex.Number == 1205)
                        {
                            Console.WriteLine("Deadlock occurred. Retrying...");

                            transaction.Rollback();
                            Console.WriteLine("Transaction rolled back.");
                            retryCount++;
                        }
                        else
                        {
                            Console.WriteLine("Error occurred: " + ex.Message);
                            transaction.Rollback();
                            Console.WriteLine("Transaction rolled back.");
                        }
                    }
                });

                thread1.Start();
                thread2.Start();
                thread1.Join();
                thread2.Join();
            }

            Console.WriteLine(retryCount >= 3
                ? "Exceeded maximum retry attempts. Aborting."
                : "All transactions completed.");
        }
    }
}