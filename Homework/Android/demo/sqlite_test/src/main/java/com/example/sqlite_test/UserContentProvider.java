package com.example.sqlite_test;

import android.content.ContentProvider;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.Context;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.net.Uri;

import androidx.annotation.Nullable;

class DBHelper
        extends SQLiteOpenHelper
{
    private static final String DB_NAME = "data.db";
    private static final int DB_VERSION = 1;
    public static final String TABLE_NAME = "user";

    public DBHelper(@Nullable Context context)
    {
        super(context, DB_NAME, null, DB_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db)
    {
        db.execSQL(
                String.format("CREATE TABLE IF NOT EXISTS %s (_id INTEGER PRIMARY KEY AUTOINCREMENT, %s %s, %s %s, %s %s);", TABLE_NAME, "name", "varchar(20)", "age", "int", "sex",
                              "int"
                ));
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion)
    {
        //db.execSQL("ALTER TABLE " + TABLE_NAME + " ADD COLUMN other STRING");
    }
}



public class UserContentProvider
        extends ContentProvider
{
    public static final UriMatcher match = new UriMatcher(UriMatcher.NO_MATCH);
    static final int USER = 1;
    static final int USER_ID = 2;
    static
    {
        match.addURI(UserContract.AUTHORITY, UserContract.User.PATH, USER);
        match.addURI(UserContract.AUTHORITY, UserContract.User.PATH + "/#", USER_ID);
    }

    private DBHelper dbHelper = null;
    private SQLiteDatabase db = null;

    public UserContentProvider()
    {
    }

    @Override
    public int delete(
            Uri uri,
            String selection,
            String[] selectionArgs
    )
    {
        int count = 0;
        switch(match.match(uri))
        {
            case USER:
                count = db.delete(DBHelper.TABLE_NAME, selection, selectionArgs);
                break;
            case USER_ID:
                long id = ContentUris.parseId(uri);
                count = db.delete(DBHelper.TABLE_NAME, UserContract.User._ID + "=?", new String[] {String.valueOf(id)});
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
            case USER:
                type = String.format("vnd.android.cursor.dir/%s.%s", UserContract.AUTHORITY, UserContract.User.PATH);
                break;
            case USER_ID:
                type = String.format("vnd.android.cursor.item/%s.%s", UserContract.AUTHORITY, UserContract.User.PATH);
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
        if(match.match(uri) == USER)
        {
            long rowID = db.insert(DBHelper.TABLE_NAME, UserContract.User._ID, values);
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
        // TODO: Implement this to initialize your content provider on startup.
        dbHelper = new DBHelper(getContext());
        db = dbHelper.getWritableDatabase();
        return true;
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
            case USER:
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
            case USER:
                count = db.update(DBHelper.TABLE_NAME, values, selection, selectionArgs);
                break;
            case USER_ID:
                String studentID = String.valueOf(ContentUris.parseId(uri));
                count = db.update(DBHelper.TABLE_NAME, values, UserContract.User._ID + "=?", new String[] {studentID});
                break;
            default:
                throw new IllegalArgumentException("Unknown Uri: " + uri.toString());
        }
        return count;
    }
}
