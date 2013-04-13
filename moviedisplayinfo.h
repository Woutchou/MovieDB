#ifndef MOVIEDISPLAYINFO_H
#define MOVIEDISPLAYINFO_H

#include <QWidget>

namespace Ui {
class MovieDisplayInfo;
}

class MovieDisplayInfo : public QWidget
{
    Q_OBJECT
    
public:
    explicit MovieDisplayInfo(QWidget *parent = 0);
    ~MovieDisplayInfo();
    
private:
    Ui::MovieDisplayInfo *ui;
};

#endif // MOVIEDISPLAYINFO_H
