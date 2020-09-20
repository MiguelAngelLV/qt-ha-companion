/**
* Create by Miguel Ángel López on 19/09/20
**/

#include <QtCore/QJsonArray>
#include "HADevice.h"



HADevice::HADevice() {

}

void HADevice::setConfig(QJsonObject &global, const QString& field) {


    auto device = global["device"].toObject();
    auto config = global[field].toObject();
    auto homeAssistant = global["home_assistant"].toObject();

    QString name = config["name"].toString();
    QString prefix = device["name"].toString();


    config["state_topic"] = QString("%1/%2/state")
            .arg(prefix)
            .arg(field);

    config["device"] = device;

    config["unique_id"] = QString("%1_%2")
            .arg(prefix)
            .arg(field);

    configTopic = QString("%1/sensor/%2_%3/memory/config")
            .arg(homeAssistant["prefix"].toString())
            .arg(prefix)
            .arg(field);



    this->config = config;


}

const QString &HADevice::getConfigTopic() const {
    return configTopic;
}

QJsonObject HADevice::getConfig() {
    return config;

}

void HADevice::initConfig(QJsonObject & config) {

}

