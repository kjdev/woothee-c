#ifndef WOOTHEE_OS_H
#define WOOTHEE_OS_H

#include "woothee.h"

int woothee_os_challenge_windows(const char *ua, woothee_t *result);
int woothee_os_challenge_osx(const char *ua, woothee_t *result);
int woothee_os_challenge_linux(const char *ua, woothee_t *result);
int woothee_os_challenge_smartphone(const char *ua, woothee_t *result);
int woothee_os_challenge_mobilephone(const char *ua, woothee_t *result);
int woothee_os_challenge_appliance(const char *ua, woothee_t *result);
int woothee_os_challenge_misc(const char *ua, woothee_t *result);

#endif
