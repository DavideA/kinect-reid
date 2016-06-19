#include <QApplication>

#include "MainWindowKinect.h"

int main(int argc, char *argv[])
{
	system("rm -r logs/*");

    QApplication app(argc, argv);
    MainWindowKinect window;
#if defined(Q_OS_SYMBIAN)
    window.showMaximized();
#else
    window.show();
#endif
    return app.exec();
}
