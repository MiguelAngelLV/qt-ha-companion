#include "mainwindow.h"
#include "HomeAssistantCompanion.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    auto ha = new HomeAssistantCompanion("/home/miguel/Desarrollo/qt-ha-companion/QtHaCompanion/config/custom.json");
    ha->createSensors();


    return a.exec();
}
