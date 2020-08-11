package com.example.content_provide;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ContentProviderOperation;
import android.content.ContentProviderResult;
import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.OperationApplicationException;
import android.database.Cursor;
import android.os.Bundle;
import android.os.RemoteException;
import android.provider.ContactsContract;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.util.ArrayList;

public class MainActivity
        extends AppCompatActivity
{

    private Button btnAdd;
    private Button btnDelete;
    private Button btnEdit;
    private Button btnQuery;
    private TextView textList;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initView();
        bingEvent();
    }

    private void bingEvent()
    {
        btnQuery.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                ContentResolver resolver = getContentResolver();
                String[] contactColumns = {ContactsContract.Contacts._ID, ContactsContract.Contacts.DISPLAY_NAME};
                String[] phoneColumns = {ContactsContract.CommonDataKinds.Phone.TYPE, ContactsContract.CommonDataKinds.Phone.NUMBER};
                Cursor contactCursor = resolver.query(ContactsContract.Contacts.CONTENT_URI, contactColumns, null, null, null);
                StringBuffer strBuff = new StringBuffer();
                String[] columnNames = contactCursor.getColumnNames();
                for(String name : columnNames)
                    strBuff.append(name).append("\t");
                strBuff.append("\n");
                int idIndex = contactCursor.getColumnIndex(ContactsContract.Contacts._ID);
                while(contactCursor.moveToNext())
                {
                    for(int i = 0; i < columnNames.length; i++)
                        strBuff.append(contactCursor.getString(i)).append("\t");
                    strBuff.append("\n");
                    int contactID = contactCursor.getInt(idIndex);
                    Cursor phoneCursor = resolver.query(ContactsContract.CommonDataKinds.Phone.CONTENT_URI, phoneColumns,
                                                        ContactsContract.CommonDataKinds.Phone.CONTACT_ID + "=" + contactID, null, null
                    );
                    while(phoneCursor.moveToNext())
                    {
                        strBuff.append("\t");
                        strBuff.append(phoneCursor.getInt(0));
                        strBuff.append(":");
                        strBuff.append(phoneCursor.getString(1)).append("\t");
                        strBuff.append("\n");
                    }
                    phoneCursor.close();
                }
                contactCursor.close();
                textList.setText(strBuff.toString());
            }
        });
        btnAdd.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                ArrayList<ContentProviderOperation> operations = new ArrayList<ContentProviderOperation>();
                ContentProviderOperation.Builder builder = ContentProviderOperation.newInsert(ContactsContract.RawContacts.CONTENT_URI);
                builder.withValue(ContactsContract.RawContacts.ACCOUNT_TYPE, null);
                builder.withValue(ContactsContract.RawContacts.ACCOUNT_NAME, null);
                operations.add(builder.build());

                builder = ContentProviderOperation.newInsert(ContactsContract.Data.CONTENT_URI);
                builder.withValueBackReference(ContactsContract.Data.RAW_CONTACT_ID, 0);
                builder.withValue(ContactsContract.Data.MIMETYPE, ContactsContract.CommonDataKinds.StructuredName.CONTENT_ITEM_TYPE);
                builder.withValue(ContactsContract.CommonDataKinds.StructuredName.DISPLAY_NAME, "bbb");
                operations.add(builder.build());

                builder = ContentProviderOperation.newInsert(ContactsContract.Data.CONTENT_URI);
                builder.withValueBackReference(ContactsContract.Data.RAW_CONTACT_ID, 0);
                builder.withValue(ContactsContract.Data.MIMETYPE, ContactsContract.CommonDataKinds.Phone.CONTENT_ITEM_TYPE);
                builder.withValue(ContactsContract.CommonDataKinds.Phone.TYPE, ContactsContract.CommonDataKinds.Phone.TYPE_MOBILE);
                builder.withValue(ContactsContract.CommonDataKinds.Phone.NUMBER, "12345678900");
                operations.add(builder.build());

                ContentResolver resolver = getContentResolver();
                try
                {
                    ContentProviderResult[] results = resolver.applyBatch(ContactsContract.AUTHORITY, operations);
                    StringBuilder stringBuilder = new StringBuilder();
                    for(ContentProviderResult result : results)
                        stringBuilder.append(result.uri.toString()).append("\n");
                    textList.setText(stringBuilder);
                } catch(OperationApplicationException e)
                {
                    e.printStackTrace();
                } catch(RemoteException e)
                {
                    e.printStackTrace();
                }
            }
        });
        btnDelete.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                String name = "bbb";
                int id = getContactID(name);
                if(id > 0)
                {
                    ArrayList<ContentProviderOperation> operations = new ArrayList<ContentProviderOperation>();
                    ContentProviderOperation.Builder builder;

                    builder = ContentProviderOperation.newDelete(ContactsContract.RawContacts.CONTENT_URI);
                    builder.withSelection(ContactsContract.RawContacts.CONTACT_ID + "=" + id, null);
                    operations.add(builder.build());

                    builder = ContentProviderOperation.newDelete(ContactsContract.Data.CONTENT_URI);
                    builder.withSelection(ContactsContract.Data.CONTACT_ID + "=" + id, null);
                    operations.add(builder.build());

                    try
                    {
                        ContentProviderResult[] results = getContentResolver().applyBatch(ContactsContract.AUTHORITY, operations);
                        StringBuilder stringBuilder = new StringBuilder();
                        for(ContentProviderResult result : results)
                            stringBuilder.append(result.toString()).append("\n");
                        textList.setText(stringBuilder);
                    } catch(OperationApplicationException | RemoteException e)
                    {
                        e.printStackTrace();
                    }
                }
                else
                {
                    textList.setText("联系人<" + name + ">不存在");
                }
            }
        });
        btnEdit.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                String name = "bbb";
                String phone = "123123123456";
                int id = getContactID(name);
                if(id > 0)
                {
                    ContentValues contentValues = new ContentValues();
                    contentValues.put(ContactsContract.Data.DATA1, phone);
                    int result = getContentResolver().update(
                            ContactsContract.Data.CONTENT_URI,
                            contentValues,
                            ContactsContract.Data.CONTACT_ID + "=? AND " + ContactsContract.Data.MIMETYPE + "=?",
                            new String[] {Integer.toString(id), "vnd.android.cursor.item/phone_v2"}
                    );
                    textList.setText("修改结果：" + result);
                }
                else
                {
                    textList.setText("联系人<" + name + ">不存在");
                }
            }
        });
    }

    int getContactID(String name)
    {
        int id = 0;
        Cursor cursor = getContentResolver().query(
                ContactsContract.Contacts.CONTENT_URI,
                new String[] {ContactsContract.Contacts._ID},
                ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME + "=?", new String[] {name}, null
        );
        assert cursor != null;
        if(cursor.moveToNext())
        {
            int idIndex = cursor.getColumnIndex(ContactsContract.Contacts._ID);
            id = cursor.getInt(idIndex);
        }
        cursor.close();
        return id;
    }

    private void initView()
    {
        btnAdd = (Button) findViewById(R.id.btnAdd);
        btnDelete = (Button) findViewById(R.id.btnDelete);
        btnEdit = (Button) findViewById(R.id.btnEdit);
        btnQuery = (Button) findViewById(R.id.btnQuery);
        textList = (TextView) findViewById(R.id.textList);
    }
}
