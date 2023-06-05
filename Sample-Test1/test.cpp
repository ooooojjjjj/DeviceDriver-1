#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TDD_DeviceDriver/DeviceDriver.cpp"

using namespace testing;
using namespace std;

class MockFlashMemoryDevice : public FlashMemoryDevice
{
public:
    MOCK_METHOD(unsigned char, read, (long address), (override));
    MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(ReadTest, ReadFlash5Times) {
    MockFlashMemoryDevice cMockFlash;

    EXPECT_CALL(cMockFlash, read(_))
        .Times(5);

    DeviceDriver cDeviceDriver(&cMockFlash);

    cDeviceDriver.read(0x0);
}

TEST(ReadTest, ReadFailException) {
    MockFlashMemoryDevice cMockFlash;

    EXPECT_CALL(cMockFlash, read(_))
        .WillOnce(Return(0x5))
        .WillOnce(Return(0xFF))
        .WillOnce(Return(0x5))
        .WillOnce(Return(0x3))
        .WillOnce(Return(0x5));

    DeviceDriver cDeviceDriver(&cMockFlash);

    EXPECT_THROW(cDeviceDriver.read(0x0), exception);
}

TEST(ReadTest, ReadDone) {
    MockFlashMemoryDevice cMockFlash;

    EXPECT_CALL(cMockFlash, read(_))
        .WillRepeatedly(Return(0x7));

    DeviceDriver cDeviceDriver(&cMockFlash);

    EXPECT_THAT(0x7, cDeviceDriver.read(0x0));
}

