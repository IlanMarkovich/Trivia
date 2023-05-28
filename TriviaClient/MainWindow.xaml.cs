using System;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Threading;
using System.Collections.Generic;

namespace TriviaClient
{
    public partial class MainWindow : Window
    {
        private Random rand;
        private double velX, velY;
        private double posX, posY;

        public static double buttonWidth { get; set; }
        public static double buttonHeight { get; set; }

        public MainWindow()
        {
            InitializeComponent();

            rand = new Random();
        }

        private async void Window_Loaded(object sender, RoutedEventArgs e)
        {
            SetSizes();

            velX = rand.Next(0, 2) == 0 ? -0.5 : 0.5;
            velY = rand.Next(0, 2) == 0 ? -0.5 : 0.5;

            posX = rand.Next(0, (int)(background_canvas.ActualWidth * 1.25)) * -1;
            posY = rand.Next(0, (int)(background_canvas.ActualHeight * 1.25)) * -1;

            await AnimateBackgroundAsync();
        }

        private async Task AnimateBackgroundAsync()
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
            double screenWidth = SystemParameters.PrimaryScreenWidth;
            double screenHeight = SystemParameters.PrimaryScreenHeight;

            logo_image.Width = screenWidth / 1.92;
            logo_image.Height = screenHeight / 2.16;

            List<Button> buttons = GetChildButtons(mainGrid);

            foreach (Button button in buttons)
            {
                button.Width = screenWidth / 3.84;
                button.Height = screenHeight / 8.64;
            }
        }

        private List<Button> GetChildButtons(DependencyObject parent)
        {
            List<Button> buttons = new List<Button>();

            for (int i = 0; i < VisualTreeHelper.GetChildrenCount(parent); i++)
            {
                DependencyObject child = VisualTreeHelper.GetChild(parent, i);

                if (child is Button button)
                {
                    buttons.Add(button);
                }
                else
                {
                    buttons.AddRange(GetChildButtons(child));
                }
            }

            return buttons;
        }

        private void quit_btn_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }
    }
}
