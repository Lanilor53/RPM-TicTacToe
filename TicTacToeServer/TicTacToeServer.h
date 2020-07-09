#ifndef TICTACTOESERVER_H
#define TICTACTOESERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TicTacToeServer : public QObject
{
  Q_OBJECT
public:
  TicTacToeServer(QHostAddress host, quint16 port, QObject *parent = nullptr);
  QString getPort();
private:
  QTcpServer* server;
  QMap<QString, QTcpSocket*> clientSockets;
  void sendData(int id, int x,int y, bool finish, QTcpSocket* target);
public slots:
  void onNewConnection();
  void getMessage();
  void onClientDisconnected();
signals:
  void userConnected(QString username);
  void userDisconnected(QString username);
};

#endif // TICTACTOESERVER_H
