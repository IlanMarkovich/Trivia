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
        private MainWindow window;

        public LoginPage(ref MainWindow window)
        {
            InitializeComponent();

            this.window = window;
        }

        private void login_btn_Click(object sender, RoutedEventArgs e)
        {
            if (login_username.Text == String.Empty || login_password.Password == String.Empty)
            {
                login_invalid_txt.Visibility = Visibility.Visible;
                return;
            }

            LoginUser user = new LoginUser(login_username.Text, login_password.Password);
            window.client.Send(RequestType.LOGIN, JsonConvert.SerializeObject(user, Formatting.Indented));

            string response = window.client.Recieve().Value;
            Status status = JsonConvert.DeserializeObject<Status>(response);

            if (status.status == 0)
            {
                ErrorWindow window = new ErrorWindow("Login Error", "Login unsuccessful! (incorrect information or already logged in)");
                window.ShowDialog();
            }
            else
            {
                window.SetUsername(login_username.Text + " ");
                window.ChangePage(new MainMenuPage(ref window));
            }
        }

        private void welcome_page_btn_Click(object sender, RoutedEventArgs e)
        {
            window.ChangePage(new WelcomePage(ref window));
        }
    }
}
