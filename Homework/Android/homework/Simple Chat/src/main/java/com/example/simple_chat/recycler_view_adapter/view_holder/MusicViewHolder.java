package com.example.simple_chat.recycler_view_adapter.view_holder;


import android.graphics.Color;
import android.graphics.drawable.GradientDrawable;
import android.os.Build;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.simple_chat.R;

public class MusicViewHolder
        extends RecyclerView.ViewHolder
{

    public LinearLayout playControlArea;
    public TextView playState;
    public SeekBar seekBar;
    public ImageView btnPlay;
    public TextView title;
    public LinearLayout root;
    public LinearLayout messageArea;

    public MusicViewHolder(@NonNull View view)
    {
        super(view);

        root = (LinearLayout) view.findViewById(R.id.item_linearLayout);

        // 消息区域布局
        messageArea = new LinearLayout(view.getContext());

        LinearLayout.LayoutParams layoutParams;

        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(10, 10, 10, 10);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        layoutParams.weight = 1.0f;
        messageArea.setLayoutParams(layoutParams);

        messageArea.setOrientation(LinearLayout.VERTICAL);
        messageArea.setPadding(20, 10, 20, 10);

        GradientDrawable drawable = new GradientDrawable();
        drawable.setCornerRadius(25);
        messageArea.setBackground(drawable);

        root.addView(messageArea);

        // music消息布局
        LinearLayout linearLayout;
        linearLayout = new LinearLayout((view.getContext()));
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        layoutParams.weight = 8.0f;
        linearLayout.setLayoutParams(layoutParams);
        linearLayout.setOrientation(LinearLayout.HORIZONTAL);

        messageArea.addView(linearLayout);

        title = new TextView(view.getContext());
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.weight = 1.0f;
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        title.setLayoutParams(layoutParams);
        title.setTextSize(TypedValue.COMPLEX_UNIT_SP, 23);
        title.setTextColor(view.getResources().getColor(android.R.color.white));
        title.setGravity(Gravity.CENTER_VERTICAL);

        linearLayout.addView(title);

        btnPlay = new ImageView(view.getContext());
        btnPlay.setImageDrawable(view.getResources().getDrawable(R.drawable.play));
        layoutParams = new LinearLayout.LayoutParams(80, 80);
        layoutParams.setMargins(0, 10, 0, 10);
        btnPlay.setLayoutParams(layoutParams);
        btnPlay.setBackground(view.getResources().getDrawable(R.drawable.bg_shape_light_gray));

        linearLayout.addView(btnPlay);

        playControlArea = new LinearLayout(view.getContext());
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        layoutParams.weight = 8.0f;
        playControlArea.setLayoutParams(layoutParams);
        playControlArea.setOrientation(LinearLayout.HORIZONTAL);
        playControlArea.setGravity(Gravity.CENTER_VERTICAL);

        messageArea.addView(playControlArea);

        seekBar = new SeekBar(view.getContext());
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.weight = 1.0f;
        seekBar.setLayoutParams(layoutParams);
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q)
        {
            seekBar.setMinHeight(5);
        }

        playControlArea.addView(seekBar);

        playState = new TextView(view.getContext());
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        playState.setLayoutParams(layoutParams);
        playState.setText("0:00 / 1:00");
        playState.setTextColor(view.getResources().getColor(android.R.color.white));

        playControlArea.addView(playState);

        playControlArea.setVisibility(View.GONE);
    }
}
