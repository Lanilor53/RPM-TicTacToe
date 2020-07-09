#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QLayout>
#include <QTcpSocket>

class TicTacToeClient : public QObject
{
  Q_OBJECT

private:
  QString username;
  QTcpSocket* socket;
public slots:
  void readMessage();
  void connectToServer(QString username, QString host, QString port);
  void sendMessage(int id, int x, int y, bool finish);
  void disconnected();
  void disconnectClient();
signals:
  void clientDisconnected();
  void gotClear();
  void gotMessage(int id, int x, int y, bool finish);
};

#endif // CHATCLIENT_H
// TODO: menu connect slot
