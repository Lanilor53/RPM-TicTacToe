#include "client.h"
#include <QLabel>
#include <QDebug>
#include <QHostAddress>
#include <QErrorMessage>



void TicTacToeClient::readMessage()
{
  QByteArray buffer = socket->read(sizeof(int)*3+sizeof(bool));
  // Reverse endianness
  std::reverse(buffer.begin(), buffer.end());
  QDataStream ds(buffer);
  int id, x, y;
  bool finish;
  ds >> finish;
  ds >> y;
  ds >> x;
  ds >> id;
  qDebug() << "[CLIENT] readMessage id, x, y, finish: " << id << ' ' << x << ' ' << y << ' ' << finish << endl;
  if(id==10){
    emit gotClear();
  }else{
    emit gotMessage(id, x, y, finish);
  }
}


void TicTacToeClient::connectToServer(QString username, QString host, QString port)
{
  // TODO: test memory leak protection
  if(this->socket == nullptr){
    this->socket = new QTcpSocket(this);
  }
  this->username = username;
  this->socket->connectToHost(host,port.toInt());
  if(socket->waitForConnected(3000)){
    QObject::connect(this->socket,
                     SIGNAL(readyRead()),
                     this,
                     SLOT(readMessage())
          );
    QObject::connect(this->socket,
                     SIGNAL(disconnected()),
                     this,
                     SLOT(disconnected())
          );
    socket->write(username.toLocal8Bit().data(),64);
    socket->waitForBytesWritten(300);

  }else{
    QErrorMessage* error = new QErrorMessage();
    error->showMessage("Connection failed...");
  }

}


void TicTacToeClient::sendMessage(int id, int x, int y, bool finish)
{

  if(this->socket != nullptr and this->socket->state() == QTcpSocket::ConnectedState){
    socket->write(reinterpret_cast<char*>(&id),sizeof(int));
    socket->write(reinterpret_cast<char*>(&x),sizeof(int));
    socket->write(reinterpret_cast<char*>(&y),sizeof(int));
    socket->write(reinterpret_cast<char*>(&finish),sizeof(bool));

    socket->waitForBytesWritten(300);
 }
}

void TicTacToeClient::disconnected()
{
  qDebug() << "disconnected";
  emit clientDisconnected();
}

void TicTacToeClient::disconnectClient()
{
  this->socket->disconnectFromHost();
}
