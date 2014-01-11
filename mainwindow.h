#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QDirModel>
#include <QStandardItemModel>
namespace Ui {
class MainWindow;
}

namespace kExtName {

enum
{
    BEGIN,
    jpg = BEGIN,
    png,
    gif,
    bmp,
    END = bmp,
    CNT = END + 1
};

const QString STRING[CNT]=
{
    "*.jpg", "*.png", "*.gif", "*.bmp"
};

}


class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void StandardModelUpdate();
private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void fileViewChange(QString path);
    void FileViewUpdate(QModelIndex);
    void currentItem(QModelIndex, QModelIndex);
    void FileModelUpdate(QString);
    void DirFilesFilter(QString);

private:
    QIcon GetThumbnail(QString imgPath);


private:
    Ui::MainWindow *ui;
    QFileSystemModel *dir_model_;
    QFileSystemModel *file_model_;
    QStringList ext_lists_;
    //QStringList dirFiles;
    QFileInfoList dir_files_;
    QStandardItemModel *standard_model_;

};

#endif // MAINWINDOW_H
