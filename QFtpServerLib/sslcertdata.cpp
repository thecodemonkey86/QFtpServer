#include "sslcertdata.h"


QString SslCertData::getPrivateKeyFilePath() const
{
    return privateKeyFilePath;
}

QString SslCertData::getLocalCertFilePath() const
{
    return localCertFilePath;
}

QByteArray SslCertData::getPassphrase() const
{
    return passphrase;
}

SslCertData::SslCertData(const QString &privateKeyFilePath, const QString &localCertFilePath, const QByteArray &passphrase)
{
    this->privateKeyFilePath = privateKeyFilePath;
    this->localCertFilePath = localCertFilePath;
    this->passphrase = passphrase;
}
