QFtpServer - an FTP server written in Qt
----------------------------------------

### Description

forked from https://github.com/sashoalm/QFtpServer, added support for multiple user/password/rootpath configurations


### Features

It supports:

* Active connections (PORT command).
* Passive connections (PASV command).
* Random access for files (APPE, RETR), so stopped uploads and downloads can be continued.
* Secure FTP, also known as FTP-ES which uses SSL/TLS sockets.
* Multiple user accounts

It doesn't support:
* IPv6.
* FTPS (this standard is obsolete and FTP-ES should be used instead).

### Example usage:

    const QString &userName("u0");
    const QString &password("123");
    const QString &rootPath("D:\\ftpserver\\root1");

    const QString &userName2("u1");
    const QString &password2("456");
    const QString &rootPath2("D:\\ftpserver\\root2");

    QHash<QString, FtpConfig> usersConfigsMappings;
    usersConfigsMappings.insert(userName, FtpConfig(rootPath, password));
    usersConfigsMappings.insert(userName2, FtpConfig(rootPath2, password2));
   
    FtpServer server(&a, usersConfigsMappings, SslCertData(QDir(a.applicationDirPath()).absoluteFilePath("private_key.pem"),QDir(a.applicationDirPath()).absoluteFilePath("cert.pem"),QByteArray("39129380423984234012312")),2121, false, false);
