#include <time.h>

#include "utils.h"

double tstamp() {
    return (double)clock()/CLOCKS_PER_SEC;
}
