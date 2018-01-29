#include "notebook.h"

bool Notebook::setNote(QPlainTextEdit *mdEditPane, QString noteName)
{
    // If the file is empty or can't be opened, do not attempt to go further
    if (noteName.isEmpty())
        return false;
    else {
        QString path = root.absoluteFilePath(noteName);
        QFile file(path);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            return false;
        }
    // Read the file and put it into mdEditPane
    mdEditPane->setPlainText(file.readAll());
    file.close();
    return true;
    }
}

bool Notebook::setRootDir(QTreeView *folderPane, QString newRoot)
{
    if (!root.mkpath(newRoot)) {
        return false;
    }
    root.setPath(newRoot);

    QStringList dirFilters;
    dirFilters << "*.md" << "*.pdf" << "*.yaml";
    QStringList modelFilters;
    modelFilters << "*.md";
    root.setNameFilters(dirFilters);

    model->setRootPath(QDir::currentPath());
    model->setNameFilters(modelFilters);
    model->setNameFilterDisables(false);
    folderPane->setModel(model);
    folderPane->setRootIndex(model->index(root.path()));

    return true;
}

QDir Notebook::rootDir()
{
    return root;
}
