#include "pen.h"


//------------------------------------------------------------------------------------------
/** Brief Constructeur par défaut de la classe Pen
 */
Pen::Pen(QWidget *parent) : QWidget(parent)
{
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(10);

    draw = true; //test
}

//------------------------------------------------------------------------------------------
/** Brief Constructeur avec initialisation du style et de la couleur
 *  \param style Style du pen
 *  \param color Couleur du pen
 */
Pen::Pen(Qt::PenStyle style, QColor color, int width)
{
    pen.setColor(color);
    pen.setStyle(style);
    pen.setWidth(width);
}

//------------------------------------------------------------------------------------------
/** Brief Fonction setter de la couleur du pen
 *  \param color Couleur du pen
 */
void Pen::setColor(const QColor &color)
{
    pen.setColor(color);
    update();
}

//------------------------------------------------------------------------------------------
/** Brief Fonction setter du style du pen
 *  \param style Style du pen
 */
void Pen::setStyle(const Qt::PenStyle &style)
{
    pen.setStyle(style);
    update();
}

//------------------------------------------------------------------------------------------
/** Brief Fonction setter de la largeur du pen
 *  \param width Largeur du pen
 */
void Pen::setWidth(int width)
{
    if(width >=1 && width <= 15)
    {
        pen.setWidth(width);
        update();
    }
}

//------------------------------------------------------------------------------------------
/** Brief Fonction setter de la largeur du pen
 *  \return Return true si la fonction de dessin est activée, et false dans le cas contraire
 */
bool Pen::isDrawing()
{
    return this->draw;
}

//------------------------------------------------------------------------------------------
/** Brief Fonction de gestion des cliques de la souris
 *  \param event Pointeur sur les évenemets souris
 */
void Pen::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        currentPoints.append(event->pos());
    }
}

//------------------------------------------------------------------------------------------
/** Brief Fonction de gestion des mouvements de la souris
 *  \param event Pointeur sur les évenemets souris
 */
void Pen::mouseMoveEvent(QMouseEvent *event)
{
    if (draw)
    {
        currentPoints.append(event->pos());  // On ajoute tout les points au conteneur de points courants
        update();
    }
}

//------------------------------------------------------------------------------------------
/** Brief Fonction de gestion des relachements de clique souris
 *  \param event Pointeur sur les évenemets souris
 */
void Pen::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && draw)
    {
        draw = false;
        if (!currentPoints.isEmpty())
        {
            listPoints.append(currentPoints);  // On ajoute les points courants au conteneur de points
            currentPoints.clear();
        }
        update();
    }
}

//------------------------------------------------------------------------------------------
/** Brief Fonction mainLoop de la classe Pen gérant l'affichage des points courants et précédement
 *  déssinés sur le painter du board passé en paramètre
 *  \param event Pointeur sur les évenements QPaintEvent
 *  \param painter Pointeur sur les évenements QPaintEvent
 */
void Pen::paintEvent(QPaintEvent *event, QPainter &painter)
{
    //QPainter painter(this);
    painter.setPen(pen);

    // Dessiner les points précédents
    for (const QList<QPoint> &point : listPoints)
    {
        for (int i=0; i < point.size()-1; ++i)
            painter.drawLine(point[i], point[i+1]);
    }

    // Dessiner les points courants si on est entrain de dessiner
    if (draw)
    {
        for (int i=0; i < currentPoints.size()-1; ++i)
            painter.drawLine(currentPoints[i], currentPoints[i+1]);
    }
}

