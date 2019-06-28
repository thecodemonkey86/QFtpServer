#ifndef FTPCONFIG_H
#define FTPCONFIG_H

#include <QString>

#include "qftpserverlib_global.h"

class QFTPSERVERLIBSHARED_EXPORT FtpConfig
{
protected:
    QString rootPath, password;
public:
    FtpConfig() = default;
    FtpConfig(const QString & rootPath,const QString & password);
    const QString & getRootPath() const;
    void setRootPath(const QString &value);
    const QString & getPassword() const;
    void setPassword(const QString &value);
};

#endif // FTPCONFIG_H
