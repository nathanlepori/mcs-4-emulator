//
// Created by nathan on 20.12.2018.
//

#include "util.h"

uint8_t l8b(uint16_t v) {
    return static_cast<uint8_t>(v & 0xff);
}

mcs4::uint5_t l5b(uint8_t v) {
    return v & (uint8_t) 0x1f;
}

mcs4::uint4_t l4b(uint8_t v) {
    return v & (uint8_t) 0xf;
}

mcs4::uint4_t l4b(uint16_t v) {
    return static_cast<uint8_t>(v & 0xf);
}

mcs4::uint4_t m4b(uint16_t v) {
    return static_cast<uint8_t>(v & 0xf0 >> 4);
}

mcs4::uint4_t h4b(uint8_t v) {
    return v >> 4;
}

mcs4::uint4_t h4b(mcs4::uint12_t v) {
    return static_cast<uint8_t>(v >> 8);
}

mcs4::uint1_t l1b(uint8_t v) {
    return v & (uint8_t) 0x1;
}

mcs4::uint1_t h1b(uint8_t v) {
    return (v & (uint8_t) 0x10) >> 4;
}

mcs4::uint1_t mask1bit(uint8_t v, uint8_t pos) {
    uint8_t mask = (uint8_t) 0x1 << pos;
    return (v & mask) >> pos;
}
