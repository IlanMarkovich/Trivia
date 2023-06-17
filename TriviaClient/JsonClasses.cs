using System;
using System.Collections.Generic;
using System.Linq;
using System.Management.Instrumentation;
using System.Security.RightsManagement;
using System.Text;
using System.Threading.Tasks;

namespace TriviaClient
{
    internal class LoginUser
    {
        public string username { get; set; }
        public string password { get; set; }

        public LoginUser(string username, string password)
        {
            this.username = username;
            this.password = password;
        }
    }

    internal class Status
    {
        public int status { get; set; }

        public Status(int status)
        {
            this.status = status;
        }
    }

    internal class SignupUser
    {
        public string username { get; set; }
        public string password { get; set; }
        public string email { get; set; }

        public SignupUser(string username, string password, string email)
        {
            this.username = username;
            this.password = password;
            this.email = email;
        }
    }

    internal class Room
    {
        public int roomId { get; set; }
        public string roomName { get; set; }
        public int maxUsers { get; set; }
        public int questionsCount { get; set; }
        public int answerTimeout { get; set; }

        public Room(string roomName, int maxUsers, int questionsCount, int answerTimeout)
        {
            this.roomName = roomName;
            this.maxUsers = maxUsers;
            this.questionsCount = questionsCount;
            this.answerTimeout = answerTimeout;
        }

        public Room(int roomId, string roomName, int maxUsers, int questionsCount, int answerTimeout)
            : this(roomName, maxUsers, questionsCount, answerTimeout)
        {
            this.roomId = roomId;
        }
    }

    internal class RoomList
    {
        public int status { get; set; }
        public string rooms { get; set; }

        public RoomList(int status, string rooms)
        {
            this.status = status;
            this.rooms = rooms;
        }

        public List<Room> getRooms()
        {
            string[] rooms = this.rooms.Split('|');
            List<Room> roomLst = new List<Room>();

            foreach(string room in rooms)
            {
                string[] roomData = room.Split(',');
                
                if(roomData.Length == 5)
                {
                    roomLst.Add(new Room(int.Parse(roomData[0]), roomData[1], int.Parse(roomData[2]),
                    int.Parse(roomData[3]), int.Parse(roomData[4])));
                }
            }

            return roomLst;
        }
    }

    internal class RoomId
    {
        public int roomId { get; set; }

        public RoomId(int roomId)
        {
            this.roomId = roomId;
        }
    }

    internal class PersonalStatistics
    {
        public int status { get; set; }
        public string statistics { get; set; }

        public PersonalStatistics(int status, string statistics)
        {
            this.status = status;
            this.statistics = statistics;
        }
    }

    internal class Player
    {
        public string username { get; set; }

        public Player(string username)
        {
            this.username = username;
        }
    }

    internal class Players
    {
        public int status { get; set; }
        public string players { get; set; }

        public Players(int status, string players)
        {
            this.status = status;
            this.players = players;
        }

        public List<Player> getPlayers()
        {
            string[] arr = players.Split('\n');
            List<Player> lst = new List<Player>();

            foreach(string player in arr)
            {
                if(player != String.Empty)
                {
                    lst.Add(new Player(player));
                }
            }

            return lst;
        }
    }

    internal class RoomData
    {
        public Players players { get; set; }
        public bool hasGameBegun { get; set; }
        public int questions { get; set; }
        public int timeout { get; set; }

        public RoomData(int status, bool hasGameBegun, string players, int questions, int timeout)
        {
            this.players = new Players(status, players);
            this.hasGameBegun = hasGameBegun;
            this.questions = questions;
            this.timeout = timeout;
        }
    }
}
