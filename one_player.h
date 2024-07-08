#ifndef ONE_PLAYER_H
#define ONE_PLAYER_H

#include <QWidget>

namespace Ui {
class one_player;
}

class one_player : public QWidget
{
    Q_OBJECT

public:
    explicit one_player(QWidget *parent = nullptr);
    ~one_player();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void write1();

private:
    Ui::one_player *ui;
};

#endif // ONE_PLAYER_H
