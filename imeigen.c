#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define RLEN sizeof(routers)/sizeof(routers[0])

int calc_digit(const char *number) {
    // Lookup table
    static const unsigned char LUT[20] = {
        // Double and reduce (0..9)
        0, 2, 4, 6, 8, 1, 3, 5, 7, 9,
        // Identity (10..19)
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    };

    int sum = 0;
    int len = strlen(number);

    for (int i = 0; i < len; i++) {
        int digit = number[len - 1 - i] - '0';
        // Index to LUT depends on whether i is even or odd
        sum += LUT[((i & 1) == 0 ? 0 : 10) + digit];
    }

    int check = 10 - (sum % 10);
    return (check == 10) ? 0 : check;
}

void drop_slashes(char* in) {
    char *pos;

    while ((pos = strstr(in, "\\\\")) != NULL) {
        memmove(pos, pos+1, strlen(pos)+1);
    }
}

int main(int argc, char **argv) {
    unsigned int i, check_digit;
    size_t router, ii;
    int len = 8;
    char number[16] = {0};

    static char *routers[][7] =
    {
        {"^MW45AN_[0-9A-F]{4}$",                                     "8", "35042693", NULL},
        {"^MobileRouter-[0-9A-F]{4}$",                               "8", "35066291", NULL},
        {"^AIS 4G Hi-Speed Home WiFi_[0-9]{6}$",                     "8", "35100755", NULL},
        {"^MW45V_[0-9A-F]{4}$",                                      "8", "35143020", NULL},
        {"^MTS874FT_[0-9A-F]{4}$",                                   "8", "35162910", NULL},
        {"^VINNWiFi_[0-9A-F]{4}$",                                   "8", "35178309", "35784508", NULL},
        {"^Optus E583C [0-9a-f]{4}$",                                "8", "35219704", NULL},
        {"^MTS850FT-[0-9A-F]{4}$",                                   "8", "35216407", NULL},
        {"^BeelineS23_[0-9A-F]{4}$",                                 "8", "35232010", NULL},
        {"^pocketwifi-[0-9a-f]{4}$",                                 "8", "35239804", "35730904", NULL},
        {"^VIVACOM 4G WiFi_[0-9A-F]{4}$",                            "8", "35240810", NULL},
        {"^MW40V_[0-9A-F]{4}$",                                      "8", "35249110", "35342609", "35647811", "35724307", NULL},
        {"^AIS4G Hispeed Pocketwifi_[0-9]{5}$",                      "8", "35252147", NULL},
        {"^Airtel 4G MiFi_[0-9A-F]{4}$",                             "8", "35271710", NULL},
        {"^MegaFonMR150-6_[0-9A-F]{4}$",                             "8", "35274110", "35742110", NULL},
        {"^SVITIN-[0-9A-F]{4}$",                                     "8", "35343011", NULL},
        {"^MegaFonMR150-7_[0-9A-F]{4}$",                             "8", "35352957", NULL},
        {"^MTN MiFi E5830S$",                                        "8", "35410303", NULL},
        {"^E5830-[0-9a-f]{4}$",                                      "8", "35410303", NULL},
        {"^MTS8920FT_[0-9A-F]{4}(_plus)?$",                          "8", "35477311", NULL},
        {"^XLGO-[0-9A-F]{4}$",                                       "8", "35497206", NULL},
        {"^BeelineSM25_[0-9A-F]{4}$",                                "8", "35595810", NULL},
        {"^MTS81020FTPB_[0-9A-F]{4}$",                               "8", "35622911", NULL},
        {"^MW70VK_[0-9A-F]{4}_(2\\.4G|5G)$",                         "8", "35700709", NULL},
        {"^MTS81231FT_[0-9A-F]{4}$",                                 "8", "35705982", NULL},
        {"^MTS81220FT_[0-9A-F]{4}$",                                 "8", "35717577", NULL},
        {"^MobileWiFi-[0-9a-f]{4}$",                                 "8", "35750304", "86361901", NULL},
        {"^Optus E586 [0-9a-f]{4}$",                                 "8", "35750604", NULL},
        {"^SMC062_[0-9A-F]{6}$",                                    "10", "35774140", NULL},
        {"^congstar\\.home_[0-9A-F]{4}(_2\\.4G|_5G)?(_Ext|_EXT)?$",  "8", "35834210", "35848108", NULL},
        {"^HH71VM_[0-9A-F]{4}_(2\\.4G|5G)$",                         "8", "35834210", NULL},
        {"^MTS872FT_[0-9A-F]{4}$",                                   "8", "35844809", NULL},
        {"^HH40V_[0-9A-F]{4}$",                                      "8", "35848108", NULL},
        {"^MTS8723FT_[0-9A-F]{4}$",                                  "8", "35861510", NULL},
        {"^Beeline_[0-9A-F]{4}$",                                    "8", "35978707", NULL},
        {"^AIS 4G Pocket Wifi_[0-9]{6}$",                            "8", "35986513", "86207503", NULL},
        {"^4G-Gateway-[0-9A-F]{4}$",                                 "8", "86009102","86803100", NULL},
        {"^MTS81330FT_[0-9A-F]{4}$",                                 "8", "86013005", NULL},
        {"^OptusWiFi E5331 [0-9a-f]{4}$",                            "8", "86066701", NULL},
        {"^inwi Home 4G [0-9A-F]{6}$",                               "8", "86074303", "86658004", NULL},
        {"^BOX4G_Inwi_[0-9A-F]{4}$",                                 "8", "86127405", "86857205", NULL},
        {"^Andromax-M3Y-[0-9A-F]{4}$",                               "8", "86145803", NULL},
        {"^MTS8330FT_[0-9A-F]{6}$",                                  "8", "86176605", NULL},
        {"^Globe_LTE MIFI_[0-9A-F]{4}$",                             "8", "86207503", NULL},
        {"^MTS8213FT-[0-9A-F]{4}$",                                  "8", "86241803", NULL},
        {"^Orange Airbox-[0-9A-F]{4}$",                              "8", "86259802", "86395503", "86742202", NULL},
        {"^OLAX_LTE_[0-9]{4}$",                                      "8", "86275506", NULL},
        {"^My Broadband-[0-9a-f]{4}$",                               "8", "86303001", NULL},
        {"^MTS835FT?_[0-9A-F]{6}$",                                  "8", "86307403", NULL},
        {"^Connect4G$",                                             "11", "86316801", NULL},
        {"^MTS837F_[0-9A-F]{6}$",                                    "8", "86357703", NULL},
        {"^TP-LINK_M5360_[0-9A-F]{6}$",                              "8", "86382402", NULL},
        {"^MTS81140FT_[0-9A-F]{4}$",                                 "8", "86386605", NULL},
        {"^VIVACOM 4G WI-FI$",                                       "8", "86398103", NULL},
        {"^TP-LINK_M5350_[0-9A-F]{6}$",                              "8", "86401101", NULL},
        {"^MTS831_[0-9A-F]{6}$",                                     "8", "86415402", NULL},
        {"^ALTEL4G-[0-9A-F]{4}(_5G)?$",                              "8", "86420805", NULL},
        {"^Domino-[0-9A-F]{4}$",                                     "8", "86434052", "86637701", NULL},
        {"^MTS838FT_[0-9A-F]{6}(_2\\.4Gz)?$",                        "8", "86477204", NULL},
        {"^VIVACOM 3G WI-FI$",                                       "8", "86570602", NULL},
        {"^MTS8430FT_[0-9A-F]{4}$",                                  "8", "86571004", NULL},
        {"^imotowifi[0-9A-F]{6}$",                                   "8", "86616703", NULL},
        {"^SMILE 4G LTE-[0-9A-F]{4}$",                               "8", "86616703", NULL},
        {"^ALTEL4G_[0-9A-F]{4}$",                                    "8", "86637403", "86848203", NULL},
        {"^ALTEL 4G_[0-9A-F]{7}$",                                   "8", "86650302", "86685501", NULL},
        {"^4GEEOnetouchY800z_[0-9A-F]{4}$",                          "8", "86681401", NULL},
        {"^HUAWEI-E5577-[0-9A-F]{4}$",                               "8", "86685202", NULL},
        {"^MTS833_[0-9A-F]{6}$",                                     "8", "86688302", NULL},
        {"^VIVA-4G-LTE-[0-9A-F]{4}$",                                "6", "86726202", NULL},
        {"^Orange-[0-9A-F]{4}$",                                     "8", "86726202", NULL},
        {"^501HWa-[0-9A-F]{6}$",                                     "7", "86738102", NULL},
        {"^CoolpadSurf_[0-9]{4}$",                                   "8", "86769504", NULL},
        {"^MTS8212FT_[0-9A-F]{4}$",                                  "8", "86796203", NULL},
        {"^inwi Home 4G[0-9A-F]{6}$",                                "8", "86846503", "86918004", NULL},
        {"^ZTE MF90+ [0-9A-F]{6}$",                                  "8", "86852702", NULL},
        {"^Coolpad Surf [0-9]{4} 2\\.4GHz$",                         "8", "86904004", NULL},
        {"^MTS411D_[0-9A-F]{4}$",                                    "8", "86996400", NULL},
        {"^MTS835FT_[0-9A-F]{6}$",                                   "8", "86998103", NULL},
        {NULL}
    };

    regex_t cregex[RLEN];

    if (argc <= 1) {
        printf("IMEIgen v0.1 (c) Alex Stanev <alex@stanev.org>\n");
        printf("Usage: %s [[8-digit TAC|SSID] [right digits count, default 8] | list | all]\n", *argv);
        exit(1);
    }

    if (argc == 2 && strcmp(argv[1], "list") == 0) {
        for (router=0; router<RLEN-1; router++) {
            drop_slashes(routers[router][0]);
            printf("%s\t%s\n", routers[router][0], routers[router][1]);
        }

        exit(0);
    }

    if (argc == 2 && strcmp(argv[1], "all") == 0) {
        for (router=0; router<RLEN-1; router++) {
            len = atoi(routers[router][1]);
            if (len < 8) continue;
            for (ii=2; ii<sizeof(routers[0]); ii++) {
                if (routers[router][ii] == NULL) break;
                for (i=0; i<1000000; i++) {
                    sprintf(number, "%s%06d", routers[router][ii], i);
                    check_digit = calc_digit(number);
                    printf("%s%d\n", number + 15 - len, check_digit);
                }
            }
        }

        exit(0);
    }

    if (argc == 3) {
        len = atoi(argv[2]);
        if (len < 1 || len > 15) {
            printf("digit count must be between 1 and 15!\n");
            exit(1);
        }
    }

    if (strspn(argv[1], "0123456789") == strlen(argv[1])) {
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
        // compile regex
        for (i=0; i<RLEN-1; i++) {
            regcomp(&cregex[i], routers[i][0], REG_EXTENDED);
        }

        for (router=0; router<RLEN-1; router++) {
            if (regexec(&cregex[router], argv[1], 0, NULL, 0) == 0) break;
        }

        // free compiled regex
        for (i=0; i<RLEN-1; i++) {
            regfree(&cregex[i]);
        }

        if (router == RLEN-1) {
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
