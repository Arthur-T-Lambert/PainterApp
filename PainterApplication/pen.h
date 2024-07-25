/*!\file board.h
 *
 * \brief Classe Pen gérant le widget de dessin libre
 */

#ifndef PEN_H
#define PEN_H

#include <QWidget>
#include <QPen>
#include <QColor>
#include <QList>
#include <QPoint>
#include <QMouseEvent>
#include <QPainter>

class Pen : public QWidget
{
    Q_OBJECT

public:
    Pen(QWidget *parent);
    Pen(Qt::PenStyle style, QColor color, int width);

    void setColor(const QColor &color);
    void setStyle(const Qt::PenStyle &style);
    void setWidth(int width);
    bool isDrawing();
    QColor getColor();
    Qt::PenStyle getStyle();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event, QPainter &painter);

private:
    QPen pen;
    QList<QPoint> currentPoints; // Conteneur de points en cour d'affichage (clique souris maintenu)
    QList<QList<QPoint>> listPoints; // Conteneur de tous les points déssinés
    bool draw;
};

#endif // PEN_H
