#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mosquitto.h>
int main(int argc, char *argv[])
{
    int rc;
    struct mosquitto *mosq;
    mosquitto_lib_init();
    mosq = mosquitto_new("test", true, NULL);
    rc = mosquitto_connect(mosq, "localhost", 1883, 60);
    if (rc != 0)
    {
        printf("Error connecting: %s\n", mosquitto_strerror(rc));
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return 1;
    }
    printf("Connected\n");
    mosquitto_publish(mosq, NULL, "test", 11, "hel o", 0, false);
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}