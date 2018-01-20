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
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Note"), "",
                                                    tr("Note (*.md)"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }
        ui->mdEditPane->setPlainText(file.readAll());
        file.close();
    }
}
