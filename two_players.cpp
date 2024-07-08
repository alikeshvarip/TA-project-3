#include "two_players.h"
#include "ui_two_players.h"
#include "qmessagebox.h"
#include "QApplication"
#include "QTimer"
#include <ctime>
#include "game2.h"

two_players::two_players(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::two_players)
{
    ui->setupUi(this);
    setWindowTitle("بازی دو نفره");

}

two_players::~two_players()
{
    delete ui;
}


QString np1;
QString np2;

void two_players::write()
{
    if (a2.turn1)
    {
    //محتویاتی برای درج کردن سوال و گزینه های جدید
    ui->label_11->setText(QString::fromStdString(a2.arr[a2.pp1][0]));
    ui->radioButton_1->setText(QString::fromStdString(a2.arr[a2.pp1][1]));
    ui->radioButton_2->setText(QString::fromStdString(a2.arr[a2.pp1][2]));
    ui->radioButton_3->setText(QString::fromStdString(a2.arr[a2.pp1][3]));
    ui->radioButton_4->setText(QString::fromStdString(a2.arr[a2.pp1][4]));
    }
    else
    {
        ui->label_11->setText(QString::fromStdString(a2.arr[a2.pp1][0]));
        ui->radioButton_1->setText(QString::fromStdString(a2.arr[a2.pp1][1]));
        ui->radioButton_2->setText(QString::fromStdString(a2.arr[a2.pp1][2]));
        ui->radioButton_3->setText(QString::fromStdString(a2.arr[a2.pp1][3]));
        ui->radioButton_4->setText(QString::fromStdString(a2.arr[a2.pp1][4]));
    }
    //دکمه های سوال یاید فعال شود تا کاربر بتواند جواب سوال را بدهد
}

void two_players::on_pushButton_5_clicked()
{
    QMessageBox *msg= new QMessageBox();
    msg->setText("خروج از بازی دو نفره!");
    msg->setInformativeText("آیا می‌خواهید\nاز بازی خارج شوید؟");
    msg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg->setIcon(QMessageBox::Question);
    int result = msg->exec();
    switch (result) {
    case QMessageBox::Yes:
         close();
        break;
    case QMessageBox::No:
        break;
    }
}


void two_players::on_pushButton_1_clicked()
{
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->label_3->setEnabled(false);
    ui->label_4->setEnabled(false);
    ui->pushButton_1->setEnabled(false);
    ui->comboBox_1->setEnabled(true);
    ui->label_1->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
}


void two_players::on_lineEdit_textChanged(const QString &arg1)
{
    np1 = arg1;
    ui->label_6->setText(arg1);
}


void two_players::on_lineEdit_2_textChanged(const QString &arg1)
{
    np2 = arg1;
    ui->label_7->setText(arg1);
}

void two_players::on_pushButton_2_clicked()
{
    a2.button_2();
    for (int i=0; i< sub_size; i++)
        ui->comboBox_2->addItem(QString::fromStdString(a2.subject.at(i)));
    ui->label_1->setEnabled(false);
    ui->comboBox_1->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->label_2->setEnabled(true);
    ui->comboBox_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
}


void two_players::on_pushButton_3_clicked()
{
    if (ui->comboBox_1->currentText()=="easy")
        a2.button_4("easy",ui->comboBox_2->currentIndex());
    else if (ui->comboBox_1->currentText()=="medium")
        a2.button_4("medium",ui->comboBox_2->currentIndex());
    else if (ui->comboBox_1->currentText()=="hard")
        a2.button_4("hard",ui->comboBox_2->currentIndex());
    write();
    ui->label_2->setEnabled(false);
    ui->comboBox_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->frame->setEnabled(true);
}


void two_players::on_pushButton_4_clicked()
{

    if (a2.turn1)
    {
        ui->label_10->setText(np1);
        if (ui->radioButton_1->isChecked())
        {
            string x=a2.arr[a2.pp1][1];//برای اینکه ارور نده ۱ نوشتم و گرنه باید شماره گزینه ای که کاربر انتخاب کرده رو به جای ۱ بنویسیم
            a2.button_6(1,x);
        }
        else if (ui->radioButton_2->isChecked())
        {
            string x=a2.arr[a2.pp1][2];//برای اینکه ارور نده ۱ نوشتم و گرنه باید شماره گزینه ای که کاربر انتخاب کرده رو به جای ۱ بنویسیم
            a2.button_6(1,x);
        }
        else if (ui->radioButton_3->isChecked())
        {
            string x=a2.arr[a2.pp1][3];//برای اینکه ارور نده ۱ نوشتم و گرنه باید شماره گزینه ای که کاربر انتخاب کرده رو به جای ۱ بنویسیم
            a2.button_6(1,x);
        }
        else if (ui->radioButton_4->isChecked())
        {
            string x=a2.arr[a2.pp1][4];//برای اینکه ارور نده ۱ نوشتم و گرنه باید شماره گزینه ای که کاربر انتخاب کرده رو به جای ۱ بنویسیم
            a2.button_6(1,x);
        }
    }
    else
    {
        ui->label_10->setText(np2);
        if (ui->radioButton_1->isChecked())
        {
            string x=a2.arr[a2.pp2][1];//برای اینکه ارور نده ۱ نوشتم و گرنه باید شماره گزینه ای که کاربر انتخاب کرده رو به جای ۱ بنویسیم
            a2.button_6(1,x);
        }
        else if (ui->radioButton_2->isChecked())
        {
            string x=a2.arr[a2.pp2][2];//برای اینکه ارور نده ۱ نوشتم و گرنه باید شماره گزینه ای که کاربر انتخاب کرده رو به جای ۱ بنویسیم
            a2.button_6(1,x);
        }
        else if (ui->radioButton_3->isChecked())
        {
            string x=a2.arr[a2.pp2][3];//برای اینکه ارور نده ۱ نوشتم و گرنه باید شماره گزینه ای که کاربر انتخاب کرده رو به جای ۱ بنویسیم
            a2.button_6(1,x);
        }
        else if (ui->radioButton_4->isChecked())
        {
            string x=a2.arr[a2.pp2][4];//برای اینکه ارور نده ۱ نوشتم و گرنه باید شماره گزینه ای که کاربر انتخاب کرده رو به جای ۱ بنویسیم
            a2.button_6(1,x);
        }
    }

    QMessageBox *m = new QMessageBox();
    if (a2.winner!=0)
    {
        //بازی خاتمه پیدا کرده و شماره بازیکن برنده در a2.winner ثبت شده است
        if (a2.winner==1){
           m->setText("بازیکن "+np1+" برنده شد!");
        m->exec();} else {m->setText("بازیکن "+np2+" برنده شد!");}
        close();
    }
    else if (a2.end_of_the_round)
    {
        if (!(a2.golden_round))
        {
            ui->pushButton_2->setEnabled(true);
            ui->comboBox_1->setEnabled(true);
            ui->label_1->setEnabled(true);
            ui->frame->setEnabled(false);
            if(a2.nobat1==1) {
                ui->label_10->setText(np1);
            }
            else {
                ui->label_10->setText(np2);
        }   // دوباره موضوع و سطح سختی را از کاربری که نوبت اوست بپرسد و اینکه نوبت چه کسی است را میتوان از a2.nobat1 فهمید، اگر درست باشد نوبت بازیکن ۱ است و اگر غلط باشد نوبت بازیکن ۲ است
        }
        else write();
    }
    else write();

}
