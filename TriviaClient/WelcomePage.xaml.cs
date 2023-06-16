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
    /// Interaction logic for WelcomePage.xaml
    /// </summary>
    public partial class WelcomePage : Page
    {
        private MainWindow window;

        public WelcomePage(ref MainWindow window)
        {
            InitializeComponent();

            this.window = window;
        }

        private void login_page_btn_Click(object sender, RoutedEventArgs e)
        {
            window.ChangePage(new LoginPage(ref window));
        }

        private void signup_page_btn_Click(object sender, RoutedEventArgs e)
        {
            window.ChangePage(new SignUpPage(ref window));
        }

        private void quit_btn_Click(object sender, RoutedEventArgs e)
        {
            window.client.Disconnect();
            Application.Current.Shutdown();
        }
    }
}
