#include <mosquitto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void on_connect(struct mosquitto *mosq, void *obj, int result)
{
    printf("ID:%d   \n", *(int *)obj);
    if (result)
    {
        printf("Connect failed\n");
        printf("code %d\n", result);
        exit(-1);
    }
    mosquitto_subscribe(mosq, NULL, "test", 0);
}
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
    printf("New message with topic %s and payload %s\n", message->topic, (char *)message->payload);
}
int main(int argc, char *argv[])
{
    int rc;
    int id = 12;
    mosquitto_lib_init();
    struct mosquitto *mosq = mosquitto_new("NULL", true, &id);
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);
    rc = mosquitto_connect(mosq, "localhost", 1883, 10);
    if (rc)
    {
        printf("Error connecting: %s\n", mosquitto_strerror(rc));
        exit(-1);
    }
    mosquitto_loop_start(mosq);
    printf("Press enter to exit\n");
    getchar();
    mosquitto_loop_stop(mosq, true);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    printf("Bye\n");
    printf("ID:%d   \n", id);
    printf("rc:%d   \n", rc);

    return 0;
}