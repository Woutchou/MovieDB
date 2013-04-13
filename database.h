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
    bool firstInsert(QString filePath);
    bool exist(Movie m);


private:

    QSqlDatabase database;
};

#endif // DATABASE_H
