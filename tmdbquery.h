#ifndef TMDBQUERY_H
#define TMDBQUERY_H

#include <QObject>
#include <QtNetwork>
#include <movie.h>

class TMDBquery : public QObject
{
    Q_OBJECT
public:
    TMDBquery(QObject *parent = 0);
    Movie getMovie();
    
signals:
    
public slots:
    void saveTmdbId();

private:
    QNetworkAccessManager *manager;
    QUrl url;
    QNetworkReply       * reply;
    Movie                 move;
};

#endif // TMDBQUERY_H
