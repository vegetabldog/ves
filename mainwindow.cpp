#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QFileInfo>
#include <QMessageBox>
#include <QLabel>
#include <QDir>
#include <QMenu>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new GraphicsScene();
    QString mystring = "d:/yrz/";
    QDir mydir;

    mydir.setPath(mystring);
    mydir.setFilter(QDir::Files|QDir::NoSymLinks);
    mydir.setSorting(QDir::Name);
    QStringList filters;
    QStringList imagesList;
    filters << "*.png" << "*.jpg";
    mydir.setNameFilters(filters);
    imagesList = mydir.entryList();
    QFileInfoList list=mydir. entryInfoList();
    QString str,suffix;

    // 设置表格的行列数
    QStandardItemModel *tableModel=new QStandardItemModel(11,2,this);

     //设置表格自适应窗口大小
 //   int width = this->width();
 //   int height = this->height();
    ui->tableView->resize(5,40);

    //背景网格线设置
    //显示
    ui->tableView->setShowGrid(true);

//    //取消
//    //ui->tableView->setShowGrid(false);

    //网格背景画笔
    ui->tableView->setGridStyle(Qt::DashLine);
    ui->tableView->setGridStyle(Qt::DotLine);

    //排序功能
    ui->tableView->setSortingEnabled(true);
    // 添加表头
    QStandardItemModel* model = new QStandardItemModel();
    QStringList labels = QObject::trUtf8("序号,文件名称").simplified().split(",");
    tableModel->setHorizontalHeaderLabels(labels);

    // 获取日志文件夹下所有的日志名称
    for(int i=0;i<list.length();i++)
    {
        QFileInfo fileinfo=list.at(i);
        str=fileinfo.baseName();
        suffix=fileinfo.suffix();
        QStandardItem *item=new QStandardItem(str+"."+suffix);
        QStandardItem *item1=new QStandardItem(QString::number(i+1));
        tableModel->setItem(i,1,item);
        tableModel->setItem(i,0,item1);

    }
    ui->tableView->setModel(tableModel);
    ui->tableView->show();

    ui->graphicsView->setScene(scene);//在graghicsview上显示图片
    scene->addItem(new GraphicsRectItem(QRect(-1, -1, 3, 3), NULL));//增加矩形
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_createRect_clicked()
{
    scene->creatRect();
}

void MainWindow::on_pushButton_getRect_clicked()
{

    if(scene->m_RectItem){
//        QPoint point = scene->m_RectItem->m_rect.topLeft();
        QRect rect = scene->m_RectItem->rect().toRect();
        ui->lineEdit->setText("x:" + QString::number(rect.topLeft().x()) + "  y:" + QString::number(rect.topLeft().y())
                              + "  w:" + QString::number(rect.width()) + "  h:" + QString::number(rect.height()));


//        ui->lineEdit->setText("x:" + QString::number(point.x()) + "  y:" + QString::number(point.y())
//                              + "  w:" + QString::number(point.x() + rect.width()) + "  h:" + QString::number(point.y() + rect.height()));
    }
}


void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)//双击文件将图片显示在graphicsView上
{
    QAbstractItemModel *Imodel=ui->tableView->model();
    //index.row()为算选择的行号。1为所选中行的第一列。。
    QModelIndex Iindex = Imodel->index(index.row(),1);
    QVariant datatemp=Imodel->data(Iindex);
    //name即为所选择行的第一列的值
    QString name=Imodel->data(index).toString();
    //cout << name;
    //qDebug()<<name;
    QString logPath;
    QString suffix;
    QString filename((QString("D:/yrz/%1.%2").arg(name).arg(suffix)));
    QPixmap pix(filename);

    scene->SetBackGroundImage(pix, ui->graphicsView->width(), ui->graphicsView->height());
}
void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(deleteAct);

}
void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    deleteAct = new QAction(tr("&Delete"), this);
    deleteAct->setShortcut(QKeySequence::Delete);
}

//void MainWindow::save()
//{
//    //if (activeMdiChild() && activeMdiChild()->save())
//        statusBar()->showMessage(tr("File saved"), 2000);
//}
