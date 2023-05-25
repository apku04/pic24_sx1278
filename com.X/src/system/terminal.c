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

#include "sx1278.h"
#include "terminal.h"
#include "ringBuffer.h"
#include "../src/driver/timerdriver.h"
#include "../hal.h"
#include "maclayer.h"



uint8_t printAllReg = 0;
uint8_t tx_test = 0;
uint8_t cnt = 0;

/*
 ** ============================================================================
 **                           LOCAL DEFINES
 ** ============================================================================
 */
#define MAX_ARGV 128


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

void set_frequency(uint32_t freq);
uint32_t get_frequency(void);
void set_data_rate(uint8_t data_rate);
uint8_t get_data_rate(void);
void set_tx_power(uint8_t power);
uint8_t get_tx_power(void);



/*
 ** ============================================================================
 **                       LOCAL VARIABLES 
 ** ============================================================================
 */
uint16_t argc;
uint8_t *argv[MAX_ARGV];

/*==============================================================================
 ** Function...: terminal
 ** Return.....: void 
 ** Description: Parse userinputs 
 ** Created....: 21.05.2015 by Achuthan
 ** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void terminal( uint8_t *msg, uint8_t size ) {
    uint8_t cmdStr[MAX_ARGV];
    cnt = size;
    memcpy(cmdStr, msg, size);
    argc = parseArgs (&cmdStr[0], argv);
    menu(argc, argv);
}


/*==============================================================================
 ** Function...: parseArgs
 ** Return.....: void 
 ** Description: Parse userinputs 
 ** Created....: 21.05.2015 by Achuthan
 ** Modified...: dd.mm.yyyy by nn
==============================================================================*/
uint16_t parseArgs(uint8_t *str, uint8_t *argv[]) {
  uint16_t i = 0;
  uint8_t *ch = str;
  
  if (*ch == '\r') {
    return 0;
  }

  while (*ch != '\0') {
    i++;

    /*Check if length  exceeds*/
    if (i > MAX_ARGV) {
      print("Too many arguments\n");
      return 0;
    }
    argv[i - 1] = ch;
    while (*ch != ' ' && *ch != '\0' && *ch != '\r' && *ch != '\n')
    {
      if (*ch == '"') // Allow space characters inside double quotes
      {
        ch++;
        argv[i - 1] = ch; // Drop the first double quote char
        while (*ch != '"') {
          if (*ch == '\0' || *ch == '\r') {
            print("Syntax error\n");
            return 0;
          }
          ch++; // Record until next double quote char
        }
        break;
      } else {
        ch++;
      }
    }
    if (*ch == '\r') {
      break;
    }
    if (*ch != '\0') {
      *ch = '\0';
      ch++;
      while (*ch == ' ') {
        ch++;
      }
    }
  }

  return i;
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
  
    if (argc) 
    {
        if (strcmp((const char*)argv[0], "help") == 0) 
        {
            help_command(argc, argv);
        }
        else if(strcmp((const char*)argv[0], "get") == 0)
        {
            get_commands(argc, argv);
        }
        else if(strcmp((const char*)argv[0], "set") == 0)
        {
            set_commands(argc, argv);
        }
        else if(strcmp((const char*)argv[0], "send") == 0)
        {
            send_commands(argc, argv);
        }
        else if(strcmp((const char*)argv[0], "test") == 0)
        {
            if(argc>1)
            {
                test_commands(argc, argv);
            }
            else
            {
                print("Invalid test command <test on/off>\n\r");
            }
        }
        else if(strcmp((const char*)argv[0], "version") == 0)
        {
            print("LF_LORA_V1\n\r");
        }
        else 
        {
          sprintf( (char*)s, "Error: unknown cmd: %s\n\r", argv[0]);
          print(s);
          print("Type <help> for available commands\n\r");
        }
    }
}



/*==============================================================================
** Function...: help_command
** Return.....: void
** Description: print out the help coomands
** Created....: 25.03.2017 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void help_command(uint16_t argc, uint8_t *argv[])
{
    print("Available commands 1:\n\r");
    print("Available commands 2:\n\r");
}


/*==============================================================================
** Function...: set_commands
** Return.....: void
** Description: set commands
** Created....: 25.03.2017 by Achuthan
** Modified...: dd.mm.yyyy by nn
==============================================================================*/
uint8_t set_commands(uint16_t argc, uint8_t *argv[]) {
    if (argc >= 3) {
        if (strcmp((const char *)argv[1], "frequency") == 0) {
            uint32_t freq = strtol((const char *)argv[2], NULL, 10);
            set_frequency(freq);
        } else if (strcmp((const char *)argv[1], "data_rate") == 0) {
            uint8_t data_rate = strtol((const char *)argv[2], NULL, 10);
            set_data_rate(data_rate);
        } else if (strcmp((const char *)argv[1], "tx_power") == 0) {
            uint8_t power = strtol((const char *)argv[2], NULL, 10);
            set_tx_power(power);
        } else if (strcmp((const char *)argv[1], "mac_adress") == 0) {
            uint8_t mac_addr = strtol((const char *)argv[2], NULL, 10);
            set_mac_address(mac_addr);
            print("Done\n\r");
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
            snprintf(output_buffer, sizeof(output_buffer), "Frequency: %.2f MHz\n\r", (double)frequency_mhz);
            print(output_buffer);
        } else if (strcmp((const char *)argv[1], "data_rate") == 0) {
            uint8_t data_rate = sx1278_get_datarate();
            snprintf(output_buffer, sizeof(output_buffer), "Data Rate: %u\n\r", data_rate);
            print(output_buffer);
        } else if (strcmp((const char *)argv[1], "tx_power") == 0) {
            int8_t tx_power = sx1278_get_tx_power();
            snprintf(output_buffer, sizeof(output_buffer), "TX Power: %d\n\r", tx_power);
            print(output_buffer);
        } else if (strcmp((const char *)argv[1], "mac_adress") == 0) {
            int8_t mac_adress = get_mac_address();
            snprintf(output_buffer, sizeof(output_buffer), "MAC Adress: %d\n\r", mac_adress);
            print(output_buffer);
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
void send_commands(uint16_t argc, uint8_t *argv[])
{   
    cnt = cnt - 4; // subtract bytes from "send" = 4
    memcpy(argv[0]+4 , &cnt, 1);

    if (GLOB_ERROR_BUFFER_FULL != buffer_full(&txBuf))
    {
        write_buffer((argv[0]+4), &txBuf);
    }
    else
    {
        print("Buffer full\n\r");
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
    else
    {
        print("Invalid test command arg must be on or off\n\r");
    }
}

void set_frequency(uint32_t freq) {
    uint8_t ret = sx1278_set_channel(freq);
    if (ret)
    {
         print("Error\n\r");
    }
    else
    {
        print("Done\n\r");
    }
}

uint32_t get_frequency(void) {
    return sx1278_get_channel();
}

void set_data_rate(uint8_t data_rate) {
    sx1278_set_datarate(data_rate);
    print("Done\n\r");
}

uint8_t get_data_rate(void) {
    return sx1278_get_datarate();
}

void set_tx_power(uint8_t power) {
    sx1278_set_tx_power(power);
    print("Done\n\r");
}

uint8_t get_tx_power(void) {
    return sx1278_get_tx_power();
}
