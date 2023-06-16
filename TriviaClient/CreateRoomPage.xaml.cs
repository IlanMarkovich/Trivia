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
    /// Interaction logic for CreateRoomPage.xaml
    /// </summary>
    public partial class CreateRoomPage : Page
    {
        public readonly int MIN_TIME = 30, MAX_TIME = 180, TIME_SPACE = 30;
        public readonly int MIN_PLAYERS = 2, MAX_PLAYERS = 20;
        public readonly int MIN_QUESTIONS = 5, MAX_QUESTIONS = 10;
        public readonly int MAX_ROOM_NAME_LENGTH = 25;

        public CreateRoomPage()
        {
            InitializeComponent();

            // Setting value for comboboxes
            for (int time = MIN_TIME; time <= MAX_TIME; time += TIME_SPACE)
            {
                create_room_choose_time_cb.Items.Add($"{time} seconds");
            }

            for (int players = MIN_PLAYERS; players <= MAX_PLAYERS; players++)
            {
                create_room_max_players_cb.Items.Add($"{players} players");
            }

            for (int questions = MIN_QUESTIONS; questions <= MAX_QUESTIONS; questions++)
            {
                create_room_questions_count_cb.Items.Add($"{questions} questions");
            }
        }

        private void create_room_btn_Click(object sender, RoutedEventArgs e)
        {
            if (AreRoomDetailsInvalid())
            {
                ErrorWindow window = new ErrorWindow("Create Room Error", "One or more of the fields are invalid!");
                window.ShowDialog();
                return;
            }

            int maxUsers = int.Parse(create_room_max_players_cb.Text.Replace(" players", ""));
            int questionsCount = int.Parse(create_room_questions_count_cb.Text.Replace(" questions", ""));
            int answerTimeout = int.Parse(create_room_choose_time_cb.Text.Replace(" seconds", ""));

            Room room = new Room(create_room_name_txt.Text, maxUsers, questionsCount, answerTimeout);
            MainWindow.client.Send(RequestType.CREATE_ROOM, JsonConvert.SerializeObject(room, Formatting.Indented));

            string response = MainWindow.client.Recieve().Value;
            int status = JsonConvert.DeserializeObject<Status>(response).status;

            if (status == 0)
            {
                ErrorWindow window = new ErrorWindow("Create Room Error", "Something went wrong while creating this room.");
                window.ShowDialog();
            }
            else
            {
                MainWindow.mainFrame.Navigate(new RoomPage(true));
            }
        }

        private bool AreRoomDetailsInvalid()
        {
            return create_room_name_txt.Text == String.Empty || create_room_name_txt.Text.Length > MAX_ROOM_NAME_LENGTH || create_room_choose_time_cb.Text == String.Empty || create_room_max_players_cb.Text == String.Empty || create_room_questions_count_cb.Text == String.Empty;
        }

        private void main_menu_back_btn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow.mainFrame.Navigate(new MainMenuPage());
        }
    }
}
