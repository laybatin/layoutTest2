#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <qDebug>
#include <QListWidget>
#include <QListWidgetItem>
//#include "thumbnailiconprovider.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString path = "./";
    dirModel = new QFileSystemModel(this);
    dirModel->setRootPath(path);
    dirModel->setFilter( QDir::NoDotAndDotDot | QDir::Dirs );

    ui->treeView->setModel(dirModel);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);


    fileModel = new QFileSystemModel(this);
    fileModel->setFilter( QDir::NoDotAndDotDot | QDir::Files );
    fileModel->setRootPath(path);

    //확장자 제한
    QStringList filters;
    for(unsigned int i = ExtName::BEGIN; i<ExtName::CNT; i++)
        filters << ExtName::STRING[i];

    fileModel->setNameFilters(filters);
    fileModel->setNameFilterDisables(false);
    //fileModel->setIconProvider(new ThumbnailIconProvider);

    //fileView설정
    ui->fileView->setModel(fileModel);
    ui->fileView->setViewMode(QListView::IconMode);
    ui->fileView->setFlow(QListView::LeftToRight);
    ui->fileView->setGridSize(QSize(60,60));







}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString sPath = dirModel->fileInfo(index).absoluteFilePath();
    //qDebug() << sPath;
    ui->fileView->setRootIndex(fileModel->setRootPath(sPath));


//    QModelIndexList selectedIndexs = ui->fileView->selectionModel()->selectedIndexes();
//    QStringList selectedTexts;

//    foreach (const QModelIndex &idx, selectedIndexs) {
//        selectedTexts << idx.data(Qt::DisplayRole).toString();
//    }

//    for(auto i:selectedIndexs)
//    {
//        qDebug() << i;
//    }

    //QModelIndex index = fileModel->index(0,0,QModelIndex());
    //QVariant value = fileModel->data(index);
    //QString text = fileModel->data(index,Qt::DisplayRole).toString();

}
