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
    if (!notebook->setRootDir(ui->folderPane, ui->labelNoteTitle))
        QMessageBox::information(this, "Error", "Error setting the notebook.");
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
    QStringList notebooks;
    QString notebookName;
    QString tmp;

    // Makes a list of all valid directories in Documents/Notebooks
    QDirIterator it(QDir::homePath() + "/Documents/Notebooks", QDir::Dirs | QDir::NoDotAndDotDot);
    while (it.hasNext()) {
        // Removes the stuff before the directory name
        tmp = it.next();
        tmp.remove(0, tmp.lastIndexOf('/') + 1);
        notebooks.append(tmp);
    }

    // Makes a new NotebookSwitcher and gives it the list found
    NotebookSwitcher *dialog = new NotebookSwitcher;
    dialog->setNotebookList(notebooks);

    // If the user clicks ok, get the selected notebook and call setRootDir for it
    if (dialog->exec()) {
        notebookName = dialog->selectedNotebook();
        if (!notebookName.isNull())
            notebook->setRootDir(ui->folderPane, ui->labelNoteTitle, notebookName);
    }

    delete dialog;
}

void MainWindow::on_actionNew_Notebook_triggered()
{
    QStringList notebooks;
    QString notebookName;
    QString tmp;

    // Makes a list of all valid directories in Documents/Notebooks
    QDirIterator it(QDir::homePath() + "/Documents/Notebooks", QDir::Dirs | QDir::NoDotAndDotDot);
    while (it.hasNext()) {
        // Removes the stuff before the directory name
        tmp = it.next();
        tmp.remove(0, tmp.lastIndexOf('/') + 1);
        notebooks.append(tmp);
    }

    // Open an input dialog for the user to enter the name of their new notebook
    bool ok;
    notebookName = QInputDialog::getText(this, QObject::tr("New Notebook"),
                                         QObject::tr("New notebook name:"), QLineEdit::Normal,
                                         "untitled", &ok);

    // If a valid notebook name is entered, call setRootDir for it
    if (!notebookName.isEmpty() && (ok == true) && !notebooks.contains(notebookName))
        notebook->setRootDir(ui->folderPane, ui->labelNoteTitle, notebookName);
    else
        QMessageBox::information(this, tr("Error"), tr("Unable to create notebook. May already exist."));
}
