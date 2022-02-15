#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "GraphicsRect/graphicsscene.h"
#include "GraphicsRect/graphicsview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool openFile(const QString &fileName);


private slots:
    void on_pushButton_createRect_clicked();

    void on_pushButton_getRect_clicked();

    //void on_pushButton_addPix_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void newFile();
    void open();
    void save();


private:
    Ui::MainWindow *ui;
    GraphicsScene *scene = NULL;
    void createActions();
    void createMenus();
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction  * deleteAct;
};

#endif // MAINWINDOW_H
