using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    public enum RequestType
    {
        ERR = -1, LOGIN, SIGNUP, SIGNOUT,
        GET_ROOMS, GET_PLAYRES_IN_ROOM, GET_PERSONAL_STAT, GET_HIGH_SCORES, JOIN_ROOM, CREATE_ROOM,
        CLOSE_ROOM, START_GAME, GET_ROOM_STATE, LEAVE_ROOM,
        LEAVE_GAME, GET_QUESTION, SUBMIT_ANSWER, GET_GAME_RESULTS
    }

    public enum ResponseType
    {
        REGULAR, START_GAME, LEAVE_ROOM, CLOSE_ROOM
    }

    public class Client
    {
        private readonly int PORT = 7777;
        private readonly int MAX_MESSAGE_SIZE = 4096;
        private readonly int MAX_TRIES = 5;

        private TcpClient client;

        public Client()
        {
            client = new TcpClient();
        }

        public async Task ConnectAsync()
        {
            int tries = MAX_TRIES;

            while(tries != 0)
            {
                try
                {
                    await client.ConnectAsync(IPAddress.Parse("127.0.0.1"), PORT);
                    break;
                }
                catch (Exception)
                {
                    tries--;
                }
            }
        }

        public bool IsConnected()
        {
            return client.Connected;
        }

        public void Disconnect()
        {
            if (client.Connected)
                client.Close();
        }

        public void Send(RequestType type)
        {
            Send(type, "");
        }

        public void Send(RequestType type, string data)
        {
            List<byte> buffer = new List<byte>
            {
                (byte)type
            };

            byte[] length = new byte[4];
            length[0] = (byte)(data.Length >> 24);
            length[1] = (byte)(data.Length >> 16);
            length[2] = (byte)(data.Length >> 8);
            length[3] = (byte)data.Length;
            buffer.AddRange(length);

            buffer.AddRange(Encoding.ASCII.GetBytes(data));

            client.GetStream().Write(buffer.ToArray(), 0, buffer.Count);
            client.GetStream().Flush();
        }

        public KeyValuePair<ResponseType, string> Recieve()
        {
            byte[] buffer = new byte[MAX_MESSAGE_SIZE];
            client.GetStream().Read(buffer, 0, MAX_MESSAGE_SIZE);

            ResponseType type = (ResponseType)buffer[0];

            byte[] lengthArr = new byte[4];
            Array.Copy(buffer, 1, lengthArr, 0, 4);

            if(BitConverter.IsLittleEndian)
            {
                Array.Reverse(lengthArr);
            }

            int length = BitConverter.ToInt32(lengthArr, 0);

            byte[] data = new byte[length];
            Array.Copy(buffer, 5, data, 0, length);

            return new KeyValuePair<ResponseType, string>(type, Encoding.ASCII.GetString(data));
        }
    }
}
