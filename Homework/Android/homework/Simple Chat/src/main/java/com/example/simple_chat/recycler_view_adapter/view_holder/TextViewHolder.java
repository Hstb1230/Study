package com.example.simple_chat.recycler_view_adapter.view_holder;

import android.graphics.drawable.GradientDrawable;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.simple_chat.R;

public class TextViewHolder
        extends RecyclerView.ViewHolder
{
    public LinearLayout messageArea;
    public LinearLayout root;
    public TextView text;

    public TextViewHolder(@NonNull View view)
    {
        super(view);

        root = (LinearLayout) itemView.findViewById(R.id.item_linearLayout);

        messageArea = new LinearLayout(itemView.getContext());

        LinearLayout.LayoutParams layoutParams;
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.gravity = Gravity.CENTER_VERTICAL;
        layoutParams.weight = 1.0f;
        messageArea.setLayoutParams(layoutParams);
        messageArea.setOrientation(LinearLayout.VERTICAL);
        root.addView(messageArea);

        text = new TextView(view.getContext());
        text.setTextSize(TypedValue.COMPLEX_UNIT_SP, 18);
        text.setTextColor(view.getResources().getColor(android.R.color.white));

        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.setMargins(10, 10, 10, 10);
        text.setLayoutParams(layoutParams);
        text.setPadding(20, 10, 20, 10);


        GradientDrawable drawable = new GradientDrawable();
        drawable.setCornerRadius(25);
        text.setBackground(drawable);

        messageArea.addView(text);
    }
}
