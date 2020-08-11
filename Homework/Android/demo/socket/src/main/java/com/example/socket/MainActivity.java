package com.example.socket;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;

public class MainActivity
        extends AppCompatActivity
{

    private EditText editIP;
    private EditText editPort;
    private EditText editMessage;
    private Button btnOpenTCP;
    private Button btnCloseTCP;
    private Button btnSendTCP;
    private Button btnOpenUDP;
    private Button btnCloseUDP;
    private Button btnSendUDP;
    private Socket tcpSocket;
    private Thread tcpThread;
    private HandlerMe handler;
    private TextView textResponse;
    private ArrayList<String> list;
    private Thread udpSocket;

    class HandlerMe extends Handler
    {
        @Override
        public void handleMessage(@NonNull Message msg)
        {
            if(msg.what == 0x01)
            {
                textResponse.setText(textResponse.getText().toString() + "\n" + list.get(msg.arg1));
            }
            super.handleMessage(msg);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        list = new ArrayList<String>();
        handler = new HandlerMe();

        initView();
        bindEvent();
    }

    void sendMessage(byte[] bytes, int count)
            throws UnsupportedEncodingException
    {
        Message message = new Message();
        message.what = 0x01;
        list.add("[Receive]" + new String((new String(bytes, 0, count, "GB2312")).getBytes(StandardCharsets.UTF_8), StandardCharsets.UTF_8));
        message.arg1 = list.size() - 1;
        handler.sendMessage(message);
    }

    void sendMessage(String msg)
    {
        Message message = new Message();
        message.what = 0x01;
        list.add(msg);
        message.arg1 = list.size() - 1;
        handler.sendMessage(message);
    }

    private void bindEvent()
    {
        btnOpenTCP.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                new AsyncTask<String, String, Void>()
                {
                    @Override
                    protected Void doInBackground(String... strings)
                    {
                        try
                        {
                            tcpSocket = new Socket(strings[0], Integer.valueOf(strings[1]).intValue());
                            //  tcpSocket.setSoTimeout(10000);
                            tcpThread = new Thread()
                            {
                                @Override
                                public void run()
                                {
                                    InputStream is = null;
                                    try
                                    {
                                        is = tcpSocket.getInputStream();
                                        int count;
                                        do
                                        {
                                            byte[] bytes = new byte[1024];
                                            count = is.read(bytes);
                                            if(count > 0)
                                            {
                                                sendMessage(bytes, count);
                                            }
                                        } while(count != -1);

                                    } catch(IOException e)
                                    {
                                        e.printStackTrace();
                                    }
                                }
                            };
                            tcpThread.start();
                        } catch(IOException e)
                        {
                            e.printStackTrace();
                        }
                        return null;
                    }
                }.execute(editIP.getText().toString(), editPort.getText().toString());
            }
        });
        btnSendTCP.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                String msg = editMessage.getText().toString();
                if(msg.length() == 0 || tcpSocket == null)
                    return;
                editMessage.setText("");
                OutputStream outStream = null;
                try
                {
                    outStream = tcpSocket.getOutputStream();
                    outStream.write(msg.getBytes("GB2312"));
                    outStream.flush();
                    sendMessage("[Send]" + msg);
                } catch(IOException e)
                {
                    e.printStackTrace();
                }
            }
        });
        btnCloseTCP.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                if(tcpSocket == null)
                    return;
                try
                {
                    tcpSocket.close();
                    sendMessage("Close TCP");
                } catch(IOException e)
                {
                    e.printStackTrace();
                }
            }
        });
        btnOpenUDP.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                udpSocket = new Thread()
                {
                    @Override
                    public void run()
                    {
                        try
                        {
                            DatagramSocket udp = new DatagramSocket(9999);
                            byte[] bytes = new byte[1024];
                            DatagramPacket packet = new DatagramPacket(bytes, bytes.length);
                            while(true)
                            {
                                udp.receive(packet);
                                String msg = new String(new String(packet.getData(), 0, packet.getLength(), "GB2312").getBytes(), StandardCharsets.UTF_8);
                                sendMessage("[Listen] " + msg);
                            }
                        } catch(IOException e)
                        {
                            e.printStackTrace();
                        }
                    }
                };
                udpSocket.start();
            }
        });
        btnSendUDP.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                new AsyncTask<String, Void, Void>()
                {
                    @Override
                    protected Void doInBackground(String... args)
                    {
                        try
                        {
                            InetAddress address = Inet4Address.getByName(args[0]);
                            byte[] bytes = args[2].getBytes("GB2312");
                            DatagramPacket receivePacket = new DatagramPacket(bytes, bytes.length, address, Integer.valueOf(args[1]).intValue());
                            DatagramSocket socket = new DatagramSocket();
                            socket.send(receivePacket);
                            socket.receive(receivePacket);
                            String msg = new String(new String(receivePacket.getData(), 0, receivePacket.getLength(), "GB2312").getBytes(), StandardCharsets.UTF_8);
                            sendMessage("[Receive] " + msg);
                            socket.close();
                        } catch(UnknownHostException | UnsupportedEncodingException | SocketException e)
                        {
                            e.printStackTrace();
                        } catch(IOException e)
                        {
                            e.printStackTrace();
                        }
                        return null;
                    }
                }.execute(editIP.getText().toString(), editPort.getText().toString(), editMessage.getText().toString());
            }
        });
    }

    private void initView()
    {
        editIP = (EditText) findViewById(R.id.editIP);
        editPort = (EditText) findViewById(R.id.editPort);
        editMessage = (EditText) findViewById(R.id.editMessage);
        btnOpenTCP = (Button) findViewById(R.id.btnOpenTCP);
        btnCloseTCP = (Button) findViewById(R.id.btnCloseTCP);
        btnSendTCP = (Button) findViewById(R.id.btnSendTCP);
        btnOpenUDP = (Button) findViewById(R.id.btnOpenUDP);
        btnCloseUDP = (Button) findViewById(R.id.btnCloseUDP);
        btnSendUDP = (Button) findViewById(R.id.btnSendUDP);
        textResponse = (TextView) findViewById(R.id.textResponse);
    }
}
