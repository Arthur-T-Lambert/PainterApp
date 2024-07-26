#include "board.h"
//------------------------------------------------------------------------------------------
/** Brief Constructeur de la classe Board
 *  \param parent Pointeur sur le widget parent
 *  \param ui Association du user interface
 */
Board::Board(QWidget *parent) : QWidget(parent), ui(new Ui::Board),
    draggedShape(nullptr){

    zoomVal = 1.0;
    translateWidget = {0,0};
    lastMousePosition = {0,0};

    ui->setupUi(this);
    //setupShapes();
}

//------------------------------------------------------------------------------------------
/** Brief Déstructeur de la classe Board */
Board::~Board()
{
    delete ui;
    qDeleteAll(formes);
}

//------------------------------------------------------------------------------------------
/** Brief Fonction de gestion du rendu graphique
 *  \param event Pointeur sur les évènements récupérés
*/
void Board::paintEvent(QPaintEvent *event)
{
   // Q_UNUSED(event);
    QWidget::paintEvent(event);
    QPainter painter(this);

    // Affichage du background
    drawBackground(painter, Qt::SolidPattern , Qt::yellow); //Valeur à remplacer dynamiquement

    // Gestion des dimensions en fonction du zoom et de la translation
    updateDimensionAndPosition(painter);

    // Affichage de la grille
    drawGrid(painter);



    // Dessin des formes
    for (Shapes *shape : formes) {
        shape->draw(&painter);
    }


    // Dessiner la forme temporaire si on est en train de dessiner
    if (isDrawing) {
        QPainter tempPainter(this);
        tempPainter.setPen(QPen(Qt::red, 2, Qt::DashLine));
        QRect rect = QRect(lastMousePosition, this->mapFromGlobal(QCursor::pos())).normalized();

        switch(currentTool) {
        case RectangleTool:
            tempPainter.drawRect(rect);
            break;
        case EllipseTool:
            tempPainter.drawEllipse(rect);
            break;
        case StarTool:
        {
                QPoint center = rect.center();
                int radius = std::min(rect.width(), rect.height()) / 2;
                QPolygon polygon;
                const int numPoints = 5;
                const double angleStep = M_PI / numPoints;
                for (int i = 0; i < 2 * numPoints; ++i) {
                    double r = (i % 2 == 0) ? radius : radius / 2;
                    double angle = i * angleStep - M_PI / 2;
                    polygon << QPoint(center.x() + r * cos(angle), center.y() + r * sin(angle));
                }
                tempPainter.drawPolygon(polygon,Qt::WindingFill);
        }
            break;
        default:
            break;
        }
    }
}

//------------------------------------------------------------------------------------------
/** Brief Fonction d'affichage du background
 *  \param painter Pointeur sur le canva painter
 *  \param brushStyle Style dy brush
 *  \param color Couleur du brush
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

    if (event->button() == Qt::LeftButton)
    {
        lastMousePosition = event->pos();
        if (currentTool == RectangleTool || currentTool == EllipseTool || currentTool == StarTool) {
            isDrawing = true;
        } else if (currentTool == Cursor) {
            // Logique pour sélectionner/déplacer des formes existantes
            for (Shapes *shape : formes) {
                if (shape->contains(event->pos())) {
                    draggedShape = shape;
                    break;
                }
            }
        }
    }
}

//------------------------------------------------------------------------------------------
/** Brief Gestion des mouvements de la souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        if (isDrawing) {
            drawShape(lastMousePosition, event->pos());
        } else if (draggedShape && currentTool == Cursor) {
            QPoint delta = event->pos() - lastMousePosition;
            draggedShape->move(delta);
            lastMousePosition = event->pos();
            update();
        }
    }

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

        // translateWidget += delta / zoomVal;
        // lastMousePosition = event->pos();
        // refresh();

}

//------------------------------------------------------------------------------------------
/** Gestion des relâchements de clic de souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (isDrawing) {
            // Finaliser le dessin de la forme
            Shapes* newShape = createShape(lastMousePosition, event->pos());
            if (newShape) {
                formes.append(newShape);
            }
            isDrawing = false;
        }
        draggedShape = nullptr;
    }
    update();
}

Shapes* Board::createShape(const QPoint &start, const QPoint &end)
{
    QRect rect = QRect(start, end).normalized();

    QPen pen(Qt::black, 2, Qt::SolidLine);
    QBrush brush(Qt::white);

    switch(currentTool) {
    case RectangleTool:
        return new Rectangle(rect);
    case EllipseTool:
        return new Ellipse(rect);
    case StarTool:
    {
        // Calculer le centre et le rayon pour l'étoile
        QPoint center = rect.center();
        int radius = std::min(rect.width(), rect.height()) / 2;
        Star *star = new Star(center, radius);
        star->setProperties(pen, brush);
        return star;
    }
    default:
        return nullptr;
    }
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

void Board::addShape(Shapes *shape)
{
    formes.append(shape);
    update(); // Demande la redessination du tableau
}

void Board::drawShape(const QPoint &start, const QPoint &end)
{
    update();
}
void Board::setCurrentTool(Tool tool)
{
    currentTool = tool;
    updateCursor();
}

void Board::updateCursor()
{
    switch(currentTool) {
    case Cursor:
        setCursor(Qt::ArrowCursor);
        break;
    case RectangleTool:
        setCursor(QCursor(QPixmap(":/images/rectangle_cursor.png")));
        break;
    case EllipseTool:
        setCursor(QCursor(QPixmap(":/images/circle_cursor.png")));
        break;
    case StarTool:
        setCursor(QCursor(QPixmap(":/images/star_cursor.png")));
        break;
    default:
        setCursor(Qt::ArrowCursor);
    }
}
