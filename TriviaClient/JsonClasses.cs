using System;
using System.Collections.Generic;
using System.Linq;
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

    internal class CreateRoom
    {
        public string roomName { get; set; }
        public int maxUsers { get; set; }
        public int questionsCount { get; set; }
        public int answerTimeout { get; set; }

        public CreateRoom(string roomName, int maxUsers, int questionsCount, int answerTimeout)
        {
            this.roomName = roomName;
            this.maxUsers = maxUsers;
            this.questionsCount = questionsCount;
            this.answerTimeout = answerTimeout;
        }
    }
}
