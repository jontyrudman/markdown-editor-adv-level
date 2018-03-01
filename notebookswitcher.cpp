#include "notebookswitcher.h"
#include "ui_notebookswitcher.h"

NotebookSwitcher::NotebookSwitcher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotebookSwitcher)
{
    ui->setupUi(this);
}

NotebookSwitcher::~NotebookSwitcher()
{
    delete ui;
}
