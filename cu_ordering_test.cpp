#include <cstdio>
#include "CUTrace.h"

extern "C" void CUTraceHelper(char const *file, char const *msg, va_list args) {
    char sz1[1024]; vsprintf(sz1, msg, args); printf("%s: %s", file, sz1);
}

int main(int /* argc */, char ** /*argv*/) {
    printf("%s\n", __BASE_FILE__);
    return 0;
}