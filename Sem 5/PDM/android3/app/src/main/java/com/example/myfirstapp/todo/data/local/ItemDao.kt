package com.example.myfirstapp.todo.data.local

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import androidx.room.Update
import com.example.myfirstapp.todo.data.Employee
import kotlinx.coroutines.flow.Flow

@Dao
interface ItemDao {
    @Query("SELECT * FROM Employees")
    fun getAll(): Flow<List<Employee>>

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insert(item: Employee)

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insert(items: List<Employee>)

    @Update
    suspend fun update(item: Employee): Int

    @Query("DELETE FROM Employees WHERE _id = :id")
    suspend fun deleteById(id: Int): Int

    @Query("DELETE FROM Employees")
    suspend fun deleteAll(): Int

    @Query("DELETE FROM Employees where first_name= :first_name and isSaved = :isSaved")
    suspend fun deleteSongNotSaved(first_name: String, isSaved: Boolean)

    @Query("SELECT * FROM Employees where isSaved = :isSaved")
    suspend fun getLocalEmployees(isSaved: Boolean): List<Employee>

    @Query("DELETE FROM Employees where isSaved = :isSaved")
    suspend fun deleteNotSaved(isSaved: Boolean): Int

    @Query("SELECT COUNT(*) FROM Employees where isSaved = :isSaved")
    suspend fun getNotSaved(isSaved: Boolean): Int
}
