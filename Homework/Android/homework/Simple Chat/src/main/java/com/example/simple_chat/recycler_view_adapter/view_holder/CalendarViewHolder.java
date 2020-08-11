package com.example.simple_chat.recycler_view_adapter.view_holder;

import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.GradientDrawable;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CalendarView;
import android.widget.DatePicker;
import android.widget.LinearLayout;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.example.simple_chat.R;

import java.util.Calendar;
import java.util.Locale;

import static android.view.View.GONE;

public class CalendarViewHolder
        extends RecyclerView.ViewHolder
{
    public DatePicker datePicker;
    public LinearLayout root;
    public LinearLayout messageArea;

    public CalendarViewHolder(@NonNull View view)
    {
        super(view);

        root = (LinearLayout) view.findViewById(R.id.item_linearLayout);

        messageArea = new LinearLayout(view.getContext());

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

        datePicker = new DatePicker(view.getContext());
        Calendar calendarInstance = Calendar.getInstance(Locale.CHINA);
        datePicker.init(calendarInstance.get(Calendar.YEAR), calendarInstance.get(Calendar.MONTH), calendarInstance.get(Calendar.DAY_OF_MONTH), null);
        layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT);
        datePicker.setLayoutParams(layoutParams);

        ViewGroup mContainer = (ViewGroup) datePicker.getChildAt(0);
        View mFooter = mContainer.getChildAt(1);
        mFooter.setVisibility(GONE);

        View mHeader = mContainer.getChildAt(0);
        drawable = new GradientDrawable();
        drawable.setCornerRadius(25);
        mHeader.setBackground(drawable);

        messageArea.addView(datePicker);
    }
}
