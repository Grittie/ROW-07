#include <iostream>
#include<wiringPi.h>
#include<softPwm.h>

#include <mosquitto.h>

int main() {
     

    int rc;
    struct mosquitto *mosq;
    mosquitto_lib_init();
    mosq = mosquitto_new("publisher-test", true, nullptr);
    rc = mosquitto_connect(mosq,"192.168.25.203", 1883, 10);
    if (rc != 0) {
        std::cout << "Client could not connect to broker! Error Code: " << rc << std::endl;
        mosquitto_destroy(mosq);
        return -1;
    }
    std::cout << "We are now connected to the broker!" << std::endl;
     
    mosquitto_publish(mosq, nullptr, "test", 6, "Hello", 0, false);
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return 0;
}
