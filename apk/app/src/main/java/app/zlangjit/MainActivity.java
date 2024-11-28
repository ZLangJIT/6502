package app.zlangjit;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Build;
import android.view.View;
import android.util.Log;
import java.util.*;

import com.google.androidgamesdk.GameActivity;

public class MainActivity extends GameActivity {
    static {
        System.loadLibrary("emu_main_jni");
    }
    
    // final BroadcastReceiver foo = new BroadcastReceiver() {
    //     @Override
    //     public void onReceive(Context context, Intent intent) {
    //         MainActivity a = (MainActivity)context;
    //         a.unregisterReceiver(this);
    //         a.finish();
    //     }
    // };

    private static final String TAG = "MainActivity";
    
    private static String determineTermuxArchName() {
      // Note that we cannot use System.getProperty("os.arch") since that may give e.g. "aarch64"
      // while a 64-bit runtime may not be installed (like on the Samsung Galaxy S5 Neo).
      // Instead we search through the supported abi:s on the device, see:
      // http://developer.android.com/ndk/guides/abis.html
      // Note that we search for abi:s in preferred order (the ordering of the
      // Build.SUPPORTED_ABIS list) to avoid e.g. installing arm on an x86 system where arm
      // emulation is available.
      for (String androidArch : Build.SUPPORTED_ABIS) {
        switch (androidArch) {
          case "arm64-v8a": return "aarch64";
          case "armeabi-v7a": return "arm";
          case "x86_64": return "x86_64";
          case "x86": return "i686";
        }
      }
      throw new RuntimeException("Unable to determine arch from Build.SUPPORTED_ABIS =  " +
      Arrays.toString(Build.SUPPORTED_ABIS));
    }

    private static String determineTermuxLibName() {
      // Note that we cannot use System.getProperty("os.arch") since that may give e.g. "aarch64"
      // while a 64-bit runtime may not be installed (like on the Samsung Galaxy S5 Neo).
      // Instead we search through the supported abi:s on the device, see:
      // http://developer.android.com/ndk/guides/abis.html
      // Note that we search for abi:s in preferred order (the ordering of the
      // Build.SUPPORTED_ABIS list) to avoid e.g. installing arm on an x86 system where arm
      // emulation is available.
      for (String androidArch : Build.SUPPORTED_ABIS) {
        switch (androidArch) {
          case "arm64-v8a": return "arm64-v8a";
          case "armeabi-v7a": return "armeabi-v7a";
          case "x86_64": return "x86_64";
          case "x86": return "x86";
        }
      }
      throw new RuntimeException("Unable to determine arch from Build.SUPPORTED_ABIS =  " +
      Arrays.toString(Build.SUPPORTED_ABIS));
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        IRCService.FILES_DIR = getFilesDir().getPath();
        IRCService.ARCH_LIB = determineTermuxLibName();
        IRCService.ARCH_NAME = determineTermuxArchName();
        
        String apk = getApplicationInfo().publicSourceDir;
        
        Log.i(TAG, "extracting apk " + IRCService.ARCH_LIB + " libs...");
        net.lingala.zip4j.ZipFile z = new net.lingala.zip4j.ZipFile(apk);
        z.getFileHeaders().stream().forEach(fileHeader -> {
            String name = fileHeader.getFileName();
            if (name.startsWith("lib/" + IRCService.ARCH_LIB)) {
                if (name.startsWith("lib/" + IRCService.ARCH_LIB + "/executable__")) {
                    String out = name.replace("executable__", "").replace(".so", "");
                    Log.i(TAG, "extracting executable: " + out);
                    try {
                        z.extractFile(fileHeader, IRCService.FILES_DIR + "/bin", out);
                    } catch (net.lingala.zip4j.exception.ZipException e) {
                        // wrap exception in RuntimeException
                        throw new RuntimeException(e);
                    }
                    if ((new java.io.File(IRCService.FILES_DIR + "/bin/" + out).setExecutable(true, true))) {
                        Log.i(TAG, "chmod +x " + out);
                    } else {
                        throw new RuntimeException("failed to chmod +x " + out);
                    }
                } else {
                    Log.i(TAG, "extracting shared library: " + name);
                    try {
                        z.extractFile(fileHeader, IRCService.FILES_DIR + "/lib");
                    } catch (net.lingala.zip4j.exception.ZipException e) {
                        // wrap exception in RuntimeException
                        throw new RuntimeException(e);
                    }
                }
            }
        });
        Log.i(TAG, "extracted apk " + IRCService.ARCH_LIB + " libs to " + IRCService.FILES_DIR);
        IRCService.createNotificationChannel(this);
        IRCService.start(this);
        //registerReceiver(foo, new IntentFilter("app.zlangjit.broadcast.service_exit_pressed"), Context.RECEIVER_NOT_EXPORTED);
    }

    boolean saved_vis = false;
    int vis_original = 0;
    int vis_immersive = 0;

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);

        if (hasFocus) {
            //hideSystemUi();
        }
    }

    private void hideSystemUi() {
        View decorView = getWindow().getDecorView();
        if (!saved_vis) {
            vis_original = decorView.getSystemUiVisibility();
            vis_immersive = View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                    | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                    | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                    | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                    | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                    | View.SYSTEM_UI_FLAG_FULLSCREEN;
            saved_vis = true;
        }
        decorView.setSystemUiVisibility(vis_immersive);
    }
}
