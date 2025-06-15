/*  ============================================================================
    Copyright (C) 2015 Achuthan Paramanathan.
    All rights reserved.
    ============================================================================
    This document contains proprietary information belonging to Achuthan 
    Paramanathan. Passing on and copying of this document, use and communication 
    of its contents is not permitted without prior written authorisation.
    ============================================================================
    Revision Information:
        File name: terminal.c
        Version:   v0.0
        Date:      23-07-2015
    ============================================================================
 */

/*
 ** ============================================================================
 **                        INCLUDE STATEMENTS
 ** ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h> 

#include "sx1278.h"
#include "terminal.h"
#include "../src/driver/timerdriver.h"
#include "../hal.h"
#include "maclayer.h"
#include "flashHandler.h"


uint8_t printAllReg = 0;
uint8_t tx_test = 0;
uint8_t sniffer = 0;
uint8_t cnt = 0;

/*
 ** ============================================================================
 **                           LOCAL DEFINES
 ** ============================================================================
 */
#define MAX_ARGV 128
#define SEND_CMD_LENGTH 4

/*
 ** ============================================================================
 **                   LOCAL EXPORTED FUNCTION DECLARATIONS
 ** ============================================================================
 */
uint16_t parseArgs(uint8_t *str, uint8_t *argv[]);
void help_command(uint16_t argc, uint8_t *argv[]);
void get_commands(uint16_t argc, uint8_t *argv[]);
void send_commands(uint16_t argc, uint8_t *argv[]);
uint8_t set_commands(uint16_t argc, uint8_t *argv[]);
void test_commands(uint16_t argc, uint8_t *argv[]);
void ping_commands(uint16_t argc, uint8_t *argv[]);
void menu(uint16_t argc, uint8_t *argv[]);

void set_frequency(uint32_t freq);
uint32_t get_frequency(void);
void set_data_rate(uint8_t data_rate);
uint8_t get_data_rate(void);
void set_tx_power(uint8_t power);
uint8_t get_tx_power(void);
void set_macAddr(uint8_t mac_addr);
void softwareReset(void);



/*
 ** ============================================================================
 **                       LOCAL VARIABLES 
 ** ============================================================================
 */

deviceData_t flash_data;

ulme Ulme;

/*==============================================================================
 ** Function...: terminal
 ** Return.....: void 
 ** Description: Parse userinputs 
 ** Created....: 21.05.2015 by Achuthan
 ** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void terminal( uint8_t *msg, uint8_t size ) {
    uint8_t cmdStr[MAX_ARGV];
    uint8_t *argv[MAX_ARGV];
    uint16_t argc;
    cnt = size;
    memcpy(cmdStr, msg, size);
    argc = parseArgs (&cmdStr[0], argv);
    menu(argc, argv);
}

void user_layer_init(PacketBuffer *pTxBuf){
    Ulme.pktTxBuf = pTxBuf;
}


/*==============================================================================
 ** Function...: parseArgs
 ** Return.....: void 
 ** Description: Parse userinputs 
 ** Created....: 21.05.2015 by Achuthan
 ** Modified...: dd.mm.yyyy by nn
==============================================================================*/
uint16_t parseArgs(uint8_t *str, uint8_t *argv[]) {
    uint16_t argc = 0;
    uint8_t *ch = str;

    if (*ch == '\r' || *ch == '\n' || *ch == '\0') {
        return 0; // No arguments to process
    }

    while (*ch == ' ') ch++; // Skip leading spaces

    // Process the first argument/command
    argv[argc++] = ch;
    while (*ch != ' ' && *ch != '\0' && *ch != '\r' && *ch != '\n') ch++;

    if (*ch == ' ' || *ch == '\r' || *ch == '\n') {
        *ch++ = '\0'; // Properly terminate the command string
        while (*ch == ' ') ch++; // Skip spaces after command
    }

    // If there are additional arguments, parse them normally
    while (*ch != '\0' && *ch != '\r' && *ch != '\n') {
        argv[argc++] = ch;
        while (*ch != ' ' && *ch != '\0' && *ch != '\r' && *ch != '\n') ch++;

        if (*ch == ' ' || *ch == '\r' || *ch == '\n') {
            *ch++ = '\0';
            while (*ch == ' ' && *ch != '\0') ch++;
        }
    }

    return argc; // Return the number of arguments
}




/*==============================================================================
** Function...: menu
** Return.....: void
** Description: Terminal menu
** Created....: 25.03.2017 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void menu(uint16_t argc, uint8_t *argv[])
{
    uint8_t s[200];
    const char* cmd;
  
    if (argc) 
    {
        cmd = (const char*)argv[0];
        if (strcmp(cmd, "help") == 0) 
        {
            help_command(argc, argv);
        }
        else if(strcmp(cmd, "get") == 0)
        {
            get_commands(argc, argv);
        }
        else if(strcmp(cmd, "set") == 0)
        {
            set_commands(argc, argv);
        }
        else if(strcmp(cmd, "send") == 0)
        {
            send_commands(argc, argv);
        }
        else if(strcmp(cmd, "reset") == 0)
        {
            softwareReset();;
        }
        else if(strcmp(cmd, "test") == 0)
        {
            if(argc>1)
            {
                test_commands(argc, argv);
            }
            else
            {
                print("Invalid test command <test on/off>\n");
            }
        }
        else if(strcmp(cmd, "version") == 0)
        {
            print("LF_LORA_V1\n");
        }
        else if(strcmp(cmd, "ping") == 0)
        {
            ping_commands(argc, argv);
        }
        else 
        {
          sprintf( (char*)s, "Error: unknown cmd: %s\n", argv[0]);
          print(s);
          print("Type <help> for available commands\n");
        }
    }
}

/*==============================================================================
** Function...: help_command
** Return.....: void
** Description: print out the help commands
** Created....: 25.03.2017 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void help_command(uint16_t argc, uint8_t *argv[])
{
    char output_buffer[255];
    
    snprintf(output_buffer, sizeof(output_buffer), 
             "Commands:\n"
             "  help - This message\n"
             "  get <param>\n"
             "  set <param> <value>\n"
             "  send <message>\n"
             "  test <on/off>\n"
             "  version\n"
             "Params: frequency (hz), data_rate, tx_power, mac_address, flash\n"
            "Done");
    print(output_buffer);
}



/*==============================================================================
** Function...: set_commands
** Return.....: void
** Description: set commands
** Created....: 25.03.2017 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
uint8_t set_commands(uint16_t argc, uint8_t *argv[]) {
    uint8_t s[200];
    errno = 0;  // reset errno
    
    if (argc >= 3) {
        if (strcmp((const char *)argv[1], "frequency") == 0) {
            uint32_t freq = strtol((const char *)argv[2], NULL, 10);
            if (errno != 0) {
                sprintf((char*)s, "Error: Invalid frequency '%s'. Frequency must be in hz either 444000000, 868000000 or 870000000.\n", argv[2]);
                print(s);
                return 1;
            }
            if (freq == 444000000 || freq == 868000000 || freq == 870000000) {
                set_frequency(freq);
                flash_data.radioFreq1 = (freq >> 24) & 0xFF;
                flash_data.radioFreq2 = (freq >> 16) & 0xFF;
                flash_data.radioFreq3 = (freq >> 8) & 0xFF;
                flash_data.radioFreq4 = freq & 0xFF;
            }else {
                sprintf( (char*)s, "Error: Invalid frequency %f. Frequency must"
                        " be either 444 MHz or 868 MHz.\n",(double)freq);
                print(s);
                return 1;
            }
        } else if (strcmp((const char *)argv[1], "data_rate") == 0) {
            uint8_t data_rate = strtol((const char *)argv[2], NULL, 10);
            if (errno != 0) {
                sprintf((char*)s, "Error: Invalid data rate '%s'. Data rate must be a number between 1 and 12.\n", argv[2]);
                print(s);
                return 1;
            }
            if (data_rate > 0 && data_rate < 13) {
                set_data_rate(data_rate);
                flash_data.radioDataRate = data_rate;
            }else {
                sprintf( (char*)s, "Error: Invalid data rate %d. Data rate must"
                        " be between 1 and 12.\n",data_rate);
                print(s);
                return 1;
            }
        } else if (strcmp((const char *)argv[1], "tx_power") == 0) {
            uint8_t power = strtol((const char *)argv[2], NULL, 10);
            if (errno != 0) {
                sprintf((char*)s, "Error: Invalid tx Power '%s'. Tx Power must be a number between 1 and 14.\n", argv[2]);
                print(s);
                return 1;
            }
            if (power > 0 && power < 15) {
                set_tx_power(power);
                flash_data.radioTxPwr = power;
            }else {
                sprintf( (char*)s, "Error: Invalid Tx Power %d. Tx Power must"
                        " be between 0 and 10 dbm.\n",power);
                print(s);
                return 1;
            }
            
        } else if (strcmp((const char *)argv[1], "mac_address") == 0) {
            uint8_t mac_addr = strtol((const char *)argv[2], NULL, 10);
            set_macAddr(mac_addr);
            flash_data.deviceID = mac_addr;
        }else if (strcmp((const char *)argv[1], "flash") == 0) {
            writeFlash(&flash_data);
            print("Done\n");
        }
        else if (strcmp((const char *)argv[1], "beacon") == 0) {
            uint8_t send_beacon = strtol((const char *)argv[2], NULL, 10);
             if (send_beacon == 0 || send_beacon == 1) {
                 send_beacon_flag(send_beacon);
             }
            print("Done\n");
        }
        else {
            print("Unknown parameter\n");
        }
    } else {
        print("Insufficient arguments\n");
    }
    return 0;
}



/*==============================================================================
** Function...: get_commands
** Return.....: void
** Description: get commands
** Created....: 25.03.2017 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void get_commands(uint16_t argc, uint8_t *argv[]) {
    char output_buffer[128];

    if (argc > 1) {
        if (strcmp((const char *)argv[1], "frequency") == 0) {
            uint32_t frequency = sx1278_get_channel();
            float frequency_mhz = frequency / 1000000.0;
            snprintf(output_buffer, sizeof(output_buffer), "Frequency: %.2f MHz\n", (double)frequency_mhz);
            print(output_buffer);
        } else if (strcmp((const char *)argv[1], "data_rate") == 0) {
            uint8_t data_rate = sx1278_get_datarate();
            snprintf(output_buffer, sizeof(output_buffer), "Data Rate: %u\n", data_rate);
            print(output_buffer);
        } else if (strcmp((const char *)argv[1], "tx_power") == 0) {
            int8_t tx_power = sx1278_get_tx_power();
            snprintf(output_buffer, sizeof(output_buffer), "TX Power: %d\n", tx_power);
            print(output_buffer);
        } else if (strcmp((const char *)argv[1], "mac_address") == 0) {
            uint8_t device_id = get_mac_address();
            snprintf(output_buffer, sizeof(output_buffer), "MAC Address: %d\n", device_id);
            print(output_buffer);
        }else if (strcmp((const char *)argv[1], "flash_temp") == 0) {
            uint32_t frequency = ((uint32_t)flash_data.radioFreq1 << 24) 
                                | ((uint32_t)flash_data.radioFreq2 << 16) 
                                | ((uint32_t)flash_data.radioFreq3 << 8) 
                                | (uint32_t)flash_data.radioFreq4;
            
            float frequency_mhz = frequency / 1000000.0;
            snprintf(output_buffer, sizeof(output_buffer), "\nFlash Data\n"
                    "Frequency: %.2f MHz\n"
                    "Data Rate: %d\n"
                    "TX Power: %d\n"
                    "MAC Address: %d\n", (double)frequency_mhz, 
                    flash_data.radioDataRate,
                    flash_data.radioTxPwr,
                    flash_data.deviceID
                    );
            print(output_buffer);
        }else if (strcmp((const char *)argv[1], "flash") == 0) {
            
            deviceData_t fData;
            uint8_t *fData_ptr = (uint8_t*)&fData;
            const uint8_t flash_ids[] = { DEVICE_ID, RADIO_FREQ1, RADIO_FREQ2, RADIO_FREQ3, RADIO_FREQ4, RADIO_DR, RADIO_TX_PWR };
            const size_t flash_ids_count = sizeof(flash_ids)/sizeof(flash_ids[0]);

            for(size_t i = 0; i < flash_ids_count; i++) {
                readFlash(flash_ids[i], fData_ptr + i);
            }

            uint32_t frequency = ((uint32_t)fData.radioFreq1 << 24) 
                                | ((uint32_t)fData.radioFreq2 << 16) 
                                | ((uint32_t)fData.radioFreq3 << 8) 
                                | (uint32_t)fData.radioFreq4;
            
            float frequency_mhz = frequency / 1000000.0;
            snprintf(output_buffer, sizeof(output_buffer), "\nFlash Data\n"
                    "Frequency: %.2f MHz\n"
                    "Data Rate: %d\n"
                    "TX Power: %d\n"
                    "MAC Address: %d\n", (double)frequency_mhz, 
                    fData.radioDataRate,
                    fData.radioTxPwr,
                    fData.deviceID
                    );
            print(output_buffer);
        }else if (strcmp((const char *)argv[1], "routing") == 0) {
            print_routing_table();
        }
        else {
            printAllReg = 1;
        }
    } else {
        printAllReg = 1;
    }
}

/*==============================================================================
** Function...: send_commands
** Return.....: void
** Description: send commands
** Created....: 01.03.2020 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void send_commands(uint16_t argc, uint8_t *argv[]) {   
    // Calculate the message length by excluding the length of "send" command and the following space
    // Assuming the message is terminated with a newline character.
    cnt = cnt - (SEND_CMD_LENGTH + 2); // SEND_CMD_LENGTH for "send", 1 for space, and 1 for the newline character.

    Packet pkt;

    // Initialize the packet data with null characters.
    // The size of pkt.data should be defined somewhere as 50 or more.
    memset(pkt.data, 0, sizeof(pkt.data));
    
    pkt.pOwner = APP;
    pkt.pktDir = OUTGOING;

    // If the message is longer than 49 bytes, truncate it to make room for the null terminator.
    // The "- 1" ensures there is space for the null terminator.
    if (cnt > sizeof(pkt.data) - 1) {
        cnt = sizeof(pkt.data) - 1;
    }

    // Store the length of the data (not including the null terminator).
    pkt.length = cnt;

    // Copy the actual message into pkt.data, starting after "send " and before the newline character.
    // Adjust the indices according to how your input is structured.
    memcpy(pkt.data, argv[0] + SEND_CMD_LENGTH + 1, cnt);

    // No need to null-terminate the message if we have initialized pkt.data with zeros
    // and we're not exceeding the buffer.

    // Send the packet if the buffer is not full.
    if (buffer_full(Ulme.pktTxBuf) != GLOB_ERROR_BUFFER_FULL) {
        write_packet(Ulme.pktTxBuf, &pkt);
    } else {
        print("Buffer full\n");
    }
}


/*==============================================================================
** Function...: test_commands
** Return.....: void
** Description: test commands
** Created....: 07.03.2020 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void test_commands(uint16_t argc, uint8_t *argv[])
{
    if (0 == strcmp ((const char*)argv[1], "on"))
    {
        tx_test = 1;
    }
    else if (0 == strcmp ((const char*)argv[1], "off"))
    {
        tx_test = 0;
    }
    else if (0 == strcmp ((const char*)argv[1], "snif"))
    {
        sniffer = 0;
    }
    else
    {
        print("Invalid test command arg must be on or off\n");
    }
}


/*==============================================================================
** Function...: ping_commands
** Return.....: void
** Description: ping commands
** Created....: 16.04.2024 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void ping_commands(uint16_t argc, uint8_t *argv[])
{
    Packet pkt;

    // Initialize the packet data with null characters.
    // The size of pkt.data should be defined somewhere as 50 or more.
    memset(pkt.data, 0, sizeof(pkt.data));
    
    pkt.pOwner = NET;
    pkt.pktDir = OUTGOING;
    pkt.control_app = PING;

    pkt.length = 4 + 0; // Add APP header + data

    // Send the packet if the buffer is not full.
    if (buffer_full(Ulme.pktTxBuf) != GLOB_ERROR_BUFFER_FULL) {
        write_packet(Ulme.pktTxBuf, &pkt);
    } else {
        print("Buffer full\n");
    }
}


void set_macAddr(uint8_t mac_addr) {
    GLOB_RET ret = set_mac_address(mac_addr);
    if (ret)
    {
         print("Error\n");
    }
    else
    {
        print("Done\n");
    }
}

void set_frequency(uint32_t freq) {
    uint8_t ret = sx1278_set_channel(freq);
    if (ret)
    {
         print("Error\n");
    }
    else
    {
        print("Done\n");
    }
}

uint32_t get_frequency(void) {
    return sx1278_get_channel();
}

void set_data_rate(uint8_t data_rate) {
    sx1278_set_datarate(data_rate);
    print("Done\n");
}

uint8_t get_data_rate(void) {
    return sx1278_get_datarate();
}

void set_tx_power(uint8_t power) {
    sx1278_set_tx_power(power);
    print("Done\n");
}

uint8_t get_tx_power(void) {
    return sx1278_get_tx_power();
}

void softwareReset(void) {
    asm("RESET");
}
