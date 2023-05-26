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
using System.Windows.Media.Media3D;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace TriviaClient
{
    //Width = SystemParameters.PrimaryScreenWidth;
    //Height = SystemParameters.PrimaryScreenHeight;

    //Image.Width = Width;
    //Image.Height = Height;

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private DispatcherTimer timer;
        private Random rand;

        private int velX, velY;
        private int posX, posY;

        public MainWindow()
        {
            InitializeComponent();

            rand = new Random();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            velX = rand.Next(0, 2) == 0 ? -1 : 1;
            velY = rand.Next(0, 2) == 0 ? -1 : 1;

            posX = rand.Next(0, (int)(background_canvas.ActualWidth * 1.25)) * -1;
            posY = rand.Next(0, (int)(background_canvas.ActualHeight * 1.25)) * -1;

            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromMilliseconds(1);
            timer.Tick += Timer_Tick;
            timer.Start();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            if (posX + velX > 0 || posX + velX < background_canvas.ActualWidth * -1.25)
                velX *= -1;

            if (posY + velY > 0 || posY + velY < background_canvas.ActualHeight * -1.25)
                velY *= -1;

            posX += velX;
            posY += velY;

            Canvas.SetLeft(background_image, posX);
            Canvas.SetTop(background_image, posY);
        }
    }
}
