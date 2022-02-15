#include "sizehandlerect.h"
#include <QPainter>

SizeHandleRect::SizeHandleRect(QGraphicsItem *parent, QRectF rect, Direction dir) :
    QGraphicsRectItem(rect, parent),
    m_dir(dir),
    m_state(SelectionHandleOff)
{
    setParentItem(parent);
    hide();
}

SizeHandleRect::Direction SizeHandleRect::dir() const
{
    return m_dir;
}

bool SizeHandleRect::hitTest(const QPointF &point)
{
    QPointF pt = mapFromScene(point);
    return rect().contains(pt);
}

void SizeHandleRect::move(qreal x, qreal y)
{
    setPos(x,y);
}

void SizeHandleRect::setState(SelectionHandleState st)//设置状态
{
    if (st == m_state)
        return;
    switch (st) {
    case SelectionHandleOff:
        hide();
        break;
    case SelectionHandleInactive:
    case SelectionHandleActive:
        show();
        break;
    }
    m_state = st;
}

void SizeHandleRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor c = QColor("limegreen");
  //  c.setAlpha(200);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(c));

    painter->drawRect(rect());
    //painter->restore();
}
