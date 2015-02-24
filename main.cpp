#include "convertdialog.h"
#include <QApplication>
#include <QDebug>
#include <QtCore/QCoreApplication>

#ifdef QT_NO_DEBUG_OUTPUT
#undef QT_NO_DEBUG_OUTPUT
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ConvertDialog convertdialog;
#ifdef Q_OS_SYMBIAN
    convertdialog.showMaximized();
#else
    convertdialog.show();
#endif

    return app.exec();
}
