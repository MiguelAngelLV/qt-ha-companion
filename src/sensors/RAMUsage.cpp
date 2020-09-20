/**
* Create by Miguel Ángel López on 19/09/20
**/

#include <QtCore/QProcess>
#include "RAMUsage.h"


RAMUsage::RAMUsage() {
}

void RAMUsage::initConfig(QJsonObject &config) {
    HASensor::setConfig(config, "ram_usage");

}

QJsonObject RAMUsage::getValue() const {

    QProcess readTotal;
    readTotal.start("awk", QStringList() << "( $1 == \"MemTotal:\" ) { print $2 }" << "/proc/meminfo");

    QProcess readAvailable;
    readAvailable.start("awk", QStringList() << "( $1 == \"MemAvailable:\" ) { print $2 }" << "/proc/meminfo");

    readTotal.waitForFinished();
    readAvailable.waitForFinished();

    qint64 total = readTotal.readAllStandardOutput().toLong();
    qint64 available = readAvailable.readAllStandardOutput().toLong();

    readTotal.close();
    readAvailable.close();

    QJsonObject value;
    value["total"] = total / 1024;
    value["available"] = available / 1024;
    value["state"] = (total - available) / 1024;

    return value;
}

