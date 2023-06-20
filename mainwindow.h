#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "client/actions/action_client.h"
#include "client/actions/action_create.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::shared_ptr<ActionClient>& startAction, QWidget *parent = nullptr);
    unsigned int getWinId() const;
    ~MainWindow();

private slots:
    void createButtonClicked();
    void joinButtonClicked();
    void sliderChanged(int value);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    std::shared_ptr<ActionClient>& startAction;
};

#endif // MAINWINDOW_H


