#include "board.h"

//------------------------------------------------------------------------------------------
/** Brief Constructeur de la classe Board
 *  \param parent Pointeur sur le widget parent
 *  \param ui Association du user interface
 */
Board::Board(QWidget *parent) : QWidget(parent), ui(new Ui::Board)
{
    zoomVal = 1.0;
    translateWidget = {0,0};
    lastMousePosition = {0,0};

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

    // Affichage du background
    drawBackground(painter, Qt::SolidPattern , Qt::yellow); //Valeur à remplacer dynamiquement

    // Gestion des dimensions en fonction du zoom et de la translation
    updateDimensionAndPosition(painter);

    // Affichage de la grille
    drawGrid(painter);

    /*
     * Shapes à dessiner ici
    */
}

//------------------------------------------------------------------------------------------
/** Brief Fonction d'affichage du background
 *  \param painter Pointeur sur le canva painter
 *  \param color Couleur du background
 */
void Board::drawBackground(QPainter &painter, const Qt::BrushStyle brushStyle, const Qt::GlobalColor &brushColor)
{
    QBrush brush;
    brush.setColor(brushColor);
    brush.setStyle(brushStyle);
    painter.setBrush(brush);
    painter.drawRect(rect());
}


//------------------------------------------------------------------------------------------
/** Brief Fonction d'affichage de la grille en background
 *  \param event Pointeur sur les évènements récupérés
*/
void Board::drawGrid(QPainter &painter)
{
    int gridSpacing = 30;
    QPen pen(Qt::gray, 1, Qt::SolidLine);
    painter.setPen(pen);

    int width = this->width();
    int height = this->height();

    // Lignes verticales
    for (int x = 0; x < width; x += gridSpacing) {
        painter.drawLine(x, 0, x, height);
    }
    // Lignes horizontales
    for (int y = 0; y < height; y += gridSpacing) {
        painter.drawLine(0, y, width, y);
    }
}

//------------------------------------------------------------------------------------------
/** Brief Fonction dynamique de gestion du zoom et de la translation du widget
 *  \param painter Pointeur sur le canva painter
 */
void Board::updateDimensionAndPosition(QPainter &painter)
{
    // Application de la transformation pour la translation et le zoom
    painter.setTransform(QTransform().translate(translateWidget.x(), translateWidget.y()).scale(zoomVal, zoomVal));
}


//------------------------------------------------------------------------------------------
/** Brief Gestion des cliques de la souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mousePressEvent(QMouseEvent *event)
{
    // Récupération de l'event clique gauche
    if (event->button() == Qt::LeftButton)
    {
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
        QPoint delta = (event->pos() - lastMousePosition);
/*
        // Si une forme est séléctionnée, on la déplace en tenant compte du zoom
        if (indexShapeSelected != -1)
        {

            shapes[indexShapeSelected].moveLeft(shapes[indexShapeSelected].left() + delta.x() / zoomVal);
            shapes[indexShapeSelected].moveTop(shapes[indexShapeSelected].top() + delta.y() / zoomVal);
        }

        // Sinon, on déplace le widget en vue panoramique
        else
        {
            translateWidget += delta / zoomVal;
        }
*/

        translateWidget += delta / zoomVal;
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
    indexShapeSelected = -1; // Reset de l'index de la forme séléctionné
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
