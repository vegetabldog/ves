#ifndef SIZEHANDLERECT_H
#define SIZEHANDLERECT_H

#include <QGraphicsRectItem>

enum SelectionHandleState { SelectionHandleOff, SelectionHandleInactive, SelectionHandleActive };

class SizeHandleRect : public QGraphicsRectItem
{
public:
    enum Direction { LeftTop , Top, RightTop, Right, RightBottom, Bottom, LeftBottom, Left , Center, None};
    SizeHandleRect(QGraphicsItem* parent , QRectF rect, Direction dir);
    Direction dir() const;
    bool hitTest( const QPointF & point );
    void move(qreal x, qreal y );
    void setState(SelectionHandleState st);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    const Direction m_dir;
    SelectionHandleState m_state;
};

#endif // SIZEHANDLERECT_H
