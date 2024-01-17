#include "logger.h"
#include <stdio.h>
#include <time.h>

void
LOG(char const * const tag, char const * const message)
{
   time_t now;
   time(&now);
   printf("%s [%s]: %s\n", ctime(&now), tag, message);
}
