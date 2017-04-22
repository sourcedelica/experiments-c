#pragma once

#include <functional>

bool waitForChange(std::function<bool()> predicate, int tries = 5, int sleepMs = 250);

