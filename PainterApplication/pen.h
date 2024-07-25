/*!\file board.h
 *
 * \brief Classe Pen gérant le widget de dessin libre
 */

#ifndef PEN_H
#define PEN_H

#include <QWidget>
#include <QPen>
#include <QColor>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QList>
#include <QPainter>
#include <QPoint>


// Structure permettant d'enregistrer les informations de chaques points dessinés
struct DrawPoint {
    QList<QPoint> tabPoints;
    QPen pen;
};


class Pen : public QWidget
{
    Q_OBJECT

public:
    Pen(QWidget *parent = nullptr);
    Pen(Qt::PenStyle style, QColor color, int width);

    void setStyle(const Qt::PenStyle &style);
    void setColor(const QColor &color);
    void setWidth(int width);
    bool isDrawing();
    QColor getColor();
    void paintEvent(QPaintEvent *event, QPainter &painter);
    void activateDrawing(bool val);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPen pen;
    QList<QPoint> currentPoints;  // Points du chemin en cours
    QList<DrawPoint> listPoints;  // Liste de tous les chemins dessinés
    bool draw;
};

#endif // PEN_H
