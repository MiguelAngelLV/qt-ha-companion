/**
* Create by Miguel Ángel López on 19/09/20
**/

#ifndef QTHACOMPANION_HASENSOR_H
#define QTHACOMPANION_HASENSOR_H


#include "HADevice.h"

class HASensor : public HADevice {


private:

    QString stateTopic;


protected:
    void setConfig(QJsonObject &global, const QString &field) override;

public:

    virtual QJsonObject getValue() const;



    const QString &getStateTopic() const;
};


#endif //QTHACOMPANION_HASENSOR_H
