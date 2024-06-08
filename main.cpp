#include <iostream>
#include <vector>
#include <chrono>//به خاطر تابع رندوم و ایجاد وقفه
#include <random>//به خاطر تابع رندوم
#include <cstdlib>//به خاطر تابع سیستم
#include <thread>//به خاطر ایجاد وقفه 
//#include <future>
using namespace std;
int random1(int x, int y);
class game
{
        string arr[5][6];
        vector <string> subject;
    public:
        void reading_subject();//خواندن موضوعات از سایت و ذخیره سازی آنها در فضای محلی
        void one_player();//دستورات لازم برای اجرای بازی به صورت تک نفره
        void two_players();//دستورات لازم برای اجرای بازی به صورت دو نفره
        void reading_questions(int l, int s,int n);//خواندن سوالات با سختی ال  و موضوع اس
}a;//تعریف یک متغیر برای دسترسی به اعضای کلاس
int main()
{
    a.reading_subject();
    int n;//تعداد بازیکنان
    while (true)
    {
        cin>>n;
        if (n==1)
            a.one_player();
        else if (n==2)
            a.two_players();
        else break;
    }
    return 0;
}
void game:: reading_subject()
{
    //ذخیره سازی موضوعات سایت در متغیر وکتور به نامsubject
}
void game:: one_player()
{
    int l,s,f=0;// سطح سختی سوالات و موضوع سوالات
    cin>>l;
    while (f<3)
    {
        s=random1(0,subject.size()-1);//زمانی که بازی به صورت تک نفره در حال برگزاری است ، موضوع باید به صورت رندوم انتخاب شود
        cin>>l;
        reading_questions(l,s,1);
    }
}
void game:: two_players()
{
    int l,su,sc1=0,sc2=0,t1=0,t2=0,x;// سطح سختی سوالات و موضوع سوالات
    for (int i=0;i<4;i++)
    {
        t1=0,t2=0;
        if (i%2==0)
        {
            cout<<"It is the turn of the first player:\n"<<"Determine the difficulty of this round:   (hard: 3, medium: 2, easy: 1)\n";
            cin>>l;
            cout<<"Determine the topic of this round:\n";
            for (int j=0;j<subject.size();j++)
                cout<<subject[j]<<" : "<<j<<"\n";
            cin>>su;
            reading_questions(l,su,5);
        }
        system ("cls");//پاک کردن cmd
        //نمایش سوالات و دریافت پاسخ ها و ثبت تعداد پاسخ های صحیح بازیکن اول
        for (int j=0;j<5;j++)
        {
            cout<<arr[j][0]<<"\n1)"<<arr[j][1]<<"\n2)"<<arr[j][2]<<"\n3)"<<arr[j][3]<<"\n4)"<<arr[j][4]<<"\n";
            cin>>x;
            if (arr[j][5]==arr[j][x])
            {
                t1++;
                cout<<"Your answer was correct.\n";
            }
            else cout<<"Your answer was wrong.    The option of "<<arr[j][5]<<" was correct.\n";
        }
        this_thread::sleep_for(std::chrono::seconds(3));//ایجاد وقفه سه ثانیه ای
        system ("cls");
        //نمایش سوالات و دریافت پاسخ ها و ثبت تعداد پاسخ های صحیح بازیکن دوم
        for (int j=0;j<5;j++)
        {
            cout<<arr[j][0]<<"\n1)"<<arr[j][1]<<"\n2)"<<arr[j][2]<<"\n3)"<<arr[j][3]<<"\n4)"<<arr[j][4]<<"\n";
            cin>>x;
            if (arr[j][5]==arr[j][x])
            {
                t2++;
                cout<<"Your answer was correct.\n";
            }
            else cout<<"Your answer was wrong.    The option of "<<arr[j][5]<<" was correct.\n";
        }
        this_thread::sleep_for(std::chrono::seconds(3));//ایجاد وقفه سه ثانیه ای
        system ("cls");
        if (t1>t2)
        {
            sc1++;
            cout<<"The score of this round went to the first player\n";
        }
        else if (t1<t2)
        {
            sc2++;
            cout<<"The score of this round went to the second player\n";
        }
        else 
        {
            sc1++;
            sc2++;
            cout<<"The points of this round went to both players.\n";
        }
        if (i%2==0)
        {
            cout<<"It is the turn of the second player:\n"<<"Determine the difficulty of this round:   (hard: 3, medium: 2, easy: 1)\n";
            cin>>l;
            cout<<"Determine the topic of this round:\n";
            for (int j=0;j<subject.size();j++)
                cout<<subject[j]<<" : "<<j<<"\n";
            cin>>su;
            reading_questions(l,su,5);
        }
    }
    if (sc1==sc2)
    {
        while (sc1==sc2)
        {
            t1=0,t2=0;
            su=random1(0,subject.size()-1);
            l=random1(1,3);
            reading_questions(l,su,5);
            system("cls");
            //نمایش سوالات و دریافت پاسخ ها و ثبت تعداد پاسخ های صحیح بازیکن اول
            system("cls");
            //نمایش سوالات و دریافت پاسخ ها و ثبت تعداد پاسخ های صحیح بازیکن دوم
            if (t1>t2)
                sc1++;
            else if (t1<t2)
                sc2++;
            else 
            {
                sc1++;
                sc2++;
            }
        }
    }
}
void game:: reading_questions(int l, int s,int n)
{
    if (l==1)
        ;
    else if (l==2)
        ;
    else if (l==3)
        ;
}
int random1(int x, int y)//تابعی برای دریافت اعداد رندوم در بازه دلخواه
{
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
    uniform_int_distribution<int> distribution(x, y);
    int random_number = distribution(generator);
    return random_number;
}