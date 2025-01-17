#include <QPainter>
#include <QPoint>

#include "shapes.h"

Ellipse::Ellipse(const QRect &r) : rect(r) {}

void Ellipse::draw(QPainter *painter) {
        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawEllipse(rect);
}

void Ellipse::setProperties(const QPen &pen, const QBrush &brush) {
        this->pen = pen;
        this->brush = brush;
}

void Ellipse::move(const QPoint &delta) {
        rect.translate(delta);
}

bool Ellipse::contains(const QPoint &point) {
    return rect.contains(point);
}

void Ellipse::save(QDataStream& stream)
{
    stream << QString("Ellipse") << rect << pen << brush;
}

Rectangle::Rectangle(const QRect &r) : rect(r) {}

void Rectangle::draw(QPainter *painter) {
        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawRect(rect);
}

void Rectangle::setProperties(const QPen &pen, const QBrush &brush) {
        this->pen = pen;
        this->brush = brush;
}

void Rectangle::move(const QPoint &delta) {
        rect.translate(delta);
}

bool Rectangle::contains(const QPoint &point) {
    return rect.contains(point);
}

void Rectangle::save(QDataStream& stream)
{
    stream << QString("Rectangle") << rect << pen << brush;
}

Star::Star(const QPoint &c, int r) : center(c), radius(r) {
        updatePolygon();
}

void Star::draw(QPainter *painter) {
        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawPolygon(polygon, Qt::WindingFill);
}

void Star::setProperties(const QPen &pen, const QBrush &brush) {
        this->pen = pen;
        this->brush = brush;
}

void Star::move(const QPoint &delta) {
        center += delta;
        updatePolygon();
}

bool Star::contains(const QPoint &point){
    return polygon.containsPoint(point, Qt::WindingFill);
}

void Star::save(QDataStream &stream)
{
    stream << QString("Star") << center << radius << pen << brush;
}

void Star::updatePolygon() {
        polygon.clear();
        for (int i = 0; i < 5; ++i) {
            polygon << QPoint(center.x() + radius * cos(0.8 * i * M_PI), center.y() + radius * sin(0.8 * i * M_PI));
        }
}

ImageQuick::ImageQuick(const QRect &r, const QString &path) : rect(r), imagePath(path) {
        image.load(imagePath);
}

void ImageQuick::draw(QPainter *painter) {
        painter->drawImage(rect, image);
}

void ImageQuick::setProperties(const QPen &, const QBrush &) {
        // No pen or brush properties needed for images
}
void ImageQuick::move(const QPoint &delta) {
        rect.translate(delta);
}

bool ImageQuick::contains(const QPoint &point) {
    return rect.contains(point);
}

void ImageQuick::save(QDataStream &)
{

}

