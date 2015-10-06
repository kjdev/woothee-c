#ifndef WOOTHEE_WOOTHEE_H
#define WOOTHEE_WOOTHEE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataset.h"

typedef struct {
  char *name;
  char *category;
  char *os;
  char *os_version;
  char *version;
  char *vendor;
} woothee_t;

void woothee_delete(woothee_t *self);

woothee_t * woothee_parse(const char *useragent);
int woothee_is_crawler(const char *useragent);


#endif
