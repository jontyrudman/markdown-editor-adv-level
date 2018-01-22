#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    // Read the file and set the test of mdEditPane to it
    ui->mdEditPane->setPlainText(file.readAll());
    file.close();
    }
}
