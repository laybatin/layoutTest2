#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <QDebug>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMimeType>
#include <QImageReader>
#include <QTime>

#include "thumbnailiconprovider.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString path = "./";
    dir_model_ = new QFileSystemModel(this);
    dir_model_->setRootPath(path);
    dir_model_->setFilter( QDir::NoDotAndDotDot | QDir::Dirs );

    ui->treeView->setModel(dir_model_);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);


    file_model_ = new QFileSystemModel(this);
    file_model_->setFilter( QDir::NoDotAndDotDot | QDir::Files );
    file_model_->setRootPath(path);
    //fileModel->index(path);

    //확장자 제한

    for(unsigned int i = kExtName::BEGIN; i<kExtName::CNT; i++)
        ext_lists_ << kExtName::STRING[i];


    file_model_->setNameFilters(ext_lists_);
    file_model_->setNameFilterDisables(false);
    //fileModel->setIconProvider(new ThumbnailIconProvider);

    //fileView설정
    //ui->fileView->setModel(fileModel);

    standard_model_ = new QStandardItemModel();
    //ui->fileView->setModel(m_FileModel);
    ui->fileView->setModel(standard_model_);
    ui->fileView->setViewMode(QListView::IconMode);
    ui->fileView->setFlow(QListView::LeftToRight);
    ui->fileView->setGridSize(QSize(60,60));
    ui->fileView->setUniformItemSizes(true);



    //connect(ui->fileView->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(currentItem()));        //바꿀때!
    //connect(dirModel, SIGNAL(directoryLoaded(QString)), this, SLOT( fileViewUpdate()));
    //connect(ui->treeView, SIGNAL(pressed(QModelIndex)), this, SLOT( fileViewUpdate()));
    //connect(ui->fileView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(currentItem(QModelIndex,QModelIndex)));
    //connect(fileModel, SIGNAL())

    //connect(iStandardModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this ,SLOT(fileModelUpdate()));

    connect(file_model_, SIGNAL(rootPathChanged(QString)), this, SLOT(FileModelUpdate(QString)));
    connect(file_model_, SIGNAL(directoryLoaded(QString)), this, SLOT(DirFilesFilter(QString)));
    connect(standard_model_, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(FileViewUpdate(QModelIndex)));

    //connect(iStandardModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(fileViewUpdate()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    //TreeView를 클릭하면 ListModel의 RootPath를 바꾸어준다.
    Q_ASSERT( index.isValid() );
    QString sPath = dir_model_->fileInfo(index).absoluteFilePath();


    qDebug() << "path = " << sPath;
    QModelIndex fileIdx = file_model_->setRootPath(sPath);        //파일모델 업데이트
    //QModelIndex fileIdx = fileModel->index(sPath);
    //fileModel->setNameFilters(extLists);
    //ui->fileView->setRootIndex(fileIdx);


//    int numRows = m_FileModel->rowCount(fileIdx);
////    qDebug() << numRows;
//    QImageReader imgReader;
//    for(int i=0;i<numRows;i++)
//    {
//        QModelIndex mi = m_FileModel->index(i,0,fileIdx);
//        QFileInfo fileInfo = m_FileModel->fileInfo(mi);
//        //qDebug() << fileInfo.absoluteFilePath();
//        imgReader.setFileName(fileInfo.absoluteFilePath());
//        if(imgReader.canRead())
//            dirFiles << fileInfo;
//            //dirFiles << fileInfo.absoluteFilePath();
//    }







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

void MainWindow::fileViewChange(QString path)
{

    QModelIndex fileIdx = file_model_->setRootPath(path);
    //QModelIndex fileIdx = fileModel->index(path);
    int numRows = file_model_->rowCount(fileIdx);

    for(int i=0;i<numRows;i++)
    {
        QModelIndex mi = file_model_->index(i,0,fileIdx);
        QFileInfo fileInfo = file_model_->fileInfo(mi);

        qDebug() << fileInfo.absoluteFilePath();
    }

}

void MainWindow::FileViewUpdate(QModelIndex index)
{
    //dirFiles의 List를 Icon화 시켜서 ListView에 담음
//    qDebug() << "???";
//    for(auto idx:dirFiles)
//    {
//        qDebug() << "idx = " << idx;
//    }
//    for(int i=0;i<dirFiles.count();i++)
//    {
//        qDebug() << "idx = " << dirFiles.at(i).toLocal8Bit().constData();
//        QStandardItem item(QIcon())
//    }

    //for(auto idx : dirFiles)
    //{
        //QStandardItem item(QIcon(idx),"1");
        //qDebug() << idx;
    //}

    //리로딩을 안할수는 없다.


    //ui->fileView->setModel();


    qDebug() << "one row add";
    ui->fileView->viewport()->update();
    QCoreApplication::processEvents();

}

void MainWindow::currentItem(QModelIndex current, QModelIndex prev)
{
    Q_ASSERT( current.isValid() );
    //QFileInfo fileInfo = fileModel->fileInfo(current);
    //qDebug() << "select file  " << fileInfo.absoluteFilePath();

    QVariant data = standard_model_->data(current);
    qDebug() << data;

    //qDebug() << "item";
}

QIcon MainWindow::GetThumbnail(QString imgPath)
{
    QTime time;
    time.start();
//    QImage image(imgPath);
//    image = image.scaled(64,64);

    QPixmap buffer;
    buffer.load(imgPath);
    //buffer = QPixmap::fromImage(image);
    buffer = buffer.scaled(64,64);

    int diff = time.elapsed();
    qDebug() << diff;

    return QIcon(buffer);
}

void MainWindow::FileModelUpdate(QString path)
{
    //m_FileModel의 업데이트 이후
    //QModelIndex fileIdx = m_FileModel->setRootPath(sPath);        //파일모델 업데이트

    //fileModel->setNameFilters(extLists);
    //ui->fileView->setRootIndex(fileIdx);





//    QFileInfoList::const_iterator iter;

//    iStandardModel->clear();
//    int i = 0;
//    for(iter = dirFiles.constBegin(); iter != dirFiles.constEnd(); ++iter)
//    {
//        if(i == 20) break;
//        i++;
//        QIcon icon = getThumbnail((*iter).absoluteFilePath()) ;
//        QStandardItem * item;
//        if(!icon.isNull())
//             item = new QStandardItem(icon, (*iter).fileName() );
//        else
//            item = new QStandardItem((*iter).fileName() );

//        //iStandardModel->setData(0, (*iter).absoluteFilePath() );
//        iStandardModel->appendRow(item);

//    //    qDebug() << (*iter).absoluteFilePath() << " " << (*iter).fileName();

//    }



//    dirFiles.clear();

    //ui->fileView->setSelectionModel(iStandardModel);


}

void MainWindow::StandardModelUpdate()
{
    QFileInfoList::const_iterator iter;

    standard_model_->clear();

    int i=0;
    for (iter = dir_files_.constBegin(); iter != dir_files_.constEnd(); ++iter)
    {

        QIcon icon = GetThumbnail((*iter).absoluteFilePath()) ;
        QStandardItem * item;
        if(!icon.isNull())
             item = new QStandardItem(icon, (*iter).fileName() );
        else
            item = new QStandardItem((*iter).fileName() );

        //iStandardModel->setData(0, (*iter).absoluteFilePath() );
        standard_model_->appendRow(item);

    //    qDebug() << (*iter).absoluteFilePath() << " " << (*iter).fileName();
        i++;

    }

    //dirFiles의 리스트를 클리어해준다.
    dir_files_.clear();
}

void MainWindow::DirFilesFilter(QString path)
{
    //디렉토리가 로드된 후 QFileSystemModel의 버그때문에
    //이미지 + 폴더가 같이나올때가 있다.
    //그래서 QImageReader로 읽을 수 있는 이미지인지 판단한다.
    //읽을 수 있는 이미지라면 List에 넣는다.

    QModelIndex fileIdx = file_model_->index(path);
    int numRows = file_model_->rowCount(fileIdx);


    QImageReader imgReader;
    for (int index=0;index<numRows;index++)
    {
        QModelIndex mi = file_model_->index(index,0,fileIdx);
        QFileInfo fileInfo = file_model_->fileInfo(mi);
        //qDebug() << fileInfo.absoluteFilePath();
        imgReader.setFileName(fileInfo.absoluteFilePath());
        if(imgReader.canRead())
            dir_files_ << fileInfo;
    }

    //List에 넣은 파일들을 모델로 만든다.    
    StandardModelUpdate();


}
