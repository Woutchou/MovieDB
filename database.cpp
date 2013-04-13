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
    if(database.open()) {
        QSqlQuery createQuery;
        createQuery.prepare("CREATE TABLE IF NOT EXISTS movieDB (tmdb_ID INTEGER , title TEXT ,"
                            "originalTitle TEXT, Year INTEGER, Runtime INTEGER, Synopsis TEXT, filePath TEXT UNIQUE NOT NULL PRIMARY KEY);");
        if(!createQuery.exec()) {
            qDebug() << createQuery.lastError().databaseText();
            return false;
        }else {
            return true;
        }

    }else {
        qDebug() << database.lastError().databaseText();
        return false;
    }

}

QList<Movie> Database::getMovieList(){
    QList<Movie> response;
    QSqlQuery listQuery;

    if(!listQuery.exec("SELECT * FROM movieDB;")) {
        qDebug() << listQuery.lastError().databaseText();
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
    getMovieQuery.prepare("SELECT * FROM movieDB where originalTitle LIKE :title ;");
    getMovieQuery.bindValue(":title", "%"+title+"%");
    getMovieQuery.exec();
    getMovieQuery.last();

    if(getMovieQuery.at()+1 == 1) {
        temp.setTMDB_ID(getMovieQuery.value(0).toInt());
        temp.setYear(getMovieQuery.value(3).toInt());
        temp.setOriginalTitle(getMovieQuery.value(2).toString());
        temp.setTitle(getMovieQuery.value(1).toString());
        temp.setRuntime(getMovieQuery.value(4).toInt());
        temp.setSynopsis(getMovieQuery.value(5).toString());
    }else if(getMovieQuery.at()+1 == -1) {
        getMovieQuery.clear();
        getMovieQuery.prepare("SELECT * FROM movieDB where Title LIKE :title ;");
        getMovieQuery.bindValue(":title", "%"+title+"%");
        getMovieQuery.exec();
        getMovieQuery.last();

        if(getMovieQuery.at()+1 == 1) {
            temp.setTMDB_ID(getMovieQuery.value(0).toInt());
            temp.setYear(getMovieQuery.value(3).toInt());
            temp.setOriginalTitle(getMovieQuery.value(2).toString());
            temp.setTitle(getMovieQuery.value(1).toString());
            temp.setRuntime(getMovieQuery.value(4).toInt());
            temp.setSynopsis(getMovieQuery.value(5).toString());
        }
    }

    return temp;
}

bool Database::insertMovie(Movie m) {

    if(!this->exist(m)) {
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT OR REPLACE INTO movieDB (tmdb_ID, title, originalTitle, Year, Runtime, Synopsis)"
                            "VALUES (:id, :title, :originalTitle, :year, :runtime, :synopsis);");
        insertQuery.bindValue(":id", m.getTmdbId());
        insertQuery.bindValue(":title", m.getTitle());
        insertQuery.bindValue(":originalTitle", m.getOriginalTitle());
        insertQuery.bindValue(":year", m.getYear());
        insertQuery.bindValue(":runtime", m.getRuntime());
        insertQuery.bindValue(":synopsis", m.getSynopsis());

        if(!insertQuery.exec()) {
            qDebug() << insertQuery.lastError().databaseText();
            qDebug() << insertQuery.lastQuery();
            return false;
        }else return true;
    }else return false;
}

bool Database::exist(Movie m) {
    QSqlQuery existQuery;
    existQuery.prepare("SELECT * FROM movieDB where tmd_ID = :id;");
    existQuery.bindValue(":id", m.getTmdbId());
    existQuery.exec();
    existQuery.last();

    if(existQuery.at()+1 == 1) {
        return true;
    }else return false;

}

bool Database::firstInsert(QString filePath) {

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO movieDB (filePath) VALUES (:filePath);");
    insertQuery.bindValue(":filePath", filePath);

    if(!insertQuery.exec()) {
        qDebug() << insertQuery.lastError().databaseText();
        return false;
    }else return true;

}
