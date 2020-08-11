package com.example.simple_chat.field;

import java.util.HashMap;

public class RecordInfo
{
    public String provide;
    public String resource;
    public String owner;
    public String type;
    public String content;
    public HashMap<String, Object> args;

    public RecordInfo()
    {
        args = new HashMap<>();
    }

    public RecordInfo(
            String _provide,
            String _owner,
            String _type,
            String _content,
            String _resource
    )
    {
        provide = _provide;
        owner = _owner;
        type = _type;
        content = _content;
        resource = _resource;
        args = new HashMap<>();
    }
}
