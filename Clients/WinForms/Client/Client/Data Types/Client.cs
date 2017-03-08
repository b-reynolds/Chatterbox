using System;
using System.IO;
using System.Net.Sockets;
using System.Text;

namespace Chatterbox
{
    public class Client
    {
        private const int kBufferSize = 1024;

        private readonly string hostName;
        private readonly int port;

        private TcpClient tcpClient;
        private NetworkStream networkStream;

        public Client(string hostName, int port)
        {
            this.hostName = hostName;
            this.port = port;
        }

        ~Client()
        {
            if (Connected())
            {
                tcpClient.Close();
            }
        }

        public bool Connect()
        {
            if (Connected())
            {
                tcpClient.Close();
            }
            try
            {
                tcpClient = new TcpClient(hostName, port);
            }
            catch (SocketException)
            {
                return false;
            }
            networkStream = tcpClient.GetStream();
            return true;
        }

        public void Disconnect()
        {
            networkStream.Close();
            tcpClient.Close();
        }
 
        public bool Connected()
        {
            return tcpClient != null && tcpClient.Connected;
        }

        public void SendData(string data)
        {
            if (!Connected())
            {
                return;
            }

            if (data.Length > kBufferSize - 1)
            {
                data = data.Substring(0, kBufferSize - 1);
            }

            var bytes = Encoding.ASCII.GetBytes(data);
            networkStream.Write(bytes, 0, bytes.Length);
        }

        public string GetData()
        {
            var bytes = new byte[kBufferSize];

            try
            {
                int bytesRead = networkStream.Read(bytes, 0, bytes.Length); // System.IO.IO.Exception
                return Encoding.ASCII.GetString(bytes, 0, bytesRead);
            }
            catch (System.IO.IOException)
            {
                Disconnect();
            }

            return string.Empty;
        }
    }
}
