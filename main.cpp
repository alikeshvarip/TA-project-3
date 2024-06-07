#include <iostream>
#include <vector>
using namespace std;
class game
{
    vector <string> subject;
    public:
    void reading_subject();//خواندن موضوعات از سایت و ذخیره سازی آنها در فضای محلی
    void one_player();//دستورات لازم برای اجرای بازی به صورت تک نفره
    void two_players();//دستورات لازم برای اجرای بازی به صورت دو نفره
    void reading_questions(int l, int s);//خواندن سوالات با سختی ال  و موضوع اس
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
    int l;// سطح سختی سوالات
    cin>>l;
    reading_questions(l,-1);
}
void game:: two_players()
{
    int l,s;// سطح سختی سوالات و موضوع سوالات
    cin>>l>>s;
    
}
void game:: reading_questions(int l, int s)
{
    if (l==1)
    ;
    else if (l==2)
    ;
    else if (l==3)
    ;
}