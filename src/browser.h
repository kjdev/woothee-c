#ifndef WOOTHEE_BROWSER_H
#define WOOTHEE_BROWSER_H

#include "woothee.h"

int woothee_browser_challenge_msie(const char *ua, woothee_t *result);
int woothee_browser_challenge_safari_chrome(const char *ua, woothee_t *result);
int woothee_browser_challenge_firefox(const char *ua, woothee_t *result);
int woothee_browser_challenge_opera(const char *ua, woothee_t *result);
int woothee_browser_challenge_webview(const char *ua, woothee_t *result);
int woothee_browser_challenge_sleipnir(const char *ua, woothee_t *result);

#endif
