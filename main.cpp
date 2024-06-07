#include <iostream>
#include <vector>
using namespace std;

void reading_questions(int l, int s);
int main()
{
    int n;//تعداد بازیکنان
    while (true)
    {
        cin>>n;
        if (n==1)
        one_player();
        else if (n==2)
        ;
    }
    cout<<"seraj\n";
    return 0;
}
void one_player()
{
    int l,s;// سطح سختی سوالات و موضوع سوالات
    cin>>l>>s;
    reading_questions(l, s);
}
void reading_questions(int l, int s)
{
    if (l==1)
    ;
    else if (l==2)
    ;
    else if (l==3)
    ;
}