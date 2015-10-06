#include "browser.h"
#include "dataset.h"
#include "util.h"

int
woothee_browser_challenge_msie(const char *ua, woothee_t *result)
{
  char *version = NULL;

  if (strstr(ua, "compatible; MSIE") == NULL
      && strstr(ua, "Trident/") == NULL
      && strstr(ua, "IEMobile") == NULL) {
    return 0;
  }

  version = woothee_match_get("MSIE ([.0-9]+);", 0, ua, 1);
  if (version == NULL) {
    if (woothee_match("Trident/([.0-9]+);", 0, ua)) {
      version = woothee_match_get(" rv:([.0-9]+)", 0, ua, 1);
    }
  }
  if (version == NULL) {
    version = woothee_match_get("IEMobile/([.0-9]+);", 0, ua, 1);
  }

  woothee_update(result, woothee_dataset_get(MSIE));
  if (version != NULL) {
    woothee_update_version(result, version);
    free(version);
  } else {
    woothee_update_version(result, WOOTHEE_DATASET_VALUE_UNKNOWN);
  }

  return 1;
}

int
woothee_browser_challenge_safari_chrome(const char *ua, woothee_t *result)
{
  char *version = NULL;

  if (strstr(ua, "Safari/") == NULL) {
    return 0;
  }

  /* Edge */
  if ((version = woothee_match_get("Edge/([.0-9]+)", 0, ua, 1))) {
    woothee_update(result, woothee_dataset_get(Edge));
    woothee_update_version(result, version);
    free(version);
    return 1;
  }

  version = woothee_match_get("(?:Chrome|CrMo|CriOS)/([.0-9]+)", 0, ua, 1);
  if (version) {
    char *opera_version = woothee_match_get("OPR/([.0-9]+)", 0, ua, 1);
    if (opera_version) {
      woothee_update(result, woothee_dataset_get(Opera));
      woothee_update_version(result, opera_version);
      free(opera_version);
      free(version);
      return 1;
    }

    /* Chrome */
    woothee_update(result, woothee_dataset_get(Chrome));
    woothee_update_version(result, version);
    free(version);
    return 1;
  }

  /* Safari */
  version = woothee_match_get("Version/([.0-9]+)", 0, ua, 1);
  woothee_update(result, woothee_dataset_get(Safari));
  if (version) {
    woothee_update_version(result, version);
    free(version);
  } else {
    woothee_update_version(result, WOOTHEE_DATASET_VALUE_UNKNOWN);
  }

  return 1;
}

int
woothee_browser_challenge_firefox(const char *ua, woothee_t *result)
{
  char *version = NULL;

  if (strstr(ua, "Firefox/") == NULL) {
    return 0;
  }

  version = woothee_match_get("Firefox/([.0-9]+)", 0, ua, 1);
  woothee_update(result, woothee_dataset_get(Firefox));
  if (version) {
    woothee_update_version(result, version);
    free(version);
  } else {
    woothee_update_version(result, WOOTHEE_DATASET_VALUE_UNKNOWN);
  }

  return 1;
}

int
woothee_browser_challenge_opera(const char *ua, woothee_t *result)
{
  char *version = NULL;

  if (strstr(ua, "Opera") == NULL) {
    return 0;
  }

  version = woothee_match_get("Version/([.0-9]+)", 0, ua, 1);
  if (version == NULL) {
    version = woothee_match_get("Opera[/ ]([.0-9]+)", 0, ua, 1);
  }

  woothee_update(result, woothee_dataset_get(Opera));
  if (version) {
    woothee_update_version(result, version);
    free(version);
  } else {
    woothee_update_version(result, WOOTHEE_DATASET_VALUE_UNKNOWN);
  }

  return 1;
}

int
woothee_browser_challenge_webview(const char *ua, woothee_t *result)
{
  char *version = NULL;

  if (!woothee_match("iP(?:hone;|ad;|od) .*like Mac OS X", 0, ua)) {
    return 0;
  }

  if (strstr(ua, "Safari/") != NULL) {
    return 0;
  }

  version = woothee_match_get("Version/([.0-9]+)", 0, ua, 1);

  woothee_update(result, woothee_dataset_get(Webview));
  if (version) {
    woothee_update_version(result, version);
    free(version);
  } else {
    woothee_update_version(result, WOOTHEE_DATASET_VALUE_UNKNOWN);
  }

  return 1;
}

int
woothee_browser_challenge_sleipnir(const char *ua, woothee_t *result)
{
  char *version = NULL;
  woothee_data_t *win = NULL;

  if (strstr(ua, "Sleipnir/") == NULL) {
    return 0;
  }

  version = woothee_match_get("Sleipnir/([.0-9]+)", 0, ua, 1);

  woothee_update(result, woothee_dataset_get(Sleipnir));
  if (version) {
    woothee_update_version(result, version);
    free(version);
  } else {
    woothee_update_version(result, WOOTHEE_DATASET_VALUE_UNKNOWN);
  }

  win = woothee_dataset_get(Win);
  woothee_update_category(result, win->category);
  woothee_update_os(result, win->name);

  return 1;
}
