// PIN value type: holds up to 8 digits, used for both the secret and the user input.
#pragma once
#include <cstddef>

class PinCode {
public:
    static constexpr std::size_t kMaxLen = 8;

    PinCode() = default;        // empty PIN (input buffer)
    explicit PinCode(const char* digits);   // e.g. PinCode("1234")

    bool append(char digit);    // false if not a digit or buffer is full
    void clear();
    std::size_t length() const;
    bool operator==(const PinCode& other) const;

private:
    char digits_[kMaxLen+1] = {};   // +1 for the terminating '\0'
    std::size_t len_ = 0;
};
