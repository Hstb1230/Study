package com.example.sqlite_test;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.ContentProviderOperation;
import android.content.ContentProviderResult;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.DialogInterface;
import android.content.OperationApplicationException;
import android.database.Cursor;
import android.os.Bundle;
import android.os.RemoteException;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class MainActivity
        extends AppCompatActivity
{
    private ListView listData;
    // private DBHelper dbHelper;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        dbHelper = new DBHelper(this);

        initView();
    }

    private void initView()
    {
        listData = (ListView) findViewById(R.id.listData);
    }

    public void add(View view)
    {
        @SuppressLint("InflateParams") final View userInfoView = LayoutInflater.from(this).inflate(R.layout.user_info_edit, null);
        final EditText editName = (EditText) userInfoView.findViewById(R.id.editName);
        final EditText editAge = (EditText) userInfoView.findViewById(R.id.editAge);
        final RadioGroup radioSex = (RadioGroup) userInfoView.findViewById(R.id.radioSex);
        AlertDialog.Builder alert = new AlertDialog.Builder(this);
        alert.setTitle("Add");
        alert.setIcon(android.R.drawable.ic_dialog_info);
        alert.setView(userInfoView);
        alert.setPositiveButton("Continue", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialogInterface, int i)
            {
                if(editName.length() == 0 || editAge.length() == 0 || radioSex.getCheckedRadioButtonId() == -1)
                {
                    Toast.makeText(getApplicationContext(), "缺少部分信息", Toast.LENGTH_SHORT).show();
                    return;
                }
//                SQLiteDatabase db = dbHelper.getWritableDatabase();
                String name = editName.getText().toString();
                int age = Integer.parseInt(editAge.getText().toString());
                int sex = 0;
                String sexName = ((RadioButton) userInfoView.findViewById(radioSex.getCheckedRadioButtonId())).getText().toString().toLowerCase();
                if(sexName.equals("boy"))
                {
                    sex = 1;
                }
                else if(sexName.equals("girl"))
                {
                    sex = 2;
                }

                ArrayList<ContentProviderOperation> operations = new ArrayList<ContentProviderOperation>();
                ContentProviderOperation.Builder insertOpt = ContentProviderOperation.newInsert(UserContract.User.CONTENT_URI);
                insertOpt.withValue(UserContract.User.NAME, name);
                insertOpt.withValue(UserContract.User.AGE, age);
                insertOpt.withValue(UserContract.User.SEX, sex);
                operations.add(insertOpt.build());

                ContentResolver resolver = getContentResolver();
                try
                {
                    ContentProviderResult[] results = resolver.applyBatch(UserContract.AUTHORITY, operations);
                    StringBuilder stringBuilder = new StringBuilder();
                    for(ContentProviderResult result : results)
                        stringBuilder.append(result.uri.toString()).append("\n");
                    Toast.makeText(getApplicationContext(), stringBuilder, Toast.LENGTH_SHORT).show();
                } catch(RemoteException | OperationApplicationException e)
                {
                    e.printStackTrace();
                }
            }
        });
        alert.setNegativeButton("Cancel", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialogInterface, int i)
            {
            }
        });
        alert.show();
    }

    public void delete(View view)
            throws NoSuchFieldException, IllegalAccessException, OperationApplicationException, RemoteException
    {
        int len = listData.getChildCount();
//        SQLiteDatabase db = dbHelper.getWritableDatabase();
        for(int i = 0; i < len; i++)
        {
            View itemView = listData.getChildAt(i);
            CheckBox checkSelected = (CheckBox) itemView.findViewById(R.id.checkSelected);
            if(!checkSelected.isChecked())
                continue;
            String id = (((TextView) itemView.findViewById(R.id.textID)).getText().toString());

            ArrayList<ContentProviderOperation> operations = new ArrayList<>();
            ContentProviderOperation.Builder deleteOpt = ContentProviderOperation.newDelete(UserContract.User.CONTENT_URI);
            deleteOpt.withSelection(UserContract.User._ID + "=?", new String[] {id});
            operations.add(deleteOpt.build());

            ContentProviderResult[] contentProviderResults = getContentResolver().applyBatch(UserContract.AUTHORITY, operations);
//            StringBuilder stringBuilder = new StringBuilder();
//            for(ContentProviderResult result : contentProviderResults)
//                Toast.makeText(getApplicationContext(), "Delete " + result.count, Toast.LENGTH_SHORT).show();

            // db.delete((String) dbHelper.getClass().getField("TABLE_NAME").get(dbHelper), "_id = ?", new String[] {id});
        }
//        db.close();
    }

    public void edit(View view)
            throws NoSuchFieldException, IllegalAccessException
    {
        int len = listData.getChildCount();
//        SQLiteDatabase db = dbHelper.getWritableDatabase();
        for(int i = 0; i < len; i++)
        {
            View itemView = listData.getChildAt(i);
            CheckBox checkSelected = (CheckBox) itemView.findViewById(R.id.checkSelected);
            if(!checkSelected.isChecked())
                continue;
            final String id = ((TextView) itemView.findViewById(R.id.textID)).getText().toString();
            TextView textName = (TextView) itemView.findViewById(R.id.textName);
            TextView textAge = (TextView) itemView.findViewById(R.id.textAge);
            TextView textSex = (TextView) itemView.findViewById(R.id.textSex);

            @SuppressLint("InflateParams") final View userInfoView = LayoutInflater.from(this).inflate(R.layout.user_info_edit, null);
            final EditText editName = (EditText) userInfoView.findViewById(R.id.editName);
            editName.setText(textName.getText());
            final EditText editAge = (EditText) userInfoView.findViewById(R.id.editAge);
            editAge.setText(textAge.getText());
            final RadioGroup radioSex = (RadioGroup) userInfoView.findViewById(R.id.radioSex);
            int lenRadio = radioSex.getChildCount();
            for(int j = 0; j < lenRadio; j++)
            {
                RadioButton radio = (RadioButton) radioSex.getChildAt(j);
                if(radio.getText().toString().equals(textSex.getText().toString()))
                {
                    radio.setChecked(true);
                    break;
                }
            }
            AlertDialog.Builder alert = new AlertDialog.Builder(this);
            alert.setTitle("Edit");
            alert.setIcon(android.R.drawable.ic_dialog_info);
            alert.setView(userInfoView);
            alert.setPositiveButton("Continue", new DialogInterface.OnClickListener()
            {
                @Override
                public void onClick(DialogInterface dialogInterface, int i)
                {
                    if(editName.length() == 0 || editAge.length() == 0 || radioSex.getCheckedRadioButtonId() == -1)
                    {
                        Toast.makeText(getApplicationContext(), "缺少部分信息", Toast.LENGTH_SHORT).show();
                        return;
                    }
//                    SQLiteDatabase db = dbHelper.getWritableDatabase();
                    String name = editName.getText().toString();
                    int age = Integer.parseInt(editAge.getText().toString());
                    int sex = 0;
                    String sexName = ((RadioButton) userInfoView.findViewById(radioSex.getCheckedRadioButtonId())).getText().toString().toLowerCase();
                    if(sexName.equals("boy"))
                    {
                        sex = 1;
                    }
                    else if(sexName.equals("girl"))
                    {
                        sex = 2;
                    }

                    ContentValues values = new ContentValues();
                    values.put("name", name);
                    values.put("age", age);
                    values.put("sex", sex);
//
//                    try
//                    {
//                        db.update((String) dbHelper.getClass().getField("TABLE_NAME").get(dbHelper), values, "_id = ?", new String[] {id});
//                        db.close();
//                    } catch(NoSuchFieldException | IllegalAccessException e)
//                    {
//                        e.printStackTrace();
//                    }

                    int result = getContentResolver().update(
                            UserContract.User.CONTENT_URI,
                            values,
                            UserContract.User._ID + "=?",
                            new String[] {id}
                    );
//                    Toast.makeText(getApplicationContext(), "修改结果：" + result, Toast.LENGTH_SHORT).show();
                }
            });
            alert.setNegativeButton("Cancel", new DialogInterface.OnClickListener()
            {
                @Override
                public void onClick(DialogInterface dialogInterface, int i)
                {
                }
            });
            alert.show();
        }
//        db.close();
    }

    public void query(View view)
            throws NoSuchFieldException, IllegalAccessException
    {
        ArrayList<HashMap<String, Object>> list = new ArrayList<HashMap<String, Object>>();
//        SQLiteDatabase db = dbHelper.getReadableDatabase();
//        Cursor cursor = db.rawQuery("select * from " + (String) dbHelper.getClass().getField("TABLE_NAME").get(dbHelper), null);

        class User {
            public int id;
            public String name;
            public int age;
            public int sex;
        }

        ArrayList<User> userList = new ArrayList<>();

        ContentResolver resolver = getContentResolver();
        Cursor cursor = resolver.query(UserContract.User.CONTENT_URI, null, null, null, null);

        assert cursor != null;
        int idIndex = cursor.getColumnIndex(UserContract.User._ID);
        int nameIndex = cursor.getColumnIndex(UserContract.User.NAME);
        int ageIndex = cursor.getColumnIndex(UserContract.User.AGE);
        int sexIndex = cursor.getColumnIndex(UserContract.User.SEX);
        while(cursor.moveToNext())
        {
            User user = new User();
            user.id = cursor.getInt(idIndex);
            user.name = cursor.getString(nameIndex);
            user.age = cursor.getInt(ageIndex);
            user.sex = cursor.getInt(sexIndex);
            userList.add(user);
        }
//        cursor.close();
//        db.close();

        ArrayList<Map<String, Object>> dataList = new ArrayList<Map<String, Object>>();
        for(User user : userList)
        {
            Map<String, Object> data = new HashMap<String, Object>();
            data.put("id", String.valueOf(user.id));
            data.put("name", user.name);
            data.put("age", String.valueOf(user.age));
            if(user.sex == 1)
                data.put("sex", "Boy");
            else if(user.sex == 2)
                data.put("sex", "Girl");
            dataList.add(data);
        }
        SimpleAdapter adapter = new SimpleAdapter(getApplicationContext(), dataList, R.layout.user_info_item, new String[] {"id", "name", "age", "sex"}, new int[] {R.id.textID, R.id.textName, R.id.textAge, R.id.textSex}) {
            @Override
            public View getView(int position, View convertView, ViewGroup parent)
            {
                View itemView = super.getView(position, convertView, parent);
                itemView.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View view)
                    {
                        CheckBox checkSelected = (CheckBox) view.findViewById(R.id.checkSelected);
                        checkSelected.setChecked(!checkSelected.isChecked());
//                        view.setBackgroundColor(getResources().getColor(android.R.color.holo_blue_bright));
                    }
                });
                return itemView;
            }
        };
        listData.setAdapter(adapter);
    }
}
