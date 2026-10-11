#pragma once
#include "common/hal.hpp"

struct IKeypad {
    virtual ~IKeypad() = default;
    // Returns '0'-'9' or '#' while a key is pressed, 0 when no key is pressed.
    virtual char readKey() = 0;
};

struct ILock {
    virtual ~ILock() = default; 
    virtual void lock() = 0; 
    virtual void unlock() = 0; 
    virtual bool isLocked() const = 0; 
};

// All hardware the door controller needs
struct DoorBoard {
    IKeypad& keypad; 
    ILock& lock; 
    IUart& uart; 
    IClock& clock;
};

// Defined once per platform; selected at link time. 
DoorBoard& getDoorBoard(); 

