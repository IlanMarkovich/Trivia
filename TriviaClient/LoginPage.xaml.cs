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
    /// Interaction logic for LoginPage.xaml
    /// </summary>
    public partial class LoginPage : Page
    {
        public LoginPage()
        {
            InitializeComponent();
        }

        private void login_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.buttonSound.Play();

            if (login_username.Text == String.Empty || login_password.Password == String.Empty)
            {
                login_invalid_txt.Visibility = Visibility.Visible;
                return;
            }

            Login(login_username.Text, login_password.Password);
        }

        public static void Login(string username, string password)
        {
            LoginUser user = new LoginUser(username, password);
            MainWindow.client.Send(RequestType.LOGIN, JsonConvert.SerializeObject(user, Formatting.Indented));

            string response = MainWindow.client.Recieve().Value;
            Status status = JsonConvert.DeserializeObject<Status>(response);

            if (status.status == 0)
            {
                ErrorWindow errWindow = new ErrorWindow("Login Error", "Login unsuccessful! (incorrect information or already logged in)");
                errWindow.ShowDialog();
            }
            else
            {
                MainWindow.current.SetUsername(username + " ");
                MainWindow.mainFrame.Navigate(new MainMenuPage());
            }
        }

        private void welcome_page_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.buttonSound.Play();
            MainWindow.mainFrame.Navigate(new WelcomePage());
        }
    }
}
