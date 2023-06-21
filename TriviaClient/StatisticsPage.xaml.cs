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
    /// Interaction logic for StatisticsPage.xaml
    /// </summary>
    public partial class StatisticsPage : Page
    {
        public StatisticsPage()
        {
            InitializeComponent();

            personal_stat_btn_Click(null, null);
        }

        private void personal_stat_btn_Click(object sender, RoutedEventArgs e)
        {
            personal_stat_txt.Visibility = Visibility.Visible;
            high_score_players_list_view.Visibility = Visibility.Hidden;
            personal_stat_btn.IsEnabled = false;
            highscore_stat_btn.IsEnabled = true;

            if (personal_stat_txt.Visibility == Visibility.Hidden)
                return;

            MainWindow.client.Send(RequestType.GET_PERSONAL_STAT);

            string response = MainWindow.client.Recieve().Value;
            PersonalStatistics stat = JsonConvert.DeserializeObject<PersonalStatistics>(response);

            if (stat.status == 0)
            {
                ErrorWindow error = new ErrorWindow("Statistics Error", "There are no statistics for this user!");
                error.ShowDialog();
            }
            else
            {
                personal_stat_txt.Text = stat.statistics;
            }
        }

        private void highscore_stat_btn_Click(object sender, RoutedEventArgs e)
        {
            personal_stat_txt.Visibility = Visibility.Hidden;
            high_score_players_list_view.Visibility = Visibility.Visible;
            personal_stat_btn.IsEnabled = true;
            highscore_stat_btn.IsEnabled = false;

            if (high_score_players_list_view.Visibility == Visibility.Hidden)
                return;

            MainWindow.client.Send(RequestType.GET_HIGH_SCORES);

            string response = MainWindow.client.Recieve().Value;
            Players highScores = JsonConvert.DeserializeObject<Players>(response);

            if (highScores.status == 0)
            {
                ErrorWindow window = new ErrorWindow("High Scores Error", "There are no high scores!");
                window.ShowDialog();
            }
            else
            {
                high_score_players_list_view.DataContext = highScores.getPlayers();
            }
        }

        private void main_menu_back_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.mainFrame.Navigate(new MainMenuPage());
        }
    }
}
