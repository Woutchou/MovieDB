#ifndef MOVIEFILE_H
#define MOVIEFILE_H

#include <QString>
#include <QDir>
#include <QStringList>
#include <movie.h>

class movieFile
{
public:
    movieFile();
    movieFile(QString name, QDir d, Movie m);
    QString getName();
    void rename(QString newName);

    static QList<movieFile> ListMovie();

private:
    QFile *file;
    QDir dir;
    Movie associatedMovie;
};

#endif // MOVIEFILE_H
