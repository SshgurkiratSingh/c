#include <iostream>
#include <fstream>
#include <string>
#include <mqtt/async_client.h>

const std::string SERVER_ADDRESS("tcp://test.mosquitto.org:1883"); // Replace with your broker if necessary
const std::string CLIENT_ID("C++Client");
const std::string TOPIC1("mobLabView1");
const std::string TOPIC2("mobLabView2");
const std::string OUTPUT_FILE("input.txt");

std::string message_mobLabView1 = "";
std::string message_mobLabView2 = "";

// This function writes the combined message to the file
void write_to_file() {
    std::ofstream outfile(OUTPUT_FILE);
    if (outfile.is_open()) {
        std::string combined_message = "mobLabView1: " + message_mobLabView1 + ", mobLabView2: " + message_mobLabView2;
        outfile << combined_message;
        outfile.close();
        std::cout << "Written to file: " << combined_message << std::endl;
    } else {
        std::cerr << "Error: Unable to open file" << std::endl;
    }
}

// Callback class for message reception
class callback : public virtual mqtt::callback {
    void message_arrived(mqtt::const_message_ptr msg) override {
        std::string topic = msg->get_topic();
        std::string payload = msg->to_string();

        // Store the messages according to the topic
        if (topic == TOPIC1) {
            message_mobLabView1 = payload;
        } else if (topic == TOPIC2) {
            message_mobLabView2 = payload;
        }

        // Combine and write the messages to the file
        write_to_file();
    }
    
    void connection_lost(const std::string& cause) override {
        std::cerr << "Connection lost: " << cause << std::endl;
    }
};

// Function to initialize the MQTT client and subscribe to topics
int main() {
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
    callback cb;
    client.set_callback(cb);

    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);
    connOpts.set_clean_session(true);

    try {
        // Connect to the broker
        std::cout << "Connecting to the MQTT server..." << std::endl;
        client.connect(connOpts)->wait();
        std::cout << "Connected" << std::endl;

        // Subscribe to both topics
        client.subscribe(TOPIC1, 1)->wait();
        client.subscribe(TOPIC2, 1)->wait();

        // Loop forever to keep the client running
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // Disconnect (not reached in this example, but would be for cleanup)
        client.disconnect()->wait();
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}
