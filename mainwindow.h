#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTreeView>
#include "Include/notebook.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_Note_triggered();

    void on_actionSave_Note_As_triggered();

    void on_folderPane_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    // Instantiate a notebook
    Notebook *notebook = new Notebook;
};

#endif // MAINWINDOW_H
