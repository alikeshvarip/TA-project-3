#ifndef TWO_PLAYERS_H
#define TWO_PLAYERS_H

#include <QWidget>

namespace Ui {
class two_players;
}

class two_players : public QWidget
{
    Q_OBJECT

public:
    explicit two_players(QWidget *parent = nullptr);
    ~two_players();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_1_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void write();

private:
    Ui::two_players *ui;
};

#endif // TWO_PLAYERS_H
