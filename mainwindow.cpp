#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QApplication"
#include "qmessagebox.h"
#include "one_player.h"
#include "two_players.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("بازی گروه ما!");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QMessageBox *msg= new QMessageBox();
    msg->setText("خروج از برنامه!");
    msg->setInformativeText("آیا می‌خواهید\nاز برنامه خارج شوید؟");
    msg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg->setIcon(QMessageBox::Question);
    int result = msg->exec();
    switch (result) {
    case QMessageBox::Yes:
         QApplication::exit();
        break;
    case QMessageBox::No:
        break;
    }
}


void MainWindow::on_pushButton_1_clicked()
{
    one_player *One= new one_player();
    One->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    two_players *Two = new two_players();
    Two->show();
}

