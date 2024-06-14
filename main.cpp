#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>  //به خاطر تابع رندوم و ایجاد وقفه
#include <random>  //به خاطر تابع رندوم
#include <cstdlib> //به خاطر تابع سیستم
#include <thread>  //به خاطر ایجاد وقفه
// #include <future>
using namespace std;

int random1(int x, int y);

class game
{
    string arr[5][6];
    vector<string> subject;
    int category;      // موضوع سوال. باید عدد باشد و عددی به سایت ارسال شود
    string difficulty; // سختی سوال
    bool is_randomCategory, is_randomDifficulty; // متغیرهایی که سیو میکنند آیا سطح و موضوع سوال باید رندوم انتخاب شود یا خیر

public:
    void reading_subject(); // خواندن موضوعات از سایت و ذخیره سازی آنها در فضای محلی
    void one_player();      // دستورات لازم برای اجرای بازی به صورت تک نفره
    void two_players();     // دستورات لازم برای اجرای بازی به صورت دو نفره
    int show_questionsOne(int j);
    int show_questionsTwo();
    bool reading_questions(); // خواندن سوالات
} a;                          // تعریف یک متغیر برای دسترسی به اعضای کلاس

int main()
{
    a.reading_subject();
    int n; // تعداد بازیکنان
    while (true)
    {
        cin >> n;
        if (n == 1)
            a.one_player();
        else if (n == 2)
            a.two_players();
        else
            break;
    }
    return 0;
}

void game::reading_subject() // ذخیره سازی موضوعات سایت در وکتور
{
    int index1 = 0, index2 = 0, index3 = 0;
    string line, s;

    system("curl -o subjects.json https://opentdb.com/api_category.php");
    
    fstream subjects("subjects.json");
    getline(subjects, line);
    while (true)
    {
        index1 = line.find("name", index1);
        if (index1 == -1)
            break;
        index2 = line.find("\"", index1 + 5);
        index3 = line.find("\"", index2 + 1);
        subject.push_back(line.substr(index2 + 1, index3 - index2 - 1));
        index1 = index3;
    }
}

void game::one_player()
{
    is_randomDifficulty = false;
    is_randomCategory = true; // زمانی که بازی به صورت تک نفره در حال برگزاری است ، موضوع باید به صورت رندوم انتخاب شود
    int falseAnswer = 0, trueAnswer = 0, playerAnswer, j = 0;
    //cin >> difficulty; // دریافت سختی سوال
    while (falseAnswer < 3)
    {
        if (j%5 == 0)
        {
            if (!reading_questions())
            {
                cout << "error! can not reading qoestions from trivia";
                exit(0);
            }  
            j = 0;
        }

        if (show_questionsOne(j++) == 0)
            falseAnswer++;
        else
            trueAnswer++;
    }
    cout << trueAnswer;
}

void game::two_players()
{
    int score1 = 0, score2 = 0, trueAnswer1 = 0, trueAnswer2 = 0, playerAnswer;
    is_randomCategory = false;
    for (int i = 0; i < 4; i++)
    {
        trueAnswer1 = 0, trueAnswer2 = 0;
        if (i % 2 == 0)
        {
            cout << "It is the turn of the first player:\n"
                 << "Determine the difficulty of this round: (hard: 3, medium: 2, easy: 1)\n";
            // cin >> difficulty;
            cout << "Determine the topic of this round:\n";
            for (int j = 0; j < subject.size(); j++)
                cout << subject[j] << " : " << j << "\n";
            // cin >> category;   
        }
        else
        {
            cout << "It is the turn of the second player:\n"
                 << "Determine the difficulty of this round:   (hard: 3, medium: 2, easy: 1)\n";
            // cin >> difficulty;
            cout << "Determine the topic of this round:\n";
            for (int j = 0; j < subject.size(); j++)
                cout << subject[j] << " : " << j << "\n";
            // cin >> category;
        }
        if (!reading_questions())
        {
            cout << "error! can not reading qoestions from trivia";
            exit(0);
        } 

        system("cls"); // پاک کردن cmd

        // نمایش سوالات و دریافت پاسخ ها و ثبت تعداد پاسخ های صحیح بازیکن اول
        trueAnswer1 = show_questionsTwo();

        this_thread::sleep_for(std::chrono::seconds(3)); // ایجاد وقفه سه ثانیه ای
        system("cls");

        // نمایش سوالات و دریافت پاسخ ها و ثبت تعداد پاسخ های صحیح بازیکن دوم
        trueAnswer2 = show_questionsTwo();

        this_thread::sleep_for(std::chrono::seconds(3)); // ایجاد وقفه سه ثانیه ای
        system("cls");

        if (trueAnswer1 > trueAnswer2)
        {
            score1++;
            cout << "The score of this round went to the first player\n";
        }
        else if (trueAnswer1 < trueAnswer2)
        {
            score2++;
            cout << "The score of this round went to the second player\n";
        }
        else
        {
            score1++;
            score2++;
            cout << "The points of this round went to both players.\n";
        }
        /* if (i % 2 == 0)
        {
            cout << "It is the turn of the second player:\n"
                 << "Determine the difficulty of this round:   (hard: 3, medium: 2, easy: 1)\n";
            // cin >> difficulty;
            cout << "Determine the topic of this round:\n";
            for (int j = 0; j < subject.size(); j++)
                cout << subject[j] << " : " << j << "\n";
            // cin >> category;
            reading_questions();
        }*/ 
    }
    if (score1 == score2)
    {
        while (score1 == score2)
        {
            int j = 0;
            trueAnswer1 = 0, trueAnswer2 = 0;
            is_randomCategory = true;
            is_randomDifficulty = true;
            
            if (j%5 == 0)
            {
                if (!reading_questions())
                {
                    cout << "error! can not reading qoestions from trivia";
                    exit(0);
                } 
                j = 0;
            }
            
            system("cls");

            trueAnswer1 = show_questionsOne(j);

            system("cls");
            
            trueAnswer2 = show_questionsOne(j++);
            
            if (trueAnswer1 > trueAnswer2)
                score1++;
            else if (trueAnswer1 < trueAnswer2)
                score2++;
            else
            {
                score1++;
                score2++;
            }
        }
    }
    else
    {
        if (score1 > score2)
            cout << "the first player is barandeh";
        else
            cout << "the second player is barandeh";
    }
}

int game::show_questionsOne(int j)
{
    int playerAnswer, trueAnswer = 0;
    cout << arr[j][0] << "\n1)" << arr[j][1] << "\n2)" << arr[j][2] << "\n3)" << arr[j][3] << "\n4)" << arr[j][4] << "\n";
    cin >> playerAnswer;
    if (arr[j][5] == arr[j][playerAnswer])
    {
        trueAnswer++;
        cout << "Your answer was correct.\n";
    }
    else
        cout << "Your answer was wrong.    The option of " << arr[j][5] << " was correct.\n";
    return trueAnswer;
}

int game::show_questionsTwo()
{
    int playerAnswer, trueAnswer = 0;
    for (int j = 0; j < 5; j++)
    {
        cout << arr[j][0] << "\n1)" << arr[j][1] << "\n2)" << arr[j][2] << "\n3)" << arr[j][3] << "\n4)" << arr[j][4] << "\n";
        cin >> playerAnswer;
        if (arr[j][5] == arr[j][playerAnswer])
        {
            trueAnswer++;
            cout << "Your answer was correct.\n";
        }
        else
            cout << "Your answer was wrong.    The option of " << arr[j][5] << " was correct.\n";
    }
    return trueAnswer;
}

bool game::reading_questions()
{
    string cmd = "curl -o questions.json \"https://opentdb.com/api.php?amount=5";
    if (!is_randomCategory)
        cmd += "&category=" + to_string(category);
    if (!is_randomDifficulty)
        cmd += "&difficulty=" + difficulty;
    cmd += "&type=multiple\"";
    system(cmd.c_str());

    string line, question, correctAnswer, incorrectAnswers[3];
    int index1 = 0, index2 = 0, index3 = 0, index4 = 0, index5 = 0, j = 0;
    fstream Qestions("questions.json");
    getline(Qestions, line);

    if (line.substr(line.find(":", 0) + 1, 1) != "0")
        return false;

    while (true)
    {
        index1 = line.find("question", index3);
        if (index1 == -1)
            break;
        index2 = line.find("correct_answer", index1);
        index3 = line.find("incorrect_answers", index2);
        index4 = index3 + 19;
        question = line.substr(index1 + 11, (index2 - 4) - (index1 + 10));
        correctAnswer = line.substr(index2 + 17, (index3 - 4) - (index2 + 16));
        for (int i = 0; i < 3; i++)
        {
            index4 = line.find("\"", index4 + 1);
            index5 = line.find("\"", index4 + 1);
            incorrectAnswers[i] = line.substr(index4 + 1, (index5 - index4 - 1));
            index4 = index5; 
        }
        
        // چینش تصادفی گزینه در آرایه
        int in1 = 0, in2 = 0, in3 = 0, in4 = 0;
        in1 = random1(1, 4);
        in2 = random1(1, 4);
        while (in1 == in2)
            in2 = random1(1, 4);
        in3 = random1(1, 4);
        while (in2 == in3 || in1 == in3)
            in3 = random1(1, 4);
        in4 = random1(1, 4);
        while (in3 == in4  || in2 == in4  || in1 == in4)
            in4 = random1(1, 4);
        arr[j][0] == question;
        arr[j][in1] == incorrectAnswers[0];
        arr[j][in2] == incorrectAnswers[1];
        arr[j][in3] == incorrectAnswers[2];
        arr[j][in4] == correctAnswer;
        arr[j++][5] == correctAnswer;
    }
    return true;
}

int random1(int x, int y) // تابعی برای دریافت اعداد رندوم در بازه دلخواه
{
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
    uniform_int_distribution<int> distribution(x, y);
    int random_number = distribution(generator);
    return random_number;
}