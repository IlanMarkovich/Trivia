﻿using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for JoinRoomPage.xaml
    /// </summary>
    public partial class JoinRoomPage : Page
    {
        public JoinRoomPage()
        {
            InitializeComponent();
        }

        private void join_room_btn_Click(object sender, RoutedEventArgs e)
        {
            if (room_list_view.SelectedItem == null)
                return;

            Room room = room_list_view.SelectedItem as Room;
            MainWindow.client.Send(RequestType.JOIN_ROOM, JsonConvert.SerializeObject(new RoomId(room.roomId), Formatting.Indented));

            string response = MainWindow.client.Recieve().Value;
            int status = JsonConvert.DeserializeObject<Status>(response).status;

            if (status == 0)
            {
                ErrorWindow window = new ErrorWindow("Join Room", "An error occurred while trying to join the room! Please try again");
                window.ShowDialog();
            }
            else
            {
                
            }
        }

        private void main_menu_back_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.mainFrame.Navigate(new MainMenuPage());
        }
    }
}
