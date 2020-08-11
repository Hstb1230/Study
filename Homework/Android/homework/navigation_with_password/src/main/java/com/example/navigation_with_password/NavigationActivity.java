package com.example.navigation_with_password;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.PixelFormat;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.GridView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class NavigationActivity
        extends AppCompatActivity
{

    private GridView appListGrid;
    private ArrayList<Map<String, Object>> appList;
    private HashMap<String, String> appLink;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_navigation);

        initData();
        initView();
        bindData();
        bindEvent();
    }

    /**
     * 检查包是否存在
     * @param packname 包名
     * @return 是否存在
     */
    private boolean checkPackInfo(String packname) {
        PackageInfo packageInfo = null;
        try {
            packageInfo = getPackageManager().getPackageInfo(packname, 0);
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }
        return packageInfo != null;
    }

    private void bindEvent()
    {
        appListGrid.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l)
            {
                String packageName = ((TextView) (view.findViewById(R.id.appPackageName))).getText().toString();
                System.out.println(i);
                System.out.println(packageName);
                if(packageName.equals("Link"))
                {
                    String appName = ((TextView) (appListGrid.getChildAt(i).findViewById(R.id.appName))).getText().toString();
                    Uri uri = Uri.parse(appLink.get(appName));
                    Intent intent = new Intent(Intent.ACTION_VIEW);
                    intent.setData(uri);
                    startActivity(intent);
                }
                else if(packageName.equals("WebView"))
                {
                    Toast.makeText(getApplicationContext(), "Turn on another activity in this app", Toast.LENGTH_SHORT).show();
                    Intent intent = new Intent(getApplicationContext(), WebViewActivity.class);
                    startActivity(intent);
                }
                else
                {
                    PackageManager packageManager = getPackageManager();
                    if(checkPackInfo(packageName))
                    {
                        Intent intent = packageManager.getLaunchIntentForPackage(packageName);
                        startActivity(intent);
                    }
                    else
                    {
                        Toast.makeText(getApplicationContext(), packageName, Toast.LENGTH_SHORT).show();
                    }
                }
            }
        });
    }

    private void bindData()
    {
        SimpleAdapter adapter = new SimpleAdapter(
                getApplicationContext(),
                appList,
                R.layout.app_item, new String[] {"name", "package", "icon"},
                new int[] {R.id.appName, R.id.appPackageName, R.id.appIcon}
                );
        appListGrid.setAdapter(adapter);
    }

    public byte[] bitmap2Bytes(Bitmap bm)
    {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        bm.compress(Bitmap.CompressFormat.PNG, 100, baos);
        return baos.toByteArray();
    }

    public static Bitmap drawableToBitmap(Drawable drawable)
    {
        // 取 drawable 的长宽
        int w = drawable.getIntrinsicWidth();
        int h = drawable.getIntrinsicHeight();

        // 取 drawable 的颜色格式
        Bitmap.Config config = drawable.getOpacity() != PixelFormat.OPAQUE ? Bitmap.Config.ARGB_8888
                : Bitmap.Config.RGB_565;
        // 建立对应 bitmap
        Bitmap bitmap = Bitmap.createBitmap(w, h, config);
        // 建立对应 bitmap 的画布
        Canvas canvas = new Canvas(bitmap);
        drawable.setBounds(0, 0, w, h);
        // 把 drawable 内容画到画布中
        drawable.draw(canvas);
        return bitmap;
    }

    private ArrayList<Map<String, Object>> getPackages()
    {
        // 获取已经安装的所有应用, PackageInfo　系统类，包含应用信息
        List<PackageInfo> packages = getPackageManager().getInstalledPackages(0);
        ArrayList<Map<String, Object>> list = new ArrayList<>();
        Log.v("AppCount", String.valueOf(packages.size()));

        for (int i = 0; i < packages.size(); i++) {
            PackageInfo packageInfo = packages.get(i);
            if ((packageInfo.applicationInfo.flags & ApplicationInfo.FLAG_SYSTEM) == 0) { //非系统应用

                if(getPackageName().equals(packageInfo.packageName))
                    continue;
                else if(packageInfo.packageName.equals("com.papegames.evol.mi"))
                    continue;
                // AppInfo 自定义类，包含应用信息
                Map<String, Object> appInfo = new HashMap<>();
                appInfo.put("name", packageInfo.applicationInfo.loadLabel(getPackageManager()).toString());//获取应用名称
                appInfo.put("package", packageInfo.packageName); //获取应用包名，可用于卸载和启动应用
                try {
                    FileOutputStream outStream = openFileOutput("other-app-icon-" + String.valueOf(i), MODE_PRIVATE);
                    outStream.write(bitmap2Bytes(drawableToBitmap(packageInfo.applicationInfo.loadIcon(getPackageManager()))));
                    outStream.close();
                } catch(IOException e)
                {
                    e.printStackTrace();
                }

                appInfo.put("icon", getFilesDir().getAbsolutePath() + "/other-app-icon-" + String.valueOf(i));//获取应用图标
                System.out.println(appInfo.toString());
                list.add(appInfo);
            }
        }
        return list;
    }

    private void initData()
    {
        appList = getPackages();

        appLink = new HashMap<String, String> ();
        appLink.put("AliPay", "https://www.alipay.com/");
        appLink.put("NetEase", "https://music.163.com/");

        for(String app : appLink.keySet())
        {

            // AppInfo 自定义类，包含应用信息
            Map<String, Object> appInfo = new HashMap<>();
            appInfo.put("name", app);//获取应用名称
            appInfo.put("package", "Link"); //获取应用包名，可用于卸载和启动应用
            appInfo.put("icon", R.drawable.browser);//获取应用图标
            System.out.println(appInfo.toString());
            appList.add(appInfo);

        }

            // AppInfo 自定义类，包含应用信息
            Map<String, Object> appInfo = new HashMap<>();
            appInfo.put("name", "WebView");//获取应用名称
            appInfo.put("package", "WebView"); //获取应用包名，可用于卸载和启动应用
            appInfo.put("icon", android.R.mipmap.sym_def_app_icon);//获取应用图标
            System.out.println(appInfo.toString());
            appList.add(appInfo);
    }

    private void initView()
    {
        appListGrid = (GridView) findViewById(R.id.appList);
    }
}
