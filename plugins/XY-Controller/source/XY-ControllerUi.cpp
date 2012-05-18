/*
 * Qt4 Demo plugin by falkTX <falktx@gmail.com>
 */

#include "XY-Controller.h"
#include "XY-ControllerUi.h"
#include "ui_xycontroller.h"

#include <QtCore/QTimer>
#include <QtGui/QKeyEvent>
#include <QtGui/QGraphicsEllipseItem>
#include <QtGui/QGraphicsLineItem>
#include <QtGui/QGraphicsSceneMouseEvent>
#include <QtGui/QGraphicsSceneWheelEvent>

float abs_f(float value)
{
    return (value < 0.0) ? -value : value;
}

XYGraphicsScene::XYGraphicsScene(QWidget* parent) :
    QGraphicsScene(parent)
{
    m_mouseLock = false;
    m_smooth = false;
    m_smooth_x = 0;
    m_smooth_y = 0;

    setBackgroundBrush(Qt::black);

    QPen   cursorPen(QColor(255,255,255), 2);
    QColor cursorBrush(255,255,255,50);
    m_cursor = addEllipse(QRectF(-10, -10, 20, 20), cursorPen, cursorBrush);

    QPen linePen(QColor(200,200,200,100), 1, Qt::DashLine);
    m_lineH = addLine(-9999, 0, 9999, 0, linePen);
    m_lineV = addLine(0, -9999, 0, 9999, linePen);

    p_size = QRectF(-100, -100, 100, 100);
}

XYGraphicsScene::~XYGraphicsScene()
{
}

void XYGraphicsScene::setPosX(float x, bool forward)
{
    if (! m_mouseLock)
    {
        int pos_x = x*(p_size.x()+p_size.width());
        m_cursor->setPos(pos_x, m_cursor->y());
        m_lineV->setX(pos_x);

        if (! forward)
            m_smooth_x = pos_x;
    }
}

void XYGraphicsScene::setPosY(float y, bool forward)
{
    if (! m_mouseLock)
    {
        int pos_y = y*(p_size.y()+p_size.height());
        m_cursor->setPos(m_cursor->x(), pos_y);
        m_lineH->setY(pos_y);

        if (! forward)
            m_smooth_y = pos_y;
    }
}

void XYGraphicsScene::setSmooth(bool smooth)
{
    m_smooth = smooth;
}

void XYGraphicsScene::setSmoothValues(int x, int y)
{
    m_smooth_x = x*(p_size.x()+p_size.width());
    m_smooth_y = y*(p_size.y()+p_size.height());
}

void XYGraphicsScene::updateSize(QSize size)
{
    p_size.setRect(-(size.width()/2), -(size.height()/2), size.width(), size.height());
}

void XYGraphicsScene::updateSmooth()
{
    if (m_smooth)
    {
        if (m_cursor->x() != m_smooth_x || m_cursor->y() != m_smooth_y)
        {
            if (abs_f(m_cursor->x() - m_smooth_x) <= 0.001)
            {
                m_smooth_x = m_cursor->x();
                return;
            }
            else if (abs_f(m_cursor->y() - m_smooth_y) <= 0.001)
            {
                m_smooth_y = m_cursor->y();
                return;
            }

            float new_x = (m_smooth_x+m_cursor->x()*3)/4;
            float new_y = (m_smooth_y+m_cursor->y()*3)/4;
            QPointF pos(new_x, new_y);

            m_cursor->setPos(pos);
            m_lineH->setY(pos.y());
            m_lineV->setX(pos.x());

            float xp = pos.x()/(p_size.x()+p_size.width());
            float yp = pos.y()/(p_size.y()+p_size.height());

            //self.sendMIDI(xp, yp)
            emit cursorMoved(xp, yp);
        }
    }
}

void XYGraphicsScene::keyPressEvent(QKeyEvent* event)
{
    event->accept();
}

void XYGraphicsScene::wheelEvent(QGraphicsSceneWheelEvent* event)
{
    event->accept();
}

void XYGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    m_mouseLock = true;
    handleMousePos(event->scenePos());
    QGraphicsScene::mousePressEvent(event);
}

void XYGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    handleMousePos(event->scenePos());
    QGraphicsScene::mouseMoveEvent(event);
}

void XYGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    m_mouseLock = false;
    QGraphicsScene::mouseReleaseEvent(event);
}

void XYGraphicsScene::handleMousePos(const QPointF& pos_)
{
    QPointF pos(pos_);

    if (! p_size.contains(pos))
    {
        if (pos.x() < p_size.x())
            pos.setX(p_size.x());
        else if (pos.x() > p_size.x()+p_size.width())
            pos.setX(p_size.x()+p_size.width());

        if (pos.y() < p_size.y())
            pos.setY(p_size.y());
        else if (pos.y() > p_size.y()+p_size.height())
            pos.setY(p_size.y()+p_size.height());
    }

    m_smooth_x = pos.x();
    m_smooth_y = pos.y();

    if (! m_smooth)
    {
        m_cursor->setPos(pos);
        m_lineH->setY(pos.y());
        m_lineV->setX(pos.x());

        float xp = pos.x()/(p_size.x()+p_size.width());
        float yp = pos.y()/(p_size.y()+p_size.height());

        //self.sendMIDI(xp, yp);
        emit cursorMoved(xp, yp);
    }
}

// ---------------------------------------------------------------------------------------------

XYControllerUi::XYControllerUi() :
    DistrhoUiBase(),
    ui(new Ui::XYControllerW)
{
    ui->setupUi(this);

    ui->dial_x->setPixmap(2);
    ui->dial_y->setPixmap(2);
    ui->dial_x->setLabel("X");
    ui->dial_y->setLabel("Y");
    ui->keyboard->setOctaves(6);

    scene = new XYGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing);

    ui->cb_control_x->setEnabled(false);
    ui->cb_control_y->setEnabled(false);

    //connect(ui->keyboard, SIGNAL(noteOn(int)), SLOT(noteOn(int)));
    //connect(ui->keyboard, SIGNAL(noteOff(int)), SLOT(noteOff(int)));

    connect(ui->cb_smooth, SIGNAL(clicked(bool)), SLOT(setSmooth(bool)));

    connect(ui->dial_x, SIGNAL(valueChanged(int)), SLOT(updateSceneX(int)));
    connect(ui->dial_y, SIGNAL(valueChanged(int)), SLOT(updateSceneY(int)));

    connect(scene, SIGNAL(cursorMoved(float, float)), SLOT(sceneCursorMoved(float, float)));

    m_notFirstInit  = false;
    m_smoothTimerId = startTimer(50);
    QTimer::singleShot(0, this, SLOT(updateScreen()));
}

XYControllerUi::~XYControllerUi()
{
    delete scene;
}

bool XYControllerUi::d_isUiResizable()
{
    return true;
}

void XYControllerUi::d_setParameterValue(quint32 index, float value)
{
    switch (index)
    {
    case XYController::PARAMETER_SMOOTH:
        ui->cb_smooth->blockSignals(true);
        ui->cb_smooth->setChecked(value >= 0.5);
        scene->setSmooth(value >= 0.5);
        ui->cb_smooth->blockSignals(false);
        break;
    case XYController::PARAMETER_IN_X:
        ui->dial_x->blockSignals(true);
        ui->dial_x->setValue(value*100);
        scene->setPosX(value, false);
        ui->dial_x->blockSignals(false);
        break;
    case XYController::PARAMETER_IN_Y:
        ui->dial_y->blockSignals(true);
        ui->dial_y->setValue(value*100);
        scene->setPosY(value, false);
        ui->dial_y->blockSignals(false);
        break;
    }
}

void XYControllerUi::d_setProgram(quint32)
{
}

// ---------------------------------------------------------------------------------------------


void XYControllerUi::setSmooth(bool yesno)
{
    scene->setSmooth(yesno);
    emit d_parameterChanged(XYController::PARAMETER_SMOOTH, yesno ? 1.0f : 0.0f);
}

void XYControllerUi::sceneCursorMoved(float xp, float yp)
{
    ui->dial_x->blockSignals(true);
    ui->dial_y->blockSignals(true);

    ui->dial_x->setValue(xp*100);
    ui->dial_y->setValue(yp*100);

    ui->dial_x->blockSignals(false);
    ui->dial_y->blockSignals(false);

    emit d_parameterChanged(XYController::PARAMETER_IN_X, xp);
    emit d_parameterChanged(XYController::PARAMETER_IN_Y, yp);
}

void XYControllerUi::updateSceneX(int x, bool sendEmit)
{
    float xp = float(x)/100;
    scene->setPosX(xp, (!ui->dial_x->isSliderDown()) && !sendEmit);
    emit d_parameterChanged(XYController::PARAMETER_IN_X, xp);

}

void XYControllerUi::updateSceneY(int y, bool sendEmit)
{
    float yp = float(y)/100;
    scene->setPosY(yp, (!ui->dial_y->isSliderDown()) && !sendEmit);
    if (sendEmit)
        emit d_parameterChanged(XYController::PARAMETER_IN_Y, yp);
}

void XYControllerUi::updateScreen()
{
    scene->updateSize(ui->graphicsView->size());
    ui->graphicsView->centerOn(0, 0);

    int dial_x = ui->dial_x->value();
    int dial_y = ui->dial_y->value();
    updateSceneX(dial_x, m_notFirstInit);
    updateSceneY(dial_y, m_notFirstInit);
    scene->setSmoothValues(float(dial_x)/100, float(dial_y)/100);

    m_notFirstInit = true;
}

void XYControllerUi::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_smoothTimerId)
        scene->updateSmooth();

    DistrhoUiBase::timerEvent(event);
}

void XYControllerUi::resizeEvent(QResizeEvent* event)
{
    updateScreen();
    DistrhoUiBase::resizeEvent(event);
}

// ---------------------------------------------------------------------------------------------

DistrhoUiBase* createDistrhoUI()
{
    return new XYControllerUi();
}
