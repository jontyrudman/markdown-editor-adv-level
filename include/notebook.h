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
#include <QFileInfo>

#ifndef NOTEBOOK_H
#define NOTEBOOK_H

class Notebook
{
public:
    bool newNote(QPlainTextEdit *mdEditPane, QTreeView *folderPane);
    bool setNote(QPlainTextEdit *mdEditPane, QTextEdit *compilePane, const QModelIndex &index);
    bool saveNote(QPlainTextEdit *mdEditPane);
    bool compileNote(QPlainTextEdit *mdEditPane, QTextEdit *compilePane);
    bool displayCompiledNote(QTextEdit *compilePane, QString htmlPath);
    bool setRootDir(QTreeView *folderPane, QLabel *labelNoteTitle, QString newRoot = "Untitled");
    QDir rootDir();
    QFile &noteFile();
    QString notePath();
    QString noteHtmlPath();
    QStringList notebookList();
private:
    QFileSystemModel *model = new QFileSystemModel;
    QFile note;
    QDir root;
};

#endif // NOTEBOOK_H
