#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int calc_digit(char *number)
{
    int i, sum, ch, num, twoup, len;

    len = strlen(number);
    sum = 0;
    twoup = 1;

    for (i = len - 1; i >= 0; --i) {
        ch = number[i];
        num = (ch >= '0' && ch <= '9') ? ch - '0' : 0;
        if (twoup) {
            num += num;
            if (num > 9) num = (num % 10) + 1;
        }

        sum += num;
        twoup = (twoup+1) & 1;
    }
    sum = 10 - (sum % 10);
    if (sum == 10) sum = 0;
    return sum;
}

int isdigit_str(char *str)
{
    int i;

    for (i=0; i<strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char **argv)
{
    int i, ii, check_digit, router;
    int len = 8;
    char number[16] = {0};

    static const char *routers[][5] =
    {
        {"VINNWiFi",         "8", "35178309", NULL},
        {"BeelineS23",       "8", "35232010", NULL},
        {"pocketwifi-",      "8", "35239804", "35730904", NULL},
        {"VIVACOM 4G WiFi",  "8", "35240810", NULL},
        {"MegaFonMR150-6_",  "8", "35274110", "35742110", NULL},
        {"MTN MiFi E5830S",  "8", "35410303", NULL},
        {"BeelineSM25",      "8", "35595810", NULL},
        {"MobileWiFi-",      "8", "35750304", NULL},
        {"Beeline_",         "8", "35978707", NULL},
        {"OptusWiFi E5331",  "8", "86066701", NULL},
        {"Globe_LTE MIFI",   "8", "86066701", NULL},
        {"inwi Home 4G ",    "8", "86074303", "86658004", NULL},
        {"Andromax-M3Y-",    "8", "86145803", NULL},
        {"Orange Airbox-",   "8", "86259802", "86742202", NULL},
        {"My Broadband",     "8", "86303001", "86723101", NULL},
        {"Connect4G",       "11", "86316801", NULL},
        {"VIVACOM 4G WI-FI", "8", "86398103", NULL},
        {"Domino-",          "8", "86434052", "86637701", NULL},
        {"VIVACOM 3G WI-FI", "8", "86570602", NULL},
        {"VIVA-4G-LTE-",     "6", "86726202", NULL},
        {"501HWa",           "7", "86738102", NULL},
        {"4G-Gateway",       "8", "86803100", NULL},
        {"inwi Home 4G",     "8", "86846503", NULL},
        {NULL}
    };

    if (argc <= 1) {
        printf("IMEIgen v0.1 (c) Alex Stanev <alex@stanev.org>\n");
        printf("Usage: %s [8-digit TAC|SSID] [right digits count, default 8]\n", *argv);
        exit(1);
    }

    if (argc == 3) {
        len = atoi(argv[2]);
        if (len < 1 || len > 15) {
            printf("digit count must be between 1 and 15!\n");
            exit(1);
        } 
    }

    if (isdigit_str(argv[1])) {
        if (strlen(argv[1]) != 8) {
            printf("TAC must be with length 8!\n");
            exit(1);
        }

        for (i=0; i<1000000; i++) {
            sprintf(number, "%s%06d", argv[1], i);
            check_digit = calc_digit(number);
            printf("%s%d\n", number + 15 - len, check_digit);
        }
     } else {
        for (router=0; router<sizeof(routers)/sizeof(routers[0])-1; router++) {
            if (strncmp(routers[router][0], argv[1], strlen(routers[router][0])) == 0) break;
        }

        if (router == sizeof(routers)/sizeof(routers[0])-1) {
            printf("Unknown SSID!\n");
            exit(1);
        }

        len = atoi(routers[router][1]);
        for (ii=2; ii<sizeof(routers[0]); ii++) {
            if (routers[router][ii] == NULL) break;
            for (i=0; i<1000000; i++) {
                sprintf(number, "%s%06d", routers[router][ii], i);
                check_digit = calc_digit(number);
                printf("%s%d\n", number + 15 - len, check_digit);
            }
        }
     }
}
