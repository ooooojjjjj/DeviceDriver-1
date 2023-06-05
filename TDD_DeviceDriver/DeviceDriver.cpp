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
    int nResult[5];

    for (int i = 0; i < 5; i++)
    {
        Sleep(1);
        nResult[i] = (int)(m_hardware->read(address));
    }

    for (int i = 1; i < 5; i++)
    {
        if (nResult[0] != nResult[i]) throw exception("ReadFailException");
    }

    return nResult[0];
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}