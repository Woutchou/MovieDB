#ifndef QLISTDIALOG_H
#define QLISTDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QStringListModel>
#include <QListView>
#include <QPushButton>

class QListDialog : public QDialog
{
    Q_OBJECT
public:
    QListDialog(QStringList listFilm, QWidget *parent = 0);
    int getItem();
    
signals:
    
public slots:
    void Activate(const QModelIndex &index);

private:
    QGridLayout *gridLayout;
    QStringListModel *YourData;
    QListView *listView;
    QSpacerItem *spacerItem;
    QPushButton *pushButton;
    int selectedItem;

    
};

#endif // QLISTDIALOG_H
/*

#ifndef LISTDIALOG_H
#define LISTDIALOG_H

#include <QtGui>

#include <QtGui/qdialog.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QListView>
#include <QPushButton>
#include <QSpacerItem>
#include <QStringListModel>

class PDialog : public QDialog
{
    Q_OBJECT

public: PDialog( QWidget * parent , const QString tit , QStringList data  )
    : QDialog(parent)
{
  resize(400, 300);
  setWindowFlags ( Qt::Dialog );
  setWindowTitle(tit);
  currentdata = "-1";
  YourData = new QStringListModel(data,this);
  gridLayout = new QGridLayout(this);
  listView = new QListView(this);
  listView->setEditTriggers ( QAbstractItemView::NoEditTriggers );
  listView->setModel(YourData);
  gridLayout->addWidget(listView, 0, 0, 1, 2);
  spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  gridLayout->addItem(spacerItem, 1, 0, 1, 1);
  pushButton = new QPushButton(this);
  gridLayout->addWidget(pushButton, 1, 1, 1, 1);
  pushButton->setText(tr("OK"));
  connect(listView, SIGNAL(clicked(const QModelIndex &)),this, SLOT(Activate(const QModelIndex&)));
  connect(pushButton, SIGNAL(clicked()),this, SLOT(accept()));
}

QString data() {
   return  currentdata;
}

QGridLayout *gridLayout;
QStringListModel *YourData;
QListView *listView;
QSpacerItem *spacerItem;
QPushButton *pushButton;
QString currentdata;

    signals:
    public slots:
        void Activate( const QModelIndex &index ) {
                if (!index.isValid()) {
                return;
                }
                currentdata = index.data().toString();
        }
};

//
#endif // PDIALOG_H
*/
