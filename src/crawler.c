#include "crawler.h"
#include "dataset.h"
#include "util.h"

int
woothee_crawler_challenge_google(const char *ua, woothee_t *result)
{
  if (strstr(ua, "Google") == NULL) {
    return 0;
  }

  if (strstr(ua, "Googlebot") != NULL) {
    if (strstr(ua, "Googlebot-Mobile") != NULL) {
      woothee_update(result, woothee_dataset_get(GoogleBotMobile));
      return 1;
    } else {
      woothee_update(result, woothee_dataset_get(GoogleBot));
      return 1;
    }
  }

  if (strstr(ua, "Googlebot-Image/") != NULL) {
    woothee_update(result, woothee_dataset_get(GoogleBot));
    return 1;
  }

  if (strstr(ua, "Mediapartners-Google") != NULL) {
    if (strstr(ua, "compatible; Mediapartners-Google") != NULL
        || strncmp(ua, "Mediapartners-Google", 20) == 0) {
      woothee_update(result, woothee_dataset_get(GoogleMediaPartners));
      return 1;
    }
  }

  if (strstr(ua, "Feedfetcher-Google") != NULL) {
    woothee_update(result, woothee_dataset_get(GoogleFeedFetcher));
    return 1;
  }

  if (strstr(ua, "AppEngine-Google") != NULL) {
    woothee_update(result, woothee_dataset_get(GoogleAppEngine));
    return 1;
  }

  if (strstr(ua, "Google Web Preview") != NULL) {
    woothee_update(result, woothee_dataset_get(GoogleWebPreview));
    return 1;
  }

  return 0;
}

int
woothee_crawler_challenge_crawlers(const char *ua, woothee_t *result)
{
  if (strstr(ua, "Yahoo") != NULL
      || strstr(ua, "help.yahoo.co.jp/help/jp/") != NULL
      || strstr(ua, "listing.yahoo.co.jp/support/faq/") != NULL) {
    if (strstr(ua, "compatible; Yahoo! Slurp") != NULL) {
      woothee_update(result, woothee_dataset_get(YahooSlurp));
      return 1;
    }
    if (strstr(ua, "YahooFeedSeekerJp") != NULL
        || strstr(ua, "YahooFeedSeekerBetaJp") != NULL) {
      woothee_update(result, woothee_dataset_get(YahooJP));
      return 1;
    }
    if (strstr(ua, "crawler (http://listing.yahoo.co.jp/support/faq/") != NULL
        || strstr(ua, "crawler (http://help.yahoo.co.jp/help/jp/") != NULL) {
      woothee_update(result, woothee_dataset_get(YahooJP));
      return 1;
    }
    if (strstr(ua, "Y!J-BRZ/YATSHA crawler") != NULL
        || strstr(ua, "Y!J-BRY/YATSH crawler") != NULL) {
      woothee_update(result, woothee_dataset_get(YahooJP));
      return 1;
    }
    if (strstr(ua, "Yahoo Pipes") != NULL) {
      woothee_update(result, woothee_dataset_get(YahooPipes));
      return 1;
    }
  }
  if (strstr(ua, "msnbot") != NULL) {
    woothee_update(result, woothee_dataset_get(msnbot));
    return 1;
  }
  if (strstr(ua, "bingbot") != NULL) {
    if (strstr(ua, "compatible; bingbot") != NULL) {
      woothee_update(result, woothee_dataset_get(bingbot));
      return 1;
    }
  }
  if (strstr(ua, "Baidu") != NULL) {
    if (strstr(ua, "compatible; Baiduspider") != NULL
        || strstr(ua, "Baiduspider+") != NULL
        || strstr(ua, "Baiduspider-image+") != NULL) {
      woothee_update(result, woothee_dataset_get(Baiduspider));
      return 1;
    }
  }
  if (strstr(ua, "Yeti") != NULL) {
    if (strstr(ua, "http://help.naver.com/robots") != NULL) {
      woothee_update(result, woothee_dataset_get(Yeti));
      return 1;
    }
  }
  if (strstr(ua, "FeedBurner/") != NULL) {
    woothee_update(result, woothee_dataset_get(FeedBurner));
    return 1;
  }
  if (strstr(ua, "facebookexternalhit") != NULL) {
    woothee_update(result, woothee_dataset_get(facebook));
    return 1;
  }
  if (strstr(ua, "Twitterbot/") != NULL) {
    woothee_update(result, woothee_dataset_get(twitter));
    return 1;
  }
  if (strstr(ua, "ichiro") != NULL) {
    if (strstr(ua, "http://help.goo.ne.jp/door/crawler.html") != NULL
        || strstr(ua, "compatible; ichiro/mobile goo;") != NULL) {
      woothee_update(result, woothee_dataset_get(goo));
      return 1;
    }
  }
  if (strstr(ua, "gooblogsearch/") != NULL) {
    woothee_update(result, woothee_dataset_get(goo));
    return 1;
  }
  if (strstr(ua, "Apple-PubSub") != NULL) {
    woothee_update(result, woothee_dataset_get(ApplePubSub));
    return 1;
  }
  if (strstr(ua, "(www.radian6.com/crawler)") != NULL) {
    woothee_update(result, woothee_dataset_get(radian6));
    return 1;
  }
  if (strstr(ua, "Genieo/") != NULL) {
    woothee_update(result, woothee_dataset_get(Genieo));
    return 1;
  }
  if (strstr(ua, "labs.topsy.com/butterfly/") != NULL) {
    woothee_update(result, woothee_dataset_get(topsyButterfly));
    return 1;
  }
  if (strstr(ua, "rogerbot/1.0 (http://www.seomoz.org/dp/rogerbot") != NULL) {
    woothee_update(result, woothee_dataset_get(rogerbot));
    return 1;
  }
  if (strstr(ua, "compatible; AhrefsBot/") != NULL) {
    woothee_update(result, woothee_dataset_get(AhrefsBot));
    return 1;
  }
  if (strstr(ua, "livedoor FeedFetcher") != NULL
      || strstr(ua, "Fastladder FeedFetcher") != NULL) {
    woothee_update(result, woothee_dataset_get(livedoorFeedFetcher));
    return 1;
  }
  if (strstr(ua, "Hatena ") != NULL) {
    if (strstr(ua, "Hatena Antenna") != NULL
        || strstr(ua, "Hatena Pagetitle Agent") != NULL
        || strstr(ua, "Hatena Diary RSS") != NULL) {
      woothee_update(result, woothee_dataset_get(Hatena));
      return 1;
    }
  }
  if (strstr(ua, "mixi-check") != NULL
      || strstr(ua, "mixi-crawler") != NULL
      || strstr(ua, "mixi-news-crawler") != NULL) {
    woothee_update(result, woothee_dataset_get(mixi));
    return 1;
  }
  if (strstr(ua, "Indy Library") != NULL) {
    if (strstr(ua, "compatible; Indy Library") != NULL) {
      woothee_update(result, woothee_dataset_get(IndyLibrary));
      return 1;
    }
  }

  return 0;
}

int
woothee_crawler_challenge_maybe_crawler(const char *ua, woothee_t *result)
{
  if (woothee_match("(bot|crawler|spider)(?:[-_ ./;@()]|$)", 1, ua)) {
    woothee_update(result, woothee_dataset_get(VariousCrawler));
    return 1;
  }

  if (woothee_match(
        "(?:Rome Client |UnwindFetchor/|ia_archiver |Summify |PostRank/)",
        0, ua)
      || strstr(ua, "ASP-Ranker Feed Crawler") != NULL) {
    woothee_update(result, woothee_dataset_get(VariousCrawler));
    return 1;
  }

  if (woothee_match("(feed|web) ?parser", 1, ua)) {
    woothee_update(result, woothee_dataset_get(VariousCrawler));
    return 1;
  }

  if (woothee_match("watch ?dog", 1, ua)) {
    woothee_update(result, woothee_dataset_get(VariousCrawler));
    return 1;
  }

  return 0;
}
