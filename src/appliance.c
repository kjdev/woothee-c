#include "appliance.h"
#include "dataset.h"
#include "util.h"

int
woothee_appliance_challenge_playstation(const char *ua, woothee_t *result)
{
  char *version = NULL;
  woothee_data_t *data = NULL;

  if (strstr(ua, "PSP (PlayStation Portable);") != NULL) {
    data = woothee_dataset_get(PSP);
    version = woothee_match_get(
      "PSP \\(PlayStation Portable\\); ([.0-9]+)\\)", 0, ua, 1);
  } else if (strstr(ua, "PlayStation Vita") != NULL) {
    data = woothee_dataset_get(PSVita);
    version = woothee_match_get("PlayStation Vita ([.0-9]+)\\)", 0, ua, 1);
  } else if (strstr(ua, "PLAYSTATION 3 ") != NULL
             || strstr(ua, "PLAYSTATION 3;") != NULL) {
    data = woothee_dataset_get(PS3);
    version = woothee_match_get("PLAYSTATION 3;? ([.0-9]+)\\)", 0, ua, 1);
  } else if (strstr(ua, "PlayStation 4 ") != NULL) {
    data = woothee_dataset_get(PS4);
    version = woothee_match_get("PlayStation 4 ([.0-9]+)\\)", 0, ua, 1);
  }

  if (data == NULL) {
    return 0;
  }

  woothee_update(result, data);
  if (version) {
    woothee_update_os_version(result, version);
    free(version);
  }

  return 1;
}

int
woothee_appliance_challenge_nintendo(const char *ua, woothee_t *result)
{
  woothee_data_t *data = NULL;

  if (strstr(ua, "Nintendo 3DS;") != NULL) {
    data = woothee_dataset_get(Nintendo3DS);
  } else if (strstr(ua, "Nintendo DSi;") != NULL) {
    data = woothee_dataset_get(NintendoDSi);
  } else if (strstr(ua, "Nintendo Wii;") != NULL) {
    data = woothee_dataset_get(NintendoWii);
  } else if (strstr(ua, "(Nintendo WiiU)") != NULL) {
    data = woothee_dataset_get(NintendoWiiU);
  }

  if (data == NULL) {
    return 0;
  }

  woothee_update(result, data);

  return 1;
}

int
woothee_appliance_challenge_digitaltv(const char *ua, woothee_t *result)
{
  woothee_data_t *data = NULL;

  if (strstr(ua, "InettvBrowser/") != NULL) {
    data = woothee_dataset_get(DigitalTV);
  }

  if (data == NULL) {
    return 0;
  }

  woothee_update(result, data);

  return 1;
}
