#include "graphicsrectitem.h"
#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QCursor>
#include <QGraphicsTransform>

GraphicsRectItem::GraphicsRectItem(const QRect &rect, QGraphicsItem *parent) :
    QGraphicsItem(parent)

{
    m_rect = rect;
    m_handles.reserve(SizeHandleRect::None);
    for (int i = SizeHandleRect::LeftTop; i <= SizeHandleRect::Left; ++i) {
        SizeHandleRect *shr = new SizeHandleRect(this, QRectF(0,0,4,4), static_cast<SizeHandleRect::Direction>(i));
        m_handles.push_back(shr);
    }
    updateGeometry();
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->setAcceptHoverEvents(true);
}
//GraphicsRectItem::GraphicsRectItem(const QRect & rect , bool isRound , QGraphicsItem *parent)
//    :GraphicsItem(parent)
//    ,m_isRound(isRound)
//    ,m_fRatioX(1/10.0)
//    ,m_fRatioY(1/3.0)
//{

//    m_width = rect.width();
//    m_height = rect.height();
//    m_initialRect = rect;
//    m_localRect = m_initialRect;
//    m_localRect = rect;
//    m_originPoint = QPointF(0,0);
//    if( m_isRound ){
//        SizeHandleRect *shr = new SizeHandleRect(this, 9 , true);
//        m_handles.push_back(shr);
//        shr = new SizeHandleRect(this, 10 , true);
//        m_handles.push_back(shr);
        //shr = new SizeHandleRect(this, 11 , true);
        //m_handles.push_back(shr);
//    }

//    updatehandles();
//}
void GraphicsRectItem::resizeTo(SizeHandleRect::Direction dir, const QPointF &point)//调整选中的矩形大小
{
    QPointF local = mapFromScene(point);
    QString dirName;

    QRect delta =m_rect.toRect();
    switch (dir) {
    case SizeHandleRect::LeftTop:
        delta.setTopLeft(local.toPoint());

        break;
    case SizeHandleRect::Top:
        dirName = "Top";
        delta.setTop(local.y());
        break;

    case SizeHandleRect::RightTop:
        dirName = "RightTop";
        delta.setTopRight(local.toPoint());
        break;

    case SizeHandleRect::Left:
        dirName = "Left";
        delta.setLeft(local.x());
        break;
    case SizeHandleRect::Right:
        dirName = "Rigth";
        delta.setRight(local.x());
        break;

    case SizeHandleRect::LeftBottom:
        dirName = "LeftBottom";
        delta.setBottomLeft(local.toPoint());
        break;

    case SizeHandleRect::Bottom:
        dirName = "Bottom";
        delta.setBottom(local.y());
        break;

    case SizeHandleRect::RightBottom:
        dirName = "RightBottom";
        delta.setBottomRight(local.toPoint());
        break;

    default:
        break;
    }
    prepareGeometryChange();
//    if(m_isSquare)
//    {
//        delta.setHeight(delta.width());
//    }
    m_rect =delta;
    updateGeometry();
}

void GraphicsRectItem::move(const QPointF &point)//移动选中的矩形
{
    QPointF local = mapFromScene(point);

    QRectF delta = QRectF(local, m_rect.size());

    prepareGeometryChange();
    m_rect =delta;
    updateGeometry();
}

Qt::CursorShape GraphicsRectItem::getCursor(SizeHandleRect::Direction dir)//获得本进程的光标指针
{
    switch (dir) {
    case SizeHandleRect::Right:
        return Qt::SizeHorCursor;
    case SizeHandleRect::RightTop:
        return Qt::SizeBDiagCursor;
    case SizeHandleRect::RightBottom:
        return Qt::SizeFDiagCursor;
    case SizeHandleRect::LeftBottom:
        return Qt::SizeBDiagCursor;
    case SizeHandleRect::Bottom:
        return Qt::SizeVerCursor;
    case SizeHandleRect::LeftTop:
        return Qt::SizeFDiagCursor;
    case SizeHandleRect::Left:
        return Qt::SizeHorCursor;
    case SizeHandleRect::Top:
        return Qt::SizeVerCursor;
    default:
        break;
    }
    return Qt::ArrowCursor;
}

SizeHandleRect::Direction GraphicsRectItem::hitTest(const QPointF &point) const
{
    const Handles::const_iterator hend =  m_handles.end();
    for (Handles::const_iterator it = m_handles.begin(); it != hend; ++it)
    {
        if ((*it)->hitTest(point) ){
            return (*it)->dir();
        }
    }
    return SizeHandleRect::None;
}

void GraphicsRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)//画矩形
{
    QPen pen =painter->pen();
    pen.setWidth(4);
    pen.setColor(QColor(255, 0, 0));
    painter->setPen(pen);
    painter->drawRect(rect());
}

void GraphicsRectItem::updateGeometry()//更新矩形大小
{
    const QRectF &rect = this->boundingRect();

    const Handles::iterator hend =  m_handles.end();
    for (Handles::iterator it = m_handles.begin(); it != hend; ++it) {
        SizeHandleRect *hndl = *it;;
        switch (hndl->dir()) {
        case SizeHandleRect::LeftTop:
            hndl->move(rect.x() - selection_handle_size / 2, rect.y() - selection_handle_size / 2);
            break;
        case SizeHandleRect::Top:
            hndl->move(rect.x() + rect.width() / 2 - selection_handle_size / 2, rect.y() - selection_handle_size / 2);
            break;
        case SizeHandleRect::RightTop:
            hndl->move(rect.x() + rect.width() - selection_handle_size / 2, rect.y() - selection_handle_size / 2);
            break;
        case SizeHandleRect::Right:
            hndl->move(rect.x() + rect.width() - selection_handle_size / 2, rect.y() + rect.height() / 2 - selection_handle_size / 2);
            break;
        case SizeHandleRect::RightBottom:
            hndl->move(rect.x() + rect.width() - selection_handle_size / 2, rect.y() + rect.height() - selection_handle_size / 2);
            break;
        case SizeHandleRect::Bottom:
            hndl->move(rect.x() + rect.width() / 2 - selection_handle_size / 2, rect.y() + rect.height() - selection_handle_size / 2);
            break;
        case SizeHandleRect::LeftBottom:
            hndl->move(rect.x() - selection_handle_size / 2, rect.y() + rect.height() - selection_handle_size / 2);
            break;
        case SizeHandleRect::Left:
            hndl->move(rect.x() - selection_handle_size / 2, rect.y() + rect.height() / 2 - selection_handle_size / 2);
            break;
        case SizeHandleRect::Center:
            hndl->move(rect.center().x()  - selection_handle_size / 2 , rect.center().y() - selection_handle_size / 2);
            break;
        default:
            break;
        }
    }
}

QRectF GraphicsRectItem::rect() const
{
    return QRectF(QPointF(m_rect.left(),m_rect.top()),
                  QPointF(m_rect.right(), m_rect.bottom()));
}

void GraphicsRectItem::setState(SelectionHandleState st)
{
    const Handles::iterator hend =  m_handles.end();
    for (Handles::iterator it = m_handles.begin(); it != hend; ++it)
        (*it)->setState(st);
}

QVariant GraphicsRectItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if ( change == QGraphicsItem::ItemSelectedHasChanged ) {
        qDebug()<<" Item Selected : " << value.toString();
        setState(value.toBool() ? SelectionHandleActive : SelectionHandleOff);
    }else if ( change == QGraphicsItem::ItemRotationHasChanged ){
        qDebug()<<"Item Rotation Changed:" << value.toString();
    }else if ( change == QGraphicsItem::ItemTransformOriginPointHasChanged ){
        qDebug()<<"ItemTransformOriginPointHasChanged:" << value.toPointF();
    }
    return value;
}

QRectF GraphicsRectItem::boundingRect() const
{
    return rect();
}
 QXmlStreamWriter xml(&file);
 xml.writeAttribute("width",QString("%1").arg(scene()->width()));
 xml.writeAttribute("height",QString("%1").arg(scene()->height()));

bool GraphicsItem::writeBaseAttributes(QXmlStreamWriter *xml)//写xml文件
{
    xml->writeAttribute(tr("rotate"),QString("%1").arg(rotation()));
    xml->writeAttribute(tr("x"),QString("%1").arg(pos().x()));
    xml->writeAttribute(tr("y"),QString("%1").arg(pos().y()));
    xml->writeAttribute(tr("z"),QString("%1").arg(zValue()));
    xml->writeAttribute(tr("width"),QString("%1").arg(m_width));
    xml->writeAttribute(tr("height"),QString("%1").arg(m_height));
    return true;
}

bool GraphicsRectItem::saveToXml(QXmlStreamWriter * xml)
{
    xml->writeStartElement(QObject::tr("rect"));
    writeBaseAttributes(xml);
    xml->writeEndElement();
    return true;
}
