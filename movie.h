#ifndef MOVIE_H
#define MOVIE_H

#include <QString>
#include <QJsonObject>
#include <QStringListModel>

class Movie
{
public:
    Movie();
    Movie(QJsonObject newMovie);

    void getIMDBinfo();

    QString getTitle();
    void setTitle(QString newTitle);

    int getRuntime();
    void setRuntime(int newRuntime);

    QString getSynopsis();
    void setSynopsis(QString newSynopsis);

    QString getGenres();

    void setTMDB_ID(int id);
    int getTmdbId();
    void setOriginalTitle(QString newTitle);
    QString getOriginalTitle();

    void setYear(int y);
    int getYear();


private:
    int tmdbId;
    QString title;
    QString originalTitle;
    int runtime;
    int year;
    QString synopsis;
    QString genres;

};

#endif // MOVIE_H
