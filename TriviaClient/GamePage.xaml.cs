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
using System.Windows.Threading;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for GamePage.xaml
    /// </summary>
    public partial class GamePage : Page
    {
        private readonly int DID_NOT_ANSWER = -1;

        private DispatcherTimer timer;
        private int startTime;
        private int time;

        public GamePage(int startTime)
        {
            InitializeComponent();
            getQuestion();

            this.startTime = startTime;
            time = startTime;

            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += Timer_Tick;
            timer.Start();
        }

        private void getQuestion()
        {
            // Gets the question
            MainWindow.client.Send(RequestType.GET_QUESTION);
            string response = MainWindow.client.Recieve().Value;

            // Sets the current question
            Question question = JsonConvert.DeserializeObject<Question>(response);
            question_txt.Text = question.question;

            List<Button> buttons = new List<Button>{ ans_1_btn, ans_2_btn, ans_3_btn, ans_4_btn };
            List<string> answers = question.getAnswers();

            // Sets the content of the answer buttons as the answers recieved from the server
            for(int i = 0; i < buttons.Count; i++)
            {
                buttons[i].Content = answers[i];
            }
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            // If the time ran out
            if(time == 0)
            {
                string sendData = JsonConvert.SerializeObject(new SubmitAnswer(DID_NOT_ANSWER, startTime - time));
                MainWindow.client.Send(RequestType.SUBMIT_ANSWER, sendData);

                // Because the client already knows that the answer id (DID_NOT_ANSWER) isn't correct
                // the client just recieves the server's response and doesn't do anything with it
                MainWindow.client.Recieve();

                getQuestion();
                return;
            }

            time--;
        }
    }
}
