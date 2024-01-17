#ifndef LOGGER_H
#define LOGGER_H

#define INFO "INFO"
#define DEBUG "DEBUG"

#ifdef DBG
#define D(msg) \
  do { \
    fprintf(stderr, "DEBUG: %s:%d - %s\n", __FILE__, __LINE__, msg); \
  } while(0)
#else
#define D(x) \
  do {} while(0)
#endif

void LOG(char const * const tag, char const * const message);

#endif
