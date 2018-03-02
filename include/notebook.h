#include <QDir>
#include <QFile>
#include <QPlainTextEdit>
#include <QTreeView>
#include <QFileSystemModel>
#include <QStringList>
#include <QInputDialog>
#include <QCoreApplication>
#include <QTextStream>
#include <QLabel>

#ifndef NOTEBOOK_H
#define NOTEBOOK_H

class Notebook
{
public:
    bool newNote(QPlainTextEdit *mdEditPane, QTreeView *folderPane);
    bool setNote(QPlainTextEdit *mdEditPane, const QModelIndex &index);
    bool saveNote(QPlainTextEdit *mdEditPane);
    bool compileNote(QPlainTextEdit *mdEditPane, QTextEdit *compilePane);
    bool setRootDir(QTreeView *folderPane, QLabel *labelNoteTitle, QString newRoot = "Untitled");
    QDir rootDir();
    QFile &noteFile();
    QString notePath();
    QString noteHtmlPath();
private:
    QFileSystemModel *model = new QFileSystemModel;
    QFile note;
    QDir root;
};

#endif // NOTEBOOK_H
