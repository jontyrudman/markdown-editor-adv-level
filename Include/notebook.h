#include <QDir>
#include <QFile>
#include <QPlainTextEdit>
#include <QTreeView>
#include <QFileSystemModel>
#include <QStringList>

#ifndef NOTEBOOK_H
#define NOTEBOOK_H

class Notebook
{
public:
    bool setNote(QPlainTextEdit *mdEditPane, QString noteName);
    bool setRootDir(QTreeView *folderPane, QString newRoot = QDir::homePath() + "/Documents/Untitled");
    QDir rootDir();
    QFile noteFile();
private:
    QFileSystemModel *model = new QFileSystemModel;
    QFile note;
    QDir root;
};

#endif // NOTEBOOK_H
