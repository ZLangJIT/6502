package com.rogerboesch.opengltutorial

import android.app.*
import android.content.*
import android.os.*
import android.util.*
import android.view.*
import android.widget.*
import com.google.androidgamesdk.*

class MainActivity : GameActivity() {
    companion object {
        init {
            System.loadLibrary("emu_main_jni")
        }
    }
 
    var myService: MyService? = null
    var isBound = false

    private val myConnection = object : ServiceConnection {
        override fun onServiceConnected(className: ComponentName, service: IBinder) {
            val binder = service as MyService.MyLocalBinder
            myService = binder.getService()
            isBound = true
            getBackgroundNotification(applicationContext, myService).executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR)
        }

        override fun onServiceDisconnected(name: ComponentName) {
            isBound = false
        }
    }

    public override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Log.i("Assets", "copying assets folder")
        AssetsManager().copyAssetFolder(assets, filesDir.absolutePath)

        val serviceClass = MyService::class.java
        val serviceIntent = Intent(applicationContext, serviceClass)
        
        // If the service is not running then start it
        if (!isServiceRunning(serviceClass)) {
            // Start the service
            startService(serviceIntent)
            bindService(serviceIntent, myConnection, Context.BIND_AUTO_CREATE)
        } else {
            toast("Service already running.")
            bindService(serviceIntent, myConnection, Context.BIND_AUTO_CREATE)
        }
    }

    // Custom method to determine whether a service is running
    private fun isServiceRunning(serviceClass: Class<*>): Boolean {
        val activityManager = getSystemService(Context.ACTIVITY_SERVICE) as ActivityManager

        // Loop through the running services
        for (service in activityManager.getRunningServices(Integer.MAX_VALUE)) {
            if (serviceClass.name == service.service.className) {
                // If the service is running then return true
                return true
            }
        }
        return false
    }

  override fun onWindowFocusChanged(hasFocus: Boolean) {
        super.onWindowFocusChanged(hasFocus)
        if (hasFocus) {
            //hideSystemUi()
        }
    }

    private fun hideSystemUi() {
        val decorView = window.decorView
        decorView.systemUiVisibility = (View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                or View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                or View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                or View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                or View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                or View.SYSTEM_UI_FLAG_FULLSCREEN)
    }
}

// Extension function to show toast message
fun Context.toast(message:String){
    Toast.makeText(applicationContext,message,Toast.LENGTH_SHORT).show()
}
