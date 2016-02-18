#include <getopt.h>
#include <libgen.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

#include "woothee.h"

static void
usage(char *arg)
{
  char *command = basename(arg);

  printf("Usage: %s [OPTIONS] <USER_AGENT>\n\n", command);

  printf("options:\n");
  printf("  -i, --item=NAME[,..]  Show parse item\n");
  printf("                        "
         "[target|name|os|category|os_version|version|vendor]\n");
  printf("  -n, --none            Disable show item 'UNKNOWN'\n");
  printf("  -F, --file=NAME       Input filename\n");
  printf("  -h, --help            Print usage\n");
}

static void
print(woothee_t *woothee, char *target, char *item, int none)
{
  char *unknown = "UNKNOWN";

  if (item == NULL) {
    if (!none || strcmp(woothee->name, unknown) != 0) {
      printf("name: %s\n", woothee->name);
    }
    if (!none || strcmp(woothee->os, unknown) != 0) {
      printf("os: %s\n", woothee->os);
    }
    if (!none || strcmp(woothee->category, unknown) != 0) {
      printf("category: %s\n", woothee->category);
    }
    if (!none || strcmp(woothee->os_version, unknown) != 0) {
      printf("os_version: %s\n", woothee->os_version);
    }
    if (!none || strcmp(woothee->version, unknown) != 0) {
      printf("version: %s\n", woothee->version);
    }
    if (!none || strcmp(woothee->vendor, unknown) != 0) {
      printf("vendor: %s\n", woothee->vendor);
    }
  } else {
    int begin = 0, end = 0;
    char *key, *p = NULL;

    do {
      p = strchr(item + begin, ',');
      if (p == NULL) {
        end = strlen(item);
      } else {
        end = p - item;
      }

      key = strndup(item + begin, end - begin);
      if (key) {
        if (strcmp(key, "target") == 0 && target) {
          size_t i = strlen(target) - 1;
          printf("%s: %s", key, target);
          if (target[i] != '\n') {
            printf("\n");
          }
        } else {
          char *val = NULL;
          if (strcmp(key, "name") == 0) {
            val = woothee->name;
          } else if (strcmp(key, "os") == 0) {
            val = woothee->os;
          } else if (strcmp(key, "category") == 0) {
            val = woothee->category;
          } else if (strcmp(key, "os_version") == 0) {
            val = woothee->os_version;
          } else if (strcmp(key, "version") == 0) {
            val = woothee->version;
          } else if (strcmp(key, "vendor") == 0) {
            val = woothee->vendor;
          }
          if (val && (!none || strcmp(val, unknown) != 0)) {
            printf("%s: %s\n", key, val);
          }
        }

        free(key);
      }

      begin = end + 1;
    } while (p != NULL);
  }
}

int
main(int argc, char **argv)
{
  woothee_t *woothee;
  int none = 0;
  char *item = NULL, *filename = NULL;
  FILE *file = NULL;
  struct stat st;

  int opt;
  const struct option opts[] = {
    { "item", 1, NULL, 'i' },
    { "none", 0, NULL, 'n' },
    { "file", 1, NULL, 'F' },
    { "help", 0, NULL, 'h' },
    { NULL, 0, NULL, 0 }
  };

  while ((opt = getopt_long(argc, argv, "i:nF:h", opts, NULL)) != -1) {
    switch (opt) {
      case 'i':
        item = optarg;
        break;
      case 'n':
        none = 1;
        break;
      case 'F':
        filename = optarg;
        break;
      case 'h':
      default:
        usage(argv[0]);
        return 1;
    }
  }

  if (fstat(STDIN_FILENO, &st) == 0 && S_ISFIFO(st.st_mode)) {
    file = stdin;
  }

  if (filename) {
    file = fopen(filename, "r");
    if (!file) {
      fprintf(stderr, "ERROR: Unable to open file \"%s\"\n", filename);
      return 1;
    }
  }

  if (file) {
    char buf[BUFSIZ] = {0, };
    size_t len;

    while (fgets(buf, BUFSIZ, file)) {
      if ((len = strlen(buf)) == 0 || buf[0] == '\n') {
        printf("\n");
        continue;
      }

      do {
        buf[len--] = 0;
      } while (len > 0 && (buf[len] == '\n' || buf[len] == '\r'));

      woothee = woothee_parse(buf);
      if (!woothee) {
        fprintf(stderr, "ERROR: woothee parse: \"%s\"\n", buf);
        return 1;
      }

      print(woothee, buf, item, none);

      woothee_delete(woothee);
    }

    if (file != stdin) {
      fclose(file);
    }
  } else {
    if (argc <= optind || strlen(argv[optind]) == 0) {
      usage(argv[0]);
      return 1;
    }

    woothee = woothee_parse(argv[optind]);
    if (!woothee) {
      fprintf(stderr, "ERROR: woothee parse: \"%s\"\n", argv[optind]);
      return 1;
    }

    print(woothee, argv[optind], item, none);

    woothee_delete(woothee);
  }

  return 0;
}
