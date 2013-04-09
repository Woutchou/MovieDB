#ifndef QUERYTMDB_H
#define QUERYTMDB_H

#include <QObject>
#include <QtNetwork>
#include "movie.h"

const QString api_key = "5f9d81122d9185f28c936d1d257e06d9";

class queryTmdb : public QObject
{
    Q_OBJECT

public:
    queryTmdb(QObject *parent = 0, QString fileName = "default");
    Movie getMovie();
    static int getID(QString fileName);
    
signals:
    void endRequest(Movie);
    
public slots:
    void getID();
    void requestMovie();

private:
    QNetworkAccessManager *manager;
    QNetworkRequest        request;
    QUrl                   url;
    QNetworkReply         *reply;
    QString                tmdbID;
    Movie                 nMovie;

    
};

#endif // QUERYTMDB_H
