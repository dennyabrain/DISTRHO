/*
 * Qt4 Demo plugin by falkTX <falktx@gmail.com>
 */

#ifndef STEREOAUDIOGAIN_UI_H
#define STEREOAUDIOGAIN_UI_H

#include "UiBase.h"
#include <QtGui/QGraphicsScene>

namespace Ui {
class XYControllerW;
}

class XYGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    XYGraphicsScene(QWidget* parent);
    ~XYGraphicsScene();

    void setPosX(float x, bool forward=true);
    void setPosY(float y, bool forward=true);
    void setSmooth(bool smooth);
    void setSmoothValues(int x, int y);
    void updateSize(QSize size);
    void updateSmooth();

signals:
    void cursorMoved(float, float);

protected:
    void keyPressEvent(QKeyEvent*);
    void wheelEvent(QGraphicsSceneWheelEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void handleMousePos(const QPointF&);

private:
    bool m_mouseLock;
    bool m_smooth;
    float m_smooth_x, m_smooth_y;

    QGraphicsEllipseItem* m_cursor;
    QGraphicsLineItem* m_lineH;
    QGraphicsLineItem* m_lineV;
    QRectF p_size;
};

class XYControllerUi : public DistrhoUiBase
{
    Q_OBJECT

public:
    XYControllerUi();
    ~XYControllerUi();

    bool d_isUiResizable();
    void d_setParameterValue(quint32 index, float value);
    void d_setProgram(quint32 index);

    // -----------------------------------------------------------------------------------------

public Q_SLOTS:
    void setSmooth(bool);
    void sceneCursorMoved(float xp, float yp);
    void updateSceneX(int x, bool sendEmit=true);
    void updateSceneY(int y, bool sendEmit=true);
    void updateScreen();

protected:
    Ui::XYControllerW* ui;

    void timerEvent(QTimerEvent*);
    void resizeEvent(QResizeEvent*);

private:
    XYGraphicsScene* scene;

    int m_smoothTimerId;
    bool m_firstInit;
};

#endif // STEREOAUDIOGAIN_UI_H
