#include "mobilephone.h"
#include "dataset.h"
#include "util.h"

int
woothee_mobilephone_challenge_docomo(const char *ua, woothee_t *result)
{
  char *version = NULL;

  if (strstr(ua, "DoCoMo") == NULL && strstr(ua, ";FOMA;") == NULL) {
    return 0;
  }

  version = woothee_match_get("DoCoMo/[.0-9]+[ /]([^- /;()\"']+)", 0, ua, 1);
  if (version == NULL) {
    version = woothee_match_get("\\(([^;)]+);FOMA;", 0, ua, 1);
  }

  woothee_update(result, woothee_dataset_get(docomo));
  if (version) {
    woothee_update_version(result, version);
    free(version);
  } else {
    woothee_update_version(result, WOOTHEE_DATASET_VALUE_UNKNOWN);
  }

  return 1;
}

int
woothee_mobilephone_challenge_au(const char *ua, woothee_t *result)
{
  char *version = NULL;

  if (strstr(ua, "KDDI-") == NULL) {
    return 0;
  }

  version = woothee_match_get("KDDI-([^- /;()\"']+)", 0, ua, 1);

  woothee_update(result, woothee_dataset_get(au));
  if (version) {
    woothee_update_version(result, version);
    free(version);
  } else {
    woothee_update_version(result, WOOTHEE_DATASET_VALUE_UNKNOWN);
  }

  return 1;
}

int
woothee_mobilephone_challenge_softbank(const char *ua, woothee_t *result)
{
  char *version = NULL;

  if (strstr(ua, "SoftBank") == NULL && strstr(ua, "Vodafone") == NULL
      && strstr(ua, "J-PHONE") == NULL) {
    return 0;
  }

  version = woothee_match_get("(SoftBank|Vodafone|J-PHONE)"
                              "/[.0-9]+/([^ /;()]+)", 0, ua, 2);

  woothee_update(result, woothee_dataset_get(SoftBank));
  if (version) {
    woothee_update_version(result, version);
    free(version);
  } else {
    woothee_update_version(result, WOOTHEE_DATASET_VALUE_UNKNOWN);
  }

  return 1;
}

int
woothee_mobilephone_challenge_willcom(const char *ua, woothee_t *result)
{
  char *version = NULL;

  if (strstr(ua, "WILLCOM") == NULL && strstr(ua, "DDIPOCKET") == NULL) {
    return 0;
  }

  version = woothee_match_get("(WILLCOM|DDIPOCKET);[^/]+/([^ /;()]+)",
                              0, ua, 2);

  woothee_update(result, woothee_dataset_get(willcom));
  if (version) {
    woothee_update_version(result, version);
    free(version);
  } else {
    woothee_update_version(result, WOOTHEE_DATASET_VALUE_UNKNOWN);
  }

  return 1;
}

int
woothee_mobilephone_challenge_misc(const char *ua, woothee_t *result)
{
  char *version = NULL;

  if (strstr(ua, "jig browser") != NULL) {
    woothee_update(result, woothee_dataset_get(jig));
    version = woothee_match_get("jig browser[^;]+; ([^);]+)", 0, ua, 1);
    if (version) {
      woothee_update_version(result, version);
      free(version);
    }
    return 1;
  }

  if (strstr(ua, "emobile/") != NULL || strstr(ua, "OpenBrowser") != NULL
      || strstr(ua, "Browser/Obigo-Browser") != NULL) {
    woothee_update(result, woothee_dataset_get(emobile));
    return 1;
  }

  if (strstr(ua, "SymbianOS") != NULL) {
    woothee_update(result, woothee_dataset_get(SymbianOS));
    return 1;
  }

  if (strstr(ua, "Hatena-Mobile-Gateway/") != NULL) {
    woothee_update(result, woothee_dataset_get(MobileTranscoder));
    woothee_update_version(result, "Hatena");
    return 1;
  }

  if (strstr(ua, "livedoor-Mobile-Gateway/") != NULL) {
    woothee_update(result, woothee_dataset_get(MobileTranscoder));
    woothee_update_version(result, "livedoor");
    return 1;
  }

  return 0;
}
