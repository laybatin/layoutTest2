#ifndef THUMBNAILICONPROVIDER_H
#define THUMBNAILICONPROVIDER_H

#include <QFileIconProvider>

class ThumbnailIconProvider : public QFileIconProvider
{
public:
    ThumbnailIconProvider();

    QIcon icon(const QFileInfo &info) const;
};

#endif // THUMBNAILICONPROVIDER_H
