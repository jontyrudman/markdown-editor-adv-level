#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ui_init()
{
    QDir::setCurrent(QDir::homePath() + "/Documents/Notebooks");
    // Tries to set the default notebook
    if (!notebook->setRootDir(ui->folderPane))
        QMessageBox::information(this, "Error", "Error setting the notebook.");
    ui->labelNoteTitle->setText(notebook->rootDir().dirName());
}

void MainWindow::on_actionSave_Note_triggered()
{
    if (!notebook->saveNote(ui->mdEditPane))
        QMessageBox::information(this, tr("Error"), tr("Unable to save file"));
}


void MainWindow::on_folderPane_clicked(const QModelIndex &index)
{
    if (!notebook->setNote(ui->mdEditPane, index))
        QMessageBox::information(this, tr("Error"), tr("Unable to open file"));
}

void MainWindow::on_actionNew_Note_triggered()
{
    if (!notebook->newNote(ui->mdEditPane, ui->folderPane))
        QMessageBox::information(this, tr("Error"), tr("Unable to create file"));
}

void MainWindow::on_compileButton_clicked()
{
    if (!notebook->compileNote(ui->mdEditPane, ui->compilePane))
        QMessageBox::information(this, tr("Error"), tr("Unable to compile file"));
}

void MainWindow::on_actionSwitch_Notebook_triggered()
{

}
