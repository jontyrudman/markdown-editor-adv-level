#include "search.h"

// Adds to pathList by reference recursively ...
// to add files in sub-directories
void Search::genPathList(QString rootDir)
{
    // Makes a list of all valid directories in Documents/Notebooks
    QDirIterator it(rootDir, QDir::AllEntries | QDir::NoDotAndDotDot);
    while (it.hasNext()) {
        // Removes the stuff before the directory name
        strPath = it.next();
        fi.setFile(strPath);
        if (fi.isDir())
            genPathList(strPath);
        else if (fi.suffix() == "md")
            pathList.append(strPath);
    }
}

bool Search::findInFiles(QString searchTerm, QString rootDir)
{
    // Collects the list of markdown file paths
    genPathList(rootDir);

    QString curPath;
    QFile curFile;

    // Iterates over each file in pathList
    for (int i = 0; i < pathList.size(); i++) {
        curPath = pathList.at(i);
        curFile.setFileName(curPath);
        if (!curFile.open(QFile::ReadOnly | QFile::Text)) {
            return false;
        }

        // Checks for the search term in the file name
        fi.setFile(curPath);
        QString shortFileName(fi.fileName());
        shortFileName.remove(".md", Qt::CaseInsensitive);
        if (shortFileName.contains(searchTerm, Qt::CaseInsensitive)) {
            searchResults.append("- " + shortFileName);
            break;
        }

        // Read the file into a stream.
        QTextStream in(&curFile);
        // Looks for the search term in the file's text
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.contains(searchTerm, Qt::CaseInsensitive)) {
                searchResults.append("- " + shortFileName);
                break;
            }
        }
        curFile.close();
    }
    if (searchResults.isEmpty())
        return false;
    return true;
}

QStringList Search::getResults()
{
    return searchResults;
}
