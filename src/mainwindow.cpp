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
    // Opens the switch notebook dialog and sets the root dir accordingly
    switchNotebookDialog();
}

void MainWindow::on_actionSave_Note_triggered()
{
    if (!notebook->saveNote(ui->mdEditPane)) {
        QMessageBox::information(this, tr("Error"), tr("Unable to save file"));
        return;
    }
}

void MainWindow::on_folderPane_clicked(const QModelIndex &index)
{
    if (!notebook->setNote(ui->mdEditPane, ui->compilePane, index)) {
        QMessageBox::information(this, tr("Error"), tr("Unable to open file"));
        return;
    }
    ui->actionSave_Note->setEnabled(true);
    ui->actionCompile_Note->setEnabled(true);
    ui->compileButton->setEnabled(true);
}

void MainWindow::on_actionNew_Note_triggered()
{
    if (!notebook->newNote(ui->mdEditPane, ui->folderPane)) {
        QMessageBox::information(this, tr("Error"), tr("Unable to create file"));
        return;
    }
    ui->actionCompile_Note->setEnabled(true);
    ui->compileButton->setEnabled(true);
}

void MainWindow::on_compileButton_clicked()
{
    if (!notebook->compileNote(ui->mdEditPane, ui->compilePane)) {
        QMessageBox::information(this, tr("Error"), tr("Unable to compile file"));
        return;
    }
}

void MainWindow::on_actionSwitch_Notebook_triggered()
{
    switchNotebookDialog();
}

void MainWindow::on_actionNew_Notebook_triggered()
{
    QString notebookName;
    QStringList notebooks = notebook->notebookList();

    // Open an input dialog for the user to enter the name of their new notebook
    bool ok;
    notebookName = QInputDialog::getText(this, QObject::tr("New Notebook"),
                                         QObject::tr("New notebook name:"), QLineEdit::Normal,
                                         "untitled", &ok);

    // If a valid notebook name is entered, call setRootDir for it
    if (!notebookName.isEmpty() && (ok == true) && !notebooks.contains(notebookName)) {
        notebook->setRootDir(ui->folderPane, ui->labelNoteTitle, notebookName);
        ui->mdEditPane->clear();
        ui->compilePane->clear();
        ui->mdEditPane->setReadOnly(true);
    } else {
        QMessageBox::information(this, tr("Error"), tr("Unable to create notebook. May already exist."));
    }
}

void MainWindow::on_actionUndo_triggered()
{
    ui->mdEditPane->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->mdEditPane->redo();
}

void MainWindow::on_actionCut_triggered()
{
    ui->mdEditPane->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->mdEditPane->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->mdEditPane->paste();
}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->mdEditPane->selectAll();
}

void MainWindow::switchNotebookDialog()
{
    QString notebookName;
    QStringList notebooks = notebook->notebookList();

    // If there are no notebooks available, notify the user
    if (notebooks.length() == 0) {
        ui->mdEditPane->setPlaceholderText("It looks like no notebooks are available. Make a new notebook to get started.");
        QMessageBox::information(this, tr("Error"), tr("Unable to find any notebooks. Create a new notebook."));
        return;
    }

    // Makes a new NotebookSwitcher and gives it the list found
    NotebookSwitcher *dialog = new NotebookSwitcher;
    dialog->setNotebookList(notebooks);

    // If the user clicks ok, get the selected notebook and call setRootDir for it
    if (dialog->exec()) {
        notebookName = dialog->selectedNotebook();
        // If there is a valid notebook name, set it as the current notebook
        if (!notebookName.isNull()) {
            notebook->setRootDir(ui->folderPane, ui->labelNoteTitle, notebookName);
            ui->mdEditPane->clear();
            ui->compilePane->clear();
            ui->mdEditPane->setReadOnly(true);
        }
    }

    delete dialog;
}

void MainWindow::on_searchBox_returnPressed()
{
    // If nothing has been inputted, tell the user to input a search term
    if (ui->searchBox->text().isEmpty()) {
        QMessageBox::information(this, tr("Search"), tr("Please input a search term."));
        return;
    }

    Search s;
    // Try to find the search term in the current notebook's notes
    if (!s.findInFiles(ui->searchBox->text(), notebook->rootDir().absolutePath())) {
        QMessageBox::information(this, tr("Search"), tr("Could not find any files."));
        return;
    }

    QStringList results = s.getResults();
    QString text = results.join("\n");

    // Display the search results and disable any file handling functions
    ui->actionSave_Note->setEnabled(false);
    ui->actionCompile_Note->setEnabled(false);
    ui->compileButton->setEnabled(false);
    ui->mdEditPane->setPlainText("Search results:\n" + text);
    ui->compilePane->clear();
    ui->folderPane->clearSelection();
}

void MainWindow::on_actionSet_Repository_triggered()
{

}
