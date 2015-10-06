#ifndef WOOTHEE_APPLIANCE_H
#define WOOTHEE_APPLIANCE_H

#include "woothee.h"

int woothee_appliance_challenge_playstation(const char *ua, woothee_t *result);
int woothee_appliance_challenge_nintendo(const char *ua, woothee_t *result);
int woothee_appliance_challenge_digitaltv(const char *ua, woothee_t *result);

#endif
