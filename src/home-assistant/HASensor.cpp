/**
* Create by Miguel Ángel López on 19/09/20
**/

#include "HASensor.h"



QJsonObject HASensor::getValue() const {
    return QJsonObject();
}

const QString &HASensor::getStateTopic() const {
    return stateTopic;
}

void HASensor::setConfig(QJsonObject &global, const QString &field) {

    HADevice::setConfig(global, field);

    auto device = config["device"].toObject();

    QString name = config["name"].toString();
    QString prefix = device["name"].toString();


    stateTopic = QString("%1/%2/state")
            .arg(prefix)
            .arg(field);

    config["state_topic"] = stateTopic;
    config["value_template"] = "{{ value_json.state }}";
}

