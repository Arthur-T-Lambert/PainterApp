#include "pen.h"


//------------------------------------------------------------------------------------------
/** \brief Constructeur par défaut de la classe Pen
 */
Pen::Pen(QWidget *parent) : QWidget(parent)
{
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
}

//------------------------------------------------------------------------------------------
/** \brief Constructeur avec initialisation du style et de la couleur
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
/** \brief Fonction setter de la couleur du pen
 *  \param color Couleur du pen
 */
void Pen::setColor(const QColor &color)
{
    pen.setColor(color);
    this->color = color;
    update();
}

//------------------------------------------------------------------------------------------
/** \brief Fonction setter du style du pen
 *  \param style Style du pen
 */
void Pen::setStyle(const Qt::PenStyle &style)
{
    pen.setStyle(style);
    update();
}

//------------------------------------------------------------------------------------------
/** \brief Fonction setter de la largeur du pen
 *  \param width Largeur du pen
 */
void Pen::setWidth(int width)
{
    pen.setWidth(width);
    update();
}

//------------------------------------------------------------------------------------------
/** Brief Fonction setter de la largeur du pen
 *  \return Return true si la fonction de dessin est activée, et false dans le cas contraire
 */
bool Pen::isDrawing()
{
    return this->_bdraw;
}

//------------------------------------------------------------------------------------------
/** \brief Fonction getter de la couleur du pen
 *  \return Couleur du pen
 */
QColor Pen::getColor()
{
    return pen.color();
}

//------------------------------------------------------------------------------------------
/** \brief Fonction aui actiive le mode de dessin
 *  \param val true pour activer et false pour désactiver
 */
void Pen::setDrawingMode(bool val)
{
    _bdraw = val;
    if(_bdraw)
    {
        pen.setColor(color);
        currentPoints.clear();
    }
}

//------------------------------------------------------------------------------------------
/** \brief Fonction aui actiive le mode gomme
 *  \param val true pour activer et false pour désactiver
 */
void Pen::setEraseMode(bool val)
{
    erase = val;
}

//------------------------------------------------------------------------------------------
/** \brief Fonction de gestion des cliques de la souris
 *  \param event Pointeur sur les évenemets souris
 */
void Pen::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        clickLeft = true;
        currentPoints.append(event->pos());
    }
}

//------------------------------------------------------------------------------------------
/** \brief Fonction de gestion des mouvements de la souris
 *  \param event Pointeur sur les évenemets souris
 */
void Pen::mouseMoveEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        clickLeft = true;


    if (erase)
    {
        // Efface les points sous le curseur
        QList<DrawPoint>::iterator it = listPoints.begin();

        while (it != listPoints.end())
        {
            QList<QPoint>::iterator pointIt = it->tabPoints.begin();

            while (pointIt != it->tabPoints.end())
            {
                if (std::hypot(event->pos().x() - pointIt->x(), event->pos().y() - pointIt->y()) < 25)
                {
                    pointIt = it->tabPoints.erase(pointIt);
                }
                else
                {
                    pointIt++;
                }
            }
            if (it->tabPoints.isEmpty())
            {
                it = listPoints.erase(it);
            }
            else
            {
                it++;
            }
        }
        update();
    }
    else if (_bdraw)
    {
        // Mode dessin
        currentPoints.append(event->pos());
        update();
    }
}

//------------------------------------------------------------------------------------------
/** \brief Fonction de gestion des relachements de clique souris
 *  \param event Pointeur sur les évenemets souris
 */
void Pen::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton && _bdraw)
    {
        _bdraw = false;
        clickLeft = false;
        if (!currentPoints.isEmpty())
        {
            listPoints.append({currentPoints, pen});  // On ajoute les points courants au conteneur de points
            currentPoints.clear();
        }
    }

    if (event->button() == Qt::LeftButton && erase)
        clickLeft = false;

    update();
}

void Pen::save(QDataStream &)
{
    /* NOT IMPLEMENTED YET */
}

// void Pen::undo()
// {
//     if (!undoStack.isEmpty())
//     {
//         redoStack.push(listPoints);
//         listPoints = undoStack.pop();
//         update();
//     }
// }

// void Pen::redo()
// {
//     if (!redoStack.isEmpty()) {
//         undoStack.push(listPoints); // Enregistrer l'état actuel dans la pile Undo
//         listPoints = redoStack.pop(); // Restaurer l'état suivant
//         update(); // Demande de redessiner le widget
//     }
// }

//------------------------------------------------------------------------------------------
/** \brief Fonction mainLoop de la classe Pen gérant l'affichage des points courants et précédement
 *  déssinés sur le painter du board passé en paramètre
 *  \param event Pointeur sur les évenements QPaintEvent
 *  \param painter Pointeur sur les évenements QPaintEvent
 */
void Pen::draw(QPainter *painter)
{
    // Dessiner les points précédents
    for (const DrawPoint &point : listPoints)
    {
        painter->setPen(point.pen); // On recharge le pen et ses caractéristiques
        for (int i=0; i < point.tabPoints.size()-1; ++i)
            painter->drawLine(point.tabPoints[i], point.tabPoints[i+1]);
    }

    // Si gomme, ajouter un cercle a la position du curseur de la souris
    if(erase )
    {
        painter->setPen(QPen(Qt::gray, 2, Qt::SolidLine));
        painter->setBrush(Qt::NoBrush);
        QPoint cursorPos = mapFromGlobal(QCursor::pos());
        int rayon = 25;
        painter->drawEllipse(cursorPos , rayon, rayon);
    }

    // Dessiner les points courants si on est entrain de dessiner
    if (_bdraw)
    {
        painter->setPen(pen);
        for (int i=0; i < currentPoints.size()-1; ++i)
            painter->drawLine(currentPoints[i], currentPoints[i+1]);
    }


}

