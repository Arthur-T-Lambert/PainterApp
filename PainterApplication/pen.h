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
    void setStyle(const Qt::PenStyle &style);
    void setWidth(int width);
    QColor getColor();
    Qt::PenStyle getStyle();

private:
    QColor color;
    Qt::PenStyle style;
    int width
    QVector<QPoint> points;
};

#endif // PEN_H
