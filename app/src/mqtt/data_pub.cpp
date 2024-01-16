#include <iostream>
#include <mqtt/client.h>
#include <mosquitto.h>
#include <string>
#include <sstream>
#include <array>
#include <algorithm>
#include <mutex> // Adding mutex
#include <thread>
#include <chrono>


int main() {
    const std::string serverURI = "tcp://192.168.25.203:1883";
    const std::string clientId = "10";
    const std::string topic = "data";
    const std::string message = "your_message";

    mqtt::client client(serverURI, clientId);

    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);

    try {
        client.connect(connOpts);

        mqtt::message_ptr pubmsg = mqtt::make_message(topic, message);
        client.publish(pubmsg);

        client.disconnect();
    } catch (const mqtt::exception& exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }

    return 0;
}
