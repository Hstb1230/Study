package com.example.simple_chat;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.animation.ValueAnimator;
import android.annotation.SuppressLint;
import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.content.ContentProviderOperation;
import android.content.ContentProviderResult;
import android.content.ContentResolver;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.OperationApplicationException;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.drawable.GradientDrawable;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.os.RemoteException;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.GridLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.TimePicker;
import android.widget.Toast;

import com.example.simple_chat.recycler_view_adapter.ChatAdapter;
import com.example.simple_chat.field.MessageType;
import com.example.simple_chat.field.RecordInfo;
import com.example.simple_chat.util.KeyboardUtil;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;

public class MainActivity
        extends AppCompatActivity
{

    private static final int CHANGE_SYSTEM_HEADER = 0x01;
    private static final int CHANGE_MY_HEADER = 0x02;
    private Button btnMore;
    private LinearLayout viewMore;
    private RecyclerView recyclerView;
    private ArrayList<RecordInfo> recordList;
    private ChatAdapter recordAdapter;
    private LinearLayout viewMoreFunctions;
    private ArrayList<Integer> timeList;
    public static HandleMe handler;
    private LinearLayout viewMoreFunctionsFold;
    private String lastInput = "";
    private SharedPreferences accountInfo;
    private SharedPreferences settingInfo;
    private ImageView robotHead;
    private ImageView myHead;
    private String username;

    public void showMoreFunctionsButton(View view)
    {
        ImageView btn = (ImageView) view;
        btn.setFocusable(true);
        btn.setFocusableInTouchMode(true);
        btn.requestFocus();
        viewMoreFunctionsFold.setVisibility(View.VISIBLE);
    }

    public void queryWeather(final View btnQueryWeather)
    {
        if(isCreateInput((ImageView) btnQueryWeather))
        {
            // to Send
            String city = closeInput((ImageView) btnQueryWeather, R.drawable.weather, false, true);
            if(!city.isEmpty())
            {
                // send
                newChatMessage(city + "天气");
            }
            btnMore.callOnClick();
        }
        else
        {
            createInput((ImageView) btnQueryWeather, "What's your city?", false, R.drawable.search, new View.OnFocusChangeListener()
            {
                @Override
                public void onFocusChange(
                        View v,
                        boolean hasFocus
                )
                {
                    System.out.println("onFocusChange");
                    if(!hasFocus && !btnQueryWeather.isPressed())
                    {
                        System.out.println("call");
                        closeInput((ImageView) btnQueryWeather, R.drawable.weather, false, true);
                    }
                }
            });
        }
    }

    public void sing(View view)
    {
        newChatMessage("唱首歌");
        btnMore.callOnClick();
    }

    public void laugh(View view)
    {
        newChatMessage("笑话");
        btnMore.callOnClick();
    }

    public void calendar(View view)
    {
        newChatMessage("今天几号");
        btnMore.callOnClick();
    }

    public void clock(View view)
    {
        newChatMessage("几点了");
        btnMore.callOnClick();
    }

    public void setting(View v)
    {
        LinearLayout.LayoutParams layoutParams;

        LinearLayout layout = new LinearLayout(v.getContext());
        layout.setOrientation(LinearLayout.VERTICAL);
        layout.setGravity(Gravity.CENTER_VERTICAL);
        layout.setPadding(10, 10, 10, 10);
        layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layout.setLayoutParams(layoutParams);

        LinearLayout tmpLayout;
        tmpLayout = new LinearLayout(v.getContext());
        layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(10, 10, 10, 10);
        layoutParams.gravity = Gravity.END;
        layout.addView(tmpLayout, layoutParams);

        ImageView exitBtn = new ImageView(v.getContext());
        exitBtn.setImageResource(R.drawable.exit);
        layoutParams = new LinearLayout.LayoutParams(50, 50);
        tmpLayout.addView(exitBtn, layoutParams);

        exitBtn.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                AlertDialog.Builder query = new AlertDialog.Builder(v.getContext());
                query.setTitle("确认退出账户？");
                query.setPositiveButton("Exit", new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(
                            DialogInterface dialog,
                            int which
                    )
                    {
                        SharedPreferences.Editor edit = accountInfo.edit();
                        edit.remove("logged");
                        edit.apply();
                        startActivity(new Intent(MainActivity.this, LoginActivity.class));
                        finish();
                    }
                });
                query.setNegativeButton("Cancel", null);
                query.show();
            }
        });

        FrameLayout frame;
        GradientDrawable drawable;
        TextView textView;
        FrameLayout.LayoutParams frameLayoutParams;

        tmpLayout = new LinearLayout(v.getContext());
        layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(10, 20, 10, 20);
        layout.addView(tmpLayout, layoutParams);

        textView = new TextView(v.getContext());
        textView.setText("机器人头像：");
        textView.setTextSize(TypedValue.COMPLEX_UNIT_SP, 18);
        layoutParams = new LinearLayout.LayoutParams(230, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        layoutParams.setMargins(10, 10, 10, 10);
        tmpLayout.addView(textView, layoutParams);


        frame = new FrameLayout(v.getContext());
        frame.setForegroundGravity(Gravity.END);
        frameLayoutParams = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        frameLayoutParams.setMargins(10, 10, 10, 10);
        tmpLayout.addView(frame, frameLayoutParams);

        robotHead = new ImageView(v.getContext());
        robotHead.setImageURI(Uri.fromFile(new File(settingInfo.getString("system-header", ""))));
        drawable = new GradientDrawable();
        drawable.setCornerRadius(15);
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
        {
            drawable.setStroke(1, getResources().getColor(R.color.transparent_darker_gray, getTheme()));
        }
        else
        {
            drawable.setStroke(1, getResources().getColor(R.color.transparent_darker_gray));
        }
        robotHead.setBackground(drawable);
        robotHead.setPadding(10, 10, 10, 10);
        layoutParams = new LinearLayout.LayoutParams(270, 270);
        layoutParams.gravity = Gravity.CENTER;
        frame.addView(robotHead, layoutParams);

        ImageView editRobotHeader = new ImageView(v.getContext());
        editRobotHeader.setImageResource(R.drawable.edit);
        drawable = new GradientDrawable();
        drawable.setCornerRadius(15);
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
        {
            drawable.setColor(getResources().getColor(R.color.light_gray, getTheme()));
            drawable.setStroke(1, getResources().getColor(R.color.darker_gray, getTheme()));
        }
        else
        {
            drawable.setColor(getResources().getColor(R.color.light_gray));
            drawable.setStroke(1, getResources().getColor(R.color.darker_gray));
        }
        editRobotHeader.setBackground(drawable);
        frameLayoutParams = new FrameLayout.LayoutParams(70, 70);
        frameLayoutParams.setMargins(10, 10, 10, 10);
        frameLayoutParams.gravity = Gravity.END;
        frame.addView(editRobotHeader, frameLayoutParams);


        tmpLayout = new LinearLayout(v.getContext());
        layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(10, 20, 10, 20);
        layout.addView(tmpLayout, layoutParams);

        textView = new TextView(v.getContext());
        textView.setText("我的头像：");
        textView.setTextSize(TypedValue.COMPLEX_UNIT_SP, 18);
        layoutParams = new LinearLayout.LayoutParams(230, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        layoutParams.setMargins(10, 10, 10, 10);
        tmpLayout.addView(textView, layoutParams);

        frame = new FrameLayout(v.getContext());
        frame.setForegroundGravity(Gravity.END);
        frameLayoutParams = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        frameLayoutParams.setMargins(10, 10, 10, 10);
        tmpLayout.addView(frame, frameLayoutParams);

        myHead = new ImageView(v.getContext());
        myHead.setImageURI(Uri.fromFile(new File(settingInfo.getString("my-header", ""))));
        drawable = new GradientDrawable();
        drawable.setCornerRadius(15);
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
        {
            drawable.setStroke(1, getResources().getColor(R.color.transparent_darker_gray, getTheme()));
        }
        else
        {
            drawable.setStroke(1, getResources().getColor(R.color.transparent_darker_gray));
        }
        myHead.setBackground(drawable);
        myHead.setPadding(10, 10, 10, 10);
        layoutParams = new LinearLayout.LayoutParams(270, 270);
        layoutParams.gravity = Gravity.CENTER;
        frame.addView(myHead, layoutParams);

        ImageView editMyHeader = new ImageView(v.getContext());
        editMyHeader.setImageResource(R.drawable.edit);
        drawable = new GradientDrawable();
        drawable.setCornerRadius(15);
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
        {
            drawable.setColor(getResources().getColor(R.color.light_gray, getTheme()));
            drawable.setStroke(1, getResources().getColor(R.color.darker_gray, getTheme()));
        }
        else
        {
            drawable.setColor(getResources().getColor(R.color.light_gray));
            drawable.setStroke(1, getResources().getColor(R.color.darker_gray));
        }
        editMyHeader.setBackground(drawable);
        frameLayoutParams = new FrameLayout.LayoutParams(70, 70);
        frameLayoutParams.setMargins(10, 10, 10, 10);
        frameLayoutParams.gravity = Gravity.END;
        frame.addView(editMyHeader, frameLayoutParams);

        editMyHeader.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Intent intent = new Intent(Intent.ACTION_PICK);
                intent.setType("image/*");//相片类型
                startActivityForResult(intent, CHANGE_MY_HEADER);
            }
        });

        editRobotHeader.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Intent intent = new Intent(Intent.ACTION_PICK);
                intent.setType("image/*");//相片类型
                startActivityForResult(intent, CHANGE_SYSTEM_HEADER);
            }
        });

        AlertDialog.Builder alert = new AlertDialog.Builder(v.getContext());
        alert.setView(layout);
        alert.show();
    }

    @Override
    protected void onActivityResult(
            int requestCode,
            int resultCode,
            @Nullable Intent data
    )
    {
        if(resultCode == RESULT_OK)
        {
            File stream;
            switch(requestCode)
            {
                case CHANGE_MY_HEADER:
                    stream = getFileStreamPath(username + ".my.head");
                    break;
                case CHANGE_SYSTEM_HEADER:
                    stream = getFileStreamPath(username + ".system.head");
                    break;
                default:
                    return;
            }
            assert data != null;
            Uri uri = data.getData();
            ContentResolver cr = this.getContentResolver();
            try
            {
                assert uri != null;
                Bitmap bitmap = BitmapFactory.decodeStream(cr.openInputStream(uri));
                /* 将Bitmap设定到ImageView */
                FileOutputStream fileOutputStream = new FileOutputStream(stream);
                bitmap.compress(Bitmap.CompressFormat.PNG, 100, fileOutputStream);
                bitmap.recycle();
                SharedPreferences.Editor edit = settingInfo.edit();
                switch(requestCode)
                {
                    case CHANGE_MY_HEADER:
                        myHead.setImageURI(uri);
                        edit.putString("my-header", stream.getAbsolutePath());
                        break;
                    case CHANGE_SYSTEM_HEADER:
                        robotHead.setImageURI(uri);
                        edit.putString("system-header", stream.getAbsolutePath());
                        break;
                    default:
                        return;
                }
                edit.apply();
                recordAdapter.updateHeader();
                recordAdapter.notifyDataSetChanged();
            } catch(FileNotFoundException e)
            {
                e.printStackTrace();
            }
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    public void plan(View view)
    {
        btnMore.callOnClick();
        handler.sendEmptyMessage(0x02);
    }

    @SuppressLint("SetTextI18n")
    public void calculate(View view)
    {
        String[] symbol = new String[] {
                "7", "8", "9", "÷", "4", "5", "6", "×", "1", "2", "3", "－", "0", ".", "＋", "="
        };

        final String[] textA = {""};
        final String[] textB = {""};
        final int[] opt = {0};
        final boolean[] isPoint = {false};

        GridLayout grid = new GridLayout(view.getContext());
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(650, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.gravity = Gravity.CENTER_HORIZONTAL;
        grid.setPadding(10, 10, 10, 10);
        grid.setLayoutParams(layoutParams);

        grid.setRowCount(6);
        grid.setColumnCount(4);

        GridLayout.Spec rowSpec;
        GridLayout.Spec colSpec;
        GridLayout.LayoutParams params;

        final TextView textResult = new TextView(view.getContext());
        textResult.setText("0");
        textResult.getPaint().setFakeBoldText(true);
        textResult.setTextColor(getResources().getColor(R.color.darker_gray));
        textResult.setTextSize(TypedValue.COMPLEX_UNIT_SP, 50);
        textResult.setGravity(Gravity.END);
        textResult.setPadding(10, 0, 10, 0);

        rowSpec = GridLayout.spec(0);
        colSpec = GridLayout.spec(0, 4);
        params = new GridLayout.LayoutParams(rowSpec, colSpec);
        // 指定组件占满父组件
        params.setGravity(Gravity.FILL);
        grid.addView(textResult, params);

        Button btnClear = new Button(view.getContext());
        btnClear.setText("CLEAR");
        btnClear.setTextSize(TypedValue.COMPLEX_UNIT_SP, 30);
        btnClear.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                textB[0] = textA[0] = "";
                opt[0] = 0;
                isPoint[0] = false;
                textResult.setText("0");
            }
        });

        rowSpec = GridLayout.spec(1);
        colSpec = GridLayout.spec(0, 4);
        params = new GridLayout.LayoutParams(rowSpec, colSpec);
        // 指定组件占满父组件
        params.setGravity(Gravity.FILL);
        grid.addView(btnClear, params);


        View.OnClickListener optListener = new View.OnClickListener()
        {
            @SuppressLint("SetTextI18n")
            @Override
            public void onClick(View v)
            {
                Button btn = (Button) v;
                if(textResult.getText().toString().equals("0") || opt[0] == 5 || textA[0].length() == 0)
                {
                    opt[0] = 0;
                    textResult.setText("");
                    textA[0] = "";
                }
                if(btn.getText().toString().equals("－") && textResult.getText().toString().equals("－"))
                {
                    return;
                }
                else if(!btn.getText().toString().equals(".") || !isPoint[0])
                {
                    textResult.setText("" + textResult.getText().toString() + btn.getText().toString());
                }
                switch(btn.getText().toString())
                {
                    case "＋":
                        makeOpt(1);
                        break;
                    case "－":
                        makeOpt(2);
                        break;
                    case "×":
                        makeOpt(3);
                        break;
                    case "÷":
                        makeOpt(4);
                        break;
                    case "=":
                        makeOpt(5);
                        break;
                    case ".":
                        if(!isPoint[0])
                        {
                            if(opt[0] == 0)
                            {
                                if(!textA[0].contains("."))
                                {
                                    textA[0] += ".";
                                }
                            }
                            else
                            {
                                if(!textB[0].contains("."))
                                {
                                    textB[0] += ".";
                                }
                            }
                        }
                        isPoint[0] = true;
                        break;
                    default:
                        if(opt[0] == 0)
                        {
                            // textA
                            textA[0] += btn.getText().toString();
                        }
                        else
                        {
                            // textB
                            textB[0] += btn.getText().toString();
                        }
                }
            }

            private void makeOpt(int optType)
            {
                if(opt[0] != 0 || optType == 5)
                {
                    if(textA[0].indexOf(0) == '.')
                    {
                        textA[0] = "0" + textA[0];
                    }
                    if(textB[0].indexOf(0) == '.')
                    {
                        textB[0] = "0" + textB[0];
                    }

                    double a = 0;
                    double b = 0;
                    if(textA[0].length() > 0)
                    {
                        a = Double.parseDouble(textA[0]);
                    }
                    else
                    {
                        textA[0] = "0";
                    }
                    if(textB[0].length() > 0)
                    {
                        b = Double.parseDouble(textB[0]);
                    }
                    switch(opt[0])
                    {
                        case 1: // +
                            textResult.setText(String.valueOf(a + b));
                            break;
                        case 2: // -
                            textResult.setText(String.valueOf(a - b));
                            break;
                        case 3: // *
                            textResult.setText(String.valueOf(a * b));
                            break;
                        case 4: // /
                            if(b != 0)
                            {
                                textResult.setText(String.valueOf(a / b));
                            }
                            else
                            {
                                textResult.setText("0");
                            }
                            break;
                        default:
                            textResult.setText(textA[0]);
                    }
                    textResult.setText(textResult.getText().toString().replace("-", "－"));
                    textA[0] = textResult.getText().toString();
                    textB[0] = "";
                }
                else if(textA[0].length() == 0)
                {
                    textA[0] = "-";
                    return;
                }
                opt[0] = optType;
                isPoint[0] = false;
            }
        };

        for(int i = 0; i < symbol.length; i++)
        {
            Button btn = new Button(grid.getContext());
            btn.setText(symbol[i]);
            btn.setTextSize(TypedValue.COMPLEX_UNIT_SP, 35);
            btn.setPadding(0, 25, 0, 25);
            // 指定行
            rowSpec = GridLayout.spec(2 + (i / 4));
            // 指定列
            colSpec = GridLayout.spec(i % 4, 1);
            params = new GridLayout.LayoutParams(rowSpec, colSpec);
            // 指定组件占满父组件
            params.width = 150;
            //            params.setGravity(Gravity.FILL_VERTICAL);
            grid.addView(btn, params);

            btn.setOnClickListener(optListener);
        }

        AlertDialog.Builder builder = new AlertDialog.Builder(view.getContext());
        builder.setView(grid);
        builder.show();
    }

    @SuppressLint("HandlerLeak")
    public class HandleMe
            extends Handler
    {
        @Override
        public void handleMessage(@NonNull Message msg)
        {
            if(msg.what == 0x01)
            {
                recordAdapter.notifyItemChanged(msg.arg1);
            }
            else if(msg.what == 0x02)
            {
                final Bundle data = msg.getData();

                LinearLayout.LayoutParams layoutParams;

                final Calendar now = Calendar.getInstance(Locale.CHINA);
                final JSONObject timeInfo = new JSONObject();

                LinearLayout root = new LinearLayout(viewMore.getContext());
                root.setOrientation(LinearLayout.VERTICAL);
                root.setPadding(30, 30, 30, 30);
                root.setGravity(Gravity.CENTER_VERTICAL);

                layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                root.setLayoutParams(layoutParams);

                LinearLayout dateLayout = new LinearLayout(viewMore.getContext());
                dateLayout.setOrientation(LinearLayout.HORIZONTAL);
                dateLayout.setGravity(Gravity.CENTER_VERTICAL);
                layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                layoutParams.setMargins(0, 10, 0, 10);
                root.addView(dateLayout, layoutParams);

                final ImageView dateIcon = new ImageView(viewMore.getContext());
                dateIcon.setImageResource(R.drawable.calendar);
                layoutParams = new LinearLayout.LayoutParams(80, 80);
                layoutParams.setMarginStart(10);
                layoutParams.setMarginEnd(10);
                dateLayout.addView(dateIcon, layoutParams);

                final TextView dateText = new TextView(viewMore.getContext());
                if(data.isEmpty())
                {
                    dateText.setText("未设置");
                }
                else
                {
                    dateText.setText(judgeReadableDate(data.getInt("year"), data.getInt("month"), data.getInt("day")));
                }

                dateText.setTextSize(TypedValue.COMPLEX_UNIT_SP, 18);
                layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                layoutParams.setMarginStart(10);
                layoutParams.setMarginEnd(3);
                dateLayout.addView(dateText, layoutParams);

                ImageView dateSet = new ImageView(viewMore.getContext());
                dateSet.setImageResource(R.drawable.edit);
                layoutParams = new LinearLayout.LayoutParams(50, 50);
                dateLayout.addView(dateSet, layoutParams);

                final ImageView dateNoSetWarning = new ImageView(viewMore.getContext());
                dateNoSetWarning.setImageResource(R.drawable.warning);
                layoutParams = new LinearLayout.LayoutParams(45, 45);
                layoutParams.gravity = Gravity.CENTER_VERTICAL | Gravity.END;
                layoutParams.setMarginStart(100);
                dateNoSetWarning.setVisibility(dateText.getText().toString().equals("未设置") ? View.VISIBLE : View.GONE);
                dateLayout.addView(dateNoSetWarning, layoutParams);

                int setYear = now.get(Calendar.YEAR), setMonth = now.get(Calendar.MONTH), setDay = now.get(Calendar.DAY_OF_MONTH), setHour = now.get(
                        Calendar.HOUR_OF_DAY), setMinute = now.get(Calendar.MINUTE);
                if(!data.isEmpty())
                {
                    setYear = data.getInt("year");
                    setMonth = data.getInt("month");
                    setDay = data.getInt("day");
                    setHour = data.getInt("hour");
                    setMinute = data.getInt("minute");
                    try
                    {
                        timeInfo.put("year", setYear);
                        timeInfo.put("month", setMonth);
                        timeInfo.put("day", setDay);
                        timeInfo.put("hour", setHour);
                        timeInfo.put("minute", setMinute);
                    } catch(JSONException e)
                    {
                        e.printStackTrace();
                    }
                }

                final int finalSetYear = setYear;
                final int finalSetMonth = setMonth;
                final int finalSetDay = setDay;

                dateSet.setOnClickListener(new View.OnClickListener()
                {
                    @Override
                    public void onClick(View v)
                    {
                        new DatePickerDialog(MainActivity.this, new DatePickerDialog.OnDateSetListener()
                        {
                            @Override
                            public void onDateSet(
                                    DatePicker view,
                                    int year,
                                    int month,
                                    int dayOfMonth
                            )
                            {
                                try
                                {
                                    timeInfo.put("year", year);
                                    timeInfo.put("month", month);
                                    timeInfo.put("day", dayOfMonth);
                                } catch(JSONException e)
                                {
                                    e.printStackTrace();
                                }
                                dateNoSetWarning.setVisibility(View.GONE);
                                dateText.setText(String.format(Locale.CHINA, "%04d / %02d / %02d", year, month + 1, dayOfMonth));
                            }
                        }, finalSetYear, finalSetMonth, finalSetDay).show();
                    }
                });

                LinearLayout timeLayout = new LinearLayout(viewMore.getContext());
                timeLayout.setOrientation(LinearLayout.HORIZONTAL);
                timeLayout.setGravity(Gravity.CENTER_VERTICAL);
                layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                layoutParams.setMargins(0, 10, 0, 10);
                root.addView(timeLayout, layoutParams);

                final ImageView timeIcon = new ImageView(viewMore.getContext());
                timeIcon.setImageResource(R.drawable.clock);
                timeIcon.setPadding(10, 10, 10, 10);
                layoutParams = new LinearLayout.LayoutParams(80, 80);
                layoutParams.setMarginStart(10);
                layoutParams.setMarginEnd(10);
                timeLayout.addView(timeIcon, layoutParams);

                final TextView timeText = new TextView(viewMore.getContext());
                if(data.isEmpty())
                {
                    timeText.setText("未设置");
                }
                else
                {
                    timeText.setText(String.format(Locale.CHINA, "%02d:%02d", setHour, setMinute));
                }
                timeText.setTextSize(TypedValue.COMPLEX_UNIT_SP, 18);
                layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                layoutParams.setMarginStart(10);
                layoutParams.setMarginEnd(3);
                timeLayout.addView(timeText, layoutParams);

                ImageView timeSet = new ImageView(viewMore.getContext());
                timeSet.setImageResource(R.drawable.edit);
                layoutParams = new LinearLayout.LayoutParams(50, 50);
                timeLayout.addView(timeSet, layoutParams);

                final ImageView timeNoSetWarning = new ImageView(viewMore.getContext());
                timeNoSetWarning.setImageResource(R.drawable.warning);
                timeNoSetWarning.setVisibility(timeText.getText().toString().equals("未设置") ? View.VISIBLE : View.GONE);
                layoutParams = new LinearLayout.LayoutParams(45, 45);
                layoutParams.gravity = Gravity.CENTER_VERTICAL | Gravity.END;
                layoutParams.setMarginStart(100);
                timeLayout.addView(timeNoSetWarning, layoutParams);

                final int finalSetHour = setHour;
                final int finalSetMinute = setMinute;
                timeSet.setOnClickListener(new View.OnClickListener()
                {
                    @Override
                    public void onClick(View v)
                    {
                        new TimePickerDialog(MainActivity.this, new TimePickerDialog.OnTimeSetListener()
                        {
                            @Override
                            public void onTimeSet(
                                    TimePicker view,
                                    int hourOfDay,
                                    int minute
                            )
                            {
                                try
                                {
                                    timeInfo.put("hour", hourOfDay);
                                    timeInfo.put("minute", minute);
                                } catch(JSONException e)
                                {
                                    e.printStackTrace();
                                }
                                timeText.setText(String.format(Locale.CHINA, "%02d : %02d", hourOfDay, minute));
                                timeNoSetWarning.setVisibility(View.GONE);
                            }
                        }, finalSetHour, finalSetMinute, true).show();
                    }
                });

                LinearLayout nameLayout = new LinearLayout(viewMore.getContext());
                nameLayout.setOrientation(LinearLayout.HORIZONTAL);
                nameLayout.setGravity(Gravity.TOP);
                layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                layoutParams.setMargins(0, 10, 0, 10);
                root.addView(nameLayout, layoutParams);

                ImageView nameIcon = new ImageView(viewMore.getContext());
                nameIcon.setImageResource(R.drawable.name);
                nameIcon.setPadding(0, 10, 0, 5);
                layoutParams = new LinearLayout.LayoutParams(80, 80);
                layoutParams.setMargins(10, 5, 10, 0);
                nameLayout.addView(nameIcon, layoutParams);

                final EditText nameEdit = new EditText(viewMore.getContext());
                nameEdit.setHint("Plan Name");
                nameEdit.setEms(6);
                if(!data.isEmpty())
                {
                    nameEdit.setText(data.getString("name"));
                }
                layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                layoutParams.setMarginStart(5);
                layoutParams.setMarginEnd(5);
                nameLayout.addView(nameEdit, layoutParams);

                final ImageView nameNoSetWarning = new ImageView(viewMore.getContext());
                nameNoSetWarning.setImageResource(R.drawable.warning);
                nameNoSetWarning.setVisibility(nameEdit.getText().length() == 0 ? View.VISIBLE : View.GONE);
                layoutParams = new LinearLayout.LayoutParams(45, 45);
                layoutParams.gravity = Gravity.CENTER_VERTICAL | Gravity.END;
                layoutParams.setMarginStart(15);
                nameLayout.addView(nameNoSetWarning, layoutParams);

                nameEdit.addTextChangedListener(new TextWatcher()
                {
                    @Override
                    public void beforeTextChanged(
                            CharSequence s,
                            int start,
                            int count,
                            int after
                    )
                    {

                    }

                    @Override
                    public void onTextChanged(
                            CharSequence s,
                            int start,
                            int before,
                            int count
                    )
                    {
                        nameNoSetWarning.setVisibility(s.length() > 0 ? View.GONE : View.VISIBLE);
                    }

                    @Override
                    public void afterTextChanged(Editable s)
                    {

                    }
                });

                LinearLayout commentLayout = new LinearLayout(viewMore.getContext());
                commentLayout.setOrientation(LinearLayout.HORIZONTAL);
                commentLayout.setGravity(Gravity.TOP);
                layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                layoutParams.setMargins(0, 10, 0, 10);
                root.addView(commentLayout, layoutParams);

                ImageView remark = new ImageView(viewMore.getContext());
                remark.setImageResource(R.drawable.remark);
                remark.setPadding(10, 0, 10, 0);
                layoutParams = new LinearLayout.LayoutParams(80, 80);
                layoutParams.setMargins(10, 10, 10, 0);
                commentLayout.addView(remark, layoutParams);

                final EditText commentEdit = new EditText(viewMore.getContext());
                commentEdit.setHint("Remark");
                commentEdit.setEms(6);
                if(!data.isEmpty())
                {
                    commentEdit.setText(data.getString("remark"));
                }
                layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                layoutParams.setMarginStart(5);
                layoutParams.setMarginEnd(5);
                commentLayout.addView(commentEdit, layoutParams);

                final AlertDialog.Builder builder = new AlertDialog.Builder(viewMore.getContext());

                builder.setIcon(R.drawable.plan);

                if(msg.getData().isEmpty())
                {
                    builder.setTitle("New Plan");
                }
                else
                {
                    builder.setTitle("Edit Plan");
                }

                builder.setView(root);

                if(msg.getData().isEmpty())
                {
                    builder.setPositiveButton("Add", new DialogInterface.OnClickListener()
                    {
                        @Override
                        public void onClick(
                                DialogInterface dialog,
                                int which
                        )
                        {
                            boolean isFinish = false;

                            while(!isFinish)
                            {
                                if(timeInfo.length() != 5)
                                {
                                    break;
                                }
                                String planName = nameEdit.getText().toString();
                                if(planName.isEmpty())
                                {
                                    break;
                                }
                                JSONObject planInfo = new JSONObject();
                                try
                                {
                                    planInfo.put("name", planName);
                                    planInfo.put("comment", commentEdit.getText().toString());
                                } catch(JSONException e)
                                {
                                    e.printStackTrace();
                                }
//                                saveMessageToDatabase("me", MessageType.S.TEXT, "添加计划", "");
                                saveMessageToDatabase("me", MessageType.S.PLAN, planInfo.toString(), timeInfo.toString());
                                isFinish = true;
                            }

                            if(!isFinish)
                            {
                                Toast.makeText(getApplicationContext(), "信息不完整", Toast.LENGTH_SHORT).show();
                            }
                        }
                    });
                }
                else
                {
                    builder.setPositiveButton("Modify", new DialogInterface.OnClickListener()
                    {
                        @Override
                        public void onClick(
                                DialogInterface dialog,
                                int which
                        )
                        {
                            boolean isFinish = false;

                            while(!isFinish)
                            {
                                if(timeInfo.length() != 5)
                                {
                                    break;
                                }
                                String planName = nameEdit.getText().toString();
                                if(planName.isEmpty())
                                {
                                    break;
                                }
                                JSONObject planInfo = new JSONObject();
                                try
                                {
                                    planInfo.put("name", planName);
                                    planInfo.put("comment", commentEdit.getText().toString());
                                } catch(JSONException e)
                                {
                                    e.printStackTrace();
                                }

                                ContentValues values = new ContentValues();
                                values.put(RecordContract.Record.CONTENT, planInfo.toString());
                                values.put(RecordContract.Record.RESOURCE, timeInfo.toString());
                                //                                System.out.println(data.getString("provide"));
                                getContentResolver().update(Uri.parse(data.getString("provide")), values, null, null);
                                for(int i = recordList.size() - 1; i >= 0; i--)
                                {
                                    if(recordList.get(i).provide.equals(data.getString("provide")))
                                    {
                                        recordList.get(i).content = planInfo.toString();
                                        recordList.get(i).resource = timeInfo.toString();
                                        recordAdapter.notifyItemChanged(i);
                                        break;
                                    }
                                }
                                isFinish = true;
                            }

                            if(!isFinish)
                            {
                                Toast.makeText(getApplicationContext(), "信息不完整", Toast.LENGTH_SHORT).show();
                            }
                        }
                    });
                }

                builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(
                            DialogInterface dialog,
                            int which
                    )
                    {

                    }
                });

                builder.show();

            }
            else if(msg.what == 0x03)
            {
                Bundle data = msg.getData();
                String provide = data.getString("provide");
//                ContentProviderOperation.Builder newDelete = ContentProviderOperation.newDelete(RecordContract.Record.CONTENT_URI);
//                newDelete.withSelection(RecordContract.Record._ID + "=?", new String[] {String.valueOf(ContentUris.parseId(Uri.parse(provide)))});
//                newDelete.build();
                getContentResolver().delete(Uri.parse(provide), null, null);
                for(int i = recordList.size() - 1; i >= 0; i--)
                {
                    if(recordList.get(i).provide.equals(provide))
                    {
                        recordList.remove(i);
                        recordAdapter.notifyItemRemoved(i);
                        break;
                    }
                }
            }
            super.handleMessage(msg);
        }
    }

    private String judgeReadableDate(
            int year,
            int month,
            int day
    )
    {
        Calendar timeInstance = Calendar.getInstance(Locale.CHINA);
        int nowYear = timeInstance.get(Calendar.YEAR);
        int nowMonth = timeInstance.get(Calendar.MONTH);
        int nowDay = timeInstance.get(Calendar.DAY_OF_MONTH);

        String date;
        switch(year - nowYear)
        {
            case 0:
                switch(month - nowMonth)
                {
                    case 0:
                        switch(day - nowDay)
                        {
                            case 0:
                                date = "今天";
                                break;
                            case 1:
                                date = "明天";
                                break;
                            case 2:
                                date = "后天";
                                break;
                            case 3:
                                date = "大后天";
                                break;
                            case -1:
                                date = "昨天";
                                break;
                            case -2:
                                date = "前天";
                                break;
                            case -3:
                                date = "大前天";
                                break;
                            default:
                                date = String.format(Locale.CHINA, "本月%02d日", day);
                        }
                        break;
                    case 1:
                        date = String.format(Locale.CHINA, "下月%02d日", day);
                        break;
                    case -1:
                        date = String.format(Locale.CHINA, "上月%02d日", day);
                        break;
                    default:
                        date = String.format(Locale.CHINA, "%02d月%02d日", month + 1, day);
                        break;
                }
                break;
            case 1:
                date = String.format(Locale.CHINA, "明年%02d月%02d日", month + 1, day);
                break;
            case -1:
                date = String.format(Locale.CHINA, "去年%02d月%02d日", month + 1, day);
                break;
            default:
                date = String.format(Locale.CHINA, "%d年%02d月%02d日", year, month + 1, day);
        }

        return date;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if(!isLogin())
        {
            return;
        }

        initData();
        initView();
        bindData();
        bindEvent();
        // accountInfo.edit().remove("logged").apply();
    }

    private void bindEvent()
    {
    }

    private void bindData()
    {
        recordAdapter = new ChatAdapter(recordList, getApplicationContext());
        recordAdapter.updateHeader();
        recyclerView.setAdapter(recordAdapter);
        //        recyclerView.scrollToPosition(list.size() - 1);
        new Thread()
        {
            @Override
            public void run()
            {

                super.run();

                while(true)
                {
                    for(Integer i : timeList)
                    {
                        if(!recordList.get(i).args.containsKey("style") || ((int) recordList.get(i).args.get("style")) != 1)
                        {
                            continue;
                        }
                        recordList.get(i).content = getCurrentTime();
                        Message message = new Message();
                        message.what = 0x01;
                        message.arg1 = i;
                        handler.sendMessage(message);
                    }
                    try
                    {
                        Thread.sleep(1000);
                    } catch(InterruptedException e)
                    {
                        e.printStackTrace();
                        break;
                    }
                }
            }
        }.start();
    }

    private void initData()
    {
        RecordContentProvider.freshDB(getApplicationContext());

        username = accountInfo.getString("username", "");
        settingInfo = getSharedPreferences(username + ".setting", MODE_PRIVATE);

        handler = new HandleMe();

        recordList = new ArrayList<>(50);
        timeList = new ArrayList<>(50);

        ContentResolver resolver = getContentResolver();
        @SuppressLint("Recycle") Cursor cursor = resolver.query(RecordContract.Record.CONTENT_URI, null, null, null, null);

        assert cursor != null;
        int idIndex = cursor.getColumnIndex(RecordContract.Record._ID);
        int ownerIndex = cursor.getColumnIndex(RecordContract.Record.OWNER);
        int typeIndex = cursor.getColumnIndex(RecordContract.Record.TYPE);
        int contentIndex = cursor.getColumnIndex(RecordContract.Record.CONTENT);
        int resourceIndex = cursor.getColumnIndex(RecordContract.Record.RESOURCE);
        while(cursor.moveToNext())
        {
            RecordInfo recordInfo = new RecordInfo();
            recordInfo.provide = "content://" + RecordContract.AUTHORITY + "/" + RecordContract.Record.PATH + "/" + cursor.getInt(idIndex);
            recordInfo.owner = cursor.getString(ownerIndex);
            recordInfo.type = cursor.getString(typeIndex);
            recordInfo.content = cursor.getString(contentIndex);
            recordInfo.resource = cursor.getString(resourceIndex);
            recordList.add(recordInfo);
            if(recordInfo.type.equals(MessageType.S.TIME))
            {
                timeList.add(recordList.size() - 1);
            }
        }

        File file;

        if(!settingInfo.contains("system-header"))
        {
            file = getFileStreamPath(username + ".system.head");
            Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.robot);
            try
            {
                FileOutputStream outputStream = new FileOutputStream(file);
                bitmap.compress(Bitmap.CompressFormat.PNG, 100, outputStream);
                outputStream.close();

                SharedPreferences.Editor edit = settingInfo.edit();
                edit.putString("system-header", file.getAbsolutePath());
                edit.apply();

            } catch(IOException e)
            {
                e.printStackTrace();
            }
        }

        if(!settingInfo.contains("my-header"))
        {
            file = getFileStreamPath(username + ".my.head");
            Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.header);
            try
            {
                FileOutputStream outputStream = new FileOutputStream(file);
                bitmap.compress(Bitmap.CompressFormat.PNG, 100, outputStream);
                outputStream.close();

                SharedPreferences.Editor edit = settingInfo.edit();
                edit.putString("my-header", file.getAbsolutePath());
                edit.apply();

            } catch(IOException e)
            {
                e.printStackTrace();
            }
        }
    }

    static String getCurrentTime()
    {
        //        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.CHINA);
        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm", Locale.CHINA);
        //        format.setTimeZone(TimeZone.getTimeZone("GMT+08:00"));
        Date date = new Date();
        return format.format(date);
    }

    private void initView()
    {
        btnMore = findViewById(R.id.record_btnAdd);
        recyclerView = findViewById(R.id.record_recyclerView);
        recyclerView.setHasFixedSize(true);
        LinearLayoutManager llm = new LinearLayoutManager(this, LinearLayoutManager.VERTICAL, false);
        llm.setStackFromEnd(true);
        recyclerView.setLayoutManager(llm);
        viewMore = findViewById(R.id.record_viewMore);
        viewMore.setBackgroundColor(getResources().getColor(R.color.darker_gray));
        viewMore.getBackground().setAlpha(0);
        viewMoreFunctions = findViewById(R.id.record_moreFunctions);
        viewMoreFunctions.setVisibility(View.INVISIBLE);
        viewMoreFunctionsFold = findViewById(R.id.record_moreFunctionsFold);
    }

    boolean isLogin()
    {
        accountInfo = getSharedPreferences("account", Context.MODE_PRIVATE);
        if(accountInfo.contains("logged") && accountInfo.getBoolean("logged", false))
        {
            return true;
        }

        Toast.makeText(getApplicationContext(), "您还没登录，正跳转至登录界面", Toast.LENGTH_SHORT).show();

        Intent intent = new Intent(MainActivity.this, LoginActivity.class);
        startActivity(intent);
        finish();

        return false;
    }

    public void more(View view)
    {
        ValueAnimator animatorOfBackground;
        boolean isOpen = btnMore.getText().toString().equals(getResources().getString(R.string.more));

        viewMore.setClickable(isOpen);
        viewMoreFunctions.setVisibility(isOpen ? View.VISIBLE : View.INVISIBLE);

        if(isOpen)
        {
            animatorOfBackground = ValueAnimator.ofInt(0, 203);
            btnMore.setText(R.string.simple);
        }
        else
        {
            animatorOfBackground = ValueAnimator.ofInt(203, 0);
            btnMore.setText(R.string.more);
        }

        KeyboardUtil.closeKeyboard(this);

        animatorOfBackground.setDuration(800);
        animatorOfBackground.addUpdateListener(new ValueAnimator.AnimatorUpdateListener()
        {
            @Override
            public void onAnimationUpdate(ValueAnimator valueAnimator)
            {
                viewMore.getBackground().setAlpha((int) valueAnimator.getAnimatedValue());
            }
        });
        animatorOfBackground.start();

    }

    boolean isCreateInput(ImageView btn)
    {
        LinearLayout parent = (LinearLayout) btn.getParent();
        return parent.getChildCount() >= 2;
    }

    String closeInput(
            ImageView btn,
            int btnImage,
            boolean saveInput,
            boolean noPadding
    )
    {
        LinearLayout parent = (LinearLayout) btn.getParent();
        if(parent.getChildCount() == 1)
        {
            return "";
        }
        KeyboardUtil.closeKeyboard(this);
        String input = ((EditText) parent.getChildAt(0)).getText().toString();
        if(saveInput)
        {
            lastInput = input;
        }
        else
        {
            lastInput = "";
        }
        parent.removeViewAt(0);

        btn.setImageResource(btnImage);
        if(noPadding)
        {
            btn.setPadding(0, 0, 0, 0);
        }
        return input;
    }

    void createInput(
            final ImageView btn,
            String hint,
            boolean useSaveInput,
            int sendIcon,
            View.OnFocusChangeListener focusChangeListener
    )
    {
        LinearLayout parent = (LinearLayout) btn.getParent();

        // new Message
        final EditText editText = new EditText(getApplicationContext());
        editText.setHint(hint);
        editText.setHintTextColor(Color.parseColor("#FFFFFF"));

        editText.setTextSize(18);
        editText.setTextColor(Color.parseColor("#000000"));

        if(useSaveInput)
        {
            editText.setText(lastInput);
        }
        else
        {
            editText.setText("");
        }

        GradientDrawable drawable = new GradientDrawable();
        drawable.setCornerRadius(25);
        drawable.setColor(Color.parseColor("#DCDCDC")); // 设置区域颜色
        editText.setBackground(drawable);

        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(120, 0, 20, 0);
        layoutParams.weight = 1.0f;
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        editText.setLayoutParams(layoutParams);
        editText.setPadding(20, 10, 20, 10);

        parent.addView(editText, 0);
        btn.setImageResource(sendIcon);
        btn.setPadding(0, 20, 0, 10);

        editText.setOnKeyListener(new View.OnKeyListener()
        {
            @Override
            public boolean onKey(
                    View view,
                    int i,
                    KeyEvent keyEvent
            )
            {
                if(i == KeyEvent.KEYCODE_ENTER)
                {
                    editText.setOnFocusChangeListener(null);
                    btn.callOnClick();
                    return true;
                }
                return false;
            }
        });

        editText.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                viewMoreFunctionsFold.setVisibility(View.GONE);
                KeyboardUtil.showSoftInput(MainActivity.this, editText);
            }
        });

        editText.setOnFocusChangeListener(focusChangeListener);

        viewMoreFunctionsFold.setVisibility(View.GONE);
        KeyboardUtil.showSoftInput(MainActivity.this, editText);
    }

    public void chat(final View btnChat)
    {
        if(isCreateInput((ImageView) btnChat))
        {
            // to Send
            String message = closeInput((ImageView) btnChat, R.drawable.chat, false, false);
            if(!message.isEmpty())
            {
                // send
                newChatMessage(message);
            }
            btnMore.callOnClick();
        }
        else
        {
            createInput((ImageView) btnChat, "Message...", true, R.drawable.send, new View.OnFocusChangeListener()
            {
                @Override
                public void onFocusChange(
                        View v,
                        boolean hasFocus
                )
                {
                    System.out.println("onFocusChange");
                    if(!hasFocus && !btnChat.isPressed())
                    {
                        System.out.println("call");
                        closeInput((ImageView) btnChat, R.drawable.chat, true, false);
                    }
                }
            });
        }
    }


    @SuppressLint("StaticFieldLeak")
    void newChatMessage(String message)
    {
        saveMessageToDatabase("me", MessageType.S.TEXT, message, "");

        String msgWithNoSpace = message.replace(" ", "");
        if(msgWithNoSpace.equals("时间") || msgWithNoSpace.equals("现在时间") || msgWithNoSpace.equals("当前时间") || msgWithNoSpace.contains("几点了"))
        {
            saveMessageToDatabase("system", MessageType.S.TIME, getCurrentTime(), "");
        }
        else if(message.contains("今天几号"))
        {
            saveMessageToDatabase("system", MessageType.S.CALENDAR, String.valueOf(System.currentTimeMillis()), "");
        }
        else
        {
            // Internet
            new AsyncTask<String, Void, String>()
            {
                @Override
                protected String doInBackground(String... strings)
                {
                    String params = "type=10" + "&id=2361257570" + "&msg=" + Uri.encode(strings[0]);
                    return httpPost(params);
                }

                @Override
                protected void onPostExecute(String s)
                {
                    try
                    {
                        JSONObject json = new JSONObject(s);
                        if(json.getInt("Status") != 200)
                        {
                            throw new Exception("接口响应出错");
                        }
                        String resource = "";
                        String type = "";
                        switch(json.getInt("SubType"))
                        {
                            case 1:
                                type = MessageType.S.TEXT;
                                break;
                            case 2:
                                type = MessageType.S.MUSIC;
                                resource = json.getString("Data");
                                break;
                            case 3:
                                type = MessageType.S.IMAGE;
                                resource = json.getString("Data");
                                break;
                        }
                        String message = json.getString("Msg");
                        if(!resource.isEmpty())
                        {
                            new AsyncTask<RecordInfo, Void, RecordInfo>()
                            {
                                @Override
                                protected RecordInfo doInBackground(RecordInfo... args)
                                {
                                    args[0].resource = downloadFile(args[0].resource);
                                    return args[0];
                                }

                                @Override
                                protected void onPostExecute(RecordInfo record)
                                {
                                    System.out.println("onPostExecute: " + record.resource);
                                    saveMessageToDatabase(record);
                                }
                            }.execute(new RecordInfo("", "system", type, message, resource));
                        }
                        else
                        {
                            saveMessageToDatabase("system", type, message, resource);
                        }
                    } catch(Exception e)
                    {
                        e.printStackTrace();
                    }
                }
            }.execute(message);
        }
    }

    private void saveMessageToDatabase(RecordInfo record)
    {
        saveMessageToDatabase(record.owner, record.type, record.content, record.resource);
    }

    String httpPost(
            String postData
    )
    {
        StringBuilder response = new StringBuilder();
        HttpURLConnection connection = null;
        try
        {
            URL url = new URL("https://chat.1sls.cn/v2/");
            connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("POST");
            connection.setRequestProperty("Charset", "UTF-8");
            connection.setDoInput(true);
            connection.setDoOutput(true);
            connection.setUseCaches(false);
            OutputStream os = connection.getOutputStream();
            os.write(postData.getBytes());
            os.flush();
            os.close();
            connection.connect();
            int status = connection.getResponseCode();
            if(status == 200)
            {
                InputStream is = connection.getInputStream();
                byte[] bytes = new byte[1024];
                int readLen;
                do
                {
                    readLen = is.read(bytes);
                    if(readLen > 0)
                    {
                        response.append(new String(bytes, 0, readLen));
                    }
                }
                while(readLen != -1);
                is.close();
                System.out.println(response.toString());
            }
        } catch(IOException e)
        {
            e.printStackTrace();
        } finally
        {
            if(connection != null)
            {
                connection.disconnect();
            }
        }
        return response.toString();
    }

    private void saveMessageToDatabase(
            String owner,
            String type,
            String content,
            String resource
    )
    {
        ArrayList<ContentProviderOperation> operations = new ArrayList<>();
        ContentProviderOperation.Builder insertOpt = ContentProviderOperation.newInsert(RecordContract.Record.CONTENT_URI);
        insertOpt.withValue(RecordContract.Record.OWNER, owner);
        insertOpt.withValue(RecordContract.Record.TYPE, type);
        insertOpt.withValue(RecordContract.Record.CONTENT, content);
        insertOpt.withValue(RecordContract.Record.RESOURCE, resource);
        operations.add(insertOpt.build());

        ContentResolver resolver = getContentResolver();
        StringBuilder contentProvide = new StringBuilder();
        try
        {
            ContentProviderResult[] results = resolver.applyBatch(RecordContract.AUTHORITY, operations);

            for(ContentProviderResult result : results)
                contentProvide.append(result.uri.toString());
            System.out.println(contentProvide + "\n");
        } catch(RemoteException | OperationApplicationException e)
        {
            e.printStackTrace();
        }

        recordList.add(new RecordInfo(contentProvide.toString(), owner, type, content, resource));
        if(type.equals(MessageType.S.TIME))
        {
            timeList.add(recordList.size() - 1);
        }
        recordAdapter.notifyDataSetChanged();
        recyclerView.scrollToPosition(recordAdapter.mData.size() - 1);
    }

    /**
     * 读取任何文件
     * 返回-1 ，代表下载失败。返回0，代表成功。返回1代表文件已经存在
     */
    public String downloadFile(String urlStr)
    {
        if(!Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED))
        {
            System.out.println("Extra Storage is not exist");
            return "";
        }

        //        String dir = Objects.requireNonNull(getExternalFilesDir(null)).getPath() + "/downloads/";
        //        File f = new File(dir);
        //        if(!f.exists() && !f.mkdir())
        //        {
        //            System.out.println("Create Folder Failed");
        //            return "";
        //        }
        //        String name = urlStr.subSequence(urlStr.lastIndexOf("/") + 1, urlStr.length()).toString();
        //        dir += name;
        //        f = new File(dir);

        String name = urlStr.subSequence(urlStr.lastIndexOf("/") + 1, urlStr.length()).toString();
        File f = getFileStreamPath(name);

        FileOutputStream fos = null;
        try
        {
            fos = new FileOutputStream(f);
            HttpURLConnection connection = null;
            try
            {
                URL url = new URL(urlStr);
                connection = (HttpURLConnection) url.openConnection();
                connection.setRequestMethod("GET");
                connection.setConnectTimeout(8000);
                connection.setReadTimeout(8000);
                connection.connect();
                int status = connection.getResponseCode();
                if(status == 200)
                {
                    InputStream is = connection.getInputStream();
                    byte[] bytes = new byte[1024];
                    int readLen;
                    do
                    {
                        readLen = is.read(bytes);
                        if(readLen > 0)
                        {
                            fos.write(bytes, 0, readLen);
                        }
                    }
                    while(readLen != -1);
                    is.close();
                    System.out.println("Read HTTP data Successful");
                }
            } catch(IOException e)
            {
                e.printStackTrace();
            } finally
            {
                if(connection != null)
                {
                    connection.disconnect();
                }
            }
        } catch(IOException e)
        {
            e.printStackTrace();
            System.out.println("Write Content to Extra Storage Failed");
        } finally
        {
            if(fos != null)
            {
                try
                {
                    fos.close();
                } catch(IOException e)
                {
                    e.printStackTrace();
                }
                System.out.println("Write Content to Extra Storage Successfully");
            }
        }
        System.out.println("downloadFile " + f.getAbsolutePath());
        return f.getAbsolutePath();
    }
}
