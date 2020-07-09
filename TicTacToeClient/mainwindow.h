#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "paintscene.h"
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void initViews();
private:
  TicTacToeClient * client;
  QList <QGraphicsView *> views;
  Ui::MainWindow *ui;
  bool isOpen;
public slots:
  void clearViews();
private slots:
  void on_actionConnect_triggered();
};
#endif // MAINWINDOW_H
