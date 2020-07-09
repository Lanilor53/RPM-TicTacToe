#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDebug>

void MainWindow::addUser(QString username)
{
  this->users.insert(username,new QListWidgetItem(QIcon(":/user/user.png"), username, ui->userListWidget));
}

void MainWindow::delUser(QString username)
{
  if(this->users.contains(username)){
    delete this->users.take(username);
  }
}

void MainWindow::clearUsers()
{
  QMap<QString, QListWidgetItem*>::iterator i;
  for (i = users.begin(); i != users.end(); ++i)
      delUser(i.key());
}

void MainWindow::startServer(){
  if(server==nullptr){
    this->server = new TicTacToeServer(QHostAddress::LocalHost, 0);
    QObject::connect(this->server,
                     SIGNAL(userConnected(QString)),
                     this,
                     SLOT(addUser(QString))
          );
    QObject::connect(this->server,
                     SIGNAL(userDisconnected(QString)),
                     this,
                     SLOT(delUser(QString))
          );
    ui->statusLabel->setText(QString("Status: running on port ") +server->getPort());
  }
  else{
    ui->statusbar->showMessage("Server already started!");
  }
}
void MainWindow::stopServer(){
  if(server==nullptr){
    ui->statusbar->showMessage("Server is not active!");
  }
  else{
    this->server->deleteLater();
    this->server = nullptr;
    this->clearUsers();
    ui->statusLabel->setText("Status: not running");
  }
}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  // INIT
  ui->setupUi(this);
  ui->dockWidget->setTitleBarWidget(new QWidget());
  QObject::connect(ui->startButton,
                   SIGNAL(pressed()),
                   this,
                   SLOT(startServer())
        );
  QObject::connect(ui->stopButton,
                   SIGNAL(pressed()),
                   this,
                   SLOT(stopServer())
        );

}

MainWindow::~MainWindow()
{
  delete ui;
}

