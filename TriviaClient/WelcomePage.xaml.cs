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
        public WelcomePage()
        {
            InitializeComponent();
        }

        private void login_page_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.buttonSound.Play();
            MainWindow.mainFrame.Navigate(new LoginPage());
        }

        private void signup_page_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.buttonSound.Play();
            MainWindow.mainFrame.Navigate(new SignUpPage());
        }

        private void quit_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.buttonSound.Play();
            MainWindow.client.Disconnect();
            Application.Current.Shutdown();
        }
    }
}
