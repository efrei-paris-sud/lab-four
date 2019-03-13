#include <stdio.h>
#include <stdint.h>

#include "connectivity.h"

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "tcpip_adapter.h"


void setup_connectivity(void *pvParameters);

void
setup_connectivity(void *pvParameters)
{
    int8_t rc;
    struct conn_config_t *cfg;
    cfg = (struct conn_config_t*) pvParameters;

    // TODO make here some verifications on the config structure. Check for
    //      example that BLE is used in combination with 6lowpan and not with
    //      other network interface.

    tcpip_adapter_init();

    printf("[setup_connectivity] starting physical layer\n");
    rc = physical_layer_start(cfg->phy_proto);
    if (rc < 0) {
        printf("[IoT-Labs] Error while starting physical layer\n");
        goto end;
    }

    printf("[setup_connectivity] starting network layer\n");
    rc = network_layer_start(cfg->net_proto);
    if (rc < 0) {
        printf("[IoT-Labs] Error while starting network layer\n");
        goto end;
    }

    // TODO call the transport layer to initialize (encrypted or not)
    printf("[setup_connectivity] starting transport layer\n");
    rc = transport_layer_start(cfg->trans_proto, cfg->flag_ssl);
    if (rc < 0) {
        printf("[IoT-Labs] Error while starting transport layer\n");
        goto end;
    }

    // TODO call the application layer and choose which protocol we will
    // communicate with (http/mqtt/CoAP)
    printf("[setup_connectivity] starting application layer\n");
    rc = application_layer_start(cfg->app_proto);
    if (rc < 0) {
        printf("[IoT-Labs] Error while starting application layer\n");
        goto end;
    }

    printf("[setup_connectivity] END\n");

end:
    vTaskDelete(NULL);
}
