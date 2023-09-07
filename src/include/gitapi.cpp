#include "gitapi.h"

GitAPI::GitAPI(QString user, QString pass)
{
    username = user;
    password = pass;
}

bool GitAPI::getReposJson()
{
    QString reposStringJson;

    RestClient::init();
    RestClient::Connection *conn = new RestClient::Connection("https://api.github.com");
    conn->SetBasicAuth(username.toLatin1().data(), password.toLatin1().data());
    conn->SetTimeout(5);
    RestClient::Response r = conn->get("/user/repos");
    reposJson = r.body;
    reposStringJson = QString::fromStdString(reposJson);
    RestClient::disable();
}

bool GitAPI::genRepoNames()
{
    // Iterate through the json response and add any repo names to the list
    for (json::iterator it = reposJson.begin(); it != reposJson.end(); ++it) {
        if (it.key() == "name")
            repoNames.append(QString::fromStdString(it.value()));
    }
}

QStringList GitAPI::getRepoNames()
{
    return repoNames;
}

bool GitAPI::newRepo(QString name)
{

}

bool GitAPI::setCurRepoName(QString name)
{

}

QString GitAPI::curRepoName()
{

}

bool GitAPI::cloneCurRepo()
{

}

bool GitAPI::commitChanges(QString message)
{

}

bool GitAPI::setUsername(QString user)
{
    username = user;
}

bool GitAPI::setPassword(QString pass)
{
    password = pass;
}

QString GitAPI::getUsername()
{
    return username;
}

QString GitAPI::getPassword()
{
    return password;
}

bool GitAPI::correctCredentials(QString rString)
{
    if (reposJson.find("message") != reposJson.end()) {
        if (reposJson["message"] == "Bad credentials")
            return false;
        else
            return true;
    }
    return false;
}
