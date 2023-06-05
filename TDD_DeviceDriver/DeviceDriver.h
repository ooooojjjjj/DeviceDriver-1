#pragma once
#include "FlashMemoryDevice.h"

#define TOTAL_READ_TRY_COUNT    (5)
#define READ_DELAY_MILLISEC     (1)

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);

    int read(long address);
    void readFlash(long address, int(&nResult)[5]);
    void checkReadData(int nResult[5]);

    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
    const int nNoData = 0xFF;
};