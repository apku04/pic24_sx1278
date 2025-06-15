/* ============================================================================
Copyright (C) 2015 Achuthan Paramanathan.
This program is distributed under the terms of the GNU General Public License.
For details, see <http://www.gnu.org/licenses/>.
Revision Information:
File name: networklayer.c
Version:   v0.0
Date:      31-10-2019
=============================================================================== 
*/


#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "networklayer.h"
#include "maclayer.h"
#include "packetBuffer.h"

/*
 ** ============================================================================
 **                   LOCAL  FUNCTION DECLARATIONS
 ** ============================================================================
 */

static GLOB_RET network_outgoing( Packet *pkt );
static GLOB_RET network_incoming( Packet *pkt );
static GLOB_RET handle_broadcast_packet(Packet *pkt);
static GLOB_RET handle_regular_packet(Packet *pkt);
static bool process_received_beacon(Packet* pkt);
static bool is_valid_address(uint8_t address);
uint8_t calculate_crc8(uint8_t *data, uint8_t length);

static char find_next_hop(void);

nlme Nlme;

// Polynomial for CRC-8: x^8 + x^2 + x + 1
#define CRC8_POLYNOMIAL 0x07

/*
** =============================================================================
**                    PRIVATE FUNCTIONS
** =============================================================================
*/


// Function to verify CRC-8 for a received packet
uint8_t verify_crc8(uint8_t *data, uint8_t length, uint8_t crc_received) {
    uint8_t crc_calculated = calculate_crc8(data, length);
    return (crc_calculated == crc_received) ? 1 : 0;
}

// Function to calculate CRC-8 for a given data buffer
uint8_t calculate_crc8(uint8_t *data, uint8_t length) {
    uint8_t crc = 0;
    for (uint8_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ CRC8_POLYNOMIAL;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

static bool is_valid_address(uint8_t address) {
    return address >= 1 && address <= MAX_DEST_ADDR;
}

static GLOB_RET handle_broadcast_packet(Packet *pkt) {
    GLOB_RET ret = GLOB_SUCCESS;
    
    // loop to see if we have had this
    for (int i = 0; i < MAX_RX_HIST_CNT; i++) {
        if ((Nlme.rxHist[i].adr == pkt->source_adr) && 
            (Nlme.rxHist[i].seq == pkt->sequence_num)) {
            return ret;  // Return early if duplicate packet is found
        }
    }
    
    if (GLOB_ERROR_BUFFER_FULL != buffer_full(Nlme.pktTxBuf)) {
        // Check if the packet with the same src addr and seq is already in the buffer
        ret = search_packet_buffer(Nlme.pktTxBuf, pkt->source_adr, pkt->sequence_num);
        if (GLOB_FAILURE == ret) {
            
            pkt->pOwner = MAC;
            pkt->pktDir = RETX;
            pkt->TTL = pkt->TTL - 1;

            // For retransmission
            write_packet(Nlme.pktTxBuf, pkt);

            Nlme.rxHist[Nlme.rxHistCnt].adr = pkt->source_adr;
            Nlme.rxHist[Nlme.rxHistCnt].seq = pkt->sequence_num;

            // Increment the rxHistCnt index for the circular buffer
            Nlme.rxHistCnt = (Nlme.rxHistCnt + 1) % MAX_RX_HIST_CNT;
            
        } else {
            print("Network Incoming: Duplicate packet found, not retransmitting\n\r");
        }
        
        // print it on terminal via app layer 
        pkt->pOwner = APP;
        pkt->pktDir = INCOMING;
        write_packet(Nlme.pktRxBuf, pkt);

    }
    
    return ret;
}

static GLOB_RET handle_regular_packet(Packet *pkt) {
    GLOB_RET ret = GLOB_SUCCESS;

    if (GLOB_ERROR_BUFFER_FULL != buffer_full(Nlme.pktRxBuf)) {
        pkt->pOwner = APP;
        pkt->pktDir = INCOMING;
        write_packet(Nlme.pktRxBuf, pkt);
    } else {
        print("Network Incoming: Reception buffer full, failed to write packet\n\r");
    }
    
    return ret;
}

static bool process_received_beacon(Packet* pkt) {
    
    // Verify CRC before processing
    uint8_t table_length = pkt->length - PACKET_HEADER_SIZE;
    
     // Verify CRC only if the routing table is not empty
    if ((Nlme.num_entries != 0) && 
        (!verify_crc8(pkt->data, table_length - 1, pkt->data[table_length-1]))) {
        print("CRC Check Failed: Packet corrupted\n\r");
        return false;  // Packet corrupted
    }
    
    // 1. Extract the source address and routing information from the packet
    uint8_t source_address = pkt->source_adr;
    int8_t signal_strength = pkt->prssi;

    // 2. Inspect the beacon
    if (signal_strength < SIGNAL_STRENGTH_THRESHOLD) {
        return false;  // Unusable beacon
    }

    uint8_t my_addr = get_mac_address();
    if (source_address == my_addr) {
        print("Received beacon from self. Ignoring...\n\r");
        return false;  // Ignore beacons from self
    }

    // 3. Update or Add Y's beacon to Nlme's routing table
    int found_index = -1;
    for (int i = 0; i < Nlme.num_entries; i++) {
        if (Nlme.routing_table[i].destination == source_address) {
            found_index = i;
            break;
        }
    }
    if (found_index == -1 && Nlme.num_entries < MAX_ENTRIES) {
        Nlme.routing_table[Nlme.num_entries] = (RoutingEntry){ source_address, source_address, 1 };
        Nlme.num_entries++;
    }

    // 4. For each routing entry in the received beacon
    for (int i = 0; i < pkt->mesh_tbl_entries; i++) {
        RoutingEntry entry = {
            .destination = pkt->data[i * 3],
            .next_hop = pkt->data[i * 3 + 1],
            .hop_count = pkt->data[i * 3 + 2]
        };
        
        // Check if all bytes are 0 and skip this entry if they are
        if (entry.destination == 0 && 
            entry.next_hop == 0 && 
            entry.hop_count == 0) {
            continue;
        }

        uint8_t my_addr = get_mac_address();
        if (entry.destination == my_addr) continue;  // Skip if destination is the current node

        int found_entry_index = -1;
        for (int j = 0; j < Nlme.num_entries; j++) {
            if (Nlme.routing_table[j].destination == entry.destination) {
                found_entry_index = j;
                break;
            }
        }
        if (found_entry_index != -1) {
            if (entry.hop_count + 1 < Nlme.routing_table[found_entry_index].hop_count) {
                Nlme.routing_table[found_entry_index].hop_count = entry.hop_count + 1;
                Nlme.routing_table[found_entry_index].next_hop = source_address;
            }
        }
        else if (Nlme.num_entries < MAX_ENTRIES) {
            Nlme.routing_table[Nlme.num_entries] = (RoutingEntry){ entry.destination, source_address, entry.hop_count + 1 };
            Nlme.num_entries++;
        }
    }
    
    // print it on terminal via app layer 
    pkt->pOwner = APP;
    pkt->pktDir = INCOMING;
    pkt->length = pkt->length -1; // remove the crc from being prented on app layer
    write_packet(Nlme.pktRxBuf, pkt);

    return true;  // Successful beacon processing
}

static GLOB_RET network_outgoing(Packet *pkt) {
    GLOB_RET ret = GLOB_SUCCESS;

    pkt->pOwner = MAC;
    pkt->pktDir = OUTGOING;
    pkt->TTL = Nlme.ttl;
    pkt->mesh_dest = Nlme.mesh_dest;
    pkt->mesh_src = get_mac_address();
    pkt->mesh_tbl_entries = Nlme.num_entries;
    
    if (pkt->control_app == BEACON ||
        pkt->control_app == PING || 
        pkt->control_app == PONG   ) {
        
        if(pkt->control_app == PING || 
        pkt->control_app == PONG   ) {
            pkt->TTL = 0;
        }
        
        pkt->destination_adr = BROADCAST;
        
        // Only embed the routing table into the data field if there are entries
        if (Nlme.num_entries > 0) {
            memset(pkt->data, 0, 50);
            for (int i = 0; i < Nlme.num_entries; i++) {
                pkt->data[i * 3] = Nlme.routing_table[i].destination;
                pkt->data[i * 3 + 1] = Nlme.routing_table[i].next_hop;
                pkt->data[i * 3 + 2] = Nlme.routing_table[i].hop_count;
            }
            uint8_t table_length = Nlme.num_entries * 3;
            pkt->length += table_length; // Add the length of the routing entries to the existing length
            
            // Calculate CRC and append it to the end of the data
            uint8_t crc = calculate_crc8(pkt->data, table_length);
            pkt->data[table_length] = crc;
            pkt->length += 1;  // Update packet length to include CRC
        }
        pkt->length += Nlme.headerSize; // Add the network layer header size to the existing length
    } else {
        pkt->destination_adr = find_next_hop();
        pkt->length += Nlme.headerSize; // Add network layer length
    }

    if (GLOB_ERROR_BUFFER_FULL != buffer_full(Nlme.pktTxBuf)) {
        write_packet(Nlme.pktTxBuf, pkt);
    } else {
        print("Network Outgoing: Buffer full, failed to write packet\n\r");
    }
    return ret;
}


static GLOB_RET network_incoming(Packet *pkt) {
    GLOB_RET ret = GLOB_SUCCESS;

    if (pkt->control_app == BEACON) {
        if (!process_received_beacon(pkt)) {
            return GLOB_ERROR_BEACON_PROCESSING_FAILED;
        }
    } else if ((pkt->destination_adr == BROADCAST) && (pkt->TTL > 0)) {
        ret = handle_broadcast_packet(pkt);
        if (ret != GLOB_SUCCESS) {
            return ret;
        }
    } else {
        ret = handle_regular_packet(pkt);
    }

    return ret;
}

static char find_next_hop(void)
{
    return BROADCAST; 
}

/*
** =============================================================================
**                  PUBLIC FUNCTIONS
** =============================================================================
*/

void network_layer_init(PacketBuffer *pRxBuf, PacketBuffer *pTxBuf) {
    Nlme.pktRxBuf = pRxBuf;
    Nlme.pktTxBuf = pTxBuf;
    Nlme.ttl = 7;
    Nlme.headerSize = NET_HEADER_SIZE;
    Nlme.networkSize = 20;
    Nlme.networkSize = 20;
    Nlme.num_entries = 0;
    
    memset(Nlme.routing_table, 0, sizeof(RoutingEntry) * MAX_ENTRIES);

    
}

GLOB_RET network_interface(Direction iKey) {
    GLOB_RET ret = GLOB_SUCCESS;
    
    if (OUTGOING == iKey) {
        Packet pkt = search_pending_packet(Nlme.pktTxBuf, iKey, NET);
        if(pkt.pktDir != DIR_EMPTY && pkt.pOwner != OWNER_EMPTY) {
            ret = network_outgoing(&pkt);
            if (ret != GLOB_SUCCESS) {
                return GLOB_ERROR_NETWORK_OUTGOING_FAILED;
            }
        }
    } else if (INCOMING == iKey) {
        Packet pkt = search_pending_packet(Nlme.pktRxBuf, iKey, NET);
        if(pkt.pktDir != DIR_EMPTY && pkt.pOwner != OWNER_EMPTY) {
            ret = network_incoming(&pkt);
            if (ret != GLOB_SUCCESS) {
                return GLOB_ERROR_NETWORK_INCOMING_FAILED;
            }
        }
    }
    
    return ret;
}

RoutingEntry* get_routing_table(void) {
    return Nlme.routing_table;
}

uint8_t get_routing_entries(void) {
    return Nlme.num_entries;
}