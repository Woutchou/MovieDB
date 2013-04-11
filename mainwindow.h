#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <movie.h>
#include <database.h>
#include <querytmdb.h>

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QListView>
#include <QStringList>
#include <QSqlDatabase>




class MainWindow : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT

    public:
    MainWindow();
    QStringList *listeFilm;

    public slots:
    void listeClicked(QModelIndex a);
    void telechargement();
    void enregistrer();

    void insertMovie(Movie);
    void changeItem(QModelIndex, QModelIndex);
    void setSelelectedMovie(Movie);
    static QString cleanName(QString fileName);


    private:
    QPushButton *m_button;
    QGridLayout *mainLayout;
    QLabel *title;
    QLineEdit *mTitle;
    QLabel *lenght;
    QLineEdit *mLenght;
    QLabel *genre;
    QLineEdit *mGenre;
    QLabel *synopsis;
    QTextEdit *mSynopsis;
    QListView *liste;
    QLabel *poster;


    Database *sqlDb;
    QStringList listFilm;

    queryTmdb *temp;
    Movie selectedMovie;


};

#endif // MAINWINDOW_H
