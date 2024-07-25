#include "pen.h"


//------------------------------------------------------------------------------------------
/** Brief Constructeur par défaut de la classe Pen
 */
Pen::Pen():width(1), color(Qt::black){}

//------------------------------------------------------------------------------------------
/** Brief Constructeur avec initialisation du style et de la couleur
 *  \param style Style du pen
 *  \param color Couleur du pen
 */
Pen(Qt::PenStyle style, QColor color) : color(color), style(style){}

//------------------------------------------------------------------------------------------
/** Brief Fonction setter de la couleur du pen
 *  \param color Couleur du pen
 */
void Pen::setColor(const QColor &color)
{
    this->color = color;
}

//------------------------------------------------------------------------------------------
/** Brief Fonction setter du style du pen
 *  \param style Style du pen
 */
void Pen::setStyle(const Qt::PenStyle &style)
{
    this->style = style;
}

//------------------------------------------------------------------------------------------
/** Brief Fonction setter de la largeur du pen
 *  \param width Largeur du pen
 */
void Pen::setWidth(int width)
{
    if(width >=1 && width <= 15)
        this->width = width;
}

//------------------------------------------------------------------------------------------
/** Brief Fonction getter de la couleur du pen
 *  \return style Couleur du pen
 */
QColor Pen::getColor()
{
    return this->color;
}

//------------------------------------------------------------------------------------------
/** Brief Fonction getter du style du pen
 *  \return style Style du pen
 */
Qt::PenStyle Pen::getStyle()
{
    return this->style;
}
