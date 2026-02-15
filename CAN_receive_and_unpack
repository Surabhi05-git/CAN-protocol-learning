/*
 * can_receiver.cpp
 *
 * created on: 05-Feb-2026
 * Author: Surabhi
 *
 * Function:
 * - Receive CAN frames from can0
 * - Identify ABS wheel speed frame
 * - Unpack using Opel generated code (using cantools)
 * - Extract Rear Left & Rear Right wheel speed
 * - Store decoded data for S2S (globals)
 */

#include "can_receiver.h"

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

/* Generated Opel DBC code (C) */
extern "C" {
#include "opel_omega_2001.h"
}

/* -------- S2S-ready global data -------- */
double g_rear_left_speed_kmh  = 0.0;
double g_rear_right_speed_kmh = 0.0;
std::mutex wheel_speed_mutex;

/* CAN thread running flag (DEFINITION + INITIALIZATION) */
std::atomic<bool> g_can_running(true);

int start_can_receiver()
{
    int sock;
    struct ifreq ifr;
    struct sockaddr_can addr;
    struct can_frame frame;

    /* 1. Create CAN RAW socket */
    sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (sock < 0) {
        perror("Socket creation failed");
        return -1;
    }

    /* 2. Select CAN interface: can0 */
    std::strcpy(ifr.ifr_name, "can0");
    if (ioctl(sock, SIOCGIFINDEX, &ifr) < 0) {
        perror("ioctl failed");
        close(sock);
        return -1;
    }

    /* 3. Bind socket */
    addr.can_family  = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind failed");
        close(sock);
        return -1;
    }

    std::cout << "CAN Receiver started on can0\n";

    /* 4. Receive CAN frames */
    while (g_can_running)
    {
        int nbytes = read(sock, &frame, sizeof(struct can_frame));
        if (nbytes < 0) {
            if (!g_can_running) break;
            perror("CAN read error");
            continue;
        }

        /* 5. Check ABS Wheel Speed Frame ID */
        if ( (frame.can_id & CAN_EFF_MASK) ==
              OPEL_OMEGA_2001_ABS_WHEEL_SPEED_FRAME_ID &&
              frame.can_dlc ==
              OPEL_OMEGA_2001_ABS_WHEEL_SPEED_LENGTH )
        {
            struct opel_omega_2001_abs_wheel_speed_t abs_data;

            /* 6. Unpack CAN data */
            int ret = opel_omega_2001_abs_wheel_speed_unpack(
                &abs_data,
                frame.data,
                frame.can_dlc
            );

            if (ret == 0)
            {
                /* Store decoded data (used later by publisher) */
                {
                    std::lock_guard<std::mutex> lock(wheel_speed_mutex);

                    g_rear_left_speed_kmh =
                        opel_omega_2001_abs_wheel_speed_rear_left_wheel_speed_decode(
                            abs_data.rear_left_wheel_speed);

                    g_rear_right_speed_kmh =
                        opel_omega_2001_abs_wheel_speed_rear_right_wheel_speed_decode(
                            abs_data.rear_right_wheel_speed);
                }
            }
            else
            {
                std::cerr << "ABS unpack failed\n";
            }
        }
    }

    close(sock);
    std::cout << "CAN Receiver stopped.\n";
    return 0;
}
