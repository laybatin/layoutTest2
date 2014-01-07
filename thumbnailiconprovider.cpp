#include "thumbnailiconprovider.h"
#include <QDebug>
ThumbnailIconProvider::ThumbnailIconProvider()
{
}

QIcon ThumbnailIconProvider::icon(const QFileInfo &info) const
{
    QIcon ico(info.absoluteFilePath());

    if(ico.isNull())
        return QFileIconProvider::icon(info);
    else
    {
        qDebug() << "Fetch icon for " << info.absoluteFilePath();
        return ico;
    }
}
