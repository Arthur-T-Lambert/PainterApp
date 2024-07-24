#include "board.h"

//------------------------------------------------------------------------------------------
/** Brief Constructeur de la classe Board
 *  \param parent Pointeur sur le widget parent
 *  \param ui Association du user interface
 *  \param zoomVal Valeur par défaut du zoom, définit à 1.0
 */
Board::Board(QWidget *parent) : QWidget(parent), ui(new Ui::Board)
{
    zoomVal = 1.0;
    translateWidget = {0,0};
    lastMousePosition = {0,0};
    brush.setColor(QColor(0,255,0));
    brush.setStyle(Qt::Dense5Pattern);
    ui->setupUi(this);
}

//------------------------------------------------------------------------------------------
/** Brief Déstructeur de la classe Board */
Board::~Board()
{
    delete ui;
}

//------------------------------------------------------------------------------------------
/** Brief Fonction de gestion du rendu graphique
 *  \param event Pointeur sur les évènements récupérés
*/
void Board::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //Affichage du background
    setBrush(Qt::Dense3Pattern, Qt::blue);
    painter.setBrush(brush);
    painter.drawRect(rect());

    //Gestion des dimensions en fonction du zoom et de la translation
    updateDimensionAndPosition(painter);

    //Affichage d'un rectangle
    setBrush(Qt::Dense5Pattern, Qt::green);
    painter.setBrush(brush);
    painter.drawRect(QRect(10,10,50,50));

}

//------------------------------------------------------------------------------------------
/** Brief Fonction paramétrage du brush
 *  \param style style du brush
 *  \param color Couleur du brush
*/
void Board::setBrush(Qt::BrushStyle style, QColor color)
{
    brush.setColor(color);
    brush.setStyle(style);
    refresh();
}

//------------------------------------------------------------------------------------------
/** Brief Fonction dynamique de gestion du zoom et de la translation du widget
 *  \param painter Pointeur sur le canva painter
 */
void Board::updateDimensionAndPosition(QPainter &painter)
{
    painter.scale(zoomVal, zoomVal); // Zoom du widget
    painter.translate(translateWidget); // Déplacement panoramique du widget
}

//------------------------------------------------------------------------------------------
/** Brief Gestion des cliques de la souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mousePressEvent(QMouseEvent *event)
{
    // Enregistrement de la position de la souris en cas de déplacement panoramique
    if (event->button() == Qt::LeftButton) {
        lastMousePosition = event->pos();
    }
}

//------------------------------------------------------------------------------------------
/** Brief Gestion des mouvements de la souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPoint delta = (event->pos() - lastMousePosition) / zoomVal;
        translateWidget += delta;
        lastMousePosition = event->pos();
        refresh();
    }
}

//------------------------------------------------------------------------------------------
/** Gestion des relâchements de clic de souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mouseReleaseEvent(QMouseEvent *event)
{

}

//------------------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------------------
/** Brief Fonction de rafraichissement du widget */
void Board::refresh()
{
    update();
}

//------------------------------------------------------------------------------------------
/** Brief Fonction de zoom avant du widget */
void Board::zoomPlus()
{
    if(zoomVal * 1.02 < 3)
    {
        zoomVal *= 1.02;
        refresh();
    }
}

//------------------------------------------------------------------------------------------
/** Brief Fonction de zoom arrière du widget */
void Board::zoomMoins()
{
    if(zoomVal / 1.02 > 0.5)
    {
        zoomVal /= 1.02;
        refresh();
    }
}
