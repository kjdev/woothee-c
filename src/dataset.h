#ifndef WOOTHEE_DATASET_H
#define WOOTHEE_DATASET_H

#include "woothee.h"

#define WOOTHEE_DATASET_VALUE_UNKNOWN "UNKNOWN"

typedef struct {
  char *name;
  char *type;
  char *category;
  char *os;
  char *vendor;
} woothee_data_t;

typedef struct {
  woothee_data_t MSIE;
  woothee_data_t Edge;
  woothee_data_t Chrome;
  woothee_data_t Safari;
  woothee_data_t Firefox;
  woothee_data_t Opera;
  woothee_data_t Sleipnir;
  woothee_data_t Webview;
  woothee_data_t Win;
  woothee_data_t Win10;
  woothee_data_t Win8_1;
  woothee_data_t Win8;
  woothee_data_t Win7;
  woothee_data_t WinVista;
  woothee_data_t WinXP;
  woothee_data_t Win2000;
  woothee_data_t WinNT4;
  woothee_data_t WinMe;
  woothee_data_t Win98;
  woothee_data_t Win95;
  woothee_data_t WinPhone;
  woothee_data_t WinCE;
  woothee_data_t OSX;
  woothee_data_t MacOS;
  woothee_data_t Linux;
  woothee_data_t BSD;
  woothee_data_t ChromeOS;
  woothee_data_t Android;
  woothee_data_t iPhone;
  woothee_data_t iPad;
  woothee_data_t iPod;
  woothee_data_t iOS;
  woothee_data_t FirefoxOS;
  woothee_data_t BlackBerry;
  woothee_data_t BlackBerry10;
  woothee_data_t docomo;
  woothee_data_t au;
  woothee_data_t SoftBank;
  woothee_data_t willcom;
  woothee_data_t jig;
  woothee_data_t emobile;
  woothee_data_t SymbianOS;
  woothee_data_t MobileTranscoder;
  woothee_data_t Nintendo3DS;
  woothee_data_t NintendoDSi;
  woothee_data_t NintendoWii;
  woothee_data_t NintendoWiiU;
  woothee_data_t PSP;
  woothee_data_t PSVita;
  woothee_data_t PS3;
  woothee_data_t PS4;
  woothee_data_t Xbox360;
  woothee_data_t XboxOne;
  woothee_data_t DigitalTV;
  woothee_data_t SafariRSSReader;
  woothee_data_t GoogleDesktop;
  woothee_data_t WindowsRSSReader;
  woothee_data_t VariousRSSReader;
  woothee_data_t HTTPLibrary;
  woothee_data_t GoogleBot;
  woothee_data_t GoogleBotMobile;
  woothee_data_t GoogleMediaPartners;
  woothee_data_t GoogleFeedFetcher;
  woothee_data_t GoogleAppEngine;
  woothee_data_t GoogleWebPreview;
  woothee_data_t YahooSlurp;
  woothee_data_t YahooJP;
  woothee_data_t YahooPipes;
  woothee_data_t Baiduspider;
  woothee_data_t msnbot;
  woothee_data_t bingbot;
  woothee_data_t Yeti;
  woothee_data_t FeedBurner;
  woothee_data_t facebook;
  woothee_data_t twitter;
  woothee_data_t mixi;
  woothee_data_t IndyLibrary;
  woothee_data_t ApplePubSub;
  woothee_data_t Genieo;
  woothee_data_t topsyButterfly;
  woothee_data_t rogerbot;
  woothee_data_t AhrefsBot;
  woothee_data_t radian6;
  woothee_data_t Hatena;
  woothee_data_t goo;
  woothee_data_t livedoorFeedFetcher;
  woothee_data_t VariousCrawler;
} woothee_dataset_t;

__attribute__ ((unused))
static woothee_dataset_t dataset = {
  .MSIE = {"Internet Explorer", "browser", NULL, NULL, "Microsoft"},
  .Edge = {"Edge", "browser", NULL, NULL, "Microsoft"},
  .Chrome = {"Chrome", "browser", NULL, NULL, "Google"},
  .Safari = {"Safari", "browser", NULL, NULL, "Apple"},
  .Firefox = {"Firefox", "browser", NULL, NULL, "Mozilla"},
  .Opera = {"Opera", "browser", NULL, NULL, "Opera"},
  .Sleipnir = {"Sleipnir", "browser", NULL, NULL, "Fenrir Inc."},
  .Webview = {"Webview", "browser", NULL, NULL, "OS vendor"},
  .Win = {"Windows UNKNOWN Ver", "os", "pc", NULL, NULL},
  .Win10 = {"Windows 10", "os", "pc", NULL, NULL},
  .Win8_1 = {"Windows 8.1", "os", "pc", NULL, NULL},
  .Win8 = {"Windows 8", "os", "pc", NULL, NULL},
  .Win7 = {"Windows 7", "os", "pc", NULL, NULL},
  .WinVista = {"Windows Vista", "os", "pc", NULL, NULL},
  .WinXP = {"Windows XP", "os", "pc", NULL, NULL},
  .Win2000 = {"Windows 2000", "os", "pc", NULL, NULL},
  .WinNT4 = {"Windows NT 4.0", "os", "pc", NULL, NULL},
  .WinMe = {"Windows Me", "os", "pc", NULL, NULL},
  .Win98 = {"Windows 98", "os", "pc", NULL, NULL},
  .Win95 = {"Windows 95", "os", "pc", NULL, NULL},
  .WinPhone = {"Windows Phone OS", "os", "smartphone", NULL, NULL},
  .WinCE = {"Windows CE", "os", "smartphone", NULL, NULL},
  .OSX = {"Mac OSX", "os", "pc", NULL, NULL},
  .MacOS = {"Mac OS Classic", "os", "pc", NULL, NULL},
  .Linux = {"Linux", "os", "pc", NULL, NULL},
  .BSD = {"BSD", "os", "pc", NULL, NULL},
  .ChromeOS = {"ChromeOS", "os", "pc", NULL, NULL},
  .Android = {"Android", "os", "smartphone", NULL, NULL},
  .iPhone = {"iPhone", "os", "smartphone", NULL, NULL},
  .iPad = {"iPad", "os", "smartphone", NULL, NULL},
  .iPod = {"iPod", "os", "smartphone", NULL, NULL},
  .iOS = {"iOS", "os", "smartphone", NULL, NULL},
  .FirefoxOS = {"Firefox OS", "os", "smartphone", NULL, NULL},
  .BlackBerry = {"BlackBerry", "os", "smartphone", NULL, NULL},
  .BlackBerry10 = {"BlackBerry 10", "os", "smartphone", NULL, NULL},
  .docomo = {"docomo", "full", "mobilephone", "docomo", "docomo"},
  .au = {"au by KDDI", "full",  "mobilephone", "au", "au"},
  .SoftBank = {"SoftBank Mobile", "full",  "mobilephone", "SoftBank", "SoftBank"},
  .willcom = {"WILLCOM", "full", "mobilephone", "WILLCOM", "WILLCOM"},
  .jig = {"jig browser", "full",  "mobilephone", "jig", NULL},
  .emobile = {"emobile", "full", "mobilephone", "emobile", NULL},
  .SymbianOS = {"SymbianOS", "full", "mobilephone", "SymbianOS", NULL},
  .MobileTranscoder = {"Mobile Transcoder", "full", "mobilephone", "Mobile Transcoder", NULL},
  .Nintendo3DS = {"Nintendo 3DS", "full", "appliance", "Nintendo 3DS", "Nintendo"},
  .NintendoDSi = {"Nintendo DSi", "full", "appliance", "Nintendo DSi", "Nintendo"},
  .NintendoWii = {"Nintendo Wii", "full", "appliance", "Nintendo Wii", "Nintendo"},
  .NintendoWiiU = {"Nintendo Wii U", "full", "appliance", "Nintendo Wii U", "Nintendo"},
  .PSP = {"PlayStation Portable", "full", "appliance", "PlayStation Portable", "Sony"},
  .PSVita = {"PlayStation Vita", "full", "appliance", "PlayStation Vita", "Sony"},
  .PS3 = {"PlayStation 3", "full", "appliance", "PlayStation 3", "Sony"},
  .PS4 = {"PlayStation 4", "full", "appliance", "PlayStation 4", "Sony"},
  .Xbox360 = {"Xbox 360", "full", "appliance", "Xbox 360", "Microsoft"},
  .XboxOne = {"Xbox One", "full", "appliance", "Xbox One", "Microsoft"},
  .DigitalTV = {"InternetTVBrowser", "full", "appliance", "DigitalTV", NULL},
  .SafariRSSReader = {"Safari RSSReader", "full", "misc", NULL, "Apple"},
  .GoogleDesktop = {"Google Desktop", "full", "misc", NULL, "Google"},
  .WindowsRSSReader = {"Windows RSSReader", "full", "misc", NULL, "Microsoft"},
  .VariousRSSReader = {"RSSReader", "full", "misc", NULL, NULL},
  .HTTPLibrary = {"HTTP Library", "full", "misc", NULL, NULL},
  .GoogleBot = {"Googlebot", "full", "crawler", NULL, NULL},
  .GoogleBotMobile = {"Googlebot Mobile", "full", "crawler", NULL, NULL},
  .GoogleMediaPartners = {"Google Mediapartners", "full", "crawler", NULL, NULL},
  .GoogleFeedFetcher = {"Google Feedfetcher", "full", "crawler", NULL, NULL},
  .GoogleAppEngine = {"Google AppEngine", "full", "crawler", NULL, NULL},
  .GoogleWebPreview = {"Google Web Preview", "full", "crawler", NULL, NULL},
  .YahooSlurp = {"Yahoo! Slurp", "full", "crawler", NULL, NULL},
  .YahooJP = {"Yahoo! Japan", "full", "crawler", NULL, NULL},
  .YahooPipes = {"Yahoo! Pipes", "full", "crawler", NULL, NULL},
  .Baiduspider = {"Baiduspider", "full", "crawler", NULL, NULL},
  .msnbot = {"msnbot", "full", "crawler", NULL, NULL},
  .bingbot = {"bingbot", "full", "crawler", NULL, NULL},
  .Yeti = {"Naver Yeti", "full", "crawler", NULL, NULL},
  .FeedBurner = {"Google FeedBurner", "full", "crawler", NULL, NULL},
  .facebook = {"facebook", "full", "crawler", NULL, NULL},
  .twitter = {"twitter", "full", "crawler", NULL, NULL},
  .mixi = {"mixi", "full", "crawler", NULL, NULL},
  .IndyLibrary = {"Indy Library", "full", "crawler", NULL, NULL},
  .ApplePubSub = {"Apple iCloud", "full", "crawler", NULL, NULL},
  .Genieo = {"Genieo Web Filter", "full", "crawler", NULL, NULL},
  .topsyButterfly = {"topsy Butterfly", "full", "crawler", NULL, NULL},
  .rogerbot = {"SeoMoz rogerbot", "full", "crawler", NULL, NULL},
  .AhrefsBot = {"ahref AhrefsBot", "full", "crawler", NULL, NULL},
  .radian6 = {"salesforce radian6", "full", "crawler", NULL, NULL},
  .Hatena = {"Hatena", "full", "crawler", NULL, NULL},
  .goo = {"goo", "full", "crawler", NULL, NULL},
  .livedoorFeedFetcher = {"livedoor FeedFetcher", "full", "crawler", NULL, NULL},
  .VariousCrawler = {"misc crawler", "full", "crawler", NULL, NULL}
};

#define woothee_dataset_get(name) &dataset.name

#endif
