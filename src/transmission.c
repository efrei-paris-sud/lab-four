#include <errno.h>
#include <string.h>

#include "formatting.h"
#include "app_layer.h"

#define REPR_MAX    200

QueueHandle_t sensor_readings_queue;

int8_t
transmission_init()
{
    int8_t rc;

    sensor_readings_queue = xQueueCreate(MAX_READINGS, sizeof(struct a_reading));
    if (sensor_readings_queue == NULL) {
        printf("[IoT-Labs] Error while creating transmission queue\n");
        return ENOMEM;
    }

    return rc;
}

int8_t
transmission_enqueue(struct a_reading *reading)
{
    int8_t rc;

    rc = xQueueSendToBack(sensor_readings_queue, (void*)reading, portMAX_DELAY);
    if (rc != pdPASS) {
        printf("[IoT-Labs] Error while enqueuing a reading\n");
        return rc;
    }

    return rc;
}

int8_t
transmission_dequeue(struct a_reading *reading)
{
    int8_t rc;

    rc = xQueueReceive(sensor_readings_queue, reading, portMAX_DELAY);
    if (rc != pdTRUE) {
        printf("[IoT-Labs] Error while dequeuing a reading\n");
        return rc;
    }

    return rc;
}

int8_t
make_a_reading(struct a_reading *reading, struct bme280_data *data)
{
    int8_t rc = 0;

    reading->timestamp = xTaskGetTickCount();
    memcpy(&reading->data, data, sizeof(*data));

    /* debug */
    printf("[make_a_reading] reading->timestamp = %d\n", reading->timestamp);
    printf("[make_a_reading] reading->data->temperature = %d\n",
            reading->data.temperature);

    return rc;
}

void
print_a_reading(const struct a_reading *reading)
{
    assert(reading != NULL);
    printf("[print_a_reading] timestamp = %d\n", reading->timestamp);
    printf("[print_a_reading] temperature = %f\n",
            (float)reading->data.temperature);
}

void
perform_transmissions(void *pvParameters)
{
    int8_t rc;
    struct a_reading reading;
    char representation[REPR_MAX];
    //cJSON json; // FIXME very bad! very, very bad! make code modular! get rid of porosity

    // TODO make this function wait for the connection event
    while (1) {
        /* get a reading from transmission queue */
        rc = ENOSYS;

        /* debug */
        print_a_reading(&reading);

        /* format the dequeued reading and get the string representation
         * corresponding to it
         */
        rc = ENOSYS;

        /* send the formatted reading */
        rc = ENOSYS; 

        if (rc < 0) {
            printf("[IoT-Labs] Error trying to transmit\n");
            goto end;
        }
    }

end:
    vTaskDelete(NULL);
}
