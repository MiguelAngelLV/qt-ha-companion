/**
* Create by Miguel Ángel López on 19/09/20
**/

#include <src/sensors/RAMUsage.h>
#include <QtCore/QJsonDocument>
#include <QtCore/QTimer>
#include <QtCore/QFile>
#include "HomeAssistantCompanion.h"



HomeAssistantCompanion::HomeAssistantCompanion(const QString& pathConfig) {

    QFile file(pathConfig, this);
    file.open(QIODevice::OpenModeFlag::ReadOnly);
    QByteArray json = file.readAll();
    config = QJsonDocument::fromJson(json).object();

    connectToMqtt();

}



void HomeAssistantCompanion::connectToMqtt() {

    auto mqtt = config["mqtt"].toObject();

    auto port = mqtt["port"].toInt();
    auto username = mqtt["username"].toString();
    auto hostname = mqtt["hostname"].toString();
    auto password = mqtt["password"].toString();

    client = new QMqttClient(this);

    client->setPort(port);
    client->setHostname(hostname);
    client->setUsername(username);
    client->setPassword(password);

    client->connectToHost();

    connect(client, &QMqttClient::stateChanged, this, &HomeAssistantCompanion::updateStatus);
    connect(client, &QMqttClient::messageReceived, this, &HomeAssistantCompanion::messageReceived);



}



void HomeAssistantCompanion::createSensors() {

    sensors.append(new RAMUsage());

}



void HomeAssistantCompanion::updateStatus(QMqttClient::ClientState state) {
    switch (state) {
        case QMqttClient::Disconnected:
            qDebug() << "Disconnected";
            break;
        case QMqttClient::Connecting:
            qDebug() << "Connecting to Mqtt Broker";
            break;
        case QMqttClient::Connected:
            qDebug() << "Connected to Mqtt Broker";
            sendConfigs();
            break;
    }

}

void HomeAssistantCompanion::sendConfigs() {


    for (auto sensor: sensors) {

        sensor->initConfig(config);
        auto c = sensor->getConfig();
        auto topic = sensor->getConfigTopic();

        QJsonDocument document(c);
        client->publish(QMqttTopicName(topic), document.toJson(QJsonDocument::Compact), 1, true);

    }


    sendValues();

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HomeAssistantCompanion::sendValues);
    timer->start(5000);

}

void HomeAssistantCompanion::messageReceived(const QByteArray &message, const QMqttTopicName &topic) {

}

void HomeAssistantCompanion::sendValues() {

    for (auto sensor : sensors) {
        QJsonDocument document(sensor->getValue());
        client->publish(QMqttTopicName(sensor->getStateTopic()), document.toJson(QJsonDocument::Compact));
    }

}

