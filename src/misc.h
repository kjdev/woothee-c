#ifndef WOOTHEE_MISC_H
#define WOOTHEE_MISC_H

#include "woothee.h"

int woothee_misc_challenge_desktoptools(const char *ua, woothee_t *result);
int woothee_misc_challenge_smartphone_patterns(const char *ua, woothee_t *result);
int woothee_misc_challenge_http_library(const char *ua, woothee_t *result);
int woothee_misc_challenge_maybe_rss_reader(const char *ua, woothee_t *result);

#endif
