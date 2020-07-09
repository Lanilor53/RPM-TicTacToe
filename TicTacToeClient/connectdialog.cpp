#include "connectdialog.h"

#include <QPushButton>
#include <QVBoxLayout>

ConnectDialog::ConnectDialog(QWidget *parent) : QDialog(parent, Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowCloseButtonHint)
{

  this->setWindowTitle("Connect to server");

  QVBoxLayout* dialogLayout = new QVBoxLayout();
  this->usernameEdit = new QLineEdit("User");
  usernameEdit->setPlaceholderText("User");
  this->hostEdit = new QLineEdit();
  hostEdit->setPlaceholderText("Host");
  this->portEdit = new QLineEdit();
  portEdit->setPlaceholderText("Port");

  QPushButton* connectButton = new QPushButton("Connect");


  QObject::connect(connectButton,
                   SIGNAL(clicked()),
                   this,
                   SLOT(sendParams())
        );
  // TODO: close window after connection or display an error

  dialogLayout->addWidget(usernameEdit);
  dialogLayout->addWidget(hostEdit);
  dialogLayout->addWidget(portEdit);
  dialogLayout->addWidget(connectButton);

  this->setLayout(dialogLayout);
}

void ConnectDialog::sendParams()
{
  QString username = this->usernameEdit->text();
  QString host = this->hostEdit->text();
  QString port = this->portEdit->text();

  emit sendParamsSignal(username, host, port);
  this->close();
}
