#include "woothee.h"
#include "crawler.h"
#include "browser.h"
#include "os.h"
#include "mobilephone.h"
#include "appliance.h"
#include "misc.h"
#include "dataset.h"

static woothee_t *
woothee_create(void)
{
  woothee_t *self;

  self = (woothee_t *)malloc(sizeof(woothee_t));
  if (!self) {
    fprintf(stderr, "ERROR: Cannot allocate memory\n");
    return NULL;
  }
  memset(self, 0, sizeof(woothee_t));

  return self;
}

void
woothee_delete(woothee_t *self)
{
  if (!self) {
    return;
  }

  if (self->name) {
    free(self->name);
  }
  if (self->category) {
    free(self->category);
  }
  if (self->os) {
    free(self->os);
  }
  if (self->version) {
    free(self->version);
  }
  if (self->os_version) {
    free(self->os_version);
  }
  if (self->vendor) {
    free(self->vendor);
  }

  free(self);
}

static int
try_crawler(const char *useragent, woothee_t *result)
{
  if (woothee_crawler_challenge_google(useragent, result)) {
    return 1;
  }
  if (woothee_crawler_challenge_crawlers(useragent, result)) {
    return 1;
  }
  return 0;
}

static int
try_browser(const char *useragent, woothee_t *result)
{
  if (woothee_browser_challenge_msie(useragent, result)) {
    return 1;
  }
  if (woothee_browser_challenge_safari_chrome(useragent, result)) {
    return 1;
  }
  if (woothee_browser_challenge_firefox(useragent, result)) {
    return 1;
  }
  if (woothee_browser_challenge_opera(useragent, result)) {
    return 1;
  }
  if (woothee_browser_challenge_webview(useragent, result)) {
    return 1;
  }
  return 0;
}

static int
try_os(const char *useragent, woothee_t *result)
{
  if (woothee_os_challenge_windows(useragent, result)) {
    return 1;
  }

  /* OSX PC and iOS devices (strict check) */
  if (woothee_os_challenge_osx(useragent, result)) {
    return 1;
  }

  /* Linux PC and Android */
  if (woothee_os_challenge_linux(useragent, result)) {
    return 1;
  }

  /* all useragents matches /(iPhone|iPad|iPod|Android|BlackBerry)/ */
  if (woothee_os_challenge_smartphone(useragent, result)) {
    return 1;
  }

  /* mobile phones like KDDI-.* */
  if (woothee_os_challenge_mobilephone(useragent, result)) {
    return 1;
  }

  /* Nintendo DSi/Wii with Opera */
  if (woothee_os_challenge_appliance(useragent, result)) {
    return 1;
  }

  /* Win98, BSD, classic MacOS, ... */
  if (woothee_os_challenge_misc(useragent, result)) {
    return 1;
  }

  return 0;
}

static int
try_mobilephone(const char *useragent, woothee_t *result)
{
  if (woothee_mobilephone_challenge_docomo(useragent, result)) {
    return 1;
  }
  if (woothee_mobilephone_challenge_au(useragent, result)) {
    return 1;
  }
  if (woothee_mobilephone_challenge_softbank(useragent, result)) {
    return 1;
  }
  if (woothee_mobilephone_challenge_willcom(useragent, result)) {
    return 1;
  }
  if (woothee_mobilephone_challenge_misc(useragent, result)) {
    return 1;
  }
  return 0;
}

static int
try_appliance(const char *useragent, woothee_t *result)
{
  if (woothee_appliance_challenge_playstation(useragent, result)) {
    return 1;
  }
  if (woothee_appliance_challenge_nintendo(useragent, result)) {
    return 1;
  }
  if (woothee_appliance_challenge_digitaltv(useragent, result)) {
    return 1;
  }
  return 0;
}

static int
try_misc(const char *useragent, woothee_t *result)
{
  if (woothee_misc_challenge_desktoptools(useragent, result)) {
    return 1;
  }
  return 0;
}

static int
try_rare_cases(const char *useragent, woothee_t *result)
{
  if (woothee_misc_challenge_smartphone_patterns(useragent, result)) {
    return 1;
  }

  if (woothee_browser_challenge_sleipnir(useragent, result)) {
    return 1;
  }

  if (woothee_misc_challenge_http_library(useragent, result)) {
    return 1;
  }

  if (woothee_misc_challenge_maybe_rss_reader(useragent, result)) {
    return 1;
  }

  if (woothee_crawler_challenge_maybe_crawler(useragent, result)) {
    return 1;
  }

  return 0;
}

static woothee_t *
exec_parse(const char *useragent)
{
  woothee_t *result;

  if (!useragent) {
    return NULL;
  }

  result = woothee_create();
  if (!result) {
    return NULL;
  }

  if (strcmp(useragent, "-") == 0) {
    return result;
  }

  if (try_crawler(useragent, result)) {
    return result;
  }

  if (try_browser(useragent, result)) {
    if (try_os(useragent, result)) {
      return result;
    } else {
      return result;
    }
  }

  if (try_mobilephone(useragent, result)) {
      return result;
  }

  if (try_appliance(useragent, result)) {
      return result;
  }

  if (try_misc(useragent, result)) {
      return result;
  }

  /* browser unknown. check os only */
  if (try_os(useragent, result)) {
      return result;
  }

  if (try_rare_cases(useragent, result)) {
    return result;
  }

  return result;
}

woothee_t *
woothee_parse(const char *useragent)
{
  woothee_t *result = exec_parse(useragent);

  if (!result) {
    return NULL;
  }

  if (!result->name) {
    result->name = strdup(WOOTHEE_DATASET_VALUE_UNKNOWN);
  }
  if (!result->category) {
    result->category = strdup(WOOTHEE_DATASET_VALUE_UNKNOWN);
  }
  if (!result->os) {
    result->os = strdup(WOOTHEE_DATASET_VALUE_UNKNOWN);
  }
  if (!result->os_version) {
    result->os_version = strdup(WOOTHEE_DATASET_VALUE_UNKNOWN);
  }
  if (!result->version) {
    result->version = strdup(WOOTHEE_DATASET_VALUE_UNKNOWN);
  }
  if (!result->vendor) {
    result->vendor = strdup(WOOTHEE_DATASET_VALUE_UNKNOWN);
  }

  return result;
}

int
woothee_is_crawler(const char *useragent)
{
  woothee_t *result;
  int is_crawler = 0;

  if (!useragent || strlen(useragent) < 1 || strcmp(useragent, "-") == 0) {
    return is_crawler;
  }

  result = woothee_create();
  if (!result) {
    return is_crawler;
  }

  if (try_crawler(useragent, result)) {
    is_crawler = 1;
  }

  woothee_delete(result);

  return is_crawler;
}
