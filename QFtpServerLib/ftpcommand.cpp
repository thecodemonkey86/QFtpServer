#include "ftpcommand.h"

#include <QSslSocket>

FtpCommand::FtpCommand(QObject *parent) :
    QObject(parent)
{
    started = false;
}

void FtpCommand::start(QSslSocket *socket)
{
    started = true;
    this->socket = socket;
    socket->setParent(this);
    connect(socket, &QAbstractSocket::disconnected, this, &QObject::deleteLater);
    startImplementation();
}
