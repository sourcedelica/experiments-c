#pragma once

#include <chrono>

struct ClientSettings {
    uint16_t maxTries = DefaultMaxTries;
    uint16_t graceMaxTries = DefaultGraceMaxTries;
    uint64_t waitForPrimaryMs = DefaultWaitForPrimaryMs;
    uint64_t overallTimeoutMs = DefaultOverallTimeoutMs;
    uint64_t retryIntervalMs  = DefaultRetryIntervalMs;
    uint64_t connectTimeoutMs = DefaultConnectTimeoutMs;

    // Zero = unlimited unless noted
    constexpr static int DefaultMaxTries              = 0;
    constexpr static int DefaultGraceMaxTries         = 0;  // Zero = none
    constexpr static uint64_t DefaultWaitForPrimaryMs = 60 * 60 * 1000;
    constexpr static uint64_t DefaultOverallTimeoutMs = 0;
    constexpr static uint64_t DefaultRetryIntervalMs  = 5 * 1000;
    constexpr static uint64_t DefaultConnectTimeoutMs = 2 * 1000;

    int getFailoverMaxTries() const { return maxTries; }
    int getFailoverGraceMaxTries() const { return graceMaxTries; }
    uint64_t getFailoverWaitForPrimaryMs() const { return waitForPrimaryMs; }
    uint64_t getFailoverOverallTimeoutMs() const { return overallTimeoutMs; }
    uint64_t getFailoverRetryIntervalMs()  const { return retryIntervalMs; }
    uint64_t getFailoverConnectTimeoutMs() const { return connectTimeoutMs; }

    std::chrono::milliseconds getFailoverWaitForPrimary() const { return std::chrono::milliseconds(waitForPrimaryMs); }
    std::chrono::milliseconds getFailoverOverallTimeout() const { return std::chrono::milliseconds(overallTimeoutMs); }
    std::chrono::milliseconds getFailoverRetryInterval()  const { return std::chrono::milliseconds(retryIntervalMs); }
    std::chrono::milliseconds getFailoverConnectTimeout() const { return std::chrono::milliseconds(connectTimeoutMs); }
};
