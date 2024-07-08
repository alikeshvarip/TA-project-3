#include "one_player.h"
#include "ui_one_player.h"
#include "QTimer"
#include "qmessagebox.h"
#include "QApplication"
#include "game1.h"

one_player::one_player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::one_player)
{
    ui->setupUi(this);
    setWindowTitle("بازی یک نفره");


}

one_player::~one_player()
{
    delete ui;
}

void one_player::on_pushButton_clicked()
{
    if (ui->comboBox->currentText()=="easy")//داخل پرانتز کدی بنویس که اگر کاربر آسان رو انتخاب کرده بود شرط اجرا بشه
        a1.button_3("easy");
    else if(ui->comboBox->currentText()=="meduim")//داخل پرانتز شرطی رو بنویس که اگر کاربر مدیوم رو انتخاب کرده بود شرط اجرا بشه
        a1.button_3("medium");
    else if(ui->comboBox->currentText()=="hard")//داخل پرانتز چیزی بنویس که اگر کاربر هارد رو انتخاب کرده بود شرط اجرا بشه
        a1.button_3("hard");
    //QTimer *time= new QTimer();

    ui->label->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->frame->setEnabled(true);
    write1();
}


void one_player::on_pushButton_2_clicked()
{
    QMessageBox *msg= new QMessageBox();
    msg->setText("خروج از بازی یک نفره!");
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


void one_player::on_pushButton_3_clicked()
{
        write1();
        int i;
        if(ui->radioButton_1->isChecked())
            i=1;
        else if(ui->radioButton_2->isChecked())
            i=2;
        else if(ui->radioButton_3->isChecked())
            i=3;
        else if(ui->radioButton_4->isChecked())
            i=4;
        else i=0;
        string x=a1.arr[a1.pp][i];//i همون شماره گزینه انتخاب شده هست
        if(a1.button_5(1,x))
            write1();
        else {
            close();
        QMessageBox *msg = new QMessageBox;//میتونی اینجا کدی بنویسی که نتیجه رو مثل تعداد سوالات درست و تعداد سوالات غلط رو بهش نشون بده
        msg->setText("شما باختید!");
        msg->show();
        }
        //a1.pp تعداد سوالات پرسیده شده هست
        //a1.trueAnswer تعداد سوالاتی که به آنها پاسخ درست داده شده است
        //a1.falseAnswer تعداد سوالاتی که به آنها پاسخ غلط داده شده است
}

void one_player::write1 ()
{
        //محتویاتی برای درج کردن سوال و گزینه های جدید
        ui->label_2->setText(QString::fromStdString(a1.arr[a1.pp][0]));//a1.arr[a1.pp][0] در قسمت سوال
        ui->radioButton_1->setText(QString::fromStdString(a1.arr[a1.pp][1]));
        ui->radioButton_2->setText(QString::fromStdString(a1.arr[a1.pp][2]));
        ui->radioButton_3->setText(QString::fromStdString(a1.arr[a1.pp][3]));
        ui->radioButton_4->setText(QString::fromStdString(a1.arr[a1.pp][4]));
        //a2.arr[a1.pp][1] در قسمت گزینه ۱
        //....
        //a2.arr[a1.pp][4] در قسمت گزینه ۴
}

