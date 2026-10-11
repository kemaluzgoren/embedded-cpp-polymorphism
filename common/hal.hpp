// HAL interfaces: application code depends only on these.
// Each class gets a vtable; the hidden vptr in every object dispatches
// to the host or target implementation at runtime.
#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>

struct IGpio {
    virtual ~IGpio() = default;
    virtual void write(bool level) = 0;        // pure virtual: must be implemented
    virtual bool read() = 0;
    virtual void toggle() { write(!read()); }  // default, may be overridden
};

struct IUart {
    virtual ~IUart() = default;
    virtual void write(const char* data, std::size_t len) = 0;
    void print(const char* s) { write(s, std::strlen(s)); }  // non-virtual helper
};

struct IClock {
    virtual ~IClock() = default;
    virtual std::uint32_t millis() = 0;
    virtual void delayMs(std::uint32_t ms) = 0;
};

