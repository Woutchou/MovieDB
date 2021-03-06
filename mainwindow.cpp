#include "mainwindow.h"
#include "movie.h"
#include "moviefile.h"
#include "database.h"
#include "querytmdb.h"
#include "moviedisplayinfo.h"

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QFileDialog>
#include <QDomDocument>
#include <QJsonDocument>
#include <QDebug>
#include <QByteArray>
#include <QJsonObject>
#include <QButtonGroup>
#include <QJsonArray>
#include <QListView>
#include <QFileSystemModel>
#include <QModelIndex>
#include <QtGui>
#include <QtNetwork>
#include <QMessageBox>
#include <QtSql>
#include <QProgressDialog>
#include <QTimer>
#include <QPushButton>

MainWindow::MainWindow() : QWidget()
{
  //  MovieDisplayInfo *essai;
  //  essai = new MovieDisplayInfo(this);
    sqlDb = new Database("data1.db");

    queryTmdb::scanFolder(QDir("E:/Films"), sqlDb);

    /*
    QTime t;
    t.start();
    QList<movieFile> listeFilms = movieFile::ListMovie();
    for (int i = 0; i < listeFilms.count(); i++) {
            listFilm.append(listeFilms.value(i).getName());
            temp = new queryTmdb(this, MainWindow::cleanName(listeFilms.value(i).getName()));
            QObject::connect(temp, SIGNAL(endRequest(Movie)), this, SLOT(insertMovie(Movie)));
    }

    qDebug() << listeFilms.count()*2 << "requetes effectues en " << t.elapsed() << "ms";*/



    m_button = new QPushButton("Choisir un dossier");

    title = new QLabel("Titre :", this);
    title->setAlignment(Qt::AlignRight);
    mTitle = new QLineEdit(this);
    lenght = new QLabel("Durée (min) :",this);
    lenght->setAlignment(Qt::AlignRight);
    mLenght = new QLineEdit(this);
    genre = new QLabel("Genre :",this);
    mGenre = new QLineEdit(this);
    synopsis = new QLabel("Synopsis :");
    mSynopsis = new QTextEdit(this);
    mSynopsis->setAlignment(Qt::AlignJustify);

    QGridLayout *mainLayout = new QGridLayout;
    this->setLayout(mainLayout);



    mainLayout->addWidget(title, 0,2,1,1);
    mainLayout->addWidget(mTitle,0,3,1,1);
    mainLayout->addWidget(lenght, 1,2,1,1);
    mainLayout->addWidget(mLenght,1,3,1,1);
    mainLayout->addWidget(genre, 2,2,1,1);
    mainLayout->addWidget(mGenre,2,3,1,2);
    mainLayout->addWidget(synopsis, 4,1,1,1);
    mainLayout->addWidget(mSynopsis,4,2,2,2);

    QStringListModel *model = new QStringListModel();

    model->setStringList(listFilm);
    liste = new QListView(this);
    liste->setMaximumWidth(300);
    liste->setModel(model);
    QItemSelectionModel *itemModel = liste->selectionModel();

    mainLayout->addWidget(liste,0,0,1,1);



    QObject::connect(liste,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(listeClicked(QModelIndex)));
    QObject::connect(itemModel, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(changeItem(QModelIndex,QModelIndex)));
}


void MainWindow::promptTime() {
    mTitle->setText(QTime::currentTime().toString());
}


void MainWindow::listeClicked(QModelIndex a)
{
    temp = new queryTmdb(this, MainWindow::cleanName(a.data().toString()));
    QObject::connect(temp, SIGNAL(endRequest(Movie)), this, SLOT(insertMovie(Movie)));


    mTitle->repaint();
    mLenght->repaint();
    mSynopsis->repaint();
}


void MainWindow::telechargement()
{
  /*  QString query;
    query = "http://private-4021-themoviedb.apiary.io/3/movie/550?api_key=" + api_key + "&language=fr";
    const QUrl url = QUrl(query); //On récupère l'URL entrée par l'utilisateur.
    QNetworkRequest requete(url);

    requete.setRawHeader("Accept", "application/json");

    QNetworkAccessManager *m = new QNetworkAccessManager; //On crée le QNetworkAccessManager qui va traiter la requête

    Ensuite, on utilise la méthode get() pour télécharger le contenu de notre requête.
    On récupère un pointeur de QNetworkReply.
    QNetworkReply *r = m->get(requete);


  //  connect(r, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(messageErreur(QNetworkReply::NetworkError)));
    connect(r, SIGNAL(finished()), this, SLOT(enregistrer()));*/


}

void MainWindow::enregistrer() {


}


void MainWindow::insertMovie(Movie m) {
    if(!sqlDb->insertMovie(m)){
        qDebug() << "Erreur insertion film";
    }
}


void MainWindow::setSelelectedMovie(Movie current) {
    selectedMovie = current;
}


void MainWindow::changeItem(QModelIndex a, QModelIndex old)
{
    this->setSelelectedMovie(sqlDb->getMovie(cleanName(a.data().toString())));

    mTitle->setText(selectedMovie.getTitle());
    mLenght->setText(QString::number(selectedMovie.getRuntime()));
    mSynopsis->setText(selectedMovie.getSynopsis());

    mTitle->repaint();
    mLenght->repaint();
    mSynopsis->repaint();

}

QString MainWindow::cleanName(QString fileName) {
    QString cleanedFileName = fileName;
    int firstSpamIndex = 100;

    //Replace '.' with whitespace
    cleanedFileName.replace('.',' ');

    QStringList spamNames;
    spamNames << "FRENCH" << "TRUEFRENCH" << "BDRIP" << "DVDRIP" << "1080p" << "720p" << "XVID" << "HD" << "SD" << "MD" <<"R5" << "HDRip" << "TS" << "DVDscr";
    for(int i=0; i< spamNames.count(); i++){
       // qDebug() << "Searching for :" << spamNames.value(i);
        if(firstSpamIndex > cleanedFileName.indexOf(spamNames.value(i),0, Qt::CaseInsensitive) && cleanedFileName.indexOf(spamNames.value(i),0, Qt::CaseInsensitive) != -1) {
            firstSpamIndex = cleanedFileName.indexOf(spamNames.value(i),0, Qt::CaseInsensitive);
        }
    }

    //qDebug() << "First Index :" << firstSpamIndex;

    if(firstSpamIndex!=-1 && firstSpamIndex!=100) {
        cleanedFileName.remove(firstSpamIndex, cleanedFileName.count()-1);
    }

    //Searching index of [ and ] chars
    int openBracket = cleanedFileName.indexOf('[');
    int closeBracket = cleanedFileName.indexOf(']');

    //Remove content [...]
    if(openBracket != -1 && closeBracket != -1 && openBracket < closeBracket) {
        cleanedFileName.remove(openBracket, closeBracket-openBracket+1);
    }

    //Check is first char is a whitespace & remove it
    if(cleanedFileName.at(0) == ' ') {
        cleanedFileName.remove(0,1);
    }
    if(cleanedFileName.at(cleanedFileName.count()-1) == ' ') {
        cleanedFileName.remove(cleanedFileName.count()-1,1);
    }

    //qDebug() << cleanedFileName;

   return cleanedFileName;

}
