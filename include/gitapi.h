#include <QString>
#include <QStringList>
#include "restclient-cpp/restclient.h"
#include "restclient-cpp/connection.h"
#include "json.hpp"
using json = nlohmann::json;

#ifndef GITAPI_H
#define GITAPI_H

class GitAPI
{
public:
    GitAPI(QString user, QString pass);
    bool getReposJson();
    bool genRepoNames();
    QStringList getRepoNames();
    bool newRepo(QString name);
    bool setCurRepoName(QString name);
    QString curRepoName();
    bool cloneCurRepo();
    bool commitChanges(QString message);
    bool setUsername(QString user);
    bool setPassword(QString pass);
    QString getUsername();
    QString getPassword();
    bool correctCredentials(QString rString);
private:
    QString username;
    QString password;
    QStringList repoNames;
    json reposJson;
    QString curRepo;
};

#endif // GITAPI_H
