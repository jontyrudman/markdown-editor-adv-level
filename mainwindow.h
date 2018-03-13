#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTreeView>
#include <QLabel>
#include "notebook.h"
#include "notebookswitcher.h"

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
    void ui_init();

    void on_actionSave_Note_triggered();

    void on_folderPane_clicked(const QModelIndex &index);

    void on_actionNew_Note_triggered();

    void on_compileButton_clicked();

    void on_actionSwitch_Notebook_triggered();

    void on_actionNew_Notebook_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionSelect_All_triggered();

    void switchNotebookDialog();

private:
    Ui::MainWindow *ui;
    // Instantiate a notebook
    Notebook *notebook = new Notebook;
};

#endif // MAINWINDOW_H
