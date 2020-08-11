package com.example.dialog;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.app.Notification;
import android.app.NotificationManager;
import android.content.DialogInterface;
import android.graphics.Color;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private Button btn;
    private Button btn2;
    private Button btn3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btn = (Button)findViewById(R.id.button);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                AlertDialog.Builder dialog = new AlertDialog.Builder(MainActivity.this);
//                dialog.setIcon(R.mipmap.ic_launcher);
                dialog.setTitle("System Waring");
                dialog.setMessage("This is a warning");
                dialog.setPositiveButtonIcon(getResources().getDrawable(R.drawable.reconnect));
                dialog.setPositiveButton("continue", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        Toast.makeText(getApplicationContext(), "Click continue", Toast.LENGTH_SHORT).show();
                    }
                });
                dialog.setNegativeButtonIcon(getResources().getDrawable(R.drawable.unlink));
                dialog.setNegativeButton("cancel", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        Toast.makeText(getApplicationContext(), "Click cancel", Toast.LENGTH_SHORT).show();
                    }
                });
                dialog.show();
            }
        });

        btn2 = (Button)findViewById(R.id.button2);
        btn2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Notification.Builder builder = new Notification.Builder(MainActivity.this);
                builder.setSmallIcon(R.mipmap.ic_launcher);
                builder.setContentTitle("This is title");
                builder.setContentText("This is text");
                Notification notification = builder.build();
                NotificationManager notificationManager = (NotificationManager)getSystemService(NOTIFICATION_SERVICE);
                assert notificationManager != null;
                notificationManager.notify(123, notification);
            }
        });

        btn3 = (Button)findViewById(R.id.button3);
        registerForContextMenu(btn3);
    }

    @Override
    public void onCreateContextMenu(ContextMenu menu, View view, ContextMenu.ContextMenuInfo menuInfo) {
        MenuInflater inflater = new MenuInflater(this);
        inflater.inflate(R.menu.context_menu, menu);
        menu.setHeaderIcon(R.mipmap.ic_launcher);
        menu.setHeaderTitle("Select Color: ");
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.color_red:
                btn3.setTextColor(Color.RED);
                break;
            case R.id.color_green:
                btn3.setTextColor(Color.GREEN);
                break;
            case R.id.color_blue:
                btn3.setTextColor(Color.BLUE);
                break;
            case R.id.color_normal:
                btn3.setTextColor(Color.BLACK);
                break;
        }
        return true;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
//        menu.add("item");
//        menu.add("item1");
//        // 添加一个菜单分组, 分组ID为1, ID为1, 顺序为2
//        menu.add(1, 1, 2, "item2");
//        menu.add(1, 2, 3, "item3");
//        // 把分组1设置成选择框, 默认不选择
//        menu.setGroupCheckable(1, true, false);
//        menu.add(2, 3, 4, "item4");
//        menu.add(2, 4, 5, "item5");
//        menu.setGroupEnabled(2, false);
        MenuInflater inflater = new MenuInflater(this);
        inflater.inflate(R.menu.menu, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        Toast.makeText(this, item.getTitle() + "," + item.getItemId(), Toast.LENGTH_SHORT).show();
        return super.onOptionsItemSelected(item);
    }
}
