#include "database.h"
#include "movie.h"
#include <QDebug>
#include <QtSql>

#include <QDebug>

using namespace std;

Database::Database(QString DBname){
    database = QSqlDatabase::addDatabase("QSQLITE");
    this->open(DBname);
}

bool Database::open(QString DBname) {
    database.setDatabaseName(DBname);
    return database.open();
}

QList<Movie> Database::getMovieList(){
    QList<Movie> response;
    QSqlQuery listQuery;

    if(!listQuery.exec("SELECT * FROM movieDB;")) {
        qDebug() << "Error";
        return response;
    }

    while(listQuery.next()) {
        Movie temp;
        temp.setYear(listQuery.value(0).toInt());
        temp.setTMDB_ID(listQuery.value(1).toInt());
        temp.setTitle(listQuery.value(3).toString());
        temp.setRuntime(listQuery.value(4).toInt());
        temp.setSynopsis(listQuery.value(5).toString());

        response.append(temp);
    }
    return response;
}


Movie Database::getMovie(QString title) {
    QSqlQuery getMovieQuery;
    Movie temp;
    getMovieQuery.prepare("SELECT * FROM movieDB where Title LIKE '" + toSqlString(title) + "';");


    getMovieQuery.exec();
    getMovieQuery.next();


    qDebug() << "Valid ? " << getMovieQuery.isValid();


        temp.setYear(getMovieQuery.value(0).toInt());
        temp.setTMDB_ID(getMovieQuery.value(1).toInt());
        temp.setTitle(getMovieQuery.value(3).toString());
        temp.setRuntime(getMovieQuery.value(4).toInt());
        temp.setSynopsis(getMovieQuery.value(5).toString());


    return temp;
}

bool Database::insertMovie(Movie m)
{
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO movieDB (Year, tmdb_ID, Title, Runtime, Synopsis) VALUES ("
            + QString::number(m.getYear()) + ","
            + QString::number(m.getTmdbId()) + ", '"
            + toSqlString(m.getTitle()) + "',"
            + QString::number(m.getRuntime()) +",'"
            + toSqlString(m.getSynopsis()) + "');");

    return insertQuery.exec();
}

QString Database::toSqlString(QString a){
    a.replace("'","''");

    return a;
}
