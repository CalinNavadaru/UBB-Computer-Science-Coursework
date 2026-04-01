package com.example.myfirstapp.todo.ui.items

import android.util.Log
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Info
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.myfirstapp.todo.data.Employee

typealias OnItemFn = (id: String?) -> Unit

@Composable
fun ItemList(employeeList: List<Employee>, onItemClick: OnItemFn, modifier: Modifier) {
    Log.d("ItemList", "recompose")
    LazyColumn(
        modifier = modifier
            .fillMaxSize()
            .padding(12.dp)
    ) {
        items(employeeList) { item ->
            ItemDetail(item, onItemClick)
        }
    }
}

@Composable
fun ItemDetail(employee: Employee, onItemClick: OnItemFn) {
    Log.d("ItemDetail", "recompose id = ${employee._id}, first_name: ${employee.first_name}")
    var isExpanded by remember { mutableStateOf(false) }

    Row {
        Column(
            modifier = Modifier
                .padding(16.dp)
                .clickable { onItemClick(employee._id) }
        ) {
            Text(
                text = employee.first_name,
                style = TextStyle(
                    fontSize = 24.sp,
                    fontWeight = FontWeight.Bold
                )
            )
            Text(
                text = employee.last_name,
                style = TextStyle(
                    fontSize = 18.sp,
                    fontStyle = FontStyle.Italic
                )
            )
            Text(
                text = "Salary: ${employee.salary}",
                style = TextStyle(
                    fontSize = 16.sp,
                    color = Color.Gray
                )
            )
            Text(
                text = "Date: ${employee.date_join}",
                style = TextStyle(
                    fontSize = 16.sp,
                    color = Color.Gray
                )
            )
            Text(
                text = "IsSaved: ${employee.isSaved}",
                style = TextStyle(
                    fontSize = 16.sp,
                    color = Color.Gray
                )
            )
        }
    }
    Surface(modifier = Modifier
        .fillMaxWidth(),
        onClick = { isExpanded = !isExpanded }) {
        Column {
            Row {
                Icon(
                    imageVector = Icons.Default.Info,
                    contentDescription = null
                )
                Spacer(modifier = Modifier.width(16.dp))
                Text(
                    text = "Show latitude & longitude",
                    style = MaterialTheme.typography.headlineSmall
                )
            }
            if (isExpanded) {
                Spacer(modifier = Modifier.height(8.dp))
                Text(
                    text = "Latitude: ${employee.latitude}, Longitude: ${employee.longitude}",
                    textAlign = TextAlign.Center
                )
            }
        }
    }
}
