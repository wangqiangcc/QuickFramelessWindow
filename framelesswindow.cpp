#include "framelesswindow.h"
#include <QQuickItem>
#include <QDebug>
#include <QtMath>

FramelessWindow::FramelessWindow(QWindow *parent)
    : QQuickWindow(parent), mousePressed( false )
{

    setFlags( Qt::Window
              |Qt::FramelessWindowHint
              | Qt::MacWindowToolBarButtonHint
              | Qt::WindowMinimizeButtonHint
              | Qt::WindowMaximizeButtonHint );
}

FramelessWindow::~FramelessWindow()
{

}

void FramelessWindow::setMoveWindowArea(QQuickItem *moveWindowArea)
{
    m_pMoveWindowArea = moveWindowArea;
}


void FramelessWindow::mouseMoveEvent( QMouseEvent *event )
{
    if ( mousePressed ) {
        QPoint newPoint( x() + ( event->x() - clickPosition.x() ), y() + ( event->y() - clickPosition.y() ) );
        setPosition(newPoint);
    }

    QQuickWindow::mouseMoveEvent( event );
}

void FramelessWindow::mouseReleaseEvent( QMouseEvent *event )
{
    mousePressed = false;
    QQuickWindow::mouseReleaseEvent( event );
}

void FramelessWindow::mousePressEvent( QMouseEvent *event )
{
    mousePressed = true;
    clickPosition.setX( event->x() );
    clickPosition.setY( event->y() );

    QQuickWindow::mousePressEvent( event );
}


bool FramelessWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    if ( windowState() && Qt::WindowMaximized) {
        return false;
    }

    const int HIT_BORDER = 8;
    const MSG *msg=static_cast<MSG*>(message);
    if(msg->message == WM_NCHITTEST) {
        int xPos = ((int)(short)LOWORD(msg->lParam)) - this->frameGeometry().x();
        int yPos = ((int)(short)HIWORD(msg->lParam)) - this->frameGeometry().y();

        if (m_pMoveWindowArea && m_pMoveWindowArea->contains(QPointF(xPos,yPos))) {
            *result = HTCAPTION;
        }
        if (m_pMoveWindowArea) {
            if (m_pMoveWindowArea->contains(QPointF(xPos,yPos)) && !m_pMoveWindowArea->childAt(xPos,yPos)) {
                *result = HTCAPTION;
                return true;
            }
        } else {
            //if(contentItem()->childItems()[0]->childAt(xPos,yPos) == 0)
            //{
            //    *result = HTCAPTION;
            //}
        }

        auto child = contentItem()->childAt(xPos,yPos);
        if(child)
        {
            if (child != m_pMoveWindowArea) {
                return false;
            } else {
                if (m_pMoveWindowArea && !m_pMoveWindowArea->childAt(xPos,yPos)) {
                    *result = HTCAPTION;
                    return true;
                }
                return false;
            }
        }

        if(xPos > 0 && xPos < HIT_BORDER) {
            *result = HTLEFT;
        }
        if(xPos > (this->width() - HIT_BORDER) && xPos < (this->width() - 0)) {
            *result = HTRIGHT;
        }
        if(yPos > 0 && yPos < HIT_BORDER) {
            *result = HTTOP;
        }
        if(yPos > (this->height() - HIT_BORDER) && yPos < (this->height() - 0)) {
            *result = HTBOTTOM;
        }
        if(xPos > 0 && xPos < HIT_BORDER && yPos > 0 && yPos < HIT_BORDER) {
            *result = HTTOPLEFT;
        }
        if(xPos > (this->width() - HIT_BORDER) && xPos < (this->width() - 0) && yPos > 0 && yPos < HIT_BORDER) {
            *result = HTTOPRIGHT;
        }
        if(xPos > 0 && xPos < HIT_BORDER && yPos > (this->height() - HIT_BORDER) && yPos < (this->height() - 0)) {
            *result = HTBOTTOMLEFT;
        }
        if(xPos > (this->width() - HIT_BORDER) && xPos < (this->width() - 0) && yPos > (this->height() - HIT_BORDER) && yPos < (this->height() - 0)) {
            *result = HTBOTTOMRIGHT;
        }
        return true;
    }
    return false;
}
