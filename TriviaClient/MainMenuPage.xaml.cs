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
    /// Interaction logic for MainMenuPage.xaml
    /// </summary>
    public partial class MainMenuPage : Page
    {
        public MainMenuPage()
        {
            InitializeComponent();

            MainWindow.current.UpdateLogoutIsEnable(true);
        }

        private void create_room_menu_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.buttonSound.Play();
            MainWindow.mainFrame.Navigate(new CreateRoomPage());
        }

        private void join_room_menu_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.buttonSound.Play();
            MainWindow.mainFrame.Navigate(new JoinRoomPage());
        }

        private void statistics_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.buttonSound.Play();
            MainWindow.mainFrame.Navigate(new StatisticsPage());
        }

        private void quit_user_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.buttonSound.PlaySync();

            MainWindow.client.Send(RequestType.SIGNOUT);
            MainWindow.client.Disconnect();
            Application.Current.Shutdown();
        }
    }
}
