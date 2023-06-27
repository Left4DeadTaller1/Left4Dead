#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QUrl>
#include "create.h"
#include "join.h"
#include <iostream>
#include "client_game_state.h"
#include "client/client_connection/client_protocol.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ClientProtocol& protocol, QWidget *parent = nullptr);
    std::string getNamePlayer(void);
    TypeMap_t getTypeMap(void);
    ~MainWindow();

private slots:
    void createButtonClicked();
    void joinButtonClicked();
    void sliderChanged(int value);
    void handleCreateClosed(int code);
    void handleJoinClosed(int code);
    TypeMap_t StringToTypeMap(const std::string& map);
    TypeWeapon_t StringToTypeWeapon(const std::string& weaponPlayer);
    void handlerTypeMap(const QString& typeMap);

signals:
    void exitApp(int exitCode);

private:
    ClientProtocol& protocol;
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    Create *c;
    Join *j;
    std::string namePlayer;
    TypeMap_t typeMap;
};
#endif // MAINWINDOW_H
