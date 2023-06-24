using Newtonsoft.Json;
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

            PlayersResults results = new PlayersResults();

            // While the status is zero (meaning the game isn't finished yet)
            while (results.status == 0)
            {
                MainWindow.client.Send(RequestType.GET_GAME_RESULTS);
                string response = MainWindow.client.Recieve().Value;
                results = JsonConvert.DeserializeObject<PlayersResults>(response);
            }

            waiting_txt.Visibility = Visibility.Hidden;
            player_results_list_view.Visibility = Visibility.Visible;

            player_results_list_view.DataContext = results.GetPlayersResults();
        }

        private void back_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.mainFrame.Navigate(new RoomPage(isAdmin, room));
        }
    }
}
