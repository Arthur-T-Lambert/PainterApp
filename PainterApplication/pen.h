/*!\file board.h
 *
 * \brief Classe Pen gérant le widget d'affichage des formes et dessins
 */

#ifndef PEN_H
#define PEN_H

#include <QWidget>
#include <QPen>
#include <QBrushStyle>
#include <QColor>
#include <QVector>
#include <QPoint>

class Pen
{
    Q_OBJECT

public:
    Pen() = default;
    Pen(Qt::PenStyle style, QColor color);

    void setColor(const Qcolor &color);

private:
    QColor color;
    Qt::PenStyle penStyle;
    QVector<QPoint> points;

};

#endif // PEN_H
