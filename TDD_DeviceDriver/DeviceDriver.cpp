#include "DeviceDriver.h"
#include <windows.h>
#include <cstdio>
#include <stdexcept>
#include <system_error>

using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int nResult[TOTAL_READ_TRY_COUNT] = { nNoData, nNoData, nNoData, nNoData, nNoData };

    readFlash(address, nResult);
    checkReadData(nResult);

    return nResult[0];
}

void DeviceDriver::readFlash(long address, int(&nResult)[5])
{
    for (int nReadTryCount = 0; nReadTryCount < TOTAL_READ_TRY_COUNT; nReadTryCount++)
    {
        Sleep(READ_DELAY_MILLISEC);
        nResult[nReadTryCount] = (int)(m_hardware->read(address));
    }
}

void DeviceDriver::checkReadData(int nResult[5])
{
    for (int i = 1; i < TOTAL_READ_TRY_COUNT; i++)
    {
        if (nResult[0] != nResult[i]) throw exception("ReadFailException");
    }
}

void DeviceDriver::write(long address, int data)
{
    int nReadValue = (int)(m_hardware->read(address));

    if (nNoData != nReadValue) throw exception("WriteFailException");

    m_hardware->write(address, (unsigned char)data);
}

