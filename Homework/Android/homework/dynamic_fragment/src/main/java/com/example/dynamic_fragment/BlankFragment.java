package com.example.dynamic_fragment;

import android.os.Bundle;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;

import java.util.Objects;


/**
 * A simple {@link Fragment} subclass.
 * Use the {@link BlankFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class BlankFragment
        extends Fragment
{
    // TODO: Rename parameter arguments, choose names that match
    // the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
    private static final String ARG_PARAM1 = "param1";
    private static final String ARG_PARAM2 = "param2";

    // TODO: Rename and change types of parameters
    private String mParam1;
    private String mParam2;
    private LinearLayout leftView;
    private Button btnClose;
    private View fragmentView;

    public BlankFragment()
    {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment BlankFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static BlankFragment newInstance(String param1, String param2)
    {
        BlankFragment fragment = new BlankFragment();
        Bundle args = new Bundle();
        args.putString(ARG_PARAM1, param1);
        args.putString(ARG_PARAM2, param2);
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        if(getArguments() != null)
        {
            mParam1 = getArguments().getString(ARG_PARAM1);
            mParam2 = getArguments().getString(ARG_PARAM2);
        }
    }

    @Override
    public View onCreateView(
            LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState
    )
    {
        // Inflate the layout for this fragment
        fragmentView = inflater.inflate(R.layout.fragment_blank, container, false);

        initView();
        bindEvent();

        return fragmentView;
    }

    private void bindEvent()
    {
        btnClose.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                FragmentManager fragmentManager = getFragmentManager();
                assert fragmentManager != null;
                FragmentTransaction transaction = fragmentManager.beginTransaction();
                transaction.remove(BlankFragment.this);
                transaction.commit();
                backToMaxScreen();
            }
        });
    }

    private void initView()
    {
        leftView = (LinearLayout) Objects.requireNonNull(getActivity()).findViewById(R.id.leftVIew);
        btnClose = (Button) fragmentView.findViewById(R.id.btnClose);
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
        backToMaxScreen();
    }

    private void backToMaxScreen()
    {
        leftView.setLayoutParams(new LinearLayout.LayoutParams(Objects.requireNonNull(getActivity()).getWindowManager().getDefaultDisplay().getWidth(), getActivity().getWindowManager().getDefaultDisplay().getHeight()));
    }
}
