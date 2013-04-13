#include "moviefile.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>

movieFile::movieFile()
{
}

movieFile::movieFile(QString name, QDir d, Movie m) : dir(d), associatedMovie(m)
{
    file = new QFile(name);
    associatedMovie.setTitle(name);
  //  qDebug() << associatedMovie.getTitle();
}


void movieFile::rename(QString newName)
{
    if(!file->rename(newName))
    {
        qWarning() << "Erreur : Impossile de renommer le fichier";
    }
}

QList<movieFile> movieFile::ListMovie(){

    QList<movieFile> movieList;
    QDir movieDir = QDir("J:/Vidéo");

            //QFileDialog::getExistingDirectory();

    QStringList filter;
    filter << "*.avi" << "*.mp4" ;
    QStringList listeFilm = movieDir.entryList(filter);

   for(int i = 0; i < listeFilm.size(); i++)
    {
       movieFile f = movieFile(listeFilm.value(i), movieDir, Movie());
       movieList.append(f);
    }

   return movieList;
}

QString movieFile::getName()
{
    QString tempName = file->fileName().left(file->fileName().size()-4);
    return tempName;
}


