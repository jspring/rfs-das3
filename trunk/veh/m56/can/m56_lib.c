/*=========================================================================
| (c) 2011  Total Phase, Inc.
|--------------------------------------------------------------------------
| Project : Komodo Examples
| File    : monitor.c
|--------------------------------------------------------------------------
| Simple program that monitors CAN bus and GPIO activity.
|--------------------------------------------------------------------------
| Redistribution and use of this file in source and binary forms, with
| or without modification, are permitted.
|
| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
| "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
| LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
| FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
| COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
| INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
| BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
| LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
| CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
| LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
| ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
| POSSIBILITY OF SUCH DAMAGE.
 ========================================================================*/

/*=========================================================================
| INCLUDES
 ========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "komodo.h"

#define NUM_GPIOS 8


/*=========================================================================
| MACROS
 ========================================================================*/
/* This will only work for sample rates that
   are multiples of 1MHz.  If any other rates
   are desired, this code needs to be changed.*/
#define TIMESTAMP_TO_NS(stamp, samplerate_khz) \
    (u64)(stamp * (u64)1000 / (u64)(samplerate_khz/1000))

/* The printf format strings are differenct for 64-bit integers
   between Windows and Linux */
#if defined(WIN32) || defined(_WIN32)
#  define U64_FORMAT_STR "I64u"
#else
#  include <inttypes.h>
#  define U64_FORMAT_STR PRIu64
#endif


/*=========================================================================
| USAGE INFORMATION
 ========================================================================*/
static void print_usage (void) {
    printf(
"Usage: monitor TARGET_PWR NUM_EVENTS \n"
"\n"
"Example utility for capturing CAN and GPIO activity on CAN A.\n"
"\n"
"  TARGET_PWR: 1 turns on target power, 0 does not\n"
"  NUM_EVENTS: Number of events to process before exiting.  If this is set to\n"
"              zero, the capture will continue indefinitely\n"
"\n"
"For product documentation and specifications, see www.totalphase.com.\n");
};


/*=========================================================================
| FUNCTIONS
 ========================================================================*/
static void print_num_array (u08* array, int len) {
    int i = 0;

    for (i = 0; i < len; i++)
        printf("%x ", array[i]);
}

static void print_status (u32 status) {
    printf(" ");

    if (status == KM_OK)                 printf("OK ");
    if (status & KM_READ_TIMEOUT)        printf("TIMEOUT ");
    if (status & KM_READ_ERR_OVERFLOW)   printf("OVERFLOW ");
    if (status & KM_READ_END_OF_CAPTURE) printf("END OF CAPTURE ");
    if (status & KM_READ_CAN_ARB_LOST)   printf("ARBITRATION LOST ");
    if (status & KM_READ_CAN_ERR)        printf("ERROR %x ", status &
                                                KM_READ_CAN_ERR_FULL_MASK);
}

static void print_events (u32 events, u32 bitrate) {
    if (events == 0)
        return;
    if (events & KM_EVENT_DIGITAL_INPUT)
        printf("GPIO CHANGE 0x%x; ", events & KM_EVENT_DIGITAL_INPUT_MASK);
    if (events & KM_EVENT_CAN_BUS_STATE_LISTEN_ONLY)
        printf("BUS STATE LISTEN ONLY; ");
    if (events & KM_EVENT_CAN_BUS_STATE_CONTROL)
        printf("BUS STATE CONTROL; ");
    if (events & KM_EVENT_CAN_BUS_STATE_WARNING)
        printf("BUS STATE WARNING; ");
    if (events & KM_EVENT_CAN_BUS_STATE_ACTIVE)
        printf("BUS STATE ACTIVE; ");
    if (events & KM_EVENT_CAN_BUS_STATE_PASSIVE)
        printf("BUS STATE PASSIVE; ");
    if (events & KM_EVENT_CAN_BUS_STATE_OFF)
        printf("BUS STATE OFF; ");
    if (events & KM_EVENT_CAN_BUS_BITRATE)
        printf("BITRATE %dkHz; ", bitrate/1000);
}

// The main packet dump routine
static void candump (Komodo km, int max_events) {
    int ret;
    int count;
    int data_len = 8;
    u08 data[8];
    int samplerate_khz;

    km_can_info_t   info;
    km_can_packet_t pkt;


    // Print description of csv output
    printf("\nindex,time(ns),(status & events),<ID:rtr/data> hex data\n\n");

    // Start monitoring
    for (count = 0; max_events == 0 || count < max_events; count++) {

	printf("%d,%" U64_FORMAT_STR",(",
               count, TIMESTAMP_TO_NS(info.timestamp, samplerate_khz));

	if (ret < 0)
	  printf("error=%d", ret);

	print_status(info.status);
        print_events(info.events, info.bitrate_hz);
	printf(")");

        // Continue printing if we didn't see timeout, error or dataless events
        if ( (info.status == KM_OK) && !info.events) {
            printf(",<%x:%s ", pkt.id, pkt.remote_req ? "rtr>" : "data>");

            // If packet contained data, print it
            if (!pkt.remote_req)
                print_num_array(data, pkt.dlc);
        }
	printf("\n");
    }
}

int init_kom(Komodo km, int *power, int port, u16 timeout, u32 *bitrate) {
    int    i;
    int    ret;
    int    max_events;
    int    samplerate_khz;

    // Open the interfaces
    km = km_open(port);
    if (km <= 0) {
        printf("Unable to open Komodo on port 0: ");
        printf("Error code = %d\n", km);
        return 1;
    }

    /* Acquire features.  Acquiring KM_FEATURE_CAN_A_CONTROL causes the Komodo
       interface to ACK all packets transmitted on the bus.  Remove this feature
       to prevent the device from transmitting anything on the bus.*/
    ret = km_acquire(km, KM_FEATURE_CAN_A_CONFIG  |
                         KM_FEATURE_CAN_A_LISTEN  |
                         KM_FEATURE_CAN_A_CONTROL |
    			 KM_FEATURE_CAN_B_CONFIG  |
                         KM_FEATURE_CAN_B_LISTEN  |
                         KM_FEATURE_CAN_B_CONTROL |
                         KM_FEATURE_GPIO_CONFIG   |
                         KM_FEATURE_GPIO_LISTEN);
    printf("Acquired features for both CAN A&B 0x%x\n", ret);

    // Set bitrate
    ret = km_can_bitrate(km, KM_CAN_CH_A, bitrate[0]);
    printf("Chan A bitrate set to %d kHz\n", ret/1000);
    ret = km_can_bitrate(km, KM_CAN_CH_B, bitrate[1]);
    printf("Chan B bitrate set to %d kHz\n", ret/1000);

    // Set timeout
    km_timeout(km, timeout);
    printf("Timeout set to %d ms\n", timeout);

    // Set target power
    km_can_target_power(km, KM_CAN_CH_A, power[0]);
    printf("Chan A target power %s\n", power[0] ? "ON" : "OFF");
    km_can_target_power(km, KM_CAN_CH_B, power[1]);
    printf("Chan B target power %s\n", power[1] ? "ON" : "OFF");

    // Configure all GPIO pins as inputs
    for (i = 0; i < NUM_GPIOS; i++)
        km_gpio_config_in(km, i, KM_PIN_BIAS_PULLUP, KM_PIN_TRIGGER_BOTH_EDGES);
    printf("All pins set as inputs\n");

    // Get samplerate
    samplerate_khz = km_get_samplerate(km)/1000;

    // Enable Komodo
    ret = km_enable(km);
    if (ret != KM_OK) {
        printf("Unable to enable Komodo\n");
        return 1;
    }
    return 0;
}
