#include <iostream>
#include <mqtt/async_client.h>
#include<wiringPi.h>
#include<softPwm.h>
#include <mosquitto.h>

const std::string SERVER_ADDRESS("tcp://192.168.25.203:1883");
const std::string CLIENT_ID("cpp_publisher");
const std::string TOPIC("data");

int main() {
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);

    mqtt::connect_options conn_opts;
    conn_opts.set_keep_alive_interval(20);
    conn_opts.set_clean_session(true);

    try {
        client.connect(conn_opts)->wait();
        
        while (true) {
            std::string message = "Your pour button data";
            client.publish(TOPIC, message.c_str(), message.length(), 0)->wait();
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Adjust the delay as needed
        }
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}
