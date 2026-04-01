package com.example.myfirstapp.todo.data.remote

import com.example.myfirstapp.todo.data.Employee

data class Payload(val updatedEmployee: Employee)

data class ItemEvent(val event: String, val payload: Payload)
