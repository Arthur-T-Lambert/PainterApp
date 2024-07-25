#include "pen.h"


//------------------------------------------------------------------------------------------
/** Brief Constructeur par défaut de la classe Pen
 */
Pen::Pen(){}

//------------------------------------------------------------------------------------------
/** Brief Constructeur avec initialisation du style et de la couleur
 *  \param style Style du pen
 *  \param color Couleur du pen
 */
Pen(Qt::PenStyle style, QColor color);

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
void Pen::setStyle(const Qt::PenStyle style)
{
    this->penStyle = style;
}

QColor Pen::getColor()
{

}

