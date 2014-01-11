#include "iconprovider.h"

IconProvider * IconProvider::self = NULL;

IconProvider * IconProvider::instance()
{
    if(!self)
        self = new IconProvider();
    return self;
}

QIcon IconProvider::fileIcon(const QString &filename)
{
    QFileInfo fileInfo(filename);
    QPixmap pixmap;

#ifdef Q_OS_WIN
    if (fileInfo.suffix().isEmpty() || fileInfo.suffix() == "exe" && fileInfo.exists())
        {
            return instance()->iconProvider.icon(fileInfo);
        }

        if (!instance()->iconCache.find(fileInfo.suffix(), &pixmap))
        {
            // Support for nonexistent file type icons, will reimplement it as custom icon provider later
            /* We don't use the variable, but by storing it statically, we
             * ensure CoInitialize is only called once. */
            static HRESULT comInit = CoInitialize(NULL);
            Q_UNUSED(comInit);

            SHFILEINFO shFileInfo;
            unsigned long val = 0;

            val = SHGetFileInfo((const wchar_t *)("foo." + fileInfo.suffix()).utf16(), 0, &shFileInfo,
                                sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_USEFILEATTRIBUTES);

            // Even if GetFileInfo returns a valid result, hIcon can be empty in some cases
            if (val && shFileInfo.hIcon)
            {
                pixmap = QPixmap::fromWinHICON(shFileInfo.hIcon);
                if (!pixmap.isNull())
                {
                    instance()->iconCache.insert(fileInfo.suffix(), pixmap);
                }
                DestroyIcon(shFileInfo.hIcon);
            }
            else
            {
                // TODO: Return default icon if nothing else found
            }
        }

    #else
        // Default icon for Linux and Mac OS X for now
        return instance()->iconProvider.icon(fileInfo);
    #endif

        return QIcon(pixmap);

}

QIcon IconProvider::dirIcon()
{
    return instance()->iconProvider.icon(QFileIconProvider::Folder);
}
