package com.example.simple_chat.recycler_view_adapter.view_holder;

import android.graphics.Bitmap;
import android.graphics.drawable.GradientDrawable;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.simple_chat.R;

public class ImageViewHolder
        extends RecyclerView.ViewHolder
{
    public TextView text;
    public ImageView image;
    public LinearLayout root;
    public LinearLayout messageArea;

    public ImageViewHolder(@NonNull View itemView)
    {
        super(itemView);

        root = (LinearLayout) itemView.findViewById(R.id.item_linearLayout);

        messageArea = new LinearLayout(itemView.getContext());

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
        //        drawable.setStroke(1, Color.parseColor("#cccccc")); // 设置边颜色
        //        drawable.setColor(root.getResources().getColor(colors[position % colors.length])); // 设置区域颜色
        messageArea.setBackground(drawable);

        root.addView(messageArea);

        text = new TextView(itemView.getContext());
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);

        text.setTextSize(TypedValue.COMPLEX_UNIT_SP, 18);
        text.setTextColor(itemView.getResources().getColor(android.R.color.white));
        messageArea.addView(text, layoutParams);


        image = new ImageView(itemView.getContext());
        image.setAdjustViewBounds(true);
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(0, 10, 0, 10);

        messageArea.addView(image, layoutParams);

    }
}
