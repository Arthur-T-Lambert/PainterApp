#include "board.h"

/** Brief Constructeur de la classe Board
 *  \param parent Pointeur sur le widget parent
 *  \param ui Association du user interface
 *  \param zoomVal Valeur par défaut du zoom, définit à 1.0
 */
Board::Board(QWidget *parent) : QWidget(parent), ui(new Ui::Board), zoomVal(1.0)
{
    ui-> setupUi(this);
}

/** Brief Déstructeur de la classe Board */
Board::~Board()
{
    delete ui;
}

/** Brief Fonction de gestion du rendu graphique
 *  \param event Pointeur sur les évènements récupérés
*/
void Board::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    changeScale(painter); // Gestion du zoom
    draw(painter); // Dessiner
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

/** Gestion des évènements de la molette souris
 *  \param event Pointeur sur les évènements molettes récupérés
*/
void Board::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
        zoomPlus();
    else
        zoomMoins();
}

/** Brief Fonction de dessin
 *  \param painter Pointeur sur le canva painter
 */
void Board::draw(QPainter &painter)
{
    painter.drawRect(QRect(10,10,50,50));
}

/** Brief Fonction de rafraichissement du widget */
void Board::refresh()
{
    update();
}

/** Brief Fonction dynamique de gestion du zoom du widget
 *  \param painter Pointeur sur le canva painter
 */
void Board::changeScale(QPainter &painter)
{
    painter.scale(zoomVal, zoomVal);
}

/** Brief Fonction de zoom avant du widget */
void Board::zoomPlus()
{
    zoomVal *= 1.1;
    refresh();
}

/** Brief Fonction de zoom arrière du widget */
void Board::zoomMoins()
{
    zoomVal /= 1.1;
    refresh();
}
