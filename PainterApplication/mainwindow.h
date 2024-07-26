#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QList>

#include "board.h"

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

    /**
     * @brief getcurrentPen()
     *     An accessor to the current QPen property
     *     (The outline for the new Shapes created)
     * @return the current QPen
     */
    const QPen& getcurrentPen() const
    {
        return _currentPen;
    }

    /**
     * @brief getcurrentBrush()
     *     An accessor to the current QBrush property
     *     (The filling for the new Shapes created)
     * @return
     */
    const QBrush& getcurrentBrush() const
    {
        return _currentBrush;
    }

    void resetIconToolBar();

private slots:

    /**
     * @brief on_actionQuit_triggered
     * slot called when action "Quit" is triggered
     */
    void on_actionQuit_triggered();

protected:
    /**
     * @brief Handles the drag enter event.
     *
     * This function is called when a drag operation enters the widget.
     *
     * @param event Pointer to the QDragEnterEvent object containing event details.
     */

    void dragEnterEvent(QDragEnterEvent *event) override;
    /**
     * @brief Handles the drag move event.
     *
     * This function is called when a drag operation is moved within the widget.
     *
     * @param event Pointer to the QDragMoveEvent object containing event details.
     */

    void dragMoveEvent(QDragMoveEvent *event) override;
    /**
     * @brief Handles the drop event.
     *
     * This function is called when a drag operation is dropped on the widget.
     *
     * @param event Pointer to the QDropEvent object containing event details.
     */
    void dropEvent(QDropEvent *event) override;
    /**
     * @brief Handles the mouse press event.
     *
     * This function is called when a mouse button is pressed on the widget.
     *
     * @param event Pointer to the QMouseEvent object containing event details.
     */
    void mousePressEvent(QMouseEvent *event) override;

private:
    void on_directColor_clicked(const QColor&);

private slots:
    void on_fillColorPB_clicked();

    void on_fillStyleCB_currentIndexChanged(int index);

    void on_actionPen_triggered();

    void on_actionSelect_triggered();

    /**
     * @brief on_penWidthSB_valueChanged
     * slot triggered when using the pen width spinbox
     * @param width
     * the width value selected
     */
    void on_penWidthSB_valueChanged(int width);

    /**
     * @brief on_penColorPB_clicked
     * slot triggered when pressing on the pen color button
     */
    void on_penColorPB_clicked();

    void on_actionEraser_triggered();

    /**
     * @brief on_penStyleCB_currentIndexChanged
     * slot triggered when changing the pen style combobox
     * @param index
     * index of the style selected (0 to 3)
     */
    void on_penStyleCB_currentIndexChanged(int index);

    void on_actionEllipse_triggered();

    void on_actionRectangle_triggered();

    void on_actionStar_triggered();


    void on_showGrid_SpinBox_stateChanged(int arg1);

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;

    QPen _currentPen;
    QBrush _currentBrush;
    Board *board;
};
#endif // MAINWINDOW_H






