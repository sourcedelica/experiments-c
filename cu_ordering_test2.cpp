#include <cstdio>
#include "CUTrace.h"

class X {
public:
    X() {
        printf("%s\n", __BASE_FILE__);
    }
} x;