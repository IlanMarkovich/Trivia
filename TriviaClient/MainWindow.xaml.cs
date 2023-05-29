using System;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Threading;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace TriviaClient
{
    public partial class MainWindow : Window
    {
        private Random rand;
        private double velX, velY;
        private double posX, posY;

        private Client client;
        private UIElement currentMenu;

        public MainWindow()
        {
            InitializeComponent();

            rand = new Random();
            client = new Client();

            currentMenu = welcome_menu;
        }

        private async void Window_Loaded(object sender, RoutedEventArgs e)
        {
            SetSizes();

            // Background Animation variable initializations
            velX = rand.Next(0, 2) == 0 ? -0.5 : 0.5;
            velY = rand.Next(0, 2) == 0 ? -0.5 : 0.5;
            posX = rand.Next(0, (int)(background_canvas.ActualWidth * 1.25)) * -1;
            posY = rand.Next(0, (int)(background_canvas.ActualHeight * 1.25)) * -1;

            AnimateBackgroundAsync();

            await client.ConnectAsync();

            if (!client.IsConnected())
            {
                Application.Current.Shutdown();
            }

            connecting_gif.Visibility = Visibility.Hidden;
            logo_image.Visibility = Visibility.Visible;
            welcome_menu.Visibility = Visibility.Visible;
        }

        private async void AnimateBackgroundAsync()
        {
            while (true)
            {
                if (posX + velX > 0 || posX + velX < background_canvas.ActualWidth * -1.25)
                    velX *= -1;

                if (posY + velY > 0 || posY + velY < background_canvas.ActualHeight * -1.25)
                    velY *= -1;

                posX += velX;
                posY += velY;

                Canvas.SetLeft(background_image, posX);
                Canvas.SetTop(background_image, posY);

                await Task.Delay(1);
            }
        }

        private void SetSizes()
        {
            // Calculates the current sizes for elements based on screen resolution
            double screenWidth = SystemParameters.PrimaryScreenWidth;
            double screenHeight = SystemParameters.PrimaryScreenHeight;

            connecting_gif.Width = screenWidth / 3.84;
            connecting_gif.Height = screenHeight / 10.8;

            logo_image.Width = screenWidth / 1.92;
            logo_image.Height = screenHeight / 2.16;

            List<Button> buttons = Utils.GetChildComponents<Button>(mainGrid);

            foreach (Button button in buttons)
            {
                button.Width = screenWidth / 3.84;
                button.Height = screenHeight / 8.64;
            }
        }

        private void ChangeMenu(string currentMenuName)
        {
            UIElement menu = mainGrid.Children.Cast<UIElement>().ToList().First(x => (x as FrameworkElement).Name == currentMenuName);

            currentMenu.Visibility = Visibility.Hidden;
            menu.Visibility = Visibility.Visible;

            currentMenu = menu;
        }

        private void Menu_btn_Click(object sender, RoutedEventArgs e)
        {
            ChangeMenu((sender as Button).Name.Replace("_btn", ""));
        }

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            string buttonName = (sender as Button).Name;
            string menuName = "";

            foreach(char c in buttonName)
            {
                if (menuName.Contains("menu"))
                    break;

                menuName += c;
            }

            ChangeMenu(menuName);
        }

        private void quit_btn_Click(object sender, RoutedEventArgs e)
        {
            client.Disconnect();
            Application.Current.Shutdown();
        }

        private void login_btn_Click(object sender, RoutedEventArgs e)
        {
            if(login_username.Text == String.Empty || login_password.Password == String.Empty)
            {
                login_invalid_txt.Visibility = Visibility.Visible;
                return;
            }

            LoginUser user = new LoginUser(login_username.Text, login_password.Password);
            client.Send(RequestType.LOGIN, JsonConvert.SerializeObject(user, Formatting.Indented));

            string response = client.Recieve();
            Status status = JsonConvert.DeserializeObject<Status>(response);

            if (status.status == 0)
            {
                ErrorWindow window = new ErrorWindow("Login Error", "Login information is incorrect!");
                window.ShowDialog();
            }
            else
            {
                ChangeMenu("main_menu");
            }
        }
    }
}
