#include "notebook.h"
#include "markdown.h"
extern "C" {
#include "sundown.c"
}

bool Notebook::newNote(QPlainTextEdit *mdEditPane, QTreeView *folderPane)
{
    bool ok;
    QString noteName = QInputDialog::getText(mdEditPane, QObject::tr("New Note"),
                                         QObject::tr("New note name:"), QLineEdit::Normal,
                                         "untitled", &ok);

    // FUTURE-PROOFING - Set the current working directory
    // to the absolute dir path of the selected note.
    QString parentDir = "";
    if (model->isDir(folderPane->currentIndex()))
            parentDir = model->filePath(folderPane->currentIndex());
    QDir::setCurrent(parentDir);

    if (noteName.isEmpty() || noteName.count(' ') == noteName.length())
      return false;

    noteName += ".md";

    if (QDir::current().exists(noteName))
      return false;

    note.setFileName(noteName);
    if (!note.open(QFile::ReadWrite | QFile::Text)) {
        return false;
    }
    // Read the file and put it into mdEditPane
    mdEditPane->setPlainText(note.readAll());
    note.close();

    // Sets the model (and treeview) index to the path of the current file (selects the new note).
    const QModelIndex idx = model->index(QDir::current().absoluteFilePath(noteName));
    folderPane->setCurrentIndex(idx);

    mdEditPane->setReadOnly(false);

    return true;
}

bool Notebook::setNote(QPlainTextEdit *mdEditPane, const QModelIndex &index)
{
    QString noteName = model->fileName(index);
    // If the file is empty or can't be opened, do not attempt to go further.
    if (noteName.isEmpty())
        return false;
    // Bypass the error window if a directory is selected.
    else if (model->isDir(index))
        return true;
    else {
        // Set the dir path to the absolute dir path of the selected note.
        QDir::setCurrent(model->filePath(model->parent(index)));
        note.setFileName(noteName);
        if (!note.open(QFile::ReadWrite | QFile::Text)) {
            return false;
        }
        // Read the file and put it into mdEditPane
        mdEditPane->setPlainText(note.readAll());
        note.close();
        mdEditPane->setReadOnly(false);
        return true;
    }
    return false;
}

bool Notebook::saveNote(QPlainTextEdit *mdEditPane)
{
    // If the filename is empty or can't be opened, do not attempt to go further
    if (note.fileName().isEmpty())
        return false;
    else {
        QDir::setCurrent(root.absolutePath());
        if (!note.open(QFile::WriteOnly | QFile::Text)) {
            return false;
        }
    // Read mdEditPane into the file
    QTextStream stream(&note);
    stream << mdEditPane->toPlainText().trimmed() << endl;
    note.close();
    return true;
    }
}

bool Notebook::compileNote(QPlainTextEdit *mdEditPane, QTextEdit *compilePane)
{
    // Saves the note and gives sundown_parse the path of the current markdown file
    saveNote(mdEditPane);
    QFile htmlFile;

    QString mdPathString = notePath();
    QString htmlPathString = noteHtmlPath();

    // Declares char arrays of the input and output paths to give to sundown_parse
    QByteArray ba = mdPathString.toLatin1();
    char *mdPath = ba.data();
    ba = htmlPathString.toLatin1();
    char *htmlPath = ba.data();

    if (sundown_parse(mdPath, htmlPath) != 0)
        return false;

    if (!htmlPath)
        return false;

    // Opens htmlFile and writes the html to compilePane
    htmlFile.setFileName(htmlPath);
    if (!htmlFile.open(QFile::ReadOnly | QFile::Text)) {
        return false;
    }
    QTextStream stream(&htmlFile);

    compilePane->setText(stream.readAll());
    return true;
}

bool Notebook::setRootDir(QTreeView *folderPane, QString newRoot)
{
    // Makes the parent directories, if non-existent, necessary for newRoot.
    if (!root.mkpath(newRoot))
        return false;
    // Sets the root directory to the one at the newly created path.
    root.setPath(newRoot);

    // Filters in the following file types for the QDir root.
    QStringList dirFilters;
    dirFilters << "*.md" << "*.pdf" << "*.yaml" << "*.html";

    // Filters in *.md files for the QFileSystemModel.
    QStringList modelFilters;
    modelFilters << "*.md";
    root.setNameFilters(dirFilters);

    // Hooks QFileSystemModel to the path of the program.
    model->setRootPath(QDir::currentPath());
    model->setNameFilters(modelFilters);

    // Hides the file types not specified in modelFilters for QFileSystemModel.
    model->setNameFilterDisables(false);

    // Sets the model of QTreeView folderPane to model and gives it a root index of the root dir.
    folderPane->setModel(model);
    folderPane->setRootIndex(model->index(root.path()));

    // Removes all columns other than "Name".
    for (int i = 1; i < model->columnCount(); i++)
        folderPane->hideColumn(i);

    return true;
}

QDir Notebook::rootDir()
{
    return root;
}

QFile& Notebook::noteFile()
{
    return note;
}

QString Notebook::notePath()
{
    QString mdPath = QDir::currentPath() + "/" + note.fileName();
    return mdPath;
}

QString Notebook::noteHtmlPath()
{
    QString htmlPath = notePath();
    htmlPath.chop(2);
    htmlPath += "html";
    return htmlPath;
}
