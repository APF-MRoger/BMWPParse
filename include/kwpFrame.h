#pragma once
#include <ESP32-TWAI-CAN.hpp>

template <typename T>
T swap_endian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}

enum KWP_FRAME_TYPE : byte
{
    singleFrame         =   0x00,
    firstFrame          =   0x10,
    continuationFrame   =   0x20,
    flowControlFrame    =   0x30,
    invalidFrameType    =   0xFF
};

class kwpFrame
{
public:
    byte target;
    byte sender;
    byte SID;
    uint16_t length;
    uint16_t payloadLength;
    byte cursor;
    byte payload[255];
    KWP_FRAME_TYPE frameType;

    bool RXComplete = true;
    bool TXComplete = true;

    void parseMetaData(CanFrame* rxFrame);
    KWP_FRAME_TYPE processCanFrame(CanFrame* rxFrame);
    void sendKwpFrame();
    void printKwpFrame();
};