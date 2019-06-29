#include "dataconnection.h"
#include "sslserver.h"
#include "ftpcommand.h"
#include <QSslSocket>

DataConnection::DataConnection( const SslCertData & certData,QObject *parent) :
    QObject(parent)
{
    server = new SslServer(this);
    connect(server, &QTcpServer::newConnection, this, &DataConnection::newConnection);
    socket = nullptr;
    isSocketReady = false;
    isWaitingForFtpCommand = false;
    this->certData = certData;
}

void DataConnection::scheduleConnectToHost(const QString &hostName, quint16 port, bool encrypt)
{
    this->encrypt = encrypt;
    delete socket;
    this->hostName = hostName;
    this->port = port;
    isSocketReady = false;
    isWaitingForFtpCommand = true;
    isActiveConnection = true;
}

int DataConnection::listen(bool encrypt)
{
    this->encrypt = encrypt;
    delete socket;
    socket = nullptr;
    delete command;
    command = nullptr;
    isSocketReady = false;
    isWaitingForFtpCommand = true;
    isActiveConnection = false;
    server->close();
    server->listen();
    return server->serverPort();
}

bool DataConnection::setFtpCommand(FtpCommand *command)
{
    if (!isWaitingForFtpCommand) {
        return false;
    }
    isWaitingForFtpCommand = false;
    this->command = command;
    command->setParent(this);

    if (isActiveConnection) {
        socket = new QSslSocket(this);
        connect(socket, &QAbstractSocket::connected, this, &DataConnection::connected);
        socket->connectToHost(hostName, port);
    } else {
        startFtpCommand();
    }
    return true;
}

FtpCommand *DataConnection::ftpCommand()
{
    if (isSocketReady) {
        return command;
    }
    return nullptr;
}

void DataConnection::newConnection()
{
    socket = static_cast<QSslSocket *>(server->nextPendingConnection());
    server->close();
    if (encrypt) {
        connect(socket, &QSslSocket::encrypted, this, &DataConnection::encrypted);
        SslServer::setLocalCertificateAndPrivateKey(socket,certData);
        socket->startServerEncryption();
    } else {
        encrypted();
    }
}

void DataConnection::encrypted()
{
    isSocketReady = true;
    startFtpCommand();
}

void DataConnection::connected()
{
    if (encrypt) {
        connect(socket, &QSslSocket::encrypted, this, &DataConnection::encrypted);
        SslServer::setLocalCertificateAndPrivateKey(socket,certData);
        socket->startServerEncryption();
    } else {
        encrypted();
    }
}

void DataConnection::startFtpCommand()
{
    if (command && isSocketReady) {
        command->start(socket);
        socket = nullptr;
    }
}
