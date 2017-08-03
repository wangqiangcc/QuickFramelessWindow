#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QQuickWindow>
#include <QPoint>

class FramelessWindow : public QQuickWindow
{
    Q_OBJECT

    QPoint clickPosition;
    bool mousePressed;

public:
    explicit FramelessWindow(QWindow *parent = 0);
    ~FramelessWindow();

public slots:
    void setMoveWindowArea(QQuickItem *moveWindowArea);

private:
    void mousePressEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
private:
    QQuickItem *m_pMoveWindowArea;
};

#endif // FRAMELESSWINDOW_H
