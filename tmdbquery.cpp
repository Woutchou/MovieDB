#include "tmdbquery.h"

/*
    QNetworkAccessManager manager;
    QNetworkRequest       request;
    QUrl                  url;
    QNetworkReply       * reply;
    Movie                 move;
*/

TMDBquery::TMDBquery(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    url.setUrl("http://private-4021-themoviedb.apiary.io/3/movie/550?api_key="+api_key);
    QNetworkRequest requete(url);
    requete.setRawHeader("Accept", "application/json");

    reply = manager->get(requete);


    connect(reply, SIGNAL(finished()),this, SLOT(saveTmdbId()));

}

Movie TMDBquery::getMovie()
{
    return move;
}

void TMDBquery::saveTmdbId()
{
    qWarning() << "saving data from tmdb API";
    QNetworkReply *r = qobject_cast<QNetworkReply*>(sender()); //On récupère la réponse du serveur

    qWarning() << r->readAll();
   // QJsonDocument jFilm = QJsonDocument::fromJson();

    r->deleteLater();

}
