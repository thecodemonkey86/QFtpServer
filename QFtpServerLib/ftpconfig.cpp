#include "ftpconfig.h"

FtpConfig::FtpConfig(const QString &rootPath, const QString &password)
{
    this->rootPath = rootPath;
    this->password = password;
}

const QString & FtpConfig::getRootPath() const
{
    return rootPath;
}

void FtpConfig::setRootPath(const QString &value)
{
    rootPath = value;
}

const QString & FtpConfig::getPassword() const
{
    return password;
}

void FtpConfig::setPassword(const QString &value)
{
    password = value;
}

