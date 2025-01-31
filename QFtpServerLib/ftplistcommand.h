#ifndef FTPLISTCOMMAND_H
#define FTPLISTCOMMAND_H

#include "ftpcommand.h"

class QFileInfo;
typedef QList<QFileInfo> QFileInfoList;

// Implements the LIST command. Prints out a listing of the given directory, in
// the same format as the unix 'ls -l' command.

class FtpListCommand : public FtpCommand
{
    Q_OBJECT
public:
    explicit FtpListCommand(QObject *parent, const QString &listDirectory, bool nameListOnly = false);
    ~FtpListCommand();

private:
    void startImplementation();
    QString fileListingString(const QFileInfo &fi);

private :
    void listNextBatch();

private:
    QString listDirectory;
    bool nameListOnly;
    //int index;*/
};

#endif // FTPLISTCOMMAND_H
