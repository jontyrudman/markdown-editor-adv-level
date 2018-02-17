#include <QDir>
#include <QFile>
#include <QPlainTextEdit>
#include <QTreeView>
#include <QFileSystemModel>
#include <QStringList>
#include <QInputDialog>
#include <QCoreApplication>
#include <QTextStream>

#ifndef NOTEBOOK_H
#define NOTEBOOK_H

class Notebook
{
public:
    bool newNote(QPlainTextEdit *mdEditPane, QTreeView *folderPane);
    bool setNote(QPlainTextEdit *mdEditPane, const QModelIndex &index);
    bool saveNote(QPlainTextEdit *mdEditPane);
    bool setRootDir(QTreeView *folderPane, QString newRoot = QDir::homePath() + "/Documents/Untitled");
    QDir rootDir();
    QFile &noteFile();
    QString notePath(const QModelIndex &index);
private:
    QFileSystemModel *model = new QFileSystemModel;
    QFile note;
    QDir root;
};

#endif // NOTEBOOK_H
