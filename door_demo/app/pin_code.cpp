#include "pin_code.hpp"
#include <cstring>

PinCode::PinCode(const char* digits) {
    while(*digits && append(*digits)) ++digits;
}

bool PinCode::append(char digit) {
    if(digit < '0' || digit > '9') return false;
    if(len_ >= kMaxLen) return false; 
    digits_[len_++] = digit;
    digits_[len_] = '\0';
    return true;
}

void PinCode::clear() {
    len_ = 0; 
    digits_[0] = '\0';
}

std::size_t PinCode::length() const { return len_; }

bool PinCode::operator==(const PinCode& other) const {
    return len_ == other.len_ && std::memcmp(digits_, other.digits_, len_) == 0;
}
