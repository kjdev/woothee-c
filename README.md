# Woothee C

The C implementation of Project Woothee, which is multi-language user-agent
strings parsers.

https://github.com/woothee/woothee

## Installation

```
$ make
$ make test
$ make install
```

> requires pcre library

## Usage

### Parsing user-agent

``` c
#include <woothee/woothee.h>

int main() {
  woothee_t *woothee = woothee_parse("user agent string");

  woothee->name;
  // => name of browser (or string like name of user-agent)

  woothee->category;
  // => "pc", "smartphone", "mobilephone", "appliance", "crawler", "misc", "unknown"

  woothee->os;
  // => os from user-agent, or carrier name of mobile phones

  woothee->version;
  // => version of browser, or terminal type name of mobile phones

  woothee->os_version;
  // => version of operating systems (for some typical cases)

  woothee_delete(woothee);

  return 0;
}
```

Parse user-agent string and returns struct with keys `name`, `category`, `os`,
`version`, `os_version` and `vendor`.

For unknown user-agent (or partially failed to parse),
result may have value 'UNKNOWN'.

* `category`
  * labels of user terminal type, one of 'pc', 'smartphone', 'mobilephone',
    'appliance', 'crawler' or 'misc' (or 'UNKNOWN')
* `name`
  * the name of browser, like 'Internet Explorer', 'Firefox', 'GoogleBot'
* `version`
  * version string, like '8.0' for IE, '9.0.1' for Firefix,
    '0.2.149.27' for Chrome, and so on
* `os`
  * ex: 'Windows 7', 'Mac OSX', 'iPhone', 'iPad', 'Android'
  * This field used to indicate cellar phone carrier for category 'mobilephone'
* `vendor`
  * optional field, shows browser vendor
* `os_version`
  * optional field, shows version of operating systems

### Finding crawlers (almost all, not all) in fast

``` c
woothee_is_crawler("Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; Trident/4.0)");
// => 0
```

### Compile in woothee library

Create example code.

``` c
/* example.c */

#include <stdio.h>
#include <woothee/woothee.h>

int main(int argc, char **argv) {
  if (argc > 1) {
    woothee_t *woothee = woothee_parse(argv[1]);

    printf("name = %s\n", woothee->name);

    woothee_delete(woothee);
  }
  return 0;
}
```

Compile example code.

```
$ gcc -o example example.c `pkg-config --cflags --libs woothee`
```

Execute example.

```
$ ./example "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; Trident/4.0)"
name = Internet Explorer
```
