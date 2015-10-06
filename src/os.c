#include "os.h"
#include "dataset.h"
#include "util.h"

int
woothee_os_challenge_windows(const char *ua, woothee_t *result)
{
  char *version = NULL;
  woothee_data_t *data = NULL;

  if (strstr(ua, "Windows") == NULL) {
    return 0;
  }

  /* Xbox Series */
  if (strstr(ua, "Xbox") != NULL) {
    if (strstr(ua, "Xbox; Xbox One)") != NULL) {
      woothee_update(result, woothee_dataset_get(XboxOne));
    } else {
      woothee_update(result, woothee_dataset_get(Xbox360));
    }
    return 1;
  }

  data = woothee_dataset_get(Win);

  version = woothee_match_get("Windows ([ .a-zA-Z0-9]+)[;\\)]", 0, ua, 1);
  if (version == NULL) {
    woothee_update_category(result, data->category);
    woothee_update_os(result, data->name);
    return 1;
  }

  if (strncmp(version, "NT 10.0", 7) == 0) {
    data = woothee_dataset_get(Win10);
  } else if (strncmp(version, "NT 6.3", 6) == 0) {
    data = woothee_dataset_get(Win8_1);
  } else if (strncmp(version, "NT 6.2", 6) == 0) {
    data = woothee_dataset_get(Win8);
  } else if (strncmp(version, "NT 6.1", 6) == 0) {
    data = woothee_dataset_get(Win7);
  } else if (strncmp(version, "NT 6.0", 6) == 0) {
    data = woothee_dataset_get(WinVista);
  } else if (strncmp(version, "NT 5.1", 6) == 0) {
    data = woothee_dataset_get(WinXP);
  } else if (woothee_match("^Phone", 0, version)) {
    char *phone_version = woothee_match_get(
      "Phone(?: OS)? ([.0-9]+)", 0, ua, 1);
    if (phone_version) {
      free(version);
      version = phone_version;
    }
    data = woothee_dataset_get(WinPhone);
  } else if (strncmp(version, "NT 5.0", 6) == 0) {
    data = woothee_dataset_get(Win2000);
  } else if (strncmp(version, "NT 4.0", 6) == 0) {
    data = woothee_dataset_get(WinNT4);
  } else if (strncmp(version, "98", 2) == 0) {
    data = woothee_dataset_get(Win98);
  } else if (strncmp(version, "95", 2) == 0) {
    data = woothee_dataset_get(Win95);
  } else if (strncmp(version, "CE", 2) == 0) {
    data = woothee_dataset_get(WinCE);
  }

  woothee_update_category(result, data->category);
  woothee_update_os(result, data->name);
  woothee_update_os_version(result, version);
  free(version);

  return 1;
}

int
woothee_os_challenge_osx(const char *ua, woothee_t *result)
{
  char *version = NULL;
  woothee_data_t *data = NULL;

  if (strstr(ua, "Mac OS X") == NULL) {
    return 0;
  }

  data = woothee_dataset_get(OSX);

  if (strstr(ua, "like Mac OS X") != NULL) {
    if (strstr(ua, "iPhone;") != NULL) {
      data = woothee_dataset_get(iPhone);
    } else if (strstr(ua, "iPad;") != NULL) {
      data = woothee_dataset_get(iPad);
    } else if (strstr(ua, "iPod") != NULL) {
      data = woothee_dataset_get(iPod);
    }

    version = woothee_match_get(
      "; CPU(?: iPhone)? OS (\\d+_\\d+(?:_\\d+)?) like Mac OS X", 0, ua, 1);
  } else {
    version = woothee_match_get(
      "Mac OS X (10[._]\\d+(?:[._]\\d+)?)(?:\\)|;)", 0, ua, 1);
  }

  woothee_update_category(result, data->category);
  woothee_update_os(result, data->name);
  if (version) {
    size_t i, size = strlen(version);
    for (i = 0; i < size; i++) {
      if (version[i] == '_') {
        version[i] = '.';
      }
    }
    woothee_update_os_version(result, version);
    free(version);
  }

  return 1;
}

int
woothee_os_challenge_linux(const char *ua, woothee_t *result)
{
  char *version = NULL;
  woothee_data_t *data = NULL;

  if (strstr(ua, "Linux") == NULL) {
    return 0;
  }

  if (strstr(ua, "Android") != NULL) {
    data = woothee_dataset_get(Android);
    version = woothee_match_get(
      "Android[- ](\\d+\\.\\d+(?:\\.\\d+)?)", 0, ua, 1);
  } else {
    data = woothee_dataset_get(Linux);
  }

  woothee_update_category(result, data->category);
  woothee_update_os(result, data->name);
  if (version) {
    woothee_update_os_version(result, version);
    free(version);
  }

  return 1;
}

int
woothee_os_challenge_smartphone(const char *ua, woothee_t *result)
{
  char *version = NULL;
  woothee_data_t *data = NULL;

  if (strstr(ua, "iPhone") != NULL) {
    data = woothee_dataset_get(iPhone);
  } else if (strstr(ua, "iPad") != NULL) {
    data = woothee_dataset_get(iPad);
  } else if (strstr(ua, "iPod") != NULL) {
    data = woothee_dataset_get(iPod);
  } else if (strstr(ua, "Android") != NULL) {
    data = woothee_dataset_get(Android);
  } else if (strstr(ua, "CFNetwork") != NULL) {
    data = woothee_dataset_get(iOS);
  } else if (strstr(ua, "BB10") != NULL) {
    data = woothee_dataset_get(BlackBerry10);
    version = woothee_match_get("BB10(?:.+)Version/([.0-9]+)", 0, ua, 1);
  } else if (strstr(ua, "BlackBerry") != NULL) {
    data = woothee_dataset_get(BlackBerry);
    version = woothee_match_get("BlackBerry(?:\\d+)/([.0-9]+) ", 0, ua, 1);
  }

  if (result->name) {
    woothee_data_t *firefox = woothee_dataset_get(Firefox);
    if (strcmp(result->name, firefox->name) == 0) {
      char *firefox_version = woothee_match_get(
        "^Mozilla/[.0-9]+ \\((?:Mobile|Tablet);(?:.*;)? rv:([.0-9]+)\\) "
        "Gecko/[.0-9]+ Firefox/[.0-9]+$",
        0, ua, 1);
      if (firefox_version) {
        data = woothee_dataset_get(FirefoxOS);
        if (version) {
          free(version);
        }
        version = firefox_version;
      }
    }
  }

  if (data == NULL) {
    return 0;
  }

  woothee_update_category(result, data->category);
  woothee_update_os(result, data->name);
  if (version) {
    woothee_update_os_version(result, version);
    free(version);
  }

  return 1;
}

int
woothee_os_challenge_mobilephone(const char *ua, woothee_t *result)
{
  char *term = NULL;
  woothee_data_t *data = NULL;

  if (strstr(ua, "KDDI-") != NULL) {
    term = woothee_match_get("KDDI-([^- /;()\"']+)", 0, ua, 1);
    if (term) {
      data = woothee_dataset_get(au);
      woothee_update_category(result, data->category);
      woothee_update_os(result, data->os);
      woothee_update_version(result, term);
      free(term);
      return 1;
    }
  }

  if (strstr(ua, "WILLCOM") != NULL || strstr(ua, "DDIPOCKET") != NULL) {
    term = woothee_match_get(
      "(?:WILLCOM|DDIPOCKET);[^/]+/([^ /;()]+)", 0, ua, 1);
    if (term) {
        data = woothee_dataset_get(willcom);
        woothee_update_category(result, data->category);
        woothee_update_os(result, data->os);
        woothee_update_version(result, term);
        free(term);
        return 1;
    }
  }

  if (strstr(ua, "SymbianOS") != NULL) {
    data = woothee_dataset_get(SymbianOS);
    woothee_update_category(result, data->category);
    woothee_update_os(result, data->os);
    return 1;
  }

  if (strstr(ua, "Google Wireless Transcoder") != NULL) {
    woothee_update(result, woothee_dataset_get(MobileTranscoder));
    woothee_update_version(result, "Google");
    return 1;
  }

  if (strstr(ua, "Naver Transcoder") != NULL) {
    woothee_update(result, woothee_dataset_get(MobileTranscoder));
    woothee_update_version(result, "Naver");
    return 1;
  }

  return 0;
}

int
woothee_os_challenge_appliance(const char *ua, woothee_t *result)
{
  woothee_data_t *data = NULL;

  if (strstr(ua, "Nintendo DSi;") != NULL) {
    data = woothee_dataset_get(NintendoDSi);
    woothee_update_category(result, data->category);
    woothee_update_os(result, data->os);
    return 1;
  }

  if (strstr(ua, "Nintendo Wii;") != NULL) {
    data = woothee_dataset_get(NintendoWii);
    woothee_update_category(result, data->category);
    woothee_update_os(result, data->os);
    return 1;
  }

  return 0;
}

int
woothee_os_challenge_misc(const char *ua, woothee_t *result)
{
  char *version = NULL;
  woothee_data_t *data = NULL;

  if (strstr(ua, "(Win98;") != NULL) {
    data = woothee_dataset_get(Win98);
    version = strdup("98");
  } else if (strstr(ua, "Macintosh; U; PPC;") != NULL) {
    data = woothee_dataset_get(MacOS);
    version = woothee_match_get("rv:(\\d+\\.\\d+\\.\\d+)", 0, ua, 1);
  } else if (strstr(ua, "Mac_PowerPC") != NULL) {
    data = woothee_dataset_get(MacOS);
  } else if (strstr(ua, "X11; FreeBSD ") != NULL) {
    data = woothee_dataset_get(BSD);
    version = woothee_match_get("FreeBSD ([^;\\)]+)", 0, ua, 1);
  } else if (strstr(ua, "X11; CrOS ") != NULL) {
    data = woothee_dataset_get(ChromeOS);
    version = woothee_match_get("CrOS ([^\\)]+)\\)", 0, ua, 1);
  }

  if (data) {
    woothee_update_category(result, data->category);
    woothee_update_os(result, data->name);
    if (version) {
      woothee_update_os_version(result, version);
      free(version);
    }
    return 1;
  }

  if (version) {
    free(version);
  }

  return 0;
}
