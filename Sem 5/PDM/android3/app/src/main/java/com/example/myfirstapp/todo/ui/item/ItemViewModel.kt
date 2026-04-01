package com.example.myfirstapp.todo.ui.item

import android.util.Log
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.initializer
import androidx.lifecycle.viewmodel.viewModelFactory
import com.example.myfirstapp.MyFirstApplication
import com.example.myfirstapp.core.Result
import com.example.myfirstapp.core.TAG
import com.example.myfirstapp.todo.data.Employee
import com.example.myfirstapp.todo.data.ItemRepository
import kotlinx.coroutines.launch

data class ItemUiState(
    val itemId: String? = null,
    val employee: Employee = Employee(),
    var loadResult: Result<Employee>? = null,
    var submitResult: Result<Employee>? = null,
)

class ItemViewModel(private val itemId: String?, private val itemRepository: ItemRepository) :
    ViewModel() {

    var uiState: ItemUiState by mutableStateOf(ItemUiState(loadResult = Result.Loading))
        private set

    init {
        Log.d(TAG, "init with id: ${itemId}")
        if (itemId != null) {
            loadItem()
        } else {
            uiState = uiState.copy(loadResult = Result.Success(Employee()))
        }
    }

    fun loadItem() {
        viewModelScope.launch {
            itemRepository.employeeStream.collect { items ->
                if (!(uiState.loadResult is Result.Loading)) {
                    return@collect
                }
                Log.d(TAG, "searching for ${itemId}")
                val employee = items.find { it._id == itemId } ?: Employee()
                Log.d(TAG, "found ${employee}")
                uiState = uiState.copy(employee = employee, loadResult = Result.Success(employee))
            }
        }
    }


    fun saveItem(first_name: String, last_name: String, salary: Double, date_join: String, on_field: Boolean){
        viewModelScope.launch {
            Log.d(TAG, "save new song!!!");
            try{
                uiState = uiState.copy(submitResult = Result.Loading)
                val item = uiState.employee.copy(first_name = first_name, last_name = last_name,
                    salary = salary, date_join = date_join, on_field = on_field, _id = "")
                val savedEmployee: Employee;
                savedEmployee = itemRepository.save(item)
                Log.d(TAG, "saved employee with success!!!!");
                uiState = uiState.copy(submitResult = Result.Success(savedEmployee))
            }catch (e: Exception){
                Log.d(TAG, "saveOrUpdateItem failed");
                val nrUnsaved = itemRepository.getNrUnsaved()
                val currentId = nrUnsaved + 1
                uiState = uiState.copy(submitResult = Result.Error(e))
                val item = uiState.employee.copy(first_name = first_name, last_name = last_name,
                    salary = salary, date_join = date_join, on_field = on_field, isSaved = false, _id = currentId.toString())
                itemRepository.addLocally(item);
                Log.d(TAG, "added item ${item} locally");
            }
        }
    }

    fun UpdateItem(first_name: String, last_name: String, salary: Number, lat: Double, lon: Double) {
        viewModelScope.launch {
            Log.d(TAG, "update Song!!!");
            try {
                uiState = uiState.copy(submitResult = Result.Loading)
                val item = uiState.employee.copy(first_name=first_name, last_name = last_name, isSaved = true, latitude = lat, longitude = lon)
                val savedEmployee: Employee;
                savedEmployee = itemRepository.update(item)
                Log.d(TAG, "UpdateItem succeeeded");
                uiState = uiState.copy(submitResult = Result.Success(savedEmployee))
            } catch (e: Exception) {
                Log.d(TAG, "saveOrUpdateItem failed");
                uiState = uiState.copy(submitResult = Result.Error(e))
                val item = uiState.employee.copy(first_name=first_name, last_name = last_name, isSaved = false, latitude=lat, longitude=lon)
                itemRepository.updateLocally(item)
            }
        }
    }

    companion object {
        fun Factory(itemId: String?): ViewModelProvider.Factory = viewModelFactory {
            initializer {
                val app =
                    (this[ViewModelProvider.AndroidViewModelFactory.APPLICATION_KEY] as MyFirstApplication)
                ItemViewModel(itemId, app.container.itemRepository)
            }
        }
    }
}
