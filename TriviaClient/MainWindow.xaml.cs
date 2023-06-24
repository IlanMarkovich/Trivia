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
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Navigation;

namespace TriviaClient
{
    public partial class MainWindow : Window
    {
        // Static properties for pages to use
        public static Frame mainFrame { get; } = new Frame
        {
            NavigationUIVisibility = NavigationUIVisibility.Hidden,
            Content = new ConnectingPage()
        };
        public static Client client { get; } = new Client();
        public static MainWindow current { get; set; }

        // Variables for the moving background
        private Random rand;
        private double velX, velY;
        private double posX, posY;

        public MainWindow()
        {
            InitializeComponent();

            rand = new Random();
            current = this;

            mainGrid.Children.Add(mainFrame);
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            // Sets the random values for the moving background
            velX = rand.Next(0, 2) == 0 ? -0.5 : 0.5;
            velY = rand.Next(0, 2) == 0 ? -0.5 : 0.5;
            posX = rand.Next(0, (int)(background_canvas.ActualWidth * 1.25)) * -1;
            posY = rand.Next(0, (int)(background_canvas.ActualHeight * 1.25)) * -1;

            AnimateBackgroundAsync();
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

        // UI FUNCTIONS

        public void SetUsername(string username)
        {
            username_sp.Visibility = Visibility.Visible;
            username_txt.Text = username;
        }

        public void UpdateLogoutIsEnable(bool isEnabled)
        {
            logout_btn.IsEnabled = isEnabled;
        }

        private void logout_btn_Click(object sender, RoutedEventArgs e)
        {
            client.Send(RequestType.SIGNOUT);
            client.Recieve();
            username_sp.Visibility = Visibility.Hidden;

            mainFrame.Navigate(new WelcomePage());
        }
    }
}
