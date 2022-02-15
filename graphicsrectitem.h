#ifndef GRAPHICSRECTITEM_H
#define GRAPHICSRECTITEM_H

#include <QGraphicsItem>
#include "sizehandlerect.h"
#include <QXmlStreamReader>
#include <QGraphicsScene>
class GraphicsRectItem : public QGraphicsItem
{
public:
    GraphicsRectItem(const QRect & rect ,QGraphicsItem * parent);

    QRectF boundingRect() const;
    virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point );
    void move(const QPointF & point);
    QGraphicsItem *duplicate () const ;
    virtual Qt::CursorShape getCursor(SizeHandleRect::Direction dir );
    SizeHandleRect::Direction  hitTest( const QPointF & point ) const;
    virtual QRectF  rect() const;
    virtual void updateGeometry();
    QRectF m_rect;
    QPen   pen() const {return m_pen;}
    void   setPen(const QPen & pen ) { m_pen = pen;}
    void   setBrush( const QBrush & brush ) { m_brush = brush ; }
    void updateCoordinate();
   // virtual bool loadFromXml(QXmlStreamReader * xml );
   // virtual bool saveToXml( QXmlStreamWriter * xml );
   // bool readBaseAttributes(QXmlStreamReader *xml);
    bool writeBaseAttributes(QXmlStreamWriter *xml);//写xml文件
private:

    typedef QVector<SizeHandleRect*> Handles;
    Handles m_handles;
    int selection_handle_size = 4;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setState(SelectionHandleState st);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    bool m_isRound;
    qreal m_fRatioY;
    qreal m_fRatioX;
    qreal m_width;
    qreal m_height;
    QPen m_pen;
    QBrush m_brush;
    QRectF m_localRect;
    bool readBaseAttributes(QXmlStreamReader *xml);
};


#endif // GRAPHICSRECTITEM_H
