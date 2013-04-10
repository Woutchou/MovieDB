#include "database.h"
#include "movie.h"
#include <QDebug>
#include <QtSql>
#include <QErrorMessage>
#include <QDebug>

using namespace std;

Database::Database(QString DBname){
    database = QSqlDatabase::addDatabase("QSQLITE");
    if(!open(DBname)) {
            qDebug() << "Error ouverture base de donnée";
    }
}

bool Database::open(QString DBname) {
    database.setDatabaseName(DBname);
    return database.open();
}

QList<Movie> Database::getMovieList(){
    QList<Movie> response;
    QSqlQuery listQuery;

    if(!listQuery.exec("SELECT * FROM movie;")) {
        return response;
    }

    while(listQuery.next()) {
        Movie temp;
        temp.setTMDB_ID(listQuery.value(0).toInt());
        temp.setTitle(listQuery.value(1).toString());
        temp.setOriginalTitle(listQuery.value(2).toString());
        temp.setYear(listQuery.value(3).toInt());
        temp.setRuntime(listQuery.value(4).toInt());
        temp.setSynopsis(listQuery.value(5).toString());

        response.append(temp);
    }
    return response;
}


Movie Database::getMovie(QString title) {
    QSqlQuery getMovieQuery;
    Movie temp;
    getMovieQuery.prepare("SELECT * FROM movieDB where originalTitle LIKE '" + toSqlString(title) + "';");


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

bool Database::insertMovie(Movie m) {
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO movieDB (tmdb_ID, title, originalTitle, Year, Runtime, Synopsis) VALUES ("
            + QString::number(m.getTmdbId()) + ", '"
            + toSqlString(m.getTitle()) + "',"
            + toSqlString(m.getOriginalTitle()) + "',"
            + QString::number(m.getYear()) + ","
            + QString::number(m.getRuntime()) +",'"
            + toSqlString(m.getSynopsis()) + "');");

    qDebug() << "INSERT INTO movieDB (tmdb_ID, title, originalTitle, Year, Runtime, Synopsis) VALUES ("
                + QString::number(m.getTmdbId()) + ", '"
                + toSqlString(m.getTitle()) + "','"
                + toSqlString(m.getOriginalTitle()) + "',"
                + QString::number(m.getYear()) + ","
                + QString::number(m.getRuntime()) +",'"
                + toSqlString(m.getSynopsis()) + "');";

    if(insertQuery.exec()) {
       // qDebug() << insertQuery.lastError().databaseText();
        return true;
    }
    else return false;

}

QString Database::toSqlString(QString a){
    a.replace(QString("'"), QString("''"));
    qDebug() << "ToSqlQuery" << a;
    return a;
}
