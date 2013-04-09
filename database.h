#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include "movie.h"

class Database
{
public:
    Database(QString DBname);
    bool open(QString DBname);

    QList<Movie> getMovieList();
    Movie getMovie(QString Title);
    bool insertMovie(Movie m);
    static QString toSqlString(QString);


private:

    QSqlDatabase database;
};

#endif // DATABASE_H
