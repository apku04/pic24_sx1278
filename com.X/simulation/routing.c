#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ENTRIES 10  // This is the maximum we calculated earlier. Adjust as needed.
#define SIGNAL_STRENGTH_THRESHOLD 100  // Define a suitable threshold for your system.

typedef struct {
    uint8_t destination;
    uint8_t next_hop;
    uint8_t hop_count;
    uint8_t sequence_number;  // Added as per your steps
} RoutingEntry;

typedef struct {
    uint8_t source_address;
    uint8_t sequence_number;
    uint8_t signal_strength;  // Added for signal strength
    RoutingEntry routing_info[MAX_ENTRIES];
} BeaconPacket;

typedef struct {
    uint8_t address;
    RoutingEntry routing_table[MAX_ENTRIES];
    uint8_t num_entries;  // Number of actual entries in the routing table
} Node;

BeaconPacket generate_random_beacon() {
    BeaconPacket beacon;
    beacon.source_address = rand() % MAX_ENTRIES;
    beacon.sequence_number = rand() % MAX_ENTRIES;
    beacon.signal_strength = rand() % 200;  // Random value between 0 and 200
    for (int i = 0; i < MAX_ENTRIES; i++) {
        beacon.routing_info[i].destination = rand() % MAX_ENTRIES;
        beacon.routing_info[i].next_hop = rand() % MAX_ENTRIES;
        beacon.routing_info[i].hop_count = rand() % 10;  // Random hop count between 0 and 9
        beacon.routing_info[i].sequence_number = rand() % MAX_ENTRIES;
    }
    return beacon;
}

bool receive_beacon(Node* node_X, BeaconPacket* beacon_from_Y) {
    // 1. Extract the source address, sequence number, routing information, and signal strength
    uint8_t source_address = beacon_from_Y->source_address;
    uint8_t sequence_number = beacon_from_Y->sequence_number;
    uint8_t signal_strength = beacon_from_Y->signal_strength;

    // 2. Inspect the beacon
    if (signal_strength < SIGNAL_STRENGTH_THRESHOLD) {
        return false;  // Unusable beacon
    }

    // 3. Update or Add Y's beacon to X's routing table
    int found_index = -1;
    for (int i = 0; i < node_X->num_entries; i++) {
        if (node_X->routing_table[i].destination == source_address) {
            found_index = i;
            break;
        }
    }
    if (found_index != -1) {
        node_X->routing_table[found_index].sequence_number = sequence_number;
        // Update any other metadata if needed
    }
    else if (node_X->num_entries < MAX_ENTRIES) {
        node_X->routing_table[node_X->num_entries] = (RoutingEntry){ source_address, source_address, 1, sequence_number };
        node_X->num_entries++;
    }

    // 4. For each routing entry in beacon_from_Y
    for (int i = 0; i < MAX_ENTRIES; i++) {
        RoutingEntry entry = beacon_from_Y->routing_info[i];
        if (entry.destination == node_X->address) continue;  // Skip if destination is node_X

        int found_entry_index = -1;
        for (int j = 0; j < node_X->num_entries; j++) {
            if (node_X->routing_table[j].destination == entry.destination) {
                found_entry_index = j;
                break;
            }
        }
        if (found_entry_index != -1) {
            if (entry.hop_count + 1 < node_X->routing_table[found_entry_index].hop_count) {
                node_X->routing_table[found_entry_index].hop_count = entry.hop_count + 1;
                node_X->routing_table[found_entry_index].next_hop = source_address;
            }
        }
        else if (node_X->num_entries < MAX_ENTRIES) {
            node_X->routing_table[node_X->num_entries] = (RoutingEntry){ entry.destination, source_address, entry.hop_count + 1, sequence_number };
            node_X->num_entries++;
        }
    }

    return true;  // Successful beacon processing
}


int main() {
    Node node;
    node.address = 1;  // Example address
    node.num_entries = 0;

    // Manually construct a beacon packet
    BeaconPacket beacon;
    beacon.source_address = 2;  // Let's say this beacon is from node 2
    beacon.sequence_number = 1;  // First sequence number
    beacon.signal_strength = 150;  // Good signal strength

    // Manually fill in the routing info for this beacon
    beacon.routing_info[0].destination = 3;
    beacon.routing_info[0].next_hop = 3;
    beacon.routing_info[0].hop_count = 1;
    beacon.routing_info[0].sequence_number = 1;

    beacon.routing_info[1].destination = 4;
    beacon.routing_info[1].next_hop = 4;
    beacon.routing_info[1].hop_count = 1;
    beacon.routing_info[1].sequence_number = 1;

    // ... You can add more routing entries if needed

    // Process the manually constructed beacon
    receive_beacon(&node, &beacon);

    // Print the routing table after processing the beacon
    printf("Node %d Routing Table:\n", node.address);
    for (int i = 0; i < node.num_entries; i++) {
        printf("Destination: %d, Next Hop: %d, Hop Count: %d, Sequence: %d\n",
            node.routing_table[i].destination,
            node.routing_table[i].next_hop,
            node.routing_table[i].hop_count,
            node.routing_table[i].sequence_number);
    }

    return 0;
}



/*
    for (int i = 0; i < 10; i++) {
        BeaconPacket beacon = generate_random_beacon();
        receive_beacon(&node, &beacon);
    }
*/