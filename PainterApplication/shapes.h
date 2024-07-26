/**
 * @file Shape.h
 * @brief Declarations of classes for drawing shapes.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QPoint>

class Dessin {
public:
    virtual void move(const QPoint &delta) = 0;
   // virtual void undo() = 0;
   // virtual void redo() = 0;
};

/**
 * @brief Abstract base class for shapes.
 */

class Shapes : public Dessin {
public:
    /**
     * @brief Draws the shape.
     * @param painter The QPainter used to draw the shape.
     */
    virtual void draw(QPainter *painter) = 0;
    /**
     * @brief Sets the properties of the shape.
     * @param pen The QPen used to draw the shape's outline.
     * @param brush The QBrush used to fill the shape.
     */
    virtual void setProperties(const QPen &pen, const QBrush &brush) = 0;
    /**
     * @brief Moves the shape.
     * @param delta The translation to apply to the shape.
     */
    virtual void move(const QPoint &delta) = 0;
    /**
     * @brief Destroys the shape.
     */
    virtual ~Shapes() {}
   // virtual void undo() = 0;
   // virtual void redo() = 0;
    /**
     * @brief Checks if a point is contained within the shape.
     * @param point The point to check.
     * @return true if the point is contained, false otherwise.
     */
    virtual bool contains(const QPoint &point) = 0;
};

/**
 * @brief Class representing an ellipse shape.
 */

class Ellipse : public Shapes {
public:
    /**
     * @brief Constructor for the ellipse.
     * @param r The bounding rectangle of the ellipse.
     */
    Ellipse(const QRect &r);
    /**
     * @brief Draws the ellipse.
     * @param painter The QPainter used to draw the ellipse.
     */
    void draw(QPainter *painter) override;
    /**
     * @brief Sets the properties of the ellipse.
     * @param pen The QPen used to draw the ellipse's outline.
     * @param brush The QBrush used to fill the ellipse.
     */
    void setProperties(const QPen &pen, const QBrush &brush) override;
    /**
     * @brief Moves the ellipse.
     * @param delta The translation to apply to the ellipse.
     */
    void move(const QPoint &delta) override;
    /**
     * @brief Checks if a point is contained within the ellipse.
     * @param point The point to check.
     * @return true if the point is contained, false otherwise.
     */
    bool contains(const QPoint &point) override;

private:
    QRect rect;///< The bounding rectangle of the ellipse.
    QPen pen;///< The pen used to draw the ellipse's outline.
    QBrush brush;///< The brush used to fill the ellipse.
};

/**
 * @brief Class representing a rectangle shape.
 */
class Rectangle : public Shapes {
public:
    /**
     * @brief Constructor for the rectangle.
     * @param r The bounding rectangle.
     */
    Rectangle(const QRect &r);
    /**
     * @brief Draws the rectangle.
     * @param painter The QPainter used to draw the rectangle.
     */
    void draw(QPainter *painter) override;
    /**
     * @brief Sets the properties of the rectangle.
     * @param pen The QPen used to draw the rectangle's outline.
     * @param brush The QBrush used to fill the rectangle.
     */
    void setProperties(const QPen &pen, const QBrush &brush) override;
    /**
     * @brief Moves the rectangle.
     * @param delta The translation to apply to the rectangle.
     */
    void move(const QPoint &delta) override;
    /**
     * @brief Checks if a point is contained within the rectangle.
     * @param point The point to check.
     * @return true if the point is contained, false otherwise.
     */
    bool contains(const QPoint &point) override;

private:
    QRect rect;///< The bounding rectangle.
    QPen pen;///< The pen used to draw the rectangle's outline.
    QBrush brush;///< The brush used to fill the rectangle.
};

/**
 * @brief Class representing a star shape.
 */
class Star : public Shapes {
public:
    /**
     * @brief Constructor for the star.
     * @param c The center of the star.
     * @param r The radius of the star.
     */
    Star(const QPoint &c, int r);
    /**
     * @brief Draws the star.
     * @param painter The QPainter used to draw the star.
     */
    void draw(QPainter *painter) override;
    /**
     * @brief Sets the properties of the star.
     * @param pen The QPen used to draw the star's outline.
     * @param brush The QBrush used to fill the star.
     */
    void setProperties(const QPen &pen, const QBrush &brush) override;
    /**
     * @brief Moves the star.
     * @param delta The translation to apply to the star.
     */
    void move(const QPoint &delta) override;
    /**
     * @brief Checks if a point is contained within the star.
     * @param point The point to check.
     * @return true if the point is contained, false otherwise.
     */
    bool contains(const QPoint &point) override;

private:
    /**
     * @brief Updates the polygon representing the star.
     */
    void updatePolygon();

    QPoint center;///< The center of the star.
    int radius;///< The radius of the star.
    QPen pen;///< The pen used to draw the star's outline.
    QBrush brush;///< The brush used to fill the star.
    QPolygon polygon;///< The polygon representing the star.
};

/**
 * @brief Class representing an image.
 */
class ImageQuick : public Shapes {
public:
    /**
     * @brief Constructor for the image.
     * @param r The bounding rectangle of the image.
     * @param path The path to the image.
     */
    ImageQuick(const QRect &r, const QString &path);
    /**
     * @brief Draws the image.
     * @param painter The QPainter used to draw the image.
     */
    void draw(QPainter *painter) override;
    /**
     * @brief Sets the properties of the image.
     * @param pen Not used for images.
     * @param brush Not used for images.
     */
    void setProperties(const QPen &, const QBrush &) override;
    /**
     * @brief Moves the image.
     * @param delta The translation to apply to the image.
     */
    void move(const QPoint &delta) override;
    /**
     * @brief Checks if a point is contained within the image.
     * @param point The point to check.
     * @return true if the point is contained, false otherwise.
     */
    bool contains(const QPoint &point) override;

private:
    QRect rect;///< The bounding rectangle of the image.
    QString imagePath;///< The path to the image.
    QImage image;///< The image to display.
};

#endif // SHAPE_H
