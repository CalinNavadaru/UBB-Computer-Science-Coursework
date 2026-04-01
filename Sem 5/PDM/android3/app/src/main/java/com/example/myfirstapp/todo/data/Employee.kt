package com.example.myfirstapp.todo.data

import androidx.room.Entity
import androidx.room.PrimaryKey
import java.util.UUID

@Entity(tableName = "Employees")
data class Employee(
    @PrimaryKey var _id: String = UUID.randomUUID().toString(),
    val first_name: String = "",
    val last_name: String = "",
    val salary: Double = 0.0,
    val date_join: String = "",
    val on_field: Boolean = true,
    var isSaved: Boolean = true,
    var latitude: Double = 0.0,
    var longitude: Double = 0.0
) {
}
