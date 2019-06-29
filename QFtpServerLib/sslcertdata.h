#ifndef SSLCERTDATA_H
#define SSLCERTDATA_H

#include <QString>


#include "qftpserverlib_global.h"
class QFTPSERVERLIBSHARED_EXPORT SslCertData
{
private:
    QString privateKeyFilePath, localCertFilePath;
    QByteArray passphrase;
public:
    SslCertData()= default;
    SslCertData( const QString & privateKeyFilePath,
                 const QString &  localCertFilePath,
                 const QByteArray & passphrase);
    QString getPrivateKeyFilePath() const;
    QString getLocalCertFilePath() const;
    QByteArray getPassphrase() const;
};

#endif // SSLCERTDATA_H
