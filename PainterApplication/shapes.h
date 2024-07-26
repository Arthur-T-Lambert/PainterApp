#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QPoint>

#include "dessin.h"

class Shapes : public Dessin {
public:
    // virtual void draw(QPainter *painter) = 0;
    virtual void setProperties(const QPen &pen, const QBrush &brush) = 0;
    virtual void move(const QPoint &delta) = 0;
    virtual ~Shapes() {}
   // virtual void undo() = 0;
   // virtual void redo() = 0;
    virtual bool contains(const QPoint &point) = 0;
};

class Ellipse : public Shapes {
public:
    Ellipse(const QRect &r);
    void draw(QPainter *painter) override;
    void setProperties(const QPen &pen, const QBrush &brush) override;
    void move(const QPoint &delta) override;
    bool contains(const QPoint &point) override;

private:
    QRect rect;
    QPen pen;
    QBrush brush;
};

class Rectangle : public Shapes {
public:
    Rectangle(const QRect &r);
    void draw(QPainter *painter) override;
    void setProperties(const QPen &pen, const QBrush &brush) override;
    void move(const QPoint &delta) override;
    bool contains(const QPoint &point) override;

private:
    QRect rect;
    QPen pen;
    QBrush brush;
};

class Star : public Shapes {
public:
    Star(const QPoint &c, int r);
    void draw(QPainter *painter) override;
    void setProperties(const QPen &pen, const QBrush &brush) override;
    void move(const QPoint &delta) override;
    bool contains(const QPoint &point) override;

private:
    void updatePolygon();

    QPoint center;
    int radius;
    QPen pen;
    QBrush brush;
    QPolygon polygon;
};

class ImageQuick : public Shapes {
public:
    ImageQuick(const QRect &r, const QString &path);
    void draw(QPainter *painter) override;
    void setProperties(const QPen &, const QBrush &) override;
    void move(const QPoint &delta) override;
    bool contains(const QPoint &point) override;

private:
    QRect rect;
    QString imagePath;
    QImage image;
};

#endif // SHAPE_H
