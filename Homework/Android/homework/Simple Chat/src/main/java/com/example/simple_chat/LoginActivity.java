package com.example.simple_chat;

import androidx.appcompat.app.AppCompatActivity;

import android.animation.Animator;
import android.animation.AnimatorSet;
import android.animation.ObjectAnimator;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.text.Editable;
import android.text.InputType;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.view.KeyboardShortcutGroup;
import android.view.Menu;
import android.view.View;
import android.view.animation.DecelerateInterpolator;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.util.List;

public class LoginActivity
        extends AppCompatActivity
{

    private View inputUsername;
    private View inputPassword;
    private SharedPreferences accountInfo;
    private String username;
    private String password;
    private CheckBox checkRememberPassword;
    private Button btnLogin;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        initData();
        initView();
        bindData();
        bindEvent();
    }

    void setBtnLoginClickable()
    {
        btnLogin.setClickable(
                ((EditText) inputUsername.findViewById(R.id.value_content)).getText().length() > 0
                &&
                ((EditText) inputPassword.findViewById(R.id.value_content)).getText().length() > 0
        );
        if(btnLogin.isClickable())
        {
            btnLogin.setText(R.string.right_darker);
            btnLogin.setBackground(getResources().getDrawable(R.drawable.bg_shape_darker_gray));
        }
        else
        {
            btnLogin.setText(R.string.right_light);
            btnLogin.setBackground(getResources().getDrawable(R.drawable.bg_shape_light_gray));
        }
    }

    private void bindEvent()
    {
        TextWatcher btnLoginClickableWatcher = new TextWatcher()
        {
            @Override
            public void beforeTextChanged(
                    CharSequence charSequence,
                    int i,
                    int i1,
                    int i2
            )
            {

            }

            @Override
            public void onTextChanged(
                    CharSequence charSequence,
                    int i,
                    int i1,
                    int i2
            )
            {
            }

            @Override
            public void afterTextChanged(Editable editable)
            {
                setBtnLoginClickable();
            }
        };
        ((EditText) inputUsername.findViewById(R.id.value_content)).addTextChangedListener(btnLoginClickableWatcher);
        ((EditText) inputPassword.findViewById(R.id.value_content)).addTextChangedListener(btnLoginClickableWatcher);
        setBtnLoginClickable();
        if(!username.isEmpty())
            animationUp(inputPassword);
    }

    private void bindData()
    {
        initInputArea(
                inputUsername,
                "Username",
                username,
                InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_NORMAL
        );
        initInputArea(
                inputPassword,
                "Password",
                password,
                InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_PASSWORD
        );
        checkRememberPassword.setChecked(!password.isEmpty());
    }

    private void initData()
    {
        accountInfo = getSharedPreferences("account", Context.MODE_PRIVATE);
        username = accountInfo.getString("username", "");
        password = accountInfo.getString("password", "");
    }

    public void animationUp(final View view) {
        final TextView label = (TextView) view.findViewById(R.id.label_content);
        final EditText input = (EditText) view.findViewById(R.id.value_content);
        final CheckBox rememberValue = (CheckBox) view.getRootView().findViewById(R.id.log_checkRememberPassword);

        ObjectAnimator scaleX = ObjectAnimator.ofFloat(label, "scaleX", 0.6f);
        ObjectAnimator scaleY = ObjectAnimator.ofFloat(label, "scaleY", 0.6f);

        AnimatorSet animatorSet = new AnimatorSet();
        animatorSet.setDuration(100);
        animatorSet.setInterpolator(new DecelerateInterpolator());
        animatorSet.play(scaleX).with(scaleY); //两个动画同时开始
        animatorSet.start();

        animatorSet.addListener(new Animator.AnimatorListener() {
            @Override
            public void onAnimationStart(Animator animation) {
            }

            @Override
            public void onAnimationEnd(Animator animation) {
                if(view == inputPassword)
                    rememberValue.setVisibility(View.VISIBLE);
                input.setVisibility(View.VISIBLE);
                input.requestFocus();
                //弹出键盘
                InputMethodManager imm = (InputMethodManager) getApplicationContext().getSystemService(Context.INPUT_METHOD_SERVICE);
                assert imm != null;
                imm.showSoftInput(input, 0);
            }

            @Override
            public void onAnimationCancel(Animator animation) {

            }

            @Override
            public void onAnimationRepeat(Animator animation) {

            }
        });
    }

    public void animationDown(View view) {
        final TextView label = (TextView) view.findViewById(R.id.label_content);
        final EditText input = (EditText) view.findViewById(R.id.value_content);
        CheckBox rememberValue = (CheckBox) view.getRootView().findViewById(R.id.log_checkRememberPassword);

        input.setVisibility(View.GONE);
        if(view == inputPassword)
            rememberValue.setVisibility(View.GONE);

        ObjectAnimator scaleX = ObjectAnimator.ofFloat(label, "scaleX", 1);
        ObjectAnimator scaleY = ObjectAnimator.ofFloat(label, "scaleY", 1);

        AnimatorSet animatorSet = new AnimatorSet();
        animatorSet.setDuration(100);
        animatorSet.setInterpolator(new DecelerateInterpolator());
        animatorSet.play(scaleX).with(scaleY); //两个动画同时开始
        animatorSet.start();
    }

    private void initView()
    {
        inputUsername = findViewById(R.id.log_inputUsername);
        inputPassword = findViewById(R.id.log_inputPassword);
        checkRememberPassword = (CheckBox) findViewById(R.id.log_checkRememberPassword);
        btnLogin = (Button) findViewById(R.id.log_btnLogin);
    }

    private void initInputArea(final View inputArea, String label, String value, int inputType)
    {
        inputArea.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                animationUp(view);
            }
        });
        final TextView labelView = (TextView) inputArea.findViewById(R.id.label_content);
        final EditText inputView = (EditText) inputArea.findViewById(R.id.value_content);
        labelView.setText(label);
        inputView.setText(value);
        inputView.setInputType(inputType);
        inputView.setOnFocusChangeListener(new View.OnFocusChangeListener() {
            @Override
            public void onFocusChange(
                    View view,
                    boolean b
            )
            {
                if (!b && TextUtils.isEmpty(inputView.getText())) {
                    animationDown(inputArea);
                }
            }
        });
        if(!value.isEmpty())
            animationUp(inputArea);
    }

    String getInputValue(View inputArea)
    {
        return ((EditText) inputArea.findViewById(R.id.value_content)).getText().toString();
    }

    public void login(View view)
    {
        username = getInputValue(inputUsername);
        password = getInputValue(inputPassword);
        SharedPreferences.Editor accountEdit = accountInfo.edit();
        accountEdit.putString("username", username);
        if(checkRememberPassword.isChecked())
            accountEdit.putString("password", password);
        else
            accountEdit.remove("password");
        accountEdit.putBoolean("logged", true);
        accountEdit.apply();
        Toast.makeText(getApplicationContext(), "Login Successfully", Toast.LENGTH_SHORT).show();
        startActivity(new Intent(LoginActivity.this, MainActivity.class));
        finish();
    }

}
