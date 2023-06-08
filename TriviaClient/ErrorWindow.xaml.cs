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
using System.Windows.Shapes;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for ErrorWindow.xaml
    /// </summary>
    public partial class ErrorWindow : Window
    {
        public ErrorWindow(string title, string error_detail)
        {
            InitializeComponent();

            this.title.Text = title;
            this.error_detail.Text = error_detail;
        }

        private void close_btn_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
