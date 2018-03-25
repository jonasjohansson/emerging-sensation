using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Net.Sockets;
using System.Net;
using System;

public class OSCWrapper {
    public bool SocketsOpen { private set; get; }

    private UdpClient Sender;
    private UdpClient Receiver;

    /// <summary>
    /// Open a UDP socket and create a UDP sender.
    /// 
    /// </summary>
    /// <returns>True on success, false on failure.</returns>
    public bool Open(int localPort){
        try {
            Sender = new UdpClient();
            Debug.Log("Opening OSC listener on port " + localPort);

            IPEndPoint listenerIp = new IPEndPoint(IPAddress.Any, localPort);
            Receiver = new UdpClient(listenerIp);


            SocketsOpen = true;

            return true;
        }
        catch (Exception e){
            Debug.LogWarning("cannot open udp client interface at port " + localPort);
            Debug.LogWarning(e);
        }

        return false;
    }

    /// <summary>
    /// Close the socket currently listening, and destroy the UDP sender device.
    /// </summary>
    public void Close(){
        if (Sender != null)
            Sender.Close();

        if (Receiver != null){
            Receiver.Close();
            // Debug.Log("UDP receiver closed");
        }
        Receiver = null;
        SocketsOpen = false;
    }

    public void SendPacket(byte[] packet, int length, string remoteHostName, int remotePort)
    {
        Sender.Send(packet, length, remoteHostName, remotePort);
    }

    public byte[] Receive(int localPort) {
        IPEndPoint iep = new IPEndPoint(IPAddress.Any, localPort);
        return Receiver.Receive(ref iep);
    }
}
