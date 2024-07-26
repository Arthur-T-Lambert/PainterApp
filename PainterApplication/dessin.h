#ifndef DESSIN_H
#define DESSIN_H

#include <QPoint>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dessin;
}
QT_END_NAMESPACE

/**
 * \class Dessin
 * \brief Base class for all drawing that can be added to the board.
 */
class Dessin
{
public:
    /**
     * \brief Dessin constructor.
     */
    Dessin();

    /**
     * \brief Dessin destructor.
     */
    virtual ~Dessin() {}

    /**
     * \brief Move method.
     * \param delta Move vector from the old position to the new position.
     */
    virtual void move(const QPoint &delta) = 0;

    /**
     * \brief Draw method, draw the dessin to a QPainter
     * \param painter The QPainter to draw the dessin.
     */
    virtual void draw(QPainter *painter) = 0;

    /**
     * \brief Getter fot the position of a Dessin.
     * \return The position of the Dessin.
     */
    // virtual QPoint getPosition() const = 0;
    virtual QPoint getPosition() const { return QPoint(); }
    /**
     * \brief Setter fot the position of a Dessin.
     * \param The new position of the Dessin.
     */
    // virtual void SetPosition(const QPoint& point) = 0;
    virtual void SetPosition(const QPoint& point) { Q_UNUSED(point);}
};

#endif // DESSIN_H
