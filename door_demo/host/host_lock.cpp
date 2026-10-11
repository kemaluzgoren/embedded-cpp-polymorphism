#include "host_lock.hpp"

HostLock::HostLock(IUart& uart) : uart_(uart) {}

void HostLock::lock() {
    if(locked_) return; // already locked, nothing to report
    locked_ = true; 
    uart_.print("lock: LOCKED\n");
}

void HostLock::unlock() {
    if(!locked_) return; 
    locked_ = false; 
    uart_.print("lock: UNLOCKED\n");
}

bool HostLock::isLocked() const { return locked_; }
