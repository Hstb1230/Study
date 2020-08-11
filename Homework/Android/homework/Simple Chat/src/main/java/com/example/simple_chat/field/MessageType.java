package com.example.simple_chat.field;

public class MessageType
{

    public static class S
    {
        public static final String TEXT = "text";
        public static final String IMAGE = "image";
        public static final String MUSIC = "music";
        public static final String CALCULATOR = "calculator";
        public static final String CALENDAR = "calendar";
        public static final String TIME = "time";
        public static final String PLAN = "plan";
    }

    public static class I
    {
        public static final int TEXT = 0;
        public static final int IMAGE = 1;
        public static final int MUSIC = 2;
        public static final int CALCULATOR = 3;
        public static final int TIME = 4;
        public static final int CALENDAR = 5;
        public static final int PLAN = 6;
        public static final int UNKNOWN = -1;
    }

    public static String getTypeString(int type)
    {
        return "";
    }

    public static int getTypeInt(String type)
    {
        switch(type)
        {
            case S.TEXT:
                return I.TEXT;
            case S.IMAGE:
                return I.IMAGE;
            case S.MUSIC:
                return I.MUSIC;
            case S.CALCULATOR:
                return I.CALCULATOR;
            case S.CALENDAR:
                return I.CALENDAR;
            case S.TIME:
                return I.TIME;
            case S.PLAN:
                return I.PLAN;
            default:
                return I.UNKNOWN;
        }
    }

}
