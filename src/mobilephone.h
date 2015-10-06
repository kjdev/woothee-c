#ifndef WOOTHEE_MOBILEPHONE_H
#define WOOTHEE_MOBILEPHONE_H

#include "woothee.h"

int woothee_mobilephone_challenge_docomo(const char *ua, woothee_t *result);
int woothee_mobilephone_challenge_au(const char *ua, woothee_t *result);
int woothee_mobilephone_challenge_softbank(const char *ua, woothee_t *result);
int woothee_mobilephone_challenge_willcom(const char *ua, woothee_t *result);
int woothee_mobilephone_challenge_misc(const char *ua, woothee_t *result);

#endif
