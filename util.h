//
// Created by nathan on 20.12.2018.
//

#ifndef MCS_4_EMULATOR_UTIL_H
#define MCS_4_EMULATOR_UTIL_H


#include <cstdint>
#include "mcs4_stdint.h"

uint8_t l8b(uint16_t v);

/**
 * Mask lower 5 bits (i.e. for accumulator and carry combined)
 *
 * @param v
 * @return
 */
mcs4::uint5_t l5b(uint8_t v);

/**
 * Mask lower 4 bits
 *
 * @param v
 * @return
 */
mcs4::uint4_t l4b(uint8_t v);

mcs4::uint4_t l4b(uint16_t v);

mcs4::uint4_t m4b(uint16_t v);

/**
 * Mask higher 4 bits
 *
 * @param v
 * @return
 */
mcs4::uint4_t h4b(uint8_t v);

/**
 * Misk higher 4 bits.
 * ⚠ Working on a 12-bit value, not 16-bit!
 *
 * @param v
 * @return
 */
mcs4::uint4_t h4b(mcs4::uint12_t v);

/**
 * Mask lower 1 bit (i.e. for carry register)
 *
 * @param v
 * @return
 */
mcs4::uint1_t l1b(uint8_t v);

/**
 * Mask higher 1 bit (i.e. for carry register)
 *
 * @param v
 * @return
 */
mcs4::uint1_t h1b(uint8_t v);

mcs4::uint1_t mask1bit(uint8_t v, uint8_t pos);

#endif //MCS_4_EMULATOR_UTIL_H
