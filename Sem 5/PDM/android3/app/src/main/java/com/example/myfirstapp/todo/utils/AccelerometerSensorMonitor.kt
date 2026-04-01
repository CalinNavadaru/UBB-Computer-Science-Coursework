package com.example.myfirstapp.todo.utils

import android.content.Context
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import kotlinx.coroutines.ExperimentalCoroutinesApi
import kotlinx.coroutines.channels.awaitClose
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.callbackFlow
import android.app.Application
import android.util.Log
import androidx.compose.foundation.layout.Column
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.unit.sp
import androidx.lifecycle.viewmodel.compose.viewModel


@OptIn(ExperimentalCoroutinesApi::class)
class AccelerometerSensorMonitor(val context: Context) {
    val acceleration: Flow<List<Float>> = callbackFlow {
        val sensorManager: SensorManager =
            context.getSystemService(Context.SENSOR_SERVICE) as SensorManager
        val accelerometer: Sensor? = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER)

        val accelerometerSensorEventListener = object : SensorEventListener {
            override fun onAccuracyChanged(sensor: Sensor, accuracy: Int) {}

            override fun onSensorChanged(event: SensorEvent) {
                if (event.sensor.type == Sensor.TYPE_ACCELEROMETER) {
                    Log.d(
                        "Accelerometer",
                        "X: ${event.values[0]}, Y: ${event.values[1]}, Z: ${event.values[2]}"
                    )
                    channel.trySend(event.values.toList())
                }
            }
        }

        sensorManager.registerListener(
            accelerometerSensorEventListener,
            accelerometer,
            SensorManager.SENSOR_DELAY_NORMAL
        )

        awaitClose {
            sensorManager.unregisterListener(accelerometerSensorEventListener)
        }
    }
}


@Composable
fun AccelerometerSensor() {
    val accelerometerViewModel = viewModel<AccelerometerViewModel>(
        factory = AccelerometerViewModel.Factory(
            LocalContext.current.applicationContext as Application
        )
    )

    Text(
        text = "X Acceleration: ${accelerometerViewModel.xAcceleration} m/s²",
        style = TextStyle(fontSize = 20.sp, color = Color.Black)
    )
    Text(
        text = "Y Acceleration: ${accelerometerViewModel.yAcceleration} m/s²",
        style = TextStyle(fontSize = 20.sp, color = Color.Black)
    )
    Text(
        text = "Z Acceleration: ${accelerometerViewModel.zAcceleration} m/s²",
        style = TextStyle(fontSize = 20.sp, color = Color.Black)
    )
    if (accelerometerViewModel.xAcceleration in 8.0..10.0) {
        Text(
            text = "X acceleration is within the range 80-100!",
            style = TextStyle(fontSize = 20.sp, color = Color.Green)
        )
    }
}
