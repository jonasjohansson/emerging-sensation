#if UNITY_EDITOR
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Net.Sockets;
using System.Net;
using System;

namespace FasettNet
{
    public class UnityOsc : OSCWrapper
    {
        public bool _socketsOpen;

        private UdpClient Sender;
        private UdpClient Receiver;

        /// <summary>
        /// Open a UDP socket and create a UDP sender.
        /// 
        /// </summary>
        /// <returns>True on success, false on failure.</returns>
        public override bool Open(int localPort)
        {
            try
            {
                Sender = new UdpClient();
                Debug.Log("Opening OSC listener on port " + localPort);

                IPEndPoint listenerIp = new IPEndPoint(IPAddress.Any, localPort);
                Receiver = new UdpClient(listenerIp);
                _socketsOpen = true;

                return true;
            }
            catch (Exception e)
            {
                Debug.LogWarning("cannot open udp client interface at port " + localPort);
                Debug.LogWarning(e);
            }

            return false;
        }

        /// <summary>
        /// Close the socket currently listening, and destroy the UDP sender device.
        /// </summary>
        public override void Close()
        {
            if (Sender != null)
                Sender.Close();

            if (Receiver != null)
            {
                Receiver.Close();
                // Debug.Log("UDP receiver closed");
            }
            Receiver = null;
            _socketsOpen = false;
        }

        public override bool SocketsOpen()
        {
            return _socketsOpen;
        }

        public override void SendPacket(byte[] packet, int length, string remoteHostName, int remotePort)
        {
            Sender.Send(packet, length, remoteHostName, remotePort);
        }

        public override byte[] Receive(int localPort)
        {
            IPEndPoint iep = new IPEndPoint(IPAddress.Any, localPort);
            return Receiver.Receive(ref iep);
        }
    }
}
#endif