// Host simulation of the door lock: prints state changes instead of driving a relay.
#pragma once
#include "../door_hal.hpp"

class HostLock final : public ILock {
public: 
    explicit HostLock(IUart& uart); 
    void lock() override; 
    void unlock() override; 
    bool isLocked() const override;
private:
    IUart& uart_; 
    bool locked_ = true;    // door starts locked
};