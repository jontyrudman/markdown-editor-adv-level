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
    if (!notebook->setRootDir(ui->folderPane))
        QMessageBox::information(this, "Error", "Error setting the notebook.");

//    if (notebook->setRootDir(ui->folderPane))
//        QMessageBox::information(this, "Information", "Great success!");
}

void MainWindow::on_actionOpen_Note_triggered()
{
    // Opens a file dialog and sets fileName to the selected *.md file
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Note"), "",
                                                    tr("Note (*.md)"));

    // If the file is empty or can't be opened, do not attempt to go further
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }
    // Read the file and put it into mdEditPane
    ui->mdEditPane->setPlainText(file.readAll());
    file.close();
    }
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
        QMessageBox::information(this, tr("Error"), tr("Unable to open file"));
}
