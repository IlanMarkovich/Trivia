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
        private int maxTime;
        private int time;
        private int questionsCount;
        private int correctAnswers;

        public GamePage(int maxTime, int questionsCount)
        {
            InitializeComponent();
            GetQuestion();

            this.maxTime = maxTime;
            time = 0;
            time_txt.Text = TimeSpan.FromSeconds(maxTime).ToString("mm\\:ss");

            this.questionsCount = questionsCount;
            questions_left_txt.Text = "Questions Left: " + questionsCount;
            questions_correct_txt.Text = "Correct Answers: 0";

            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += Timer_Tick;
            timer.Start();
        }

        private void GetQuestion()
        {
            // Gets the question
            MainWindow.client.Send(RequestType.GET_QUESTION);
            string response = MainWindow.client.Recieve().Value;

            Question question = JsonConvert.DeserializeObject<Question>(response);

            if(question.question == String.Empty)
            {
                MainWindow.mainFrame.Navigate(new GameResultsPage());
                return;
            }

            // Sets the current question
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
            if(time == maxTime)
            {
                MessageBox.Show("Time ran out!");

                string sendData = JsonConvert.SerializeObject(new SubmitAnswerRequest(DID_NOT_ANSWER, time));
                MainWindow.client.Send(RequestType.SUBMIT_ANSWER, sendData);

                // Because the client already knows that the answer id (DID_NOT_ANSWER) isn't correct
                // the client just recieves the server's response and doesn't do anything with it
                MainWindow.client.Recieve();

                time = 0;
                GetQuestion();
                return;
            }

            time++;
            time_txt.Text = TimeSpan.FromSeconds(maxTime - time).ToString("mm\\:ss");
        }

        private void ans_btn_Click(object sender, RoutedEventArgs e)
        {
            // Gets the answer id by the name of the button
            int answerId = int.Parse((sender as Button).Name.Replace("ans_", "").Replace("_btn", "")) - 1;

            string sendData = JsonConvert.SerializeObject(new SubmitAnswerRequest(answerId, time));
            MainWindow.client.Send(RequestType.SUBMIT_ANSWER, sendData);

            string response = MainWindow.client.Recieve().Value;
            SubmitAnswerResponse saResponse = JsonConvert.DeserializeObject<SubmitAnswerResponse>(response);

            if (saResponse.status == 0)
            {
                ErrorWindow window = new ErrorWindow("Answer Error", "An error occurred while submiting the answer");
                window.ShowDialog();

                return;
            }

            if (saResponse.correctAnswerId == answerId)
            {
                correctAnswers++;
            }

            // Update variable according to the answer
            time = 0;
            questionsCount--;
            questions_left_txt.Text = "Questions Left: " + questionsCount;
            questions_correct_txt.Text = "Correct Answers: " + correctAnswers;

            // Get the next question
            GetQuestion();
        }
    }
}
