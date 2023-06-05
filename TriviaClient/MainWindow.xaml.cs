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

        // GENERAL FUNCTIONS

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

        private void Cb_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            (sender as ComboBox).Text = (string)(sender as ComboBox).SelectedItem;
        }

        // WELCOME MENU FUNCTIONS

        private void quit_btn_Click(object sender, RoutedEventArgs e)
        {
            client.Disconnect();
            Application.Current.Shutdown();
        }

        private void welcome_menu_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            logo_image.Visibility = Visibility.Visible;
        }

        // LOGIN MENU FUNCTIONS

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
                ErrorWindow window = new ErrorWindow("Login Error", "Login unsuccessful! (incorrect information or already logged in)");
                window.ShowDialog();
            }
            else
            {
                username_txt.Text = login_username.Text + " ";
                username_sp.Visibility = Visibility.Visible;

                ChangeMenu("main_menu");
            }
        }

        private void welcome_menu_back1_Click(object sender, RoutedEventArgs e)
        {
            login_username.Text = "";
            login_password.Password = "";
            login_invalid_txt.Visibility = Visibility.Hidden;

            ChangeMenu("welcome_menu");
        }

        // SIGNUP MENU FUNCTIONS

        private void signup_btn_Click(object sender, RoutedEventArgs e)
        {
            if(signup_username.Text == String.Empty || signup_password.Password == String.Empty || signup_email.Text == String.Empty)
            {
                signup_invalid_txt.Visibility = Visibility.Visible;
                return;
            }

            SignupUser user = new SignupUser(signup_username.Text, signup_password.Password, signup_email.Text);
            client.Send(RequestType.SIGNUP, JsonConvert.SerializeObject(user, Formatting.Indented));

            string response = client.Recieve();
            Status status = JsonConvert.DeserializeObject<Status>(response);

            if(status.status == 0)
            {
                ErrorWindow window = new ErrorWindow("Signup Error", "User already exists!");
                window.ShowDialog();
            }
            else
            {
                login_username.Text = signup_username.Text;
                login_password.Password = signup_password.Password;

                login_btn_Click(sender, e);
            }
        }

        private void welcome_menu_back2_Click(object sender, RoutedEventArgs e)
        {
            signup_username.Text = "";
            signup_password.Password = "";
            signup_email.Text = "";
            signup_invalid_txt.Visibility = Visibility.Hidden;

            ChangeMenu("welcome_menu");
        }

        // MAIN MENU FUNCTIONS

        private void main_menu_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            // Clear previous menu's data
            if(main_menu.Visibility == Visibility.Visible)
            {
                login_username.Text = "";
                login_password.Password = "";
                login_invalid_txt.Visibility = Visibility.Hidden;

                signup_username.Text = "";
                signup_password.Password = "";
                signup_email.Text = "";
                signup_invalid_txt.Visibility = Visibility.Hidden;
            }
        }

        private void Main_menu_change_btn_Click(object sender, RoutedEventArgs e)
        {
            logo_image.Visibility = Visibility.Hidden;
            ChangeMenu((sender as Button).Name.Replace("_btn", ""));
        }

        private void quit_user_btn_Click(object sender, RoutedEventArgs e)
        {
            client.Send(RequestType.SIGNOUT);
            quit_btn_Click(sender, e);
        }

        private void logout_uibtn_Click(object sender, RoutedEventArgs e)
        {
            client.Send(RequestType.SIGNOUT);
            client.Recieve();
            username_sp.Visibility = Visibility.Hidden;

            ChangeMenu("welcome_menu");
        }

        // CREATE ROOM MENU FUNCTIONS

        private void create_room_menu_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            for(int time = 30; time <= 180; time += 30)
            {
                create_room_choose_time_cb.Items.Add($"{time} seconds");
            }

            for(int players = 2; players <= 20; players++)
            {
                create_room_max_players_cb.Items.Add($"{players} players");
            }

            for(int questions = 5; questions <= 10; questions++)
            {
                create_room_questions_count_cb.Items.Add($"{questions} questions");
            }
        }

        private void create_room_btn_Click(object sender, RoutedEventArgs e)
        {
            if(create_room_name_txt.Text == String.Empty || create_room_choose_time_cb.Text == String.Empty || create_room_max_players_cb.Text == String.Empty || create_room_questions_count_cb.Text == String.Empty)
            {
                ErrorWindow window = new ErrorWindow("Create Room Error", "One or more of the fields are invalid!");
                window.ShowDialog();
                return;
            }

            int maxUsers = int.Parse(create_room_max_players_cb.Text.Replace(" players", ""));
            int questionsCount = int.Parse(create_room_questions_count_cb.Text.Replace(" questions", ""));
            int answerTimeout = int.Parse(create_room_choose_time_cb.Text.Replace(" seconds", ""));

            Room room = new Room(create_room_name_txt.Text, maxUsers, questionsCount, answerTimeout);
            client.Send(RequestType.CREATE_ROOM, JsonConvert.SerializeObject(room, Formatting.Indented));

            string response = client.Recieve();
            int status = JsonConvert.DeserializeObject<Status>(response).status;

            if(status == 0)
            {
                ErrorWindow window = new ErrorWindow("Create Room Error", "Something went wrong while creating this room.");
                window.ShowDialog();
            }
            else
            {
                // Switch to the room
            }
        }

        // JOIN ROOM FUNCTIONS

        private void join_room_menu_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            if(join_room_menu.Visibility == Visibility.Visible)
            {
                client.Send(RequestType.GET_ROOMS);

                string response = client.Recieve();
                room_list_view.DataContext = JsonConvert.DeserializeObject<RoomList>(response).getRooms();
            }
        }

        private void room_list_view_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if ((sender as ListView).SelectedItem == null)
                return;

            Room room = (sender as ListView).SelectedItem as Room;
            client.Send(RequestType.JOIN_ROOM, JsonConvert.SerializeObject(new RoomId(room.roomId), Formatting.Indented));

            string response = client.Recieve();
            int status = JsonConvert.DeserializeObject<Status>(response).status;

            if (status == 0)
            {
                ErrorWindow window = new ErrorWindow("Join Room", "An error occurred while trying to join the room! Please try again");
                window.ShowDialog();
            }
            else
            {
                // Switch to the room
            }
        }
    }
}
