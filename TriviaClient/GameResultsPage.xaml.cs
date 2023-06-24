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
    /// Interaction logic for GameResultsPage.xaml
    /// </summary>
    public partial class GameResultsPage : Page
    {
        private bool isAdmin;
        private Room room;

        public GameResultsPage(bool isAdmin, Room room)
        {
            InitializeComponent();

            this.isAdmin = isAdmin;
            this.room = room;

            // Wait for the game to finish in a seperate thread, so tha the UI thread won't be interrupted
            Task.Run(waitForGameFinish);
        }

        private void waitForGameFinish()
        {
            int status;
            PlayersResults results;

            // While the status is zero (meaning the game isn't finished yet)
            do
            {
                MainWindow.client.Send(RequestType.GET_GAME_RESULTS);
                string response = MainWindow.client.Recieve().Value;
                results = JsonConvert.DeserializeObject<PlayersResults>(response);
                status = results.status;

                // Wait for a second before the next request
                Thread.Sleep(1000);
            } while (status == 0);

            Application.Current.Dispatcher.Invoke(() =>
            {
                waiting_txt.Visibility = Visibility.Hidden;
                player_results_list_view.Visibility = Visibility.Visible;
                back_btn.Visibility = Visibility.Visible;

                player_results_list_view.DataContext = results.GetPlayersResults();
            });
        }

        private void back_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.mainFrame.Navigate(new RoomPage(isAdmin, room));
        }
    }
}
