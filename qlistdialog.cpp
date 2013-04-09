#include "qlistdialog.h"

QListDialog::QListDialog(QStringList listFilm, QWidget *parent) : QDialog(parent)
{
    resize(400, 300);
    setWindowFlags ( Qt::Dialog );
    setWindowTitle("Résultat de la recherche");
    selectedItem = -1;
    YourData = new QStringListModel(listFilm,this);
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

void QListDialog::Activate(const QModelIndex &index)
{
    if (!index.isValid()) {
    return;
    }
    selectedItem = index.row();
}

int QListDialog::getItem()
{
    return selectedItem;
}
