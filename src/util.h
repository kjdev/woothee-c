#ifndef WOOTHEE_UTIL_H
#define WOOTHEE_UTIL_H

#include "woothee.h"

void woothee_update(woothee_t *result, woothee_data_t *source);
void woothee_update_category(woothee_t *target, char *category);
void woothee_update_version(woothee_t *target, char *version);
void woothee_update_os(woothee_t *target, char *os);
void woothee_update_os_version(woothee_t *target, char *version);

int woothee_match(const char *regex, int caseless, const char *str);
char * woothee_match_get(const char *regex, int caseless, const char *str, int n);

#endif
