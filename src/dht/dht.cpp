#include <Arduino.h>
#include "dht.h"


/**
 * TempAndHumidity é uma struct da seguinte forma:
 * 
 * struct TempAndHumidity {
        float temperature;
        float humidity;
    };
 */

TempAndHumidity temp_umidade(){
    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    
    // data.temperature
    // data.humidity

    return data;
}

#include "dht.h"