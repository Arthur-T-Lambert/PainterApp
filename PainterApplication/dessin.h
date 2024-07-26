#ifndef DESSIN_H
#define DESSIN_H

#include <QPoint>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dessin;
}
QT_END_NAMESPACE

class Dessin
{
public:
    Dessin();

    virtual void move(const QPoint &delta) = 0;

    virtual QPoint getPosition() const {return QPoint(); }
    virtual void SetPosition(const QPoint& point) {Q_UNUSED(point);}
};

#endif // DESSIN_H
