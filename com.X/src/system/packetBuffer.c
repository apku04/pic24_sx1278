#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "packetBuffer.h"


GLOB_RET init_packet_buffer(PacketBuffer *pBuf) {
    pBuf->read_pointer = 0;
    pBuf->write_pointer = 0;
    pBuf->data_size = 0;
    return GLOB_SUCCESS;
}

GLOB_RET buffer_full(PacketBuffer *pBuf) {
    if (pBuf->data_size >= PACKET_BUFFER_SIZE) {
        return GLOB_ERROR_BUFFER_FULL;
    }
    return GLOB_SUCCESS;
}

GLOB_RET buffer_empty(PacketBuffer *pBuf) {
    if (pBuf->data_size <= 0) {
        return GLOB_ERROR_BUFFER_EMPTY;
    }
    return GLOB_SUCCESS;
}

GLOB_RET write_packet(PacketBuffer *pBuf, Packet *packet) {
    if (buffer_full(pBuf) == GLOB_ERROR_BUFFER_FULL) {
        return GLOB_ERROR_WRITE_BUFFER_SIZE_EXCEEDED;
    }

    pBuf->buffer[pBuf->write_pointer] = *packet;
    pBuf->write_pointer = (pBuf->write_pointer + 1) % PACKET_BUFFER_SIZE;
    pBuf->data_size++;

    return GLOB_SUCCESS;
}

GLOB_RET read_packet(PacketBuffer *pBuf, Packet *packet) {
    if (buffer_empty(pBuf) == GLOB_ERROR_BUFFER_EMPTY) {
        return GLOB_ERROR_READ_BUFFER_SIZE_EXCEEDED;
    }

    *packet = pBuf->buffer[pBuf->read_pointer];
    pBuf->read_pointer = (pBuf->read_pointer + 1) % PACKET_BUFFER_SIZE;
    pBuf->data_size--;

    return GLOB_SUCCESS;
}

GLOB_RET search_packet_buffer(PacketBuffer *pBuf, uint8_t source_adr, uint32_t sequence_num) {
    for (int i = 0; i < pBuf->data_size; i++) {
        int index = (pBuf->read_pointer + i) % PACKET_BUFFER_SIZE;
        if (pBuf->buffer[index].source_adr == source_adr && pBuf->buffer[index].sequence_num == sequence_num) {
            return GLOB_SUCCESS;
        }
    }
    return GLOB_FAILURE;
}

Packet search_pending_packet(PacketBuffer *pBuf, Direction dir, Owner me) {
    // Iterate through the packet buffer
    for (int i = 0; i < pBuf->data_size; i++) {
        // Calculate the index of the current element
        int index = (pBuf->read_pointer + i) % PACKET_BUFFER_SIZE;

        Packet *current_packet = &pBuf->buffer[index];

        // Check if the packet's direction and owner match
        if (current_packet->pktDir == dir && current_packet->pOwner == me) {
            // Copy the packet before removing it from the buffer
            Packet copyPkt = *current_packet;

            remove_packet_from_buffer(pBuf, current_packet);

            return copyPkt;
        }
    }

    // If no match is found, return an empty packet
    Packet emptyPkt = {0};
    return emptyPkt;
}


bool remove_packet_from_buffer(PacketBuffer *pBuf, Packet *pkt) {
    for (int i = 0; i < pBuf->data_size; i++) {
        // Calculate the index
        int index = (pBuf->read_pointer + i) % PACKET_BUFFER_SIZE;

        // Check if the current packet is the one we're looking for
        if (&pBuf->buffer[index] == pkt) {
            // Shift all remaining packets towards the read pointer
            for (int j = i; j < pBuf->data_size - 1; j++) {
                int current_index = (pBuf->read_pointer + j) % PACKET_BUFFER_SIZE;
                int next_index = (pBuf->read_pointer + j + 1) % PACKET_BUFFER_SIZE;
                pBuf->buffer[current_index] = pBuf->buffer[next_index];
            }

            // Clear the slot that now becomes free
            int clear_index = (pBuf->read_pointer + pBuf->data_size - 1) % PACKET_BUFFER_SIZE;
            memset(&pBuf->buffer[clear_index], 0, sizeof(Packet));

            pBuf->data_size--;
            // Adjust write pointer to the new free slot
            pBuf->write_pointer = (pBuf->write_pointer + PACKET_BUFFER_SIZE - 1) % PACKET_BUFFER_SIZE;

            return true;
        }
    }

    // The packet was not found in the buffer
    return false;
}

