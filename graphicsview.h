#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QWheelEvent>
#include "graphicsrectitem.h"

class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    GraphicsView(QWidget *parent = 0);
    void newFile();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    QString currentFile() { return curFile; }
protected:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    //QtRuleBar *m_hruler;
    //QtRuleBar *m_vruler;
private:
    //GraphicsItemGroup * loadGroupFromXML( QXmlStreamReader * xml );
    void setCurrentFile(const QString &fileName);
    QString curFile;
    bool isUntitled;
    bool modified;
};

#endif // GRAPHICSVIEW_H
