# MQTT Implementation in Raspberry Pi

This file describes how to establish MQTT communication between a Raspberry Pi and an Android app; MQTT is a lightweight public subscription messaging protocol ideal for IoT scenarios

### Components of MQTT

MQTT consists of the following components:

-Brokers: Brokers are servers that manage the communication between publishers and subscribers. Brokers maintain a list of topics and subscribers, and they forward messages from publishers to subscribers.

-Publishers: Publishers are devices that create and send messages to topics.

-Subscribers: Subscribers are devices that receive messages from topics.

-Topics: Topics are hierarchical names that identify the type of information being published or subscribed to.
Messages: Messages are the basic units of data that are exchanged between publishers and subscribers. Messages consist of a payload (the actual data being sent) and a header (which contains information about the message, such as the topic, QoS, and retain flag).


### How MQTT Works


1. Establish a Connection: The publisher and subscriber devices first establish a connection to the broker.
2. Publish a Message: The publisher device publishes a message to a specific topic.
3. Distribute the Message: The broker delivers the message to all subscribers that are subscribed to the topic.
4. Receive the Message: The subscriber device receives the message and processes it.

### Requirements

- Raspberry Pi with Raspbian OS
- Eclipse Paho MQTT C library for Raspberry Pi
- MQTT broker (e.g., Mosquitto)



## Raspberry Pi Setup
Step 1: Install the Eclipse Paho MQTT C library on your Raspberry Pi.

```bash
sudo apt-get install libmqttcpp-dev
```


Step 2: Write the C++ code for publishing messages from the Pi to the MQTT broker.


1. Create a C++ file for publisher.
2. Include the necessary libraries

```bash
#include <mosquitto.h>
#include <iostream>

```

3. Connect to Broker:

Create a mosquitto client object and connect to the MQTT broker:

```bash
mosquitto *client = mosquitto_new("raspberry_pi", true, NULL);
if (mosquitto_connect(client, "broker_ip", 1883, 60, NULL) != MOSQ_ERR_SUCCESS) {
    std::cerr << "Failed to connect to MQTT broker" << std::endl;
    exit(1);
}
```

4. publish messages to the specified topic:

```bash
const char *message = "Hello from Raspberry Pi";
mosquitto_publish(client, NULL, topic, strlen(message), message, 0, false);

```

5.Define functions to handle MQTT events like connection, publition, and message reception:

```bash
static void on_connect(struct mosquitto *mosq, void *obj, int rc) {
    if (rc == 0) {
        std::cout << "Connected to MQTT broker successfully" << std::endl;
    } else {
        std::cerr << "Failed to connect to MQTT broker, return code: " << rc << std::endl;
    }
}

static void on_subscribe(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *qos) {
    std::cout << "Subscribed to topic successfully" << std::endl;
}

static void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message) {
    std::string payload(message->payload, message->payloadlen);
    std::cout << "Received message: " << payload << std::endl;
}
```


6. Attach the callback functions to the client object:

```bash

mosquitto_connect_callback_set(client, on_connect);
mosquitto_subscribe_callback_set(client, on_subscribe);
mosquitto_message_callback_set(client, on_message);


```



Step 3: Write the C++ code for subscribing to messages from the MQTT broker.

1. Initialize MQTT client object
```bash
 mosquitto *client = mosquitto_new("my-client", true, NULL);

```



2. Connect to MQTT broker

```bash
  if (mosquitto_connect(client,"192.168.161.203", 1883, 10, NULL) != MOSQ_ERR_SUCCESS) {
    std::cerr << "Failed to connect to MQTT broker" << std::endl;
    return 1;
  }

```
3. Subscribe to topic 

 ```bash
  if (mosquitto_subscribe(client, NULL, "direction", 1) != MOSQ_ERR_SUCCESS) {
    std::cerr << "Failed to subscribe to topic" << std::endl;
    return 1;
  }
  
```

  4. Callback function to handle incoming messages
```bash
  void on_message(mosquitto *mosq, void *obj, const mosquitto_message *message) {
    std::string payload(message->payload, message->payloadlen);
    std::cout << "Received message: " << payload << std::endl;
  }
  
```

  5. Set message callback

 ```bash
  mosquitto_message_callback_set(client, on_message);

```
 6. Keep the connection alive to receive messages

 c
  while (true) {
    mosquitto_loop(client, 100, 1);
  }
```

