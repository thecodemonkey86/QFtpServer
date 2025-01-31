#include "ftpserver.h"
#include "ftpcontrolconnection.h"
#include "sslserver.h"
#include "ftpconfig.h"

#include <QDebug>
#include <QNetworkInterface>
#include <QSslSocket>

FtpServer::FtpServer(QObject *parent, const QHash<QString, FtpConfig> & usersConfigMapping, quint16 port,  bool readOnly, bool onlyOneIpAllowed) :
    QObject(parent)
{
    server = new SslServer(this);
    // In Qt4, QHostAddress::Any listens for IPv4 connections only, but as of
    // Qt5, it now listens on all available interfaces, and
    // QHostAddress::AnyIPv4 needs to be used if we want only IPv4 connections.
    server->listen(QHostAddress::AnyIPv4, port);
    connect(server, &QTcpServer::newConnection, this, &FtpServer::startNewControlConnection);
    this->usersConfigMapping = usersConfigMapping;
    this->readOnly = readOnly;
    this->onlyOneIpAllowed = onlyOneIpAllowed;
}

FtpServer::FtpServer(QObject *parent, const QHash<QString, FtpConfig> &usersConfigMapping, const SslCertData & certData, quint16 port, bool readOnly, bool onlyOneIpAllowed)
:FtpServer(parent, usersConfigMapping, port,  readOnly, onlyOneIpAllowed)
{
    this->certData = certData;
}

bool FtpServer::isListening()
{
  return server->isListening();
}

quint16 FtpServer::getPort() const
{
  return server->serverPort();
}

QString FtpServer::lanIp()
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {
            return address.toString();
        }
    }
    return "";
}

void FtpServer::storeCommandFinished(const QString &filepath) const
{
    emit fileStored(filepath);
}

void FtpServer::startNewControlConnection()
{
    QSslSocket *socket = static_cast<QSslSocket *>(server->nextPendingConnection());

    // If this is not a previously encountered IP emit the newPeerIp signal.
    QString peerIp = socket->peerAddress().toString();
    qDebug() << "connection from" << peerIp;
    if (!encounteredIps.contains(peerIp)) {
        // If we don't allow more than one IP for the client, we close
        // that connection.
        if (onlyOneIpAllowed && !encounteredIps.isEmpty()) {
            delete socket;
            return;
        }

        emit newPeerIp(peerIp);
        encounteredIps.insert(peerIp);
    }

    // Create a new FTP control connection on this socket.
    new FtpControlConnection(this, socket, certData, usersConfigMapping, readOnly);
}
