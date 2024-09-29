#pragma once

#include <stdint.h>
#include "namespace.h"

LED_STRIP_NAMESPACE_BEGIN

class IRmtLedStrip {
public:
    virtual ~IRmtLedStrip() = default;
    virtual void set_pixel(uint32_t i, uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual void set_pixel_rgbw(uint32_t i, uint8_t r, uint8_t g, uint8_t b, uint8_t w) = 0;
    
    // Non-blocking draw if and only if the number of strips is less than the number of channels.
    virtual void draw() = 0;

    virtual void wait_for_draw_complete() = 0;

    virtual uint32_t num_pixels() const = 0;
};


IRmtLedStrip* create_rmt_led_strip(
        uint16_t T0H, uint16_t T0L, uint16_t T1H, uint16_t T1L, uint32_t TRESET, // Timing is in nanoseconds
        int pin, uint32_t max_leds, bool is_rgbw);

LED_STRIP_NAMESPACE_END
