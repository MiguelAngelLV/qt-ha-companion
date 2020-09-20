/**
* Create by Miguel Ángel López on 19/09/20
**/

#ifndef QTHACOMPANION_RAMUSAGE_H
#define QTHACOMPANION_RAMUSAGE_H


#include <src/home-assistant/HASensor.h>

class RAMUsage : public HASensor {

public:

    RAMUsage();
    QJsonObject getValue() const override;
    void initConfig(QJsonObject &config) override;
};


#endif //QTHACOMPANION_RAMUSAGE_H
