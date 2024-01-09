#include "sub.h"
#include <iostream>
#include <mosquitto.h>
#include <string>
#include <sstream>
#include <array>
#include <algorithm>
#include <mutex> // Adding mutex
#include <thread>
#include <chrono>


#define max 2

using namespace std;
std::mutex mtx;  // Mutex for synchronization

// bool returnMessage = false;
std::array<double, 2> xyInput = {0, 0};

char returnMessage;

std::string strings[max]; //define max string

int len(string str)  
{  
    int length = 0;  
    for (int i = 0; str[i] != '\0'; i++)  
    {  
        length++;  
          
    }  
    return length;     
}  

void split (string str, char seperator)  
{  
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= len(str))  
    {  
        if (str[i] == seperator || i == len(str))  
        {  
            endIndex = i;  
            string subStr = "";  
            subStr.append(str, startIndex, endIndex - startIndex);  
            strings[currIndex] = subStr;  
            currIndex += 1;  
            startIndex = endIndex + 1;  
        }  
    i++;  
    }     
}  

void on_connect(struct mosquitto *mosq, void *obj, int rc) {
    std::cout << "ID: " << *(int *)obj << std::endl;
    if (rc) {
        std::cout << "Error with result code: " << rc << std::endl;
        exit(-1);
    }
    mosquitto_subscribe(mosq, nullptr, "joystick values", 0);
}

// double Sub::return_x() {
//     std::cout << "x: " << xyInput[0] << " ";
//     return xyInput[0];
// }

// double Sub::return_y() {
//     std::cout << "y: " << xyInput[1] << "\n";
//     return xyInput[1];
// }

char Sub::return_message() {
    return returnMessage;
}

// bool Sub::message_received() {
//     returnMessage = false;
//     return returnMessage;
// }

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg) {
    std::string receivedMessage = static_cast<char *>(msg->payload);
    std::cout << receivedMessage << "\n";

    returnMessage = receivedMessage[0];

    // char seperator = ' ';
    // std::lock_guard<std::mutex> lock(mtx);  // Lock to protect shared data
    // split(receivedMessage, seperator);
    
    // // Process and update xyInput
    // for (int i = 0; i < max; i++) {
    //     std::string val = strings[i];
    //     std::replace(val.begin(), val.end(), ',', '.');
    //     std::stringstream s(val);
    //     s >> xyInput[i];
    // }
    // returnMessage = true;
    
    // std::cout << "final x: " << xyInput[0] << " y: " << xyInput[1] << std::endl;
}

int Sub::main() {
    int rc, id = 12;
    mosquitto_lib_init();
    struct mosquitto *mosq;
    mosq = mosquitto_new("subscribe-test", true, &id);
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);
    rc = mosquitto_connect(mosq, "192.168.94.203", 1883, 10);
    if (rc) {
        std::cout << "Could not connect to Broker with return code " << rc << std::endl;
        return -1;
    }  
    mosquitto_loop_start(mosq);

    while (true) {
        {
            std::lock_guard<std::mutex> lock(mtx);  // Lock to protect shared data
            // Your existing code for MQTT message processing
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(20));  // Introduce a short delay if needed
    }

    // Note: The loop above will run indefinitely; ensure proper thread termination mechanism if needed

    // Clean up
    mosquitto_loop_stop(mosq, true);
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}
