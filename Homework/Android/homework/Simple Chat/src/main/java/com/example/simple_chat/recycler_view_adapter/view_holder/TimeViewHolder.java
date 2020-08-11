package com.example.simple_chat.recycler_view_adapter.view_holder;

import android.graphics.Typeface;
import android.graphics.drawable.GradientDrawable;
import android.os.Build;
import android.text.format.Time;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextClock;
import android.widget.TextView;
import android.widget.TimePicker;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.simple_chat.R;

import java.util.Calendar;
import java.util.Date;
import java.util.Locale;

public class TimeViewHolder
        extends RecyclerView.ViewHolder
{

    public ImageView btnChange;
    public TimePicker time;
    public TextClock clock;
    public TextView text;
    public LinearLayout root;
    public LinearLayout messageArea;

    public TimeViewHolder(@NonNull View view)
    {
        super(view);

        root = (LinearLayout) view.findViewById(R.id.item_linearLayout);

        LinearLayout.LayoutParams layoutParams;

        LinearLayout tmpLinearLayout = new LinearLayout(view.getContext());
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(10, 10, 10, 10);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        layoutParams.weight = 1.0f;
        tmpLinearLayout.setLayoutParams(layoutParams);
        tmpLinearLayout.setOrientation(LinearLayout.HORIZONTAL);
        root.addView(tmpLinearLayout);

        messageArea = new LinearLayout(view.getContext());


        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        messageArea.setLayoutParams(layoutParams);

        messageArea.setOrientation(LinearLayout.HORIZONTAL);
        messageArea.setPadding(20, 10, 20, 10);

        GradientDrawable drawable = new GradientDrawable();
        drawable.setCornerRadius(25);
        //        drawable.setStroke(1, Color.parseColor("#cccccc")); // 设置边颜色
        //        drawable.setColor(root.getResources().getColor(colors[position % colors.length])); // 设置区域颜色
        messageArea.setBackground(drawable);

        tmpLinearLayout.addView(messageArea);

        btnChange = new ImageView(view.getContext());
        btnChange.setImageDrawable(view.getResources().getDrawable(R.drawable.change));
        layoutParams = new LinearLayout.LayoutParams(50, 50);
        layoutParams.setMargins(20, 0, 0, 0);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;

        tmpLinearLayout.addView(btnChange, layoutParams);

        text = new TextView(view.getContext());
        text.setTextSize(TypedValue.COMPLEX_UNIT_SP, 18);
        text.setTypeface(Typeface.DEFAULT_BOLD);
        text.setTextColor(view.getResources().getColor(android.R.color.white));

        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);

//        messageArea.addView(text, layoutParams);

        clock = new TextClock(view.getContext());
        clock.setTimeZone("GMT+08:00");
        clock.setFormat12Hour("aa hh:mm:ss");
        clock.setFormat24Hour("HH:mm:ss");
        clock.setTextSize(TypedValue.COMPLEX_UNIT_SP, 23);
        clock.setTypeface(Typeface.DEFAULT_BOLD);
        clock.setTextColor(view.getResources().getColor(android.R.color.white));
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);

        clock.setVisibility(View.GONE);

        messageArea.addView(clock, layoutParams);


        time = new TimePicker(view.getContext());
        time.setIs24HourView(true);

        Calendar instance = Calendar.getInstance();
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
        {
            time.setHour(instance.get(Calendar.HOUR_OF_DAY));
            time.setMinute(instance.get(Calendar.MINUTE));
        }
        else
        {
            time.setCurrentHour(instance.get(Calendar.HOUR_OF_DAY));
            time.setCurrentMinute(instance.get(Calendar.MINUTE));
        }

        ViewGroup mContainer = (ViewGroup) time.getChildAt(0);

        View mHeader = mContainer.getChildAt(0);
        drawable = new GradientDrawable();
        drawable.setCornerRadius(25);
        mHeader.setBackground(drawable);

        View mFooter = mContainer.getChildAt(1);
        mFooter.setVisibility(View.GONE);

        time.setVisibility(View.GONE);

        layoutParams = new LinearLayout.LayoutParams(
                (view.getContext().getResources().getDisplayMetrics().widthPixels <= 720 ? LinearLayout.LayoutParams.MATCH_PARENT : 500),
                LinearLayout.LayoutParams.WRAP_CONTENT
        );
        layoutParams.gravity = Gravity.CENTER;

        messageArea.addView(time, layoutParams);

    }
}
