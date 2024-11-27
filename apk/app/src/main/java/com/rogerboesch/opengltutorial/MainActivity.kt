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
 
    public override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Log.i("Assets", "copying assets folder")
        AssetsManager().copyAssetFolder(assets, filesDir.absolutePath)
        IRCService.createNotificationChannel(this);
        IRCService.start(this);
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
