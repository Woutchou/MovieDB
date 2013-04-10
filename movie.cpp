#include "movie.h"
#include "moviefile.h"

#include <QDebug>
#include <QJsonArray>
#include <QDir>
#include <QStringListModel>
#include <QFileDialog>

using namespace std;

Movie::Movie() : title("Defaut title"), runtime(0), synopsis("Default synopsis") {

}

Movie::Movie(QJsonObject newMovie) {
    title = newMovie.value(QString("title")).toString();
    originalTitle = newMovie.value(QString("original_title")).toString();
    runtime = newMovie.value(QString("runtime")).toDouble();
    synopsis = "default";
    //synopsis = newMovie.value(QString("overview")).toString();
    tmdbId = newMovie.value(QString("id")).toDouble();
    year = newMovie.value(QString("release_date")).toString().left(4).toInt();

}

void Movie::setOriginalTitle(QString newTitle) {
    originalTitle = newTitle ;
}

QString Movie::getOriginalTitle() {
    return originalTitle;
}

QString Movie::getTitle() {
    return title;
}

void Movie::setTitle(QString newTitle) {
    title = newTitle;
}

int Movie::getRuntime()
{
    return runtime;
}

void Movie::setRuntime(int newRuntime)
{
    runtime= newRuntime;
}

QString Movie::getSynopsis()
{
    return synopsis;
}

void Movie::setSynopsis(QString newSynopsis)
{
    synopsis = newSynopsis;
}

QString Movie::getGenres()
{
    return genres;
}

void Movie::setTMDB_ID(int id)
{
    tmdbId = id;
}

void Movie::setYear(int y)
{
    year = y;
}

int Movie::getYear()
{
    return year;
}


int Movie::getTmdbId()
{
    return tmdbId;
}
