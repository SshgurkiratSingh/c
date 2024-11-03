#include <mosquitto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define TOPIC1 "mobLabView1"
#define TOPIC2 "mobLabView2"
#define OUTPUT_FILE "input.txt"

// Variables to store the messages from each topic
char message_mobLabView1[256] = "";
char message_mobLabView2[256] = "";

// This function writes the combined message to the file
void write_to_file()
{
    FILE *file = fopen(OUTPUT_FILE, "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    // Combine the two messages into a single string
    fprintf(file, "%s%s\n", message_mobLabView1, message_mobLabView2);
    fclose(file);
    printf("Combined message written to %s\n", OUTPUT_FILE);
}

// Callback when the client connects to the broker
void on_connect(struct mosquitto *mosq, void *obj, int result)
{
    printf("Connected with result code %d\n", result);
    if (result != 0)
    {
        printf("Failed to connect: %d\n", result);
        exit(-1);
    }

    // Subscribe to both topics
    mosquitto_subscribe(mosq, NULL, TOPIC1, 0);
    mosquitto_subscribe(mosq, NULL, TOPIC2, 0);
}

// Callback when a new message arrives
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
    if (strcmp(message->topic, TOPIC1) == 0)
    {
        strncpy(message_mobLabView1, (char *)message->payload, sizeof(message_mobLabView1) - 1);
        message_mobLabView1[sizeof(message_mobLabView1) - 1] = '\0'; // Ensure null-terminated string
    }
    else if (strcmp(message->topic, TOPIC2) == 0)
    {
        strncpy(message_mobLabView2, (char *)message->payload, sizeof(message_mobLabView2) - 1);
        message_mobLabView2[sizeof(message_mobLabView2) - 1] = '\0'; // Ensure null-terminated string
    }

    // Combine and write the messages to the file
    write_to_file();
}

int main(int argc, char *argv[])
{
    int rc;
    int id = 12;

    // Initialize the Mosquitto library
    mosquitto_lib_init();

    // Create a new Mosquitto client
    struct mosquitto *mosq = mosquitto_new("MQTT_Client", true, &id);
    if (!mosq)
    {
        printf("Error: Unable to create mosquitto instance\n");
        exit(-1);
    }

    // Set up callback functions
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    rc = mosquitto_connect(mosq, "test.mosquitto.org", 1883, 10);
    if (rc)
    {
        printf("Error connecting: %s\n", mosquitto_strerror(rc));
        mosquitto_destroy(mosq);
        exit(-1);
    }

    // Start the Mosquitto loop to process network traffic
    mosquitto_loop_start(mosq);

    printf("Press enter to exit...\n");
    getchar(); // Wait for user input to stop the loop

    // Stop the loop and clean up
    mosquitto_loop_stop(mosq, true);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    printf("MQTT Client exited successfully\n");

    return 0;
}
