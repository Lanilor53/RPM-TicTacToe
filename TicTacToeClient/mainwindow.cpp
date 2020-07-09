#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include "connectdialog.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  // Net
  this->client = new TicTacToeClient();
  // UI
  ui->setupUi(this);
  MainWindow::adjustSize();
  MainWindow::setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowCloseButtonHint|Qt::MSWindowsFixedSizeDialogHint);
  MainWindow::setWindowTitle("TicTacToe");
  initViews();


}

MainWindow::~MainWindow()
{
  delete ui;
}
// It was painful :(
void MainWindow::initViews(){
    views.append(ui->graphicsView);
    views.append(ui->graphicsView_2);
    views.append(ui->graphicsView_3);
    views.append(ui->graphicsView_4);
    views.append(ui->graphicsView_5);
    views.append(ui->graphicsView_6);
    views.append(ui->graphicsView_7);
    views.append(ui->graphicsView_8);
    views.append(ui->graphicsView_9);
    int id = 1;
    for (QGraphicsView * el: this->views){
        PaintScene * scene = new PaintScene(id);
        el->setScene(scene);
        el->setSceneRect(0,0,79,79);
        el->setMinimumSize(60, 60);
        el->setFixedSize(81, 81);
        QObject::connect(scene,
                         SIGNAL(sendField(int,int,int,bool)),
                         this->client,
                         SLOT(sendMessage(int, int, int, bool)
                         )
              );
        QObject::connect(this->client,
                         SIGNAL(gotMessage(int,int,int,bool)),
                         scene,
                         SLOT(drawAt(int, int, int, bool)
                         )
              );
        QObject::connect(this->client,
                         SIGNAL(gotClear()),
                         this,
                         SLOT(clearViews()
                         )
              );

        id +=1;
    }
}

void MainWindow::clearViews()
{
      for (QGraphicsView * el: this->views){
        el->scene()->clear();
      }
}


void MainWindow::on_actionConnect_triggered(){
    ConnectDialog* connectDialog = new ConnectDialog(this);
    QObject::connect(connectDialog,
                     SIGNAL(sendParamsSignal(QString, QString, QString)),
                     this->client,
                     SLOT(connectToServer(QString, QString, QString)
                     )
          );
    connectDialog->open();
}
