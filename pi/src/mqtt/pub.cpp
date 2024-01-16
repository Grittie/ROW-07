#include <iostream>
#include <mosquitto.h>
#include <cstring>

int main() {
    int rc;
    struct mosquitto *mosq;
    mosquitto_lib_init();
    mosq = mosquitto_new("publisher-test", true, nullptr);
    rc = mosquitto_connect(mosq, "192.168.161.203", 1883, 10);
    if (rc != 0) {
        std::cout << "Client could not connect to broker! Error Code: " << rc << std::endl;
        mosquitto_destroy(mosq);
        return -1;
    }
    std::cout << "We are now connected to the broker!" << std::endl;

    // Get the message from the user
    std::cout << "Enter the message to send: ";
    std::string message;
    std::getline(std::cin, message);

    // Publish the entered message to the topic
    mosquitto_publish(mosq, nullptr, "distance", message.size(), message.c_str(), 0, false);

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return 0;


}