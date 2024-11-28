package app.zlangjit;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.view.View;

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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        IRCService.FILES_DIR = getFilesDir().getPath();
        try {
            new net.lingala.zip4j.ZipFile(getApplicationInfo().publicSourceDir)
              .extractFile("lib/", IRCService.FILES_DIR + "/lib");
        } catch (net.lingala.zip4j.exception.ZipException e) {
            throw e;
        }
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
