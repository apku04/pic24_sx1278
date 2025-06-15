// networklayer_defs.h

#ifndef NETWORKLAYER_DEFS_H
#define NETWORKLAYER_DEFS_H

#define MAX_RX_HIST_CNT 10
#define MAX_ENTRIES 10
#define MAX_HOPS 3
#define MAX_DEST_ADDR 10

typedef struct {
    uint16_t seq;
    uint8_t adr;
} rxHistory;

typedef struct {
    uint8_t destination;
    uint8_t next_hop;
    uint8_t hop_count;
} RoutingEntry;

typedef struct {
    PacketBuffer *pktRxBuf;
    PacketBuffer *pktTxBuf;
    char ttl;
    uint8_t mesh_dest;
    char headerSize;
    char networkSize;
    rxHistory rxHist[MAX_RX_HIST_CNT];
    uint8_t rxHistCnt;
    RoutingEntry routing_table[MAX_ENTRIES];
    uint8_t num_entries;  // Number of actual entries in the routing table
} nlme;

#endif // NETWORKLAYER_DEFS_H
