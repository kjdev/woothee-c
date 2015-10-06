#ifndef WOOTHEE_CRAWLER_H
#define WOOTHEE_CRAWLER_H

#include "woothee.h"

int woothee_crawler_challenge_google(const char *ua, woothee_t *result);
int woothee_crawler_challenge_crawlers(const char *ua, woothee_t *result);
int woothee_crawler_challenge_maybe_crawler(const char *ua, woothee_t *result);

#endif
