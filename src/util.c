#include <regex.h>

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
  regex_t re;
  int ret, matched;
  int options = REG_EXTENDED;

  if (caseless) {
    options |= REG_ICASE;
  }

  if ((ret = regcomp(&re, regex, options)) != 0) {
    char err[BUFSIZ] = { 0, };
    regerror(ret, &re, err, BUFSIZ);
    fprintf(stderr, "ERROR: regcomp: '%s': %s\n", regex, err);
    regfree(&re);
    return 0;
  }

  matched = regexec(&re, str, 0, 0, 0);
  regfree(&re);

  return !matched;
}

char *
woothee_match_get(const char *regex, int caseless, const char *str, int n)
{
  regex_t re;
  int ret, matched;
  int options = REG_EXTENDED;
  size_t nmatch = 16;
  regmatch_t pmatch[nmatch];

  if (caseless) {
    options |= REG_ICASE;
  }

  if ((ret = regcomp(&re, regex, options)) != 0) {
    char err[BUFSIZ] = { 0, };
    regerror(ret, &re, err, BUFSIZ);
    fprintf(stderr, "ERROR: regcomp: '%s': %s\n", regex, err);
    regfree(&re);
    return 0;
  }

  memset(&pmatch, 0, sizeof(pmatch));

  matched = regexec(&re, str, nmatch, pmatch, 0);
  regfree(&re);

  if (matched != 0) {
    return NULL;
  }

  if (pmatch[n].rm_so < 0 || pmatch[n].rm_eo < 0) {
    return NULL;
  }

  return strndup(str + pmatch[n].rm_so, pmatch[n].rm_eo - pmatch[n].rm_so);
}
