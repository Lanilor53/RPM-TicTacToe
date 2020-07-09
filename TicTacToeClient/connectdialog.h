#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QLineEdit>

class ConnectDialog : public QDialog
{
  Q_OBJECT
public:
  ConnectDialog(QWidget *parent = nullptr);
  QLineEdit* usernameEdit;
  QLineEdit* hostEdit;
  QLineEdit* portEdit;
public slots:
  void sendParams();
signals:
  void sendParamsSignal(QString username, QString host, QString port);
};

#endif // CONNECTDIALOG_H
