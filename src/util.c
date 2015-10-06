#include <pcre.h>

#include "util.h"

void
woothee_update(woothee_t *target, woothee_data_t *source)
{
  if (!target || !source) {
    return;
  }

  if (source->name && strlen(source->name) > 0) {
    if (target->name) {
      free(target->name);
    }
    target->name = strdup(source->name);
  }
  if (source->category && strlen(source->category) > 0) {
    if (target->category) {
      free(target->category);
    }
    target->category = strdup(source->category);
  }
  if (source->os && strlen(source->os) > 0) {
    if (target->os) {
      free(target->os);
    }
    target->os = strdup(source->os);
  }
  if (source->vendor && strlen(source->vendor) > 0) {
    if (target->vendor) {
      free(target->vendor);
    }
    target->vendor = strdup(source->vendor);
  }
}

void
woothee_update_category(woothee_t *target, char *category)
{
  if (target && category) {
    if (target->category) {
      free(target->category);
    }
    target->category = strdup(category);
  }
}

void
woothee_update_version(woothee_t *target, char *version)
{
  if (target && version) {
    if (target->version) {
      free(target->version);
    }
    target->version = strdup(version);
  }
}

void
woothee_update_os(woothee_t *target, char *os)
{
  if (target && os) {
    if (target->os) {
      free(target->os);
    }
    target->os = strdup(os);
  }
}

void
woothee_update_os_version(woothee_t *target, char *version)
{
  if (target && version) {
    if (target->os_version) {
      free(target->os_version);
    }
    target->os_version = strdup(version);
  }
}

int
woothee_match(const char *regex, int caseless, const char *str)
{
  pcre *re;
  int matched;
  const char *error_string;
  int error_offset;
  int ovector = 0;
  int options = 0;

  if (caseless) {
    options |= PCRE_CASELESS;
  }

  re = pcre_compile(regex, options, &error_string, &error_offset, NULL);
  if (re == NULL) {
    fprintf(stderr, "ERROR: %s\n", error_string);
    return 0;
  }

  matched = pcre_exec(re, NULL, str, (int)strlen(str), 0, 0, &ovector, 1);
  pcre_free(re);

  if (matched < 0) {
    return 0;
  }

  return 1;
}

char *
woothee_match_get(const char *regex, int caseless, const char *str, int n)
{
  pcre *re;
  int matched;
  const char *error_string;
  int error_offset;
  int ovector[16] = {0};
  int options = 0;
  size_t m = 2 * n;

  if (caseless) {
    options |= PCRE_CASELESS;
  }

  re = pcre_compile(regex, options, &error_string, &error_offset, NULL);
  if (re == NULL) {
    fprintf(stderr, "ERROR: %s\n", error_string);
    return NULL;
  }

  matched = pcre_exec(re, NULL, str, (int)strlen(str), 0, 0, ovector, 16);
  pcre_free(re);

  if (matched < 0) {
    return NULL;
  }

  if (m > (sizeof(ovector)/sizeof(ovector[0])) || ovector[m+1] == 0) {
    return NULL;
  }

  return strndup(str + ovector[m], ovector[m+1] - ovector[m]);
}
