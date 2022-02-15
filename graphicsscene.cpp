#include "graphicsscene.h"
#include <QGraphicsView>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
enum SelectMode
{
    none,
    netSelect,
    move, //移动
    size, //改变大小
    rotate //反转
};

SelectMode selectMode = none;

SizeHandleRect::Direction nDragHandle = SizeHandleRect::None;

GraphicsScene::GraphicsScene()
{

}

void GraphicsScene::creatRect()//创造矩形
{
//    if(m_RectItem){
//        return;
//    }
    this->clearSelection();
    m_RectItem = new GraphicsRectItem(QRect(0, 0, 200, 100), NULL);
    this->addItem(m_RectItem);
    m_RectItem->setSelected(true);
    this->update();
}

void GraphicsScene::SetBackGroundImage(QPixmap pix, int width, int height)//设置背景图片
{
    this->clear();
    QGraphicsPixmapItem* _backGroundItem= this->addPixmap(pix);

    qreal scale = 0.0;
    if((double)width/height > (double)pix.width()/pix.height()){
        scale = (double)height/pix.height();
    } else{
        scale = (double)width/pix.width();
    }

    _backGroundItem->setScale(scale);

//    _backGroundItem->setPos(0,0);
}

void GraphicsScene::setCursor(const QCursor &cursor)
{
    QList<QGraphicsView*> views  = this->views();
    if ( views.count() > 0 ){
        QGraphicsView * view = views.first();
        view->setCursor(cursor);
    }
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem *> items = this->selectedItems();
    GraphicsRectItem *item = 0;
    if ( items.count() == 1 )
    {
        item = qgraphicsitem_cast<GraphicsRectItem*>(items.first());

        nDragHandle = item->hitTest(event->scenePos());
        if ( nDragHandle !=SizeHandleRect::None)
            selectMode = size;
        else
            selectMode =  move;
    }
    if(selectMode == move || selectMode == none){
        QGraphicsScene::mousePressEvent(event);
    }
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem *> items = this->selectedItems();
    if(items.count() == 1){
        GraphicsRectItem *item = qgraphicsitem_cast<GraphicsRectItem*>(items.first());
        if ( nDragHandle != SizeHandleRect::None && selectMode == size ){
            item->resizeTo(nDragHandle,event->scenePos());
        }
        else if(nDragHandle == SizeHandleRect::None && selectMode == none ){


            SizeHandleRect::Direction handle = item->hitTest(event->scenePos());
            if ( handle != SizeHandleRect::None){
                setCursor(item->getCursor(handle));
            }else{
                setCursor(Qt::ArrowCursor);
            }
        }
        else if(nDragHandle == SizeHandleRect::None && selectMode == move ){

            item->move(event->scenePos());
        }
    }

    this->update();
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ArrowCursor);
    selectMode = none;
    nDragHandle = SizeHandleRect::None;
    QGraphicsScene::mouseReleaseEvent(event);
}


