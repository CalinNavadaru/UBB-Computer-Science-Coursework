package com.example.myfirstapp

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import com.example.myfirstapp.todo.data.Employee
import com.example.myfirstapp.todo.data.local.ItemDao

@Database(entities = arrayOf(Employee::class), version = 1)
abstract class MyAppDatabase : RoomDatabase() {
    abstract fun itemDao(): ItemDao

    companion object {
        @Volatile
        private var INSTANCE: MyAppDatabase? = null

        fun getDatabase(context: Context): MyAppDatabase {
            return INSTANCE ?: synchronized(this) {
                val instance = Room.databaseBuilder(
                    context,
                    MyAppDatabase::class.java,
                    "employee_database"
                )
                    .build()
                INSTANCE = instance
                instance
            }
        }
    }
}
