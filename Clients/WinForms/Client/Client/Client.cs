using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public class Client
    {
        private TcpClient tcpClient;
        private NetworkStream networkStream;

        private readonly string hostName;
        private readonly int port;
        private readonly int bufferSize;

        public Client(string hostName, int port, int bufferSize)
        {
            this.hostName = hostName;
            this.port = port;
            this.bufferSize = bufferSize;
        }

        ~Client()
        {
            if (tcpClient != null && isConnected())
            {
                tcpClient.Close();
            }
        }

        public bool isConnected()
        {
            return tcpClient.Connected;
        }

        public bool connect()
        {
            if (tcpClient != null && isConnected())
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

        public void sendData(string data)
        {
            if (data.Length > bufferSize - 1)
            {
                data = data.Substring(0, bufferSize - 1);
            }
            byte[] bytes = Encoding.ASCII.GetBytes(data);
            networkStream.Write(bytes, 0, bytes.Length);
        }

        public string getData()
        {
            byte[] bytes = new byte[bufferSize];
            try
            {
                int bytesRead = networkStream.Read(bytes, 0, bytes.Length);
                return (Encoding.ASCII.GetString(bytes, 0, bytesRead));
            }
            catch (IOException)
            {
                return null;
            }
        }
    }
}
