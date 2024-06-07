#include <iostream>
#include <vector>
using namespace std;
class game
{
    public:
    void reading_subject();
    void one_player();
    void reading_questions(int l, int s);
}a;
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
        ;
    }
    cout<<"seraj\n";
    return 0;
}
void game:: reading_subject()
{

}
void game:: one_player()
{
    int l,s;// سطح سختی سوالات و موضوع سوالات
    cin>>l>>s;
    reading_questions(l, s);
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