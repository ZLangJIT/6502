package com.rogerboesch.opengltutorial

import android.app.NotificationChannel;
import android.app.PendingIntent;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.os.Build;
import android.os.IBinder;
import androidx.annotation.Nullable;
import androidx.core.app.NotificationCompat;

import android.os.Message;
import android.util.Log;

import java.util.HashMap;
import java.util.Map;

import io.mrarm.chatlib.dto.MessageId;
import io.mrarm.chatlib.dto.MessageInfo;
import io.mrarm.chatlib.message.MessageListener;
import io.mrarm.irc.job.ServerPingScheduler;
import io.mrarm.irc.util.WarningHelper;

public class IRCService extends Service {

    private static final String TAG = "IRCService";

    public static final int IDLE_NOTIFICATION_ID = 100;
    public static final int EXIT_ACTION_ID = 102; // 101 is taken by chat summary
    public static final String ACTION_START_FOREGROUND = "start_foreground";

    private static final String IDLE_NOTIFICATION_CHANNEL = "IdleNotification";

    public static void start(Context context) {
        Intent intent = new Intent(context, IRCService.class);
        intent.setAction(ACTION_START_FOREGROUND);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O)
            context.startForegroundService(intent);
        else
            context.startService(intent);
    }
    public static void stop(Context context) {
        context.stopService(new Intent(context, IRCService.class));
    }

    public static void createNotificationChannel(Context ctx) {
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.O)
            return;
        NotificationChannel channel = new NotificationChannel(IDLE_NOTIFICATION_CHANNEL,
                "a channel",
                android.app.NotificationManager.IMPORTANCE_MIN);
        channel.setGroup(NotificationManager.getSystemNotificationChannelGroup(ctx));
        channel.setShowBadge(false);
        android.app.NotificationManager mgr = (android.app.NotificationManager)
                ctx.getSystemService(NOTIFICATION_SERVICE);
        mgr.createNotificationChannel(channel);
    }

    @Override
    public void onCreate() {
        super.onCreate();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        String action = intent != null ? intent.getAction() : null;
        if (action == null)
            return START_STICKY;
        if (action.equals(ACTION_START_FOREGROUND)) {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O && !mCreatedChannel) {
                createNotificationChannel(this);
                mCreatedChannel = true;
            }

            StringBuilder b = new StringBuilder();
            int connectedCount = 0, connectingCount = 0, disconnectedCount = 0;
            b.append("Connected to 0 networks");
            Intent mainIntent = MainActivity.getLaunchIntent(this, null, null);
            PendingIntent exitIntent = PendingIntent.getBroadcast(this, EXIT_ACTION_ID,
                    ExitActionReceiver.getIntent(this),
                    PendingIntent.FLAG_CANCEL_CURRENT);
            NotificationCompat.Builder notification = new NotificationCompat.Builder(this, IDLE_NOTIFICATION_CHANNEL)
                    .setContentTitle("IRCService")
                    .setContentText(b.toString())
                    .setPriority(NotificationCompat.PRIORITY_MIN)
                    .setOnlyAlertOnce(true)
                    .setContentIntent(PendingIntent.getActivity(this, IDLE_NOTIFICATION_ID, mainIntent, PendingIntent.FLAG_CANCEL_CURRENT))
                    .addAction(Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP ? R.drawable.ic_close : R.drawable.ic_notification_close, getString(R.string.action_exit), exitIntent);
            notification.setSmallIcon(R.drawable.ic_close);
            startForeground(IDLE_NOTIFICATION_ID, notification.build());
        }
        return START_STICKY;
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    public static class ExitActionReceiver extends BroadcastReceiver {

        public static Intent getIntent(Context context) {
            return new Intent(context, ExitActionReceiver.class);
        }

        @Override
        public void onReceive(Context context, Intent intent) {
            //((IRCApplication) context.getApplicationContext()).requestExit();
        }
    }
}