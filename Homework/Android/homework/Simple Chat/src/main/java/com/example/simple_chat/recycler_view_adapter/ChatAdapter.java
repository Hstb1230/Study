package com.example.simple_chat.recycler_view_adapter;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.content.ComponentName;
import android.content.ContentProviderOperation;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.GradientDrawable;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.SeekBar;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.simple_chat.ImageViewActivity;
import com.example.simple_chat.MainActivity;
import com.example.simple_chat.MyService;
import com.example.simple_chat.R;
import com.example.simple_chat.recycler_view_adapter.view_holder.CalendarViewHolder;
import com.example.simple_chat.recycler_view_adapter.view_holder.ImageViewHolder;
import com.example.simple_chat.recycler_view_adapter.view_holder.MusicViewHolder;
import com.example.simple_chat.recycler_view_adapter.view_holder.PlanViewHolder;
import com.example.simple_chat.recycler_view_adapter.view_holder.TextViewHolder;
import com.example.simple_chat.recycler_view_adapter.view_holder.TimeViewHolder;
import com.example.simple_chat.field.MessageType;
import com.example.simple_chat.field.RecordInfo;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.io.IOException;
import java.util.Calendar;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;

import static android.content.Context.MODE_PRIVATE;


public class ChatAdapter
        extends RecyclerView.Adapter<RecyclerView.ViewHolder>
{

    private final SharedPreferences settingInfo;
    public List<RecordInfo> mData;
    private final Intent intent;
    MyService.MusicInfoBinder binder;
    private Bitmap headerOfSystem;
    private Bitmap headerOfMy;
    private HashMap<String, Bitmap> mapOfImage;

    public ChatAdapter(
            List<RecordInfo> data,
            Context context
    )
    {
        SharedPreferences account = context.getSharedPreferences("account", MODE_PRIVATE);
        settingInfo = context.getSharedPreferences(account.getString("username", "") + ".setting", MODE_PRIVATE);


        this.mData = data;
        intent = new Intent(context, MyService.class);
        context.bindService(intent, new ServiceConnection()
        {
            @Override
            public void onServiceConnected(
                    ComponentName name,
                    IBinder service
            )
            {
                binder = (MyService.MusicInfoBinder) service;
            }

            @Override
            public void onServiceDisconnected(ComponentName name)
            {

            }
        }, Context.BIND_AUTO_CREATE);

        mapOfImage = new HashMap<>();
    }

    @NonNull
    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(
            @NonNull ViewGroup parent,
            int viewType
    )
    {
        View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_null, parent, false);
        switch(viewType)
        {
            case MessageType.I.IMAGE:
                return new ImageViewHolder(v);
            case MessageType.I.TIME:
                return new TimeViewHolder(v);
            case MessageType.I.MUSIC:
                return new MusicViewHolder(v);
            case MessageType.I.PLAN:
                return new PlanViewHolder(v);
            case MessageType.I.CALENDAR:
                return new CalendarViewHolder(v);
            default:
                return new TextViewHolder(v);
        }
    }

    @Override
    public int getItemViewType(int position)
    {
        return MessageType.getTypeInt(mData.get(position).type);
    }

    @Override
    public void onBindViewHolder(
            @NonNull final RecyclerView.ViewHolder holder,
            final int position
    )
    {
        final RecordInfo recordInfo = mData.get(position);
        LinearLayout root = null;
        int[] colors = new int[] {
                R.color.colorAccent, R.color.colorPrimary, R.color.colorPrimaryDark, R.color.darker_gray, R.color.light_gray
        };
        if(holder instanceof TextViewHolder)
        {
            TextViewHolder viewHolder = (TextViewHolder) holder;

            root = viewHolder.root;

            GradientDrawable drawable = (GradientDrawable) viewHolder.text.getBackground();
            drawable.setColor(root.getResources().getColor(colors[position % colors.length])); // 设置区域颜色
            viewHolder.text.setBackground(drawable);

            viewHolder.text.setText(recordInfo.content);
        }
        else if(holder instanceof ImageViewHolder)
        {
            final ImageViewHolder viewHolder = (ImageViewHolder) holder;

            root = viewHolder.root;

            GradientDrawable drawable = (GradientDrawable) viewHolder.messageArea.getBackground();
            drawable.setColor(root.getResources().getColor(colors[position % colors.length])); // 设置区域颜色
            viewHolder.messageArea.setBackground(drawable);

            viewHolder.text.setText(recordInfo.content);

            if(!recordInfo.resource.isEmpty() && mapOfImage.containsKey(recordInfo.resource))
            {
                viewHolder.image.setImageBitmap(mapOfImage.get(recordInfo.resource));
            }
            else if(!recordInfo.resource.isEmpty())
            {
                if(new File(recordInfo.resource).exists())
                {
                    Bitmap bitmap = BitmapFactory.decodeFile(recordInfo.resource);
                    mapOfImage.put(recordInfo.resource, bitmap);
                    viewHolder.image.setImageBitmap(bitmap);
                }
                else
                {
                    System.out.println("File no exist: " + recordInfo.resource);
                }
            }

            viewHolder.image.setOnClickListener(new View.OnClickListener()
            {
                @Override
                public void onClick(View v)
                {
                    Intent intentToImage = new Intent(v.getContext(), ImageViewActivity.class);
                    intentToImage.putExtra("img", recordInfo.resource);
                    v.getContext().startActivity(intentToImage);
                }
            });

        }
        else if(holder instanceof TimeViewHolder)
        {
            final TimeViewHolder viewHolder = (TimeViewHolder) holder;

            root = viewHolder.root;

            GradientDrawable drawable = (GradientDrawable) viewHolder.messageArea.getBackground();
            drawable.setColor(root.getResources().getColor(colors[position % colors.length])); // 设置区域颜色
            viewHolder.messageArea.setBackground(drawable);

            //            viewHolder.text.setText(recordInfo.content);
            if(!recordInfo.args.containsKey("style"))
            {
                recordInfo.args.put("style", 0);
            }
            if(((int) recordInfo.args.get("style")) == 0)
            {
                // 显示完整时钟
                viewHolder.clock.setVisibility(View.VISIBLE);
                viewHolder.time.setVisibility(View.GONE);
            }
            else
            {
                // 显示只有小时和分钟的时钟
                viewHolder.clock.setVisibility(View.GONE);
                viewHolder.time.setVisibility(View.VISIBLE);

            }

            Calendar instance = Calendar.getInstance();
            if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
            {
                viewHolder.time.setHour(instance.get(Calendar.HOUR_OF_DAY));
                viewHolder.time.setMinute(instance.get(Calendar.MINUTE));
            }
            else
            {
                viewHolder.time.setCurrentHour(instance.get(Calendar.HOUR_OF_DAY));
                viewHolder.time.setCurrentMinute(instance.get(Calendar.MINUTE));
            }

            viewHolder.btnChange.setOnClickListener(new View.OnClickListener()
            {
                @Override
                public void onClick(View v)
                {
                    if(((int) recordInfo.args.get("style")) == 0)
                    {
                        viewHolder.clock.setVisibility(View.GONE);
                        viewHolder.time.setVisibility(View.VISIBLE);
                    }
                    else
                    {
                        viewHolder.clock.setVisibility(View.VISIBLE);
                        viewHolder.time.setVisibility(View.GONE);
                    }
                    recordInfo.args.put("style", Math.abs(((int) recordInfo.args.get("style")) - 1));
                }
            });

        }
        else if(holder instanceof MusicViewHolder)
        {
            final MusicViewHolder viewHolder = (MusicViewHolder) holder;

            root = viewHolder.root;

            GradientDrawable drawable = (GradientDrawable) viewHolder.messageArea.getBackground();
            drawable.setColor(root.getResources().getColor(colors[position % colors.length])); // 设置区域颜色
            viewHolder.messageArea.setBackground(drawable);

            viewHolder.title.setText(recordInfo.content);

            // 获取音乐长度信息
            if(!recordInfo.args.containsKey("now"))
            {
                MediaPlayer player = new MediaPlayer();
                try
                {
                    player.setDataSource(recordInfo.resource);  //recordingFilePath（）为音频文件的路径
                    player.prepare();
                } catch(IOException e)
                {
                    e.printStackTrace();
                }
                int duration = player.getDuration() / 1000;//获取音频的时间
                Log.d("ACETEST", "### duration: " + duration);
                player.release();//记得释放资源
                recordInfo.args.put("now", 0);
                recordInfo.args.put("length", duration);
            }

            int now = ((int) recordInfo.args.get("now"));
            int length = ((int) recordInfo.args.get("length"));
            viewHolder.seekBar.setProgress(now);
            viewHolder.seekBar.setMax(length);

            viewHolder.playState.setText(String.format(Locale.CHINA, "%d:%02d / %d:%02d", (now / 60), (now % 60), (length / 60), (length % 60)));
            viewHolder.playControlArea.setVisibility((((int) recordInfo.args.get("now")) > 0 ? View.VISIBLE : View.GONE));

            @SuppressLint("HandlerLeak") final Handler handler = new Handler()
            {
                @Override
                public void handleMessage(@NonNull Message msg)
                {
                    super.handleMessage(msg);
                    if(msg.what == 0x01)
                    {
                        int now = msg.arg1;
                        int length = msg.arg2;

                        if(!viewHolder.seekBar.isPressed())
                        {
                            viewHolder.seekBar.setProgress(now);
                        }
                        viewHolder.playState.setText(String.format(Locale.CHINA, "%d:%02d / %d:%02d", (now / 60), (now % 60), (length / 60), (length % 60)));
                    }
                    else if(msg.what == 0x02)
                    {
                        recordInfo.args.put("isPlaying", false);
                        viewHolder.btnPlay.setImageDrawable(viewHolder.root.getResources().getDrawable(R.drawable.play));
                    }
                }
            };

            viewHolder.btnPlay.setOnClickListener(new View.OnClickListener()
            {
                @Override
                public void onClick(View v)
                {
                    boolean isPlaying = recordInfo.args.containsKey("isPlaying") && (boolean) recordInfo.args.get("isPlaying");
                    if(isPlaying)
                    {
                        binder.pause();
                    }
                    else
                    {
                        viewHolder.playControlArea.setVisibility(View.VISIBLE);
                        viewHolder.btnPlay.setImageDrawable(v.getResources().getDrawable(R.drawable.pause));
                        if(!binder.getNowPlaying().equals(recordInfo.resource))
                        {
                            binder.setPlaying(recordInfo.resource);
                        }
                        binder.setTime((int) recordInfo.args.get("now"));
                        binder.playing();
                        recordInfo.args.put("isPlaying", true);
                        new Thread()
                        {
                            @Override
                            public void run()
                            {
                                super.run();
                                while(binder.getNowPlaying().equals(recordInfo.resource) && binder.isPlaying())
                                {
                                    int now = binder.getNowLocation();
                                    int length = ((int) recordInfo.args.get("length"));
                                    recordInfo.args.put("now", now);
                                    Message message = new Message();
                                    message.what = 0x01;
                                    message.arg1 = now;
                                    message.arg2 = length;
                                    handler.sendMessage(message);
                                    //                                ChatAdapter.super.notifyItemChanged(position);
                                    try
                                    {
                                        Thread.sleep(100);
                                    } catch(InterruptedException e)
                                    {
                                        e.printStackTrace();
                                        break;
                                    }
                                }
                                Message message = new Message();
                                message.what = 0x02;
                                handler.sendMessage(message);
                            }
                        }.start();
                    }
                }
            });

            viewHolder.btnPlay.setOnLongClickListener(new View.OnLongClickListener()
            {
                @Override
                public boolean onLongClick(View v)
                {
                    if(binder.getNowPlaying().equals(recordInfo.resource))
                    {
                        return false;
                    }
                    if(viewHolder.playControlArea.getVisibility() == View.VISIBLE)
                    {
                        viewHolder.playControlArea.setVisibility(View.GONE);
                    }
                    else
                    {
                        viewHolder.playControlArea.setVisibility(View.VISIBLE);
                    }
                    return true;
                }
            });

            viewHolder.seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener()
            {
                @Override
                public void onProgressChanged(
                        SeekBar seekBar,
                        int progress,
                        boolean fromUser
                )
                {

                }

                @Override
                public void onStartTrackingTouch(SeekBar seekBar)
                {

                }

                @Override
                public void onStopTrackingTouch(SeekBar seekBar)
                {
                    recordInfo.args.put("now", seekBar.getProgress());
                    Message message = new Message();
                    message.what = 0x01;
                    message.arg1 = seekBar.getProgress();
                    message.arg2 = seekBar.getMax();
                    handler.sendMessage(message);
                    if(binder.getNowPlaying().equals(recordInfo.resource))
                    {
                        binder.setTime(seekBar.getProgress());
                    }
                }
            });
        }
        else if(holder instanceof CalendarViewHolder)
        {
            CalendarViewHolder viewHolder = (CalendarViewHolder) holder;

            root = viewHolder.root;

            GradientDrawable drawable = (GradientDrawable) viewHolder.messageArea.getBackground();
            drawable.setColor(root.getResources().getColor(colors[position % colors.length])); // 设置区域颜色
            viewHolder.messageArea.setBackground(drawable);

        }
        else if(holder instanceof PlanViewHolder)
        {
            PlanViewHolder viewHolder = (PlanViewHolder) holder;

            root = viewHolder.root;

            GradientDrawable drawable = (GradientDrawable) viewHolder.messageArea.getBackground();
            drawable.setColor(root.getResources().getColor(colors[position % colors.length])); // 设置区域颜色
            viewHolder.messageArea.setBackground(drawable);

            viewHolder.value.provide = recordInfo.provide;
            System.out.println(viewHolder.value.provide);

            try
            {
                JSONObject planInfo = new JSONObject(recordInfo.content);
                viewHolder.value.name = planInfo.getString("name");
                viewHolder.value.remark = planInfo.getString("comment");
                viewHolder.comment.setVisibility(viewHolder.value.remark.isEmpty() ? View.GONE : View.VISIBLE);
                viewHolder.name.setText(planInfo.getString("name"));

                Calendar timeInstance = Calendar.getInstance(Locale.CHINA);
                int nowYear = timeInstance.get(Calendar.YEAR);
                int nowMonth = timeInstance.get(Calendar.MONTH);
                int nowDay = timeInstance.get(Calendar.DAY_OF_MONTH);

                JSONObject timeInfo = new JSONObject(recordInfo.resource);
                viewHolder.value.year = timeInfo.getInt("year");
                viewHolder.value.month = timeInfo.getInt("month");
                viewHolder.value.day = timeInfo.getInt("day");
                viewHolder.value.hour = timeInfo.getInt("hour");
                viewHolder.value.minute = timeInfo.getInt("minute");
                int year = timeInfo.getInt("year");
                int month = timeInfo.getInt("month");
                int day = timeInfo.getInt("day");

                String date = "";
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
                viewHolder.date.setText(date);
                viewHolder.time.setText(String.format(Locale.CHINA, "%02d:%02d", timeInfo.getInt("hour"), timeInfo.getInt("minute")));

            } catch(JSONException e)
            {
                e.printStackTrace();
            }
        }

        // 设置头像
        if(root != null)
        {
            root.setOnLongClickListener(new View.OnLongClickListener() {
                @Override
                public boolean onLongClick(View v)
                {
                    AlertDialog.Builder alert = new AlertDialog.Builder(v.getContext());
                    alert.setTitle("删除这条记录？");
                    alert.setNegativeButton("Cancel", null);
                    alert.setPositiveButton("Delete", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(
                                DialogInterface dialog,
                                int which
                        )
                        {
                            Message message = new Message();
                            message.what = 0x03;
                            Bundle data = message.getData();
                            data.putString("provide", recordInfo.provide);
                            message.setData(data);
                            MainActivity.handler.handleMessage(message);
                        }
                    });
                    alert.show();
                    return true;
                }
            });
            if(recordInfo.owner.equals("system"))
            {
                setHeaderImage(root, "left");
            }
            else if(recordInfo.owner.equals("me"))
            {
                setHeaderImage(root, "right");
            }
        }
    }

    private void setHeaderImage(
            final LinearLayout root,
//            String imageResource,
            String position
    )
    {
        // 判断原有image
        int oldIndex;
        if(root.getChildCount() != 2)
        {
            oldIndex = -1;
        }
        else if(root.getChildAt(0) instanceof ImageView)
        {
            oldIndex = 0;
        }
        else if(root.getChildAt(1) instanceof ImageView)
        {
            oldIndex = 1;
        }
        else
        {
            oldIndex = -1;
        }

        if(oldIndex > -1)
        {
            root.removeViewAt(oldIndex);
        }

        ImageView imageView = new ImageView(root.getContext());
        LinearLayout.LayoutParams imageLayoutParams = new LinearLayout.LayoutParams(100, 100);
        imageLayoutParams.setMargins(10, 10, 10, 10);
        imageView.setLayoutParams(imageLayoutParams);
//        Bitmap bm = BitmapFactory.decodeFile(imageResource);
//        imageView.setImageBitmap(bm);
//        imageView.setImageURI(Uri.fromFile(new File(imageResource)));
        if(position.equals("left"))
            imageView.setImageBitmap(headerOfSystem);
        else
            imageView.setImageBitmap(headerOfMy);

        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);

        if(position.equals("left"))
        {
            layoutParams.setMargins(10, 10, 130, 10);
            root.addView(imageView, 0);
            ((LinearLayout) root.getChildAt(1)).setGravity(Gravity.START);
        }
        else if(position.equals("right"))
        {
            layoutParams.setMargins(130, 10, 10, 10);
            root.addView(imageView);
            ((LinearLayout) root.getChildAt(0)).setGravity(Gravity.END);
        }

        layoutParams.weight = 8.0f;

        root.setLayoutParams(layoutParams);
    }

    @Override
    public int getItemCount()
    {
        return mData.size();
    }

    public void updateHeader()
    {
        headerOfSystem = BitmapFactory.decodeFile(settingInfo.getString("system-header", ""));
        headerOfMy = BitmapFactory.decodeFile(settingInfo.getString("my-header", ""));
    }

}
