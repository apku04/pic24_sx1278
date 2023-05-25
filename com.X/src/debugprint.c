/*  ============================================================================
    Copyright (C) 2015 Achuthan Paramanathan.
    ============================================================================
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    ============================================================================
    Revision Information:
        File name: debugPrint.c
        Version:   v0.0
        Date:      23-07-2015
    ============================================================================
 */

/*
 ** ============================================================================
 **                        INCLUDE STATEMENTS
 ** ============================================================================
 */

#include "hal.h"
#include "globalInclude.h"
#include "../src/driver/timerdriver.h"

int global_log_level = 1;

/*==============================================================================
 ** Function...: op_hexdump
 ** Return.....: void
 ** Description: 
 ** Created....: 29.12.2015 by Achuthan
 ** Modified...: dd.mm.yyyy by nn
==============================================================================*/
void op_hexdump(int level, const char *title, const void *buf, size_t len, char newline)
{
    // Check if the log level is less than or equal to the global_log_level
    if (level > global_log_level) {
        return;
    }

    char s[40];
    int i = 0, j = 0;
    char d[64] = { 0 };
    char output_buffer[1024] = { 0 }; // Increase the size if needed
    int buffer_pos = 0;
    
    memcpy(d, buf, len);
    
    strncpy(s, title, sizeof(s) - 1);
    s[sizeof(s) - 1] = '\0';

    buffer_pos += snprintf(output_buffer + buffer_pos, sizeof(output_buffer) - buffer_pos, "%s\n", s);

    for (i = 0; i < len; i++)
    {
        buffer_pos += snprintf(output_buffer + buffer_pos, sizeof(output_buffer) - buffer_pos, " %02x", d[i]);
        j++;
        if (newline && ( j == 16) ) // Change the number of bytes per line to 16
        {
            j = 0;
            buffer_pos += snprintf(output_buffer + buffer_pos, sizeof(output_buffer) - buffer_pos, "\n");
        }
    }

    buffer_pos += snprintf(output_buffer + buffer_pos, sizeof(output_buffer) - buffer_pos, "\n\n");

    bool ret = false;
    // Print the whole buffer at once
    ret = print(output_buffer);
    delay_ms(200);
}

