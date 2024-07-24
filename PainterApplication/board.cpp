#include "Board.h"
#include <QPainter>
#include <QMouseEvent>

/** Brief Constructeur de la classe Board
 *  \param parent Pointeur sur le widget parent
 */
Board::Board(QWidget *parent) : QWidget(parent)
{

}

/** Brief Déstructeur de la classe Board */
Board::~Board()
{

}

/** Brief Fonction de gestion du rendu graphique
 *  \param event Pointeur sur les évènements récupérés
*/
void Board::paintEvent(QPaintEvent *event)
{
    //Dessiner
    draw();
}

/** Brief Gestion des cliques de la souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mousePressEvent(QMouseEvent *event)
{

}

/** Brief Gestion des mouvements de la souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mouseMoveEvent(QMouseEvent *event)
{

}

/** Gestion des relâchements de clic de souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mouseReleaseEvent(QMouseEvent *event)
{

}

/** Brief Fonction d'affichage de formes ou dessins sur le widget */
void Board::draw()
{

}
