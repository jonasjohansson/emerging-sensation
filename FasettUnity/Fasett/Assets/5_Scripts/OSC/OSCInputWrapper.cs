

namespace FasettNet
{
    public abstract class OSCWrapper{
        public abstract bool SocketsOpen();
        public abstract bool Open(int localHost);
        public abstract void Close();
        public abstract void SendPacket(byte[] packet, int length, string remoteHostName, int remotePort);
        public abstract byte[] Receive(int localPort);
    }
}