#include "querytmdb.h"
#include "qlistdialog.h"

using namespace std;

queryTmdb::queryTmdb(QObject *parent, QString fileName) : QObject(parent)
{
    url = "http://private-4021-themoviedb.apiary.io/3/search/movie?api_key=" + api_key + "&query=" + fileName;
    request.setUrl(url);

    request.setRawHeader("Accept", "application/json");

    manager = new QNetworkAccessManager;

    reply = manager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(getID()));

}


void queryTmdb::getID()
{
    QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument tempMovie = QJsonDocument::fromJson(r->readAll());
    QJsonObject queryResponse;
    QJsonArray extractInfo;
    QList<QJsonObject> tableau;

    queryResponse = tempMovie.object();

    extractInfo = queryResponse.value(QString("results")).toArray();

    for(int i = 0; i < extractInfo.count(); i++)
    {
        tableau.push_back(extractInfo.at(i).toObject());
    }

    for(int i = 0; i < tableau.count(); i++)
    {
      //  qWarning() << tableau.at(i).value(QString("title")).toString() << " : " << tableau.at(i).value(QString("id")).toDouble();

    }

    if(tableau.count() == 1)
    {
        tmdbID = QString::number(tableau.at(0).value(QString("id")).toDouble());
        url = "http://private-4021-themoviedb.apiary.io/3/movie/"+ tmdbID +"?api_key=" + api_key + "&language=fr";
        request.setUrl(url);
        reply = manager->get(request);

        connect(reply, SIGNAL(finished()), this, SLOT(requestMovie()));


    }
    else
    {
       /* QStringList listTitre;
        for(int i = 0; i < tableau.count(); i++)
        {
            listTitre.push_back(tableau.at(i).value(QString("original_title")).toString() + " (" + tableau.at(i).value(QString("release_date")).toString()+ ")");
        }

        QListDialog temp(listTitre);

        if(temp.exec())
        {
            tmdbID = QString::number(tableau.at(temp.getItem()).value(QString("id")).toDouble());
        }*/
 }


}

void queryTmdb::requestMovie()
{
    QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument tempMovie = QJsonDocument::fromJson(r->readAll());
    QJsonObject queryResponse = tempMovie.object();
    nMovie = Movie(queryResponse);

    emit endRequest(nMovie);
}

Movie queryTmdb::getMovie()
{
    return nMovie;
}


void queryTmdb::scanFolder(QDir moviesFolder, Database *db){

    QStringList filter;
    filter << "*.avi" << "*.mp4" ;
    QStringList listeFilm = moviesFolder.entryList(filter);
    db.firstInsert("kikoo");


}


