#include "graphicsview.h"
#include <QSvgGenerator>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFileInfo>
#include <QMessageBox>
//GraphicsView::GraphicsView(QWidget *parent) :
//    QGraphicsView(parent)
//{
//    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//    this->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
//}
GraphicsView::GraphicsView(QGraphicsScene *scene)
    :QGraphicsView(scene)
{
    m_hruler = new QtRuleBar(Qt::Horizontal,this,this);
    m_vruler = new QtRuleBar(Qt::Vertical,this,this);
    box = new QtCornerBox(this);
    setViewport(new QWidget);

    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;

    modified = false;
}
void GraphicsView::keyPressEvent(QKeyEvent *event)//键盘事件
{
    switch (event->key())
    {
    case Qt::Key_Equal :
        scale(1.2, 1.2);
        break;
    case Qt::Key_Minus :
        scale(1 / 1.2, 1 / 1.2);
        break;
    case Qt::Key_Right :
        rotate(30);
        break;
    }
    QGraphicsView::keyPressEvent(event);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    // 滚轮的滚动量
    QPoint scrollAmount = event->angleDelta();
    // 正值表示滚轮远离使用者（放大），负值表示朝向使用者（缩小）
    scrollAmount.y() > 0 ? scale(1.2, 1.2) : scale(1 / 1.2, 1 / 1.2);
}
