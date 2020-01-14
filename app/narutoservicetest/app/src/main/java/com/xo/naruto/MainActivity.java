package com.xo.naruto;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.lang.reflect.Method;

/*
* 通过反射机制 调用android.app.NarutoManager类中的方法
* */

public class MainActivity extends AppCompatActivity {

    private Class clazz = null;
    private TextView tv_get;
    private EditText et_set;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        init();
    }

    private void init() {

        tv_get = findViewById(R.id.viewget);
        et_set = findViewById(R.id.et);

        try {
            clazz = Class.forName("android.app.NarutoManager");

        } catch (Exception e) {
            e.printStackTrace( );
        }

    }

    public void onGet(View view) {

        try {
            Method method = clazz.getMethod("get");
            String result = (String) method.invoke(clazz.newInstance());
            System.out.println("result: " + result);
            tv_get.setText(result);

        } catch (Exception e) {
            e.printStackTrace( );
        }

    }

    public void onSet(View view) {

        String result = et_set.getText().toString();

        if (result.isEmpty()) {
            Toast.makeText(getApplicationContext(),"please input some strings",
                    Toast.LENGTH_SHORT).show();
            return;
        }

        try {
            Method method = clazz.getMethod("set", String.class);
            method.invoke(clazz.newInstance(), result);
        } catch (Exception e) {
            e.printStackTrace( );
        }finally {
            Toast.makeText(getApplicationContext(),"set success",
                    Toast.LENGTH_SHORT).show();
        }

    }

}
