package com.example.simple_chat;

import android.content.ContentProvider;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.net.Uri;

import androidx.annotation.Nullable;

import java.util.Objects;

class DBHelper
        extends SQLiteOpenHelper
{
    private static final int DB_VERSION = 2;
    public static final String TABLE_NAME = "record";

    public DBHelper(@Nullable Context context)
    {
        super(context, RecordContentProvider.DB_NAME, null, DB_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db)
    {
        db.execSQL(
                String.format(
                        "CREATE TABLE IF NOT EXISTS %s (_id INTEGER PRIMARY KEY AUTOINCREMENT, %s %s, %s %s, %s %s, %s %s);",
                        TABLE_NAME,
                        "owner", "varchar(20)",
                        "type", "varchar(20)",
                        "content", "varchar(10240)",
                        "resource", "varchar(100)"
                )
        );
    }

    @Override
    public void onUpgrade(
            SQLiteDatabase db,
            int oldVersion,
            int newVersion
    )
    {
    }
}

public class RecordContentProvider
        extends ContentProvider
{
    public static String DB_NAME = "";

    public static final UriMatcher match = new UriMatcher(UriMatcher.NO_MATCH);
    static final int DEFAULT = 1;
    static final int RECORD_ID = 2;
    static
    {
        match.addURI(RecordContract.AUTHORITY, RecordContract.Record.PATH, DEFAULT);
        match.addURI(RecordContract.AUTHORITY, RecordContract.Record.PATH + "/#", RECORD_ID);
    }

    private static DBHelper dbHelper = null;
    private static SQLiteDatabase db = null;
    private static SharedPreferences accountInfo;

    public RecordContentProvider()
    {
    }

    @Override
    public int delete(
            Uri uri,
            String selection,
            String[] selectionArgs
    )
    {
        System.out.println(uri.toString());
        int count = 0;
        switch(match.match(uri))
        {
            case RECORD_ID:
                long id = ContentUris.parseId(uri);
                count = db.delete(DBHelper.TABLE_NAME, RecordContract.Record._ID + "=?", new String[] {String.valueOf(id)});
                break;
            default:
                throw new IllegalArgumentException("Unknown Uri: " + uri.toString());
        }
        return count;
    }

    @Override
    public String getType(Uri uri)
    {
        String type = null;

        switch(match.match(uri))
        {
            case DEFAULT:
                type = String.format("vnd.android.cursor.dir/%s.%s", RecordContract.AUTHORITY, RecordContract.Record.PATH);
                break;
            default:
                throw new IllegalArgumentException("Unknown Uri: " + uri.toString());
        }

        return type;
    }

    @Override
    public Uri insert(
            Uri uri,
            ContentValues values
    )
    {
        Uri result = null;
        if(match.match(uri) == DEFAULT)
        {
            long rowID = db.insert(DBHelper.TABLE_NAME, RecordContract.Record._ID, values);
            result = ContentUris.withAppendedId(uri, rowID);
        }
        else
        {
            throw new IllegalStateException("Unexpected value: " + match.match(uri));
        }
        return result;
    }

    @Override
    public boolean onCreate()
    {
        accountInfo = Objects.requireNonNull(getContext()).getSharedPreferences("account", Context.MODE_PRIVATE);
        return true;
    }

    public static void freshDB(Context context)
    {
        if(accountInfo.contains("logged") && accountInfo.getBoolean("logged", false))
        {
            DB_NAME = accountInfo.getString("username", "") + ".db";
        }
        else
        {
            DB_NAME = "record.db";
        }

        dbHelper = new DBHelper(context);
        db = dbHelper.getWritableDatabase();
    }

    @Override
    public Cursor query(
            Uri uri,
            String[] projection,
            String selection,
            String[] selectionArgs,
            String sortOrder
    )
    {
        Cursor cursor = null;
        switch(match.match(uri))
        {
            case DEFAULT:
                cursor = db.query(DBHelper.TABLE_NAME, projection, selection, selectionArgs, null, null, sortOrder);
                break;
            default:
                throw new IllegalArgumentException("Unknown Uri: " + uri.toString());
        }
        return cursor;
    }

    @Override
    public int update(
            Uri uri,
            ContentValues values,
            String selection,
            String[] selectionArgs
    )
    {
        int count = 0;
        switch(match.match(uri))
        {
            case DEFAULT:
                count = db.update(DBHelper.TABLE_NAME, values, selection, selectionArgs);
                break;
            case RECORD_ID:
                String recordID = String.valueOf(ContentUris.parseId(uri));
                count = db.update(DBHelper.TABLE_NAME, values, RecordContract.Record._ID + "=?", new String[] {recordID});
                break;
            default:
                throw new IllegalArgumentException("Unknown Uri: " + uri.toString());
        }
        return count;
    }
}
