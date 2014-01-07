#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>

namespace Ui {
class MainWindow;
}

namespace ExtName
{
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

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QFileSystemModel * dirModel;
    QFileSystemModel * fileModel;
};

#endif // MAINWINDOW_H
