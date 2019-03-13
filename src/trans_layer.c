#include "lwip/api.h"
#include "lwip/netdb.h"
#include "lwip/err.h"
#include "lwip/ip_addr.h"

/* mbedtls includes */
#include "mbedtls/net.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/debug.h"
/* end of mbedtls includes */

#include "trans_layer.h"

struct netconn cx;

int8_t
establish_conn(int port, char * hostname)
{
    int8_t rc;
    ip_addr_t local_ip;
    ip_addr_t remote_ip;

    rc = ENOSYS;

    return rc;
}

int8_t
trans_send(const void *app_paquet)
{
    int8_t rc;

    rc = ENOSYS;
    // TODO switch whether tls is enabled or not and choose the right function
    // in order to send data over the created socket!

    return rc;
}

int8_t
transport_layer_start(enum trans_protocols trans_proto, int ssl_flag)
{
    int8_t rc;

    switch (trans_proto) {
        case TCP:
            rc = ENOSYS;
            break;
        case UDP:
            rc = ENOSYS;
            break;
        default:
            rc = ENOSYS;
            break;
    }

    return rc;
}


int8_t
establish_secure_conn(const char *cert)
{
    int8_t rc;

    rc = ENOSYS;

    return rc;
}
