#include "flashHandler.h"


static __eds__ uint8_t flashMemory[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(psv),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));

void writeFlash(deviceData_t* data) {
    uint32_t flash_storage_address = __builtin_tbladdress(flashMemory);
    FLASH_Unlock(FLASH_UNLOCK_KEY);
    FLASH_ErasePage(flash_storage_address);
    
    uint8_t* ptr = (uint8_t*)data;
    for (int i = 0; i < sizeof(deviceData_t); i++) {
        uint32_t write_data = ptr[i] | 0xFFFFFF00;
        FLASH_WriteWord24(flash_storage_address + i*2, write_data);
    }

    FLASH_Lock();
}

void readFlash(addrEnum addr, uint8_t* read_data) {
    uint32_t flash_storage_address = __builtin_tbladdress(flashMemory);
    uint32_t read_word = FLASH_ReadWord24(flash_storage_address + addr*2);
    *read_data = (uint8_t)(read_word & 0xFF);  // Only keep the lower 8 bits
}
