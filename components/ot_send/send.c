#include "ot_send.h"

#include <openthread/ping_sender.h>
#include <openthread/logging.h>

#define DEBUG true

/**
 * @file
 *  This file defines the functions used for the sender to send
 *  packets to a given destination, at repeated intervals.
 *
 * @todo
 *  Do a simple ping to the border router to demonstrate that you can successfully
 *  send packets programmatically.
 *
 *  1. Get the source IP address. This will involve calling "otIp6GetUnicastAddresses()"
 *     and traversing to the linked list of "otIp6Address" objects until you find
 *     the multicast address.
 *
 *     A good idea is to look at the source code for the "ipaddr" command to see
 *     how this can be done.
 *
 *  2. Get the destination IP address.
 *
 *  3. Fill out the minimal configurations to get ping working.
 *
 *  4. Send it to the destination! Check Wireshark to make sure you have successfully
 *     sent ping packets at the app layer at deined intervals.
 *
 *     If need be, use the FreeRTOS API to sleep and then send packets at regular
 *     intervals (although you may not need to do this, as I believe OpenThread
 *     can already do this).
 *
 *  5. See if you can pack application layer data ontop of ICMP through ping.
 *     If so, all you need to do at the receiver side is to decrypt the app layer
 *     payload and print it out to the console!
*/

#define MLEID "fdc2:53d3:bb7e:2437:114d:c3da:9918:d5e4"

/**
 * @param
 *  The pointer to the `otNetifAddress` object returned from
 *  `otIp6GetUnicastAddresses()`.
 *
 * @return
 *  The `otNetifAddress` pointer representing the MLEID address for the currently
 *  running device. If MLEID cannot be found, NULL is returned.
*/
otNetifAddress *otIp6GetMleid(const otNetifAddress *firstUnicast) {
#if DEBUG
  char* aBuffer = calloc(1, OT_IP6_SOCK_ADDR_STRING_SIZE);
#endif //DEBUG

  for (otNetifAddress *netif = firstUnicast; netif != NULL; netif = netif->mNext) {
      otIp6Address addr = netif->mAddress;

#if DEBUG
      otIp6AddressToString(&addr, aBuffer, OT_IP6_SOCK_ADDR_STRING_SIZE);
      otLogNotePlat("*****************************");
      otLogNotePlat("The unicast address is %s.", aBuffer);
      otLogNotePlat("*****************************");
#endif // DEBUG

      if (netif->mMeshLocal == true) {
        return netif;
      }
  }
  return NULL;
}

/**
 *
*/
void ping(otInstance *aInstance) {
  const otNetifAddress *firstUnicast = otIp6GetUnicastAddresses(aInstance);

  otIp6GetMleid(firstUnicast);
  return;
};