package com.example.simple_chat;

import android.net.Uri;

class RecordContract
{
    static final String AUTHORITY = "com.example.simple_chat";
    public static class Record
    {
        static final String PATH = "record";
        public static final Uri CONTENT_URI = Uri.parse("content://" + AUTHORITY + "/" + PATH);
        static final String _ID = "_id";
        public static final String OWNER = "owner";
        public static final String TYPE = "type";
        public static final String CONTENT = "content";
        public static final String RESOURCE = "resource";
    }
}
