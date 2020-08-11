package com.example.simple_chat.recycler_view_adapter.view_holder;

import android.graphics.drawable.GradientDrawable;
import android.os.Bundle;
import android.os.Message;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.simple_chat.MainActivity;
import com.example.simple_chat.R;

public class PlanViewHolder
        extends RecyclerView.ViewHolder
{
    public TextView time;
    public TextView name;
    public LinearLayout messageArea;
    public LinearLayout root;
    public ImageView comment;
    public ImageView edit;
    public TextView date;
    public Value value;

    public class Value
    {
        public String provide;
        public String name;
        public String remark;
        public int year;
        public int month;
        public int day;
        public int hour;
        public int minute;
    }

    public PlanViewHolder(@NonNull View v)
    {
        super(v);

        value = new Value();

        root = v.findViewById(R.id.item_linearLayout);

        messageArea = new LinearLayout(v.getContext());

        LinearLayout.LayoutParams layoutParams;
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(10, 10, 10, 10);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        layoutParams.weight = 1.0f;
        messageArea.setLayoutParams(layoutParams);
        messageArea.setOrientation(LinearLayout.VERTICAL);
        messageArea.setPadding(20, 20, 20, 20);

        GradientDrawable drawable;
        drawable = new GradientDrawable();
        drawable.setCornerRadius(25);
        messageArea.setBackground(drawable);

        root.addView(messageArea);

        LinearLayout headerArea = new LinearLayout(v.getContext());
        headerArea.setOrientation(LinearLayout.HORIZONTAL);
        headerArea.setGravity(Gravity.CENTER_VERTICAL);
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(10, 0, 0, 0);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        messageArea.addView(headerArea, layoutParams);

        name = new TextView(v.getContext());
        name.setTextColor(v.getResources().getColor(android.R.color.white));
        name.setTextSize(TypedValue.COMPLEX_UNIT_SP, 18);
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        headerArea.addView(name, layoutParams);

        comment = new ImageView(v.getContext());
        comment.setImageResource(R.drawable.info);
        layoutParams = new LinearLayout.LayoutParams(35, 35);
        layoutParams.setMargins(10, 0, 5, 0);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        headerArea.addView(comment, layoutParams);

        comment.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                LinearLayout popRoot = new LinearLayout(v.getContext());
                popRoot.setOrientation(LinearLayout.HORIZONTAL);
                popRoot.setGravity(Gravity.CENTER_VERTICAL);
                popRoot.setPadding(15, 15, 15, 15);
                LinearLayout.LayoutParams lp;
                lp = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                popRoot.setLayoutParams(lp);

                ImageView icon = new ImageView(v.getContext());
                icon.setImageResource(R.drawable.remark);
                lp = new LinearLayout.LayoutParams(50, 50);
                lp.setMargins(5, 0, 5, 0);
                popRoot.addView(icon, lp);

                TextView content = new TextView(v.getContext());
                content.setTextSize(TypedValue.COMPLEX_UNIT_SP, 18);
                content.setTextColor(v.getContext().getResources().getColor(android.R.color.darker_gray));
                content.setText(value.remark.isEmpty() ? "未设置" : value.remark);
                lp = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                lp.setMargins(5, 0, 5, 0);
                popRoot.addView(content, lp);

                PopupWindow popWindow = new PopupWindow(popRoot, ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT, true);
                GradientDrawable gradientDrawable = new GradientDrawable();
                gradientDrawable.setCornerRadius(25);
                gradientDrawable.setStroke(1, v.getContext().getResources().getColor(R.color.darker_gray));
                gradientDrawable.setColor(v.getContext().getResources().getColor(R.color.transparent_gray));
                popWindow.setBackgroundDrawable(gradientDrawable);
                popWindow.showAsDropDown(v, 50, -115);
            }
        });

        LinearLayout editArea = new LinearLayout(v.getContext());
        editArea.setGravity(Gravity.END);
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        headerArea.addView(editArea, layoutParams);

        edit = new ImageView(v.getContext());
        edit.setImageResource(R.drawable.edit);
        drawable = new GradientDrawable();
        drawable.setCornerRadius(25);
        drawable.setColor(v.getResources().getColor(android.R.color.white));
        drawable.setStroke(2, v.getResources().getColor(R.color.transparent_darker_gray));
        edit.setBackground(drawable);
        layoutParams = new LinearLayout.LayoutParams(50, 50);
        layoutParams.gravity = Gravity.END;
        editArea.addView(edit, layoutParams);

        edit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                Message message = new Message();
                message.what = 0x02;
                Bundle data = message.getData();
                data.putInt("year", value.year);
                data.putInt("month", value.month);
                data.putInt("day", value.day);
                data.putInt("hour", value.hour);
                data.putInt("minute", value.minute);
                data.putString("name", value.name);
                data.putString("remark", value.remark);
                data.putString("provide", value.provide);
                message.setData(data);
                MainActivity.handler.handleMessage(message);
            }
        });

        TextView divideLine = new TextView(v.getContext());
        divideLine.setBackgroundResource(R.color.transparent_darker_gray);
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, 3);
        layoutParams.setMargins(0, 8, 0, 8);
        messageArea.addView(divideLine, layoutParams);

        LinearLayout timeArea = new LinearLayout(v.getContext());
        timeArea.setOrientation(LinearLayout.HORIZONTAL);
        timeArea.setGravity(Gravity.CENTER_VERTICAL);
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(10, 0, 10, 0);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        messageArea.addView(timeArea, layoutParams);

        ImageView clockImage = new ImageView(v.getContext());
        clockImage.setImageResource(R.drawable.clock);
        layoutParams = new LinearLayout.LayoutParams(35, 35);
        layoutParams.setMargins(5, 0, 5, 0);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        timeArea.addView(clockImage, layoutParams);

        date = new TextView(v.getContext());
        date.setTextColor(v.getResources().getColor(android.R.color.white));
        date.setTextSize(TypedValue.COMPLEX_UNIT_SP, 15);
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(10, 0, 10, 0);
        timeArea.addView(date, layoutParams);

        time = new TextView(v.getContext());
        time.setTextSize(TypedValue.COMPLEX_UNIT_SP, 15);
        time.setTextColor(v.getResources().getColor(android.R.color.white));
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(0, 0, 10, 0);
        timeArea.addView(time, layoutParams);

    }
}
