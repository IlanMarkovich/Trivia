﻿using System;
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
    /// Interaction logic for ConnectingPage.xaml
    /// </summary>
    public partial class ConnectingPage : Page
    {
        private MainWindow window;

        public ConnectingPage(ref MainWindow window)
        {
            InitializeComponent();

            this.window = window;
        }

        private async void Page_Loaded(object sender, RoutedEventArgs e)
        {
            await window.client.ConnectAsync();

            if (!window.client.IsConnected())
            {
                Application.Current.Shutdown();
            }

            window.ChangePage(new WelcomePage(ref window));
        }
    }
}
