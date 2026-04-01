package com.example.myfirstapp.todo.utils

import android.app.Application
import android.util.Log
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableDoubleStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.initializer
import androidx.lifecycle.viewmodel.viewModelFactory
import kotlinx.coroutines.launch

class AccelerometerViewModel(application: Application) : AndroidViewModel(application) {
    var xAcceleration by mutableDoubleStateOf(0.0)
        private set
    var yAcceleration by mutableDoubleStateOf(0.0)
        private set
    var zAcceleration by mutableDoubleStateOf(0.0)
        private set

    init {
        viewModelScope.launch {
            AccelerometerSensorMonitor(getApplication()).acceleration.collect { values ->
                if (values.size >= 3) {
                    xAcceleration = values[0].toDouble()
                    yAcceleration = values[1].toDouble()
                    zAcceleration = values[2].toDouble()
                    Log.d(
                        "Accelerometer",
                        "X: ${xAcceleration}, Y: ${yAcceleration}, Z: ${zAcceleration}"
                    )
                }
            }
        }
    }

    companion object {
        fun Factory(application: Application): ViewModelProvider.Factory = viewModelFactory {
            initializer {
                AccelerometerViewModel(application)
            }
        }
    }
}
