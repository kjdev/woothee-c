#include "misc.h"
#include "dataset.h"
#include "util.h"

int
woothee_misc_challenge_desktoptools(const char *ua, woothee_t *result)
{
  woothee_data_t *data = NULL;

  if (strstr(ua, "AppleSyndication/") != NULL) {
    data = woothee_dataset_get(SafariRSSReader);
  } else if (strstr(ua, "compatible; Google Desktop/") != NULL) {
    data = woothee_dataset_get(GoogleDesktop);
  } else if (strstr(ua, "Windows-RSS-Platform") != NULL) {
    data = woothee_dataset_get(WindowsRSSReader);
  }

  if (data == NULL) {
    return 0;
  }

  woothee_update(result, data);

  return 1;
}

int
woothee_misc_challenge_smartphone_patterns(const char *ua, woothee_t *result)
{
  woothee_data_t *data = NULL;

  if (strstr(ua, "CFNetwork/") != NULL) {
    data = woothee_dataset_get(iOS);
    woothee_update_category(result, data->category);
    woothee_update_os(result, data->name);
    return 1;
  }

  return 0;
}

int
woothee_misc_challenge_http_library(const char *ua, woothee_t *result)
{
  woothee_data_t *data = NULL;
  char *version = NULL;

  if (woothee_match(
        "^(?:Apache-HttpClient/|Jakarta Commons-HttpClient/|Java/)", 0, ua)
      || woothee_match("[- ]HttpClient(/|$)", 0, ua)) {
    data = woothee_dataset_get(HTTPLibrary);
    version = "Java";
  } else if (strstr(ua, "Java(TM) 2 Runtime Environment,") != NULL) {
    data = woothee_dataset_get(HTTPLibrary);
    version = "Java";
  } else if (woothee_match("^Wget", 0, ua)) {
    data = woothee_dataset_get(HTTPLibrary);
    version = "wget";
  } else if (woothee_match(
               "^(?:libwww-perl|WWW-Mechanize|LWP::Simple|LWP |lwp-trivial)",
               0, ua)) {
    data = woothee_dataset_get(HTTPLibrary);
    version = "perl";
  } else if (woothee_match("^(?:Ruby|feedzirra|Typhoeus)", 0, ua)) {
    data = woothee_dataset_get(HTTPLibrary);
    version = "ruby";
  } else if (woothee_match("^(Python-urllib/|Twisted )", 0, ua)) {
    data = woothee_dataset_get(HTTPLibrary);
    version = "python";
  } else if (woothee_match(
               "^(?:PHP|WordPress|CakePHP|PukiWiki|PECL::HTTP)(?:/| |$)", 0, ua)
             || woothee_match("(?:PEAR |)HTTP_Request(?: class|2)", 0, ua)) {
    data = woothee_dataset_get(HTTPLibrary);
    version = "php";
  }

  if (data == NULL) {
    return 0;
  }

  woothee_update(result, data);
  woothee_update_version(result, version);

  return 1;
}

int
woothee_misc_challenge_maybe_rss_reader(const char *ua, woothee_t *result)
{
  woothee_data_t *data = NULL;

  if (woothee_match("rss(?:reader|bar|[-_ /;()]|[ +]*/)", 1, ua)
      || woothee_match("headline-reader", 1, ua)) {
    data = woothee_dataset_get(VariousRSSReader);
  } else if (strstr(ua, "cococ/") != NULL) {
    data = woothee_dataset_get(VariousRSSReader);
  }

  if (data == NULL) {
    return 0;
  }

  woothee_update(result, data);

  return 1;
}
