/**
* Create by Miguel Ángel López on 19/09/20
**/

#ifndef QTHACOMPANION_HOMEASSISTANTCOMPANION_H
#define QTHACOMPANION_HOMEASSISTANTCOMPANION_H


#include <src/home-assistant/HASensor.h>
#include <QtMqtt/QMqttClient>

class HomeAssistantCompanion : public QObject {

    Q_OBJECT

private:

    QJsonObject config;
    QMqttClient * client;
    QVector<HASensor*> sensors;

public:

    HomeAssistantCompanion(const QString& pathConfig);
    void sendConfigs();

    void createSensors();
    void sendValues();
    void updateStatus(QMqttClient::ClientState state);


    void messageReceived(const QByteArray &message, const QMqttTopicName &topic = QMqttTopicName());

    void connectToMqtt();
};


#endif //QTHACOMPANION_HOMEASSISTANTCOMPANION_H
