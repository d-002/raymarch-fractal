#include "utils.h"

#include <time.h>

double tstamp() {
    return (double)clock()/CLOCKS_PER_SEC;
}
