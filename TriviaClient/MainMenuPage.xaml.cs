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
        private MainWindow window;
        
        public MainMenuPage(ref MainWindow window)
        {
            InitializeComponent();

            this.window = window;
        }

        private void create_room_menu_btn_Click(object sender, RoutedEventArgs e)
        {

        }

        private void join_room_menu_btn_Click(object sender, RoutedEventArgs e)
        {

        }

        private void statistics_btn_Click(object sender, RoutedEventArgs e)
        {

        }

        private void quit_user_btn_Click(object sender, RoutedEventArgs e)
        {
            window.client.Send(RequestType.SIGNOUT);
            window.client.Disconnect();
            Application.Current.Shutdown();
        }
    }
}
