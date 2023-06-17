using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
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
    /// Interaction logic for RoomPage.xaml
    /// </summary>
    public partial class RoomPage : Page
    {
        public static bool inRoom = false;
        public readonly int ROOM_RESPONSE_WAIT_TIME = 2000;

        private Page newPage;
        private bool switchPage;

        public RoomPage(bool isAdmin)
        {
            InitializeComponent();

            room_name_txt.Text = "Room";
            inRoom = true;

            switchPage = false;

            if (isAdmin)
            {
                admin_sp.Visibility = Visibility.Visible;
            }
            else
            {
                user_sp.Visibility = Visibility.Visible;
            }
            
            // This loop run asynchronically, and recieve a certain response from the server.
            // If the response type is REGULAR, meaning that the response is for the request that this client sent
            // which is the GET_ROOM_STATE request, it will get the list of the players
            // Otherwise it means that the response is a result of a operation requets (start game, close room or leave room)
            // and this operation needs to be handled accordingly
            Task.Run(() =>
            {
                while (inRoom)
                {
                    MainWindow.client.Send(RequestType.GET_ROOM_STATE);
                    var response = MainWindow.client.Recieve();

                    if (response.Key == ResponseType.REGULAR)
                    {
                        RecieveRoomState(response);
                    }
                    else
                    {
                        RecieveOperation(response);
                    }
                }
            });
        }

        private void RecieveRoomState(KeyValuePair<ResponseType, string>  response)
        {
            RoomData roomData = JsonConvert.DeserializeObject<RoomData>(response.Value);

            if (roomData.players.status == 0)
            {
                ErrorWindow window = new ErrorWindow("Get Players Error", "There was an error while getting the players in this room!");
                window.ShowDialog();
            }
            else
            {
                Application.Current.Dispatcher.Invoke(() =>
                {
                    room_players_list_view.DataContext = roomData.players.getPlayers();
                });
            }

            Thread.Sleep(ROOM_RESPONSE_WAIT_TIME);
        }

        private void RecieveOperation(KeyValuePair<ResponseType, string> response)
        {
            int status = JsonConvert.DeserializeObject<Status>(response.Value).status;

            if (status == 0)
            {
                ErrorWindow window = new ErrorWindow("Request Error", "Your request failed!");
                window.ShowDialog();
            }
            else
            {
                if (response.Key == ResponseType.START_GAME)
                {
                    MessageBox.Show("Game Started!");
                }
                else
                {
                    MessageBox.Show("Left Room!");

                    // Need to change the page in the same thread which the UI is running on
                    Application.Current.Dispatcher.InvokeAsync(() =>
                    {
                        MainWindow.mainFrame.Navigate(new MainMenuPage());
                    });
                }
            }
        }

        private void start_game_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.client.Send(RequestType.START_GAME);
        }

        private void close_room_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.client.Send(RequestType.CLOSE_ROOM);
        }

        private void leave_room_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.client.Send(RequestType.LEAVE_ROOM);
        }
    }
}
