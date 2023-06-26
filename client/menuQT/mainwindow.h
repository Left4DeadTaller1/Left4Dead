#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "create.h"
#include "join.h"
#include <iostream>
#include "client/client_connection/client_protocol.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ClientProtocol& protocol, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createButtonClicked();
    void joinButtonClicked();
    void sliderChanged(int value);
    //void closeEvent(QCloseEvent *event);
    void handleCreateClosed(int code);
    void handleJoinClosed(int code);

signals:
    void exitApp(int exitCode);

private:
    ClientProtocol& protocol;
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    Create *c;
    Join *j;
};
#endif // MAINWINDOW_H
