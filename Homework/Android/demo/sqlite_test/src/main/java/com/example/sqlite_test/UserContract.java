package com.example.sqlite_test;

import android.net.Uri;

public final class UserContract
{
    public static final String AUTHORITY = "com.example.sqlite_test";
    public static class User
    {
        public static final String PATH = "user";
        public static final Uri CONTENT_URI = Uri.parse("content://" + AUTHORITY + "/" + PATH);
        public static final String _ID = "_id";
        public static final String NAME = "name";
        public static final String AGE = "age";
        public static final String SEX = "sex";
    }
}
