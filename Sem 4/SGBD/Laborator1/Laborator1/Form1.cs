using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace Laborator1
{
    public partial class Form1 : Form
    {
        private const string ConnectionString = @"Server=DESKTOP-V5HRAR8\SQLEXPRESS;Database=ManagementPlati;
        Integrated Security=true;TrustServerCertificate=true;";

        private readonly DataSet _dsP = new DataSet();
        private readonly DataSet _dsC = new DataSet();
        SqlDataAdapter _parentAdapter;
        SqlDataAdapter _childAdapter;
        BindingSource _bsParent;
        BindingSource _bsChild;

        private SqlCommand _selectCommand;

        public Form1()
        {
            InitializeComponent();
            Text = @"Laboratorul1";
        }

        public sealed override string Text
        {
            get { return base.Text; }
            set { base.Text = value; }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(ConnectionString))
                {
                    tableChild.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
                    tableChild.MultiSelect = false;
                    tableChild.ReadOnly = true;
                    tableParent.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
                    tableParent.MultiSelect = false;
                    tableParent.ReadOnly = true;
                    tableParent.AutoGenerateColumns = true;
                    tableChild.AutoGenerateColumns = true;
                    
                    conn.Open();
                    MessageBox.Show(@"Starea conexiunii: " + conn.State);
                    _parentAdapter = new SqlDataAdapter("SELECT * FROM Departamente;", conn);
                    _parentAdapter.Fill(_dsP, "Departamente");
                    _bsParent = new BindingSource();
                    _bsParent.DataSource = _dsP.Tables["Departamente"];
                    tableParent.DataSource = _bsParent;
                    tableParent.Rows[0].Selected = true;
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private void TableParent_SelectionChanged(object sender, EventArgs e)
        {
            try
            {
                _dsC.Clear();
                using (SqlConnection connection = new SqlConnection(ConnectionString))
                {
                    _selectCommand = new SqlCommand("SELECT * FROM ECHIPE WHERE depid = @id", connection);
                    if (tableParent.SelectedRows.Count > 0)
                    {
                        object departament = tableParent.SelectedRows[0].Cells[0].Value;
                        _selectCommand.Parameters.AddWithValue("@id", departament);
                        _childAdapter = new SqlDataAdapter(_selectCommand);
                        _childAdapter.Fill(_dsC, "ECHIPE");
                        _bsChild = new BindingSource();
                        _bsChild.DataSource = _dsC.Tables["ECHIPE"];
                        tableChild.DataSource = _bsChild;
                    }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(ConnectionString))
                {
                    connection.Open();
                    object id = tableChild.SelectedRows[0].Cells[0].Value;
                    object departament = tableParent.SelectedRows[0].Cells[0].Value;
                    _selectCommand = new SqlCommand("SELECT * FROM ECHIPE WHERE depid = @id", connection);
                    _selectCommand.Parameters.AddWithValue("@id", departament);
                    SqlCommand deleteCommand = new SqlCommand("DELETE FROM ECHIPE WHERE id=@id;",
                        connection);
                    deleteCommand.Parameters.AddWithValue("@id", id);
                    var nr = deleteCommand.ExecuteNonQuery();
                    if (nr < 0)
                    {
                        throw new Exception("Nu s-a putut fac stergerea!");
                    }
                    _dsC.Clear();
                    _childAdapter = new SqlDataAdapter(_selectCommand);
                    _childAdapter.Fill(_dsC, "ECHIPE");
                    _bsChild = new BindingSource();
                    _bsChild.DataSource = _dsC.Tables["ECHIPE"];
                    tableChild.DataSource = _bsChild;
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private void BtnUpdate_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(ConnectionString))
                {
                    connection.Open();
                    object id = tableChild.SelectedRows[0].Cells[0].Value;
                    object departament = tableParent.SelectedRows[0].Cells[0].Value;
                    var text = textBoxName.Text;
                    _selectCommand = new SqlCommand("SELECT * FROM ECHIPE WHERE depid = @id", connection);
                    _selectCommand.Parameters.AddWithValue("@id", departament);
                    SqlCommand updateCommand = new SqlCommand("UPDATE ECHIPE SET nume = @nume WHERE id=@id;",
                        connection);
                    updateCommand.Parameters.AddWithValue("@id", id);
                    updateCommand.Parameters.AddWithValue("@nume", text);
                    var nr = updateCommand.ExecuteNonQuery();
                    if (nr < 0)
                    {
                        throw new Exception("Nu s-a putut fac Update!");
                    }
                    _dsC.Clear();
                    _childAdapter = new SqlDataAdapter(_selectCommand);
                    _childAdapter.Fill(_dsC, "ECHIPE");
                    _bsChild = new BindingSource();
                    _bsChild.DataSource = _dsC.Tables["ECHIPE"];
                    tableChild.DataSource = _bsChild;
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(ConnectionString))
                {
                    connection.Open();
                    object departament = tableParent.SelectedRows[0].Cells[0].Value;
                    var text = textBoxAddName.Text;
                    _selectCommand = new SqlCommand("SELECT * FROM ECHIPE WHERE depid = @id", connection);
                    _selectCommand.Parameters.AddWithValue("@id", departament);
                    SqlCommand insertCommand = new SqlCommand("INSERT INTO ECHIPE(nume, depid) VALUES (@nume, @depid)",
                        connection);
                    insertCommand.Parameters.AddWithValue("@depid", departament);
                    insertCommand.Parameters.AddWithValue("@nume", text);
                    var nr = insertCommand.ExecuteNonQuery();
                    if (nr < 0)
                    {
                        throw new Exception("Nu s-a putut fac inserarea!");
                    }
                    _dsC.Clear();
                    _childAdapter = new SqlDataAdapter(_selectCommand);
                    _childAdapter.Fill(_dsC, "ECHIPE");
                    _bsChild = new BindingSource();
                    _bsChild.DataSource = _dsC.Tables["ECHIPE"];
                    tableChild.DataSource = _bsChild;
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }
    }
}