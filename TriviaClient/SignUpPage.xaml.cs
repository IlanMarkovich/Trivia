using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
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
    /// Interaction logic for SignUpPage.xaml
    /// </summary>
    public partial class SignUpPage : Page
    {
        public SignUpPage()
        {
            InitializeComponent();
        }

        private void signup_btn_Click(object sender, RoutedEventArgs e)
        {
            if (signup_username.Text == String.Empty || signup_password.Password == String.Empty || signup_email.Text == String.Empty)
            {
                signup_invalid_txt.Visibility = Visibility.Visible;
                return;
            }

            SignupUser user = new SignupUser(signup_username.Text, signup_password.Password, signup_email.Text);
            MainWindow.client.Send(RequestType.SIGNUP, JsonConvert.SerializeObject(user, Formatting.Indented));

            string response = MainWindow.client.Recieve().Value;
            Status status = JsonConvert.DeserializeObject<Status>(response);

            if (status.status == 0)
            {
                ErrorWindow window = new ErrorWindow("Signup Error", "User already exists!");
                window.ShowDialog();
            }
            else
            {
                LoginPage.Login(signup_username.Text, signup_password.Password);
                MainWindow.mainFrame.Navigate(new MainMenuPage());
            }
        }

        private void welcome_page_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.mainFrame.Navigate(new WelcomePage());
        }
    }
}
