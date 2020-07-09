#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>
#include "TicTacToeServer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  // UI
  void addUser(QString username);
  void delUser(QString username);
  void clearUsers();
  // Server
  void startServer();
  void stopServer();
private:
  Ui::MainWindow *ui;
  QMap<QString, QListWidgetItem*> users;
  TicTacToeServer *server;
};
#endif // MAINWINDOW_H
