#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>  //به خاطر تابع رندوم و ایجاد وقفه
#include <random>  //به خاطر تابع رندوم
#include <cstdlib> //به خاطر تابع سیستم
using namespace std;

int random1(int x, int y);

class game
{
	string arr[5][6];
	vector<string> subject;
	int category;       // موضوع سوال. باید عدد باشد و عددی به سایت ارسال شود
	string difficulty;                           // سختی سوال
	bool is_randomCategory, is_randomDifficulty; // متغیرهایی که سیو میکنند آیا سطح و موضوع سوال باید رندوم انتخاب شود یا خیر

public:
	int pp = 0, falseAnswer = 0, trueAnswer = 0;//تعداد سوالات پرسیده شده از کاربر یک نفره رو ثبت میکنه
	int pp1, pp2, trueAnswer2, score1, score2, round, trueAnswer1, winner;
	bool turn1, end_of_the_round, golden_round, nobat1;
	void reading_subject(); // خواندن موضوعات از سایت و ذخیره سازی آنها در فضای محلی
	bool reading_questions(); // خواندن سوالات
	void button_1();//دکمه بازی یک نفره
	void button_2();//دکمه بازی دو نفره
	void button_3(string l);//دکمه ok در پنجره انتخاب سطح سختی بازی یک نفره
	void button_4(string l, int s);//دکمه ok در پنجره انتخاب سطح سختی در بازی دونفره
	bool button_5(string b);
	int button_6(string b);
} a;                          // تعریف یک متغیر برای دسترسی به اعضای کلاس

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
	int index1 = 0, index2 = 0, index3 = 0, index4 = 0, index5 = 0;
	fstream Qestions("questions.json");
	getline(Qestions, line);

	if (line.substr(line.find(":", 0) + 1, 1) != "0")
		return false;

	for (int j = 0; true; j++)
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
		while (in3 == in4 || in2 == in4 || in1 == in4)
			in4 = random1(1, 4);
		arr[j][0] = question;
		arr[j][in1] = incorrectAnswers[0];
		arr[j][in2] = incorrectAnswers[1];
		arr[j][in3] = incorrectAnswers[2];
		arr[j][in4] = correctAnswer;
		arr[j][5] = correctAnswer;
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
//------------------------------------------------------------------
void game::button_1()
{
	reading_subject();
	is_randomDifficulty = false;
	is_randomCategory = true;
}
void game::button_3(string l)
{
	difficulty = l;
	reading_questions();
	pp = 0, falseAnswer = 0, trueAnswer = 0;
}
bool game::button_5(string b)
{
	if (b == arr[pp][5])
		trueAnswer++;
	else falseAnswer++;
	pp++;
	if (pp % 5 == 0)
	{
		pp = 0;
		reading_questions();
	}
	if (falseAnswer < 3)
		return true;
	else return false;
}
//-----------------------------------------------------------
void game::button_2()
{
	reading_subject();
	is_randomDifficulty = false;//از خودم
	is_randomCategory = false;
	nobat1 = true;
	score1 = 0, score2 = 0, round = 1, winner = 0;
}
void game::button_4(string l, int s)
{
	difficulty = l;
	category = s;
	reading_questions();
	pp1 = 0, pp2 = 0, trueAnswer1 = 0, trueAnswer2 = 0, turn1 = true, end_of_the_round = false;
}
int game::button_6(string b)
{
	end_of_the_round = false;
	if (turn1)
	{
		if (b == arr[pp1][5])
			trueAnswer1++;
		pp1++;
	}
	else
	{
		if (b == arr[pp2][5])
			trueAnswer2++;
		pp2++;
	}
	if (pp1 == 5 && pp2 == 0)
	{
		turn1 = false;
	}
	if (pp2 == 5 && pp1 == 5)
	{
		if (trueAnswer1 > trueAnswer2)
			score1++;
		else if (trueAnswer1 < trueAnswer2)
			score2++;
		else
		{
			score1++;
			score2++;
		}
		if (nobat1)
			nobat1 = false;
		else nobat1 = true;
		round++;
		end_of_the_round = true;
		if (round >= 4)
		{
			if (score1 > score2)
				winner = 1;
			else if (score1 < score2)
				winner = 2;
			else if (score1 == score2)
			{
				golden_round = true, is_randomDifficulty = true, is_randomCategory = true;
				reading_questions();
				pp1 = 0, pp2 = 0, trueAnswer1 = 0, trueAnswer2 = 0, turn1 = true;
			}
		}
	}
}