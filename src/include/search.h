#include <QString>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QDirIterator>
#include <QTextStream>

#ifndef SEARCH_H
#define SEARCH_H

class Search
{
public:
    bool findInFiles(QString searchTerm, QString rootDir);
    QStringList getResults();
private:
    void genPathList(QString rootDir);
    QStringList pathList;
    QString strPath;
    QFileInfo fi;
    QStringList searchResults;
};

#endif // SEARCH_H
