#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QList>
#include "Shapes.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

<<<<<<< HEAD
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
=======
private slots:
    void on_actionQuit_triggered();
>>>>>>> 759ef0ea031129d65752f00b560f62678cac4448

private:
    Ui::MainWindow *ui;
    QList<Shapes*> shapes;
    Shapes *draggedShape;
    QPoint lastMousePosition;

    void setupShapes();
};
#endif // MAINWINDOW_H






