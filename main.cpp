#include "MainWidget.h"

#include <QtSingleApplication>

int main(int argc, char *argv[])
{
    QtSingleApplication app("MusicPlayer", argc, argv);

    //判断实例是否已经运行
    if(app.isRunning())
    {
        qDebug() << "this is already running";
        //1s后激活前个实例
        app.sendMessage("raise_window_noop", 1000);
        return EXIT_SUCCESS;
    }
    MainWidget w;
    // 如果是第一个实例,则绑定,方便下次调用
    app.setActivationWindow(&w, 1);
    w.show();

    return app.exec();
}
