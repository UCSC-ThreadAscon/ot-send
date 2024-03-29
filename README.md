| Supported Targets | ESP32-C6 | ESP32-H2 |
| ----------------- | -------- | -------- |

# OpenThread UDP Sender

This codebase enables an 802.15.4 ESP32 MCU to broadcast UDP packets in a Thread WLAN.

## Setup

You will first need to form a Thread WLAN with at least two devices.

On the sending device, wait until it has successfully connected to the Thread WLAN. If the sending device is working properly, you should expect the following output, which will keep printing in an infinite loop:
```
I(1786) OPENTHREAD:[N] Platform------: Sent UDP packet 0
I(6786) OPENTHREAD:[N] Platform------: Sent UDP packet 1
I(11786) OPENTHREAD:[N] Platform------: Sent UDP packet 2
I(16786) OPENTHREAD:[N] Platform------: Sent UDP packet 3
```

Note that the `Packet Number` may vary depending on when you have created the UDP socket. Furthermore, the built-in LED will flash whenever a packet is successfully sent.

The implementation for the UDP receiver can be found in its [respective Github repository](https://github.com/UCSC-CSE299A/ot-receive).

## Changing the TX Power

If you would like to change the 802.15.4 transmission power used by OpenThread, enter:

```bash
idf.py menuconfig
```

and navigate to:
```
UCSC Thread-Ascon OpenThread Sender → Set the 802.15.4 TX power used by OpenThread
```

to enter the TX Power (in dBm) that you would like to use.

## Enabling Automatic Start

The `UART` port must be used in order to enable automatic start of sending UDP packets without turning on the serial monitor. The `USB-Serial` port should not be utilized.
