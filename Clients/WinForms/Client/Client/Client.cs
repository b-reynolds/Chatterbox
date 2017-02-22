using System.IO;
using System.Net.Sockets;
using System.Text;

namespace Client
{
    public class Client
    {
        private const int kBufferSize = 1024;

        private readonly string host_name_;
        private readonly int port_;

        private TcpClient tcp_client_;
        private NetworkStream network_stream_;

        public Client(string host_name, int port)
        {
            host_name_ = host_name;
            port_ = port;
        }

        ~Client()
        {
            if (Connected())
            {
                tcp_client_.Close();
            }
        }

        public bool Connect()
        {
            if (Connected())
            {
                tcp_client_.Close();
            }
            try
            {
                tcp_client_ = new TcpClient(host_name_, port_);
            }
            catch (SocketException)
            {
                return false;
            }
            network_stream_ = tcp_client_.GetStream();
            return true;
        }

        public void Disconnect()
        {
            network_stream_.Close();
            tcp_client_.Close();
        }
 
        public bool Connected()
        {
            return tcp_client_ != null && tcp_client_.Connected;
        }

        public void SendData(string data)
        {
            if (Connected())
            {
                if (data.Length > kBufferSize - 1)
                {
                    data = data.Substring(0, kBufferSize - 1);
                }
                var bytes = Encoding.ASCII.GetBytes(data);
                network_stream_.Write(bytes, 0, bytes.Length);
            }
        }

        public string GetData()
        {
            if (Connected())
            {
                var bytes = new byte[kBufferSize];
                int bytesRead = network_stream_.Read(bytes, 0, bytes.Length);
                return Encoding.ASCII.GetString(bytes, 0, bytesRead);
            }
            return string.Empty;
        }
    }
}
