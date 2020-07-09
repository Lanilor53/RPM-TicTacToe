#include "TicTacToeServer.h"
#include <QDataStream>

TicTacToeServer::TicTacToeServer(QHostAddress host, quint16 port, QObject *parent) : QObject(parent)
{
  this->server = new QTcpServer();
  server->listen(host, port);
  qDebug() << "[SERVER] Server is listening on host " << host << ", port " << server->serverPort();
  connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

QString TicTacToeServer::getPort()
{
  return QString::number(server->serverPort());
}

/**
 * @brief TicTacToeServer::onNewConnection
 * Handles new connection by adding client socket and name to clientSockets list
 */
void TicTacToeServer::onNewConnection()
{
  // If there is less than 2 players on the server
  if(this->clientSockets.size()<2){
    QTcpSocket* clientSocket = server->nextPendingConnection();
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
    clientSocket->waitForReadyRead(100);
    char name[clientSocket->bytesAvailable()];
    clientSocket->read(name,clientSocket->bytesAvailable());
    clientSockets.insert(name,clientSocket);
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(getMessage()));

    emit userConnected(name);
    for(QTcpSocket* socket : this->clientSockets.values()){
      sendData(10,0,0,0,socket); // 10 is onClientConnect
    }
  }
}

void TicTacToeServer::getMessage()
{
  QTcpSocket* clientSocket = static_cast<QTcpSocket*>(sender());
  QByteArray buffer = clientSocket->read(sizeof(int)*3+sizeof(bool));

  // Reverse endianness
  std::reverse(buffer.begin(), buffer.end());
  QDataStream ds(buffer);
  int id,x,y;
  bool finish;
  ds >> finish;
  ds >> y;
  ds >> x;
  ds >> id;
  qDebug() << id << " " << x << " " << y << ' ' << finish << endl;

  if(this->clientSockets.size()==2){
    QTcpSocket* target = clientSocket;
    for(QTcpSocket* socket : this->clientSockets.values()){
      if(socket!=clientSocket){
        target = socket;
      }
    }
    sendData(id,x,y,finish,target);
  }
}

void TicTacToeServer::onClientDisconnected()
{
  QString name = clientSockets.key(qobject_cast<QTcpSocket *>(QObject::sender()));
  clientSockets.remove(name);
  qDebug() << (QString("User '%1' has disconnected").arg(name));
  // TODO: stop game and clear bitmap
  emit userDisconnected(name);
}

void TicTacToeServer::sendData(int id, int x,int y,bool finish, QTcpSocket *target)
{
  target->write(reinterpret_cast<char*>(&id),sizeof(int));
  target->write(reinterpret_cast<char*>(&x),sizeof(int));
  target->write(reinterpret_cast<char*>(&y),sizeof(int));
  target->write(reinterpret_cast<char*>(&finish),sizeof(bool));
}

/*
void TicTacToeServer::addToHistory(QString message)
{
  // History will always be 10 items long
  if(this->history.length() < 10){
    this->history.push_back(message);
  }else{
    this->history.removeAt(0);
    this->history.push_back(message);
  }

}*/
