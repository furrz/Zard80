#pragma once

#include <Arduino.h>

template<int i>
struct NBitInteger
{
    using Unsigned = uint32_t;
};
template<>
struct NBitInteger<8>
{
    using Unsigned = uint8_t;
};

template<>
struct NBitInteger<16>
{
    using Unsigned = uint16_t;
};

template<int n>
struct PinBus
{
    using T = typename NBitInteger<n>::Unsigned;

    const int pins[n];

    void PinMode(int newMode) const
    {
        for (int j = 0; j < n; j++) {
            pinMode(pins[j], newMode);
        }
    }

    void Write(T data) const
    {
        for (int j = 0; j < n; j++) {
            digitalWrite(pins[j], (data & (1 << j)) ? HIGH : LOW);
        }
    }

    T Read() const
    {
        T data = 0;
        for (int j = 0; j < n; j++) {
            data |= (digitalRead(pins[j]) == HIGH ? 1 : 0) << j;
        }
        return data;
    }
};
