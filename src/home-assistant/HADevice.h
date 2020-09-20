/**
* Create by Miguel Ángel López on 19/09/20
**/

#ifndef QTHACOMPANION_HADEVICE_H
#define QTHACOMPANION_HADEVICE_H


#include <QtCore/QString>
#include <QtCore/QJsonObject>

class HADevice : public QObject{

    Q_OBJECT


protected:
    QString configTopic;
    virtual void setConfig(QJsonObject &global, const QString& field);

    QJsonObject config;
public:
    HADevice();

    const QString &getConfigTopic() const;
    QJsonObject getConfig();

    virtual void initConfig(QJsonObject & config);

};


#endif //QTHACOMPANION_HADEVICE_H
