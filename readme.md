# IMEIgen
Simple WPA-PSK default password candidates generator for mobile broadband WIFI routers, based on IMEI.

## Background
In their conquest of more users, some ISPs and vendors tend to trade security for ease of use.

Default WIFI router passwords often use some of the device-bound constants like WAN MAC address, BSSID, serial number, or combination from those. The developers invent some (not so)sophisticated obfuscation algorithms or hash functions to generate the default WPA-PSK password.

When the device has mobile broadband interface there is another constant - the [IMEI](https://en.wikipedia.org/wiki/International_Mobile_Equipment_Identity) number. In its general form IMEI has 15 digits with the following form:

| TAC      | Serial | Check digit |
| :------: | :----: | :---------: |
| TTTTTTTT | SSSSSS | C           |

When given device uses part of the IMEI for password and we know the *TAC* used, we can bruteforce 6-digit *Serial* and compute the *Check digit* with [Luhn algorithm](https://en.wikipedia.org/wiki/Luhn_algorithm). In most cases, where vendors use the last 8 digits of the IMEI, we can shrink the password candidates keyspace 100 times.

## Known devices
These devices were confirmed via various images, found on the Internet and validated against [wpa-sec](https://wpa-sec.stanev.org) submissions. Please note that some models phased out this insecure password generation in their latest revisions and there may be more TACs used.

| SSID mask | Model | TAC | Length | Notes |
| --------- | ----- | --- | :----: | ----- |
| MW45AN_XXXX | TCL/Alcatel MW45AN | 35042693 | 8 | |
| MW45V_XXXX | TCL/Alcatel MW45V | 35143020 | 8 | |
| VINNWiFi_XXXX[_5G] | TCL/Alcatel MW40V1 | 35178309 <br/> 35784508 | 8 | |
| BeelineS23_XXXX | Beeline S23 | 35232010 | 8 | |
| pocketwifi-xxxx | Huawei E585 | 35239804 <br/> 35730904 | 8 | |
| VIVACOM 4G WiFi_XXXX[_5G] | TCL/Alcatel MW40V1 | 35240810 | 8 | |
| MW40V_XXXX | TCL/Alcatel MW40V1 | 35249110 <br/> 35342609 <br/> 35647811 <br/> 35724307 | 8 | |
| MegaFonMR150-6_XXXX | WeWins MR150-6 | 35274110 <br/> 35742110 | 8 | |
| SVITIN-XXXX | WeWins M09 | 35343011 | 8 | |
| MTN MiFi E5830S | Huawei E5830S | 35410303 | 8 | |
| E5830-xxxx | Huawei E5830S | 35410303 | 8 | |
| MTS8920FT_XXXX[_plus] | WeWins MTS 8920FT | 35477311 | 8 | |
| XLGO-XXXX | MOVIMAX MV003 | 35497206 | 8 | |
| BeelineSM25_XXXX | Beeline SM25 | 35595810 | 8 | |
| MW70VK_XXXX_[2.4G\|5G] | TCL/Alcatel MW70VK | 35700709 | 8 | |
| MTS81231FT_XXXX | Vobis/Highscreen Limited MTS 81231FT | 35705982 | 8 | |
| MTS81220FT_XXXX | Vobis/Highscreen Limited MTS 81220FT | 35717577 | 8 | |
| MobileWiFi-xxxx | Huawei E560 | 35750304 | 8 | Used by Beeline |
| MTS8723FT_XXXX | Senseit MTS 8723FT | 35861510 | 8 | |
| Beeline_XXXX | Beeline L02H | 35978707 | 8 | |
| MTS81330FT_XXXX | Shenzhen Harvilon Technology MTS 81330FT | 86013005 | 8 | |
| OptusWiFi E5331 xxxx | Huawei E5531 | 86066701 | 8 | |
| Globe_LTE MIFI_XXXX | YOUWIN M022T | 86066701 | 8 | |
| inwi Home 4G XXXXXX | ZTE MF253V | 86074303 <br/> 86658004 | 8 | Note the space after 4G |
| Andromax-M3Y-XXXX | Smartfren M26Z1H | 86145803 | 8 | |
| Orange Airbox-XXXX | Huawei E5573 | 86259802 <br/> 86395503 <br/> 86742202 | 8 | |
| My Broadband-xxxx | Huawei E589 | 86303001 <br/> 86723101 | 8 | |
| Connect4G | Huawei B593 | 86316801 | 11 | |
| MTS81140FT_XXXX | Mobot Technology/Signalinks MTS 81140FT | 86386605 | 8 | |
| VIVACOM 4G WI-FI | Huawei E5573s-320 | 86398103 | 8 | |
| Domino-XXXX | Huawei E5327 / ZTE MF63 CU | 86434052 </br> 86637701 | 8 | Huawei model uncertain |
| MTS838FT_XXXXXX[_2.4Gz] | ZTE 838FT | 86477204 | 8 | |
| VIVACOM 3G WI-FI | Huawei E5330Bs-2 | 86570602 | 8 | |
| MTS8430FT_XXXX | Shenzhen ZhuiFengMa Technology Jiffma 8430FT MTS | 86571004 | 8 | |
| imotowifiXXXXXX | Shanghai Notion Information Technology | 86616703 | 8 | |
| HUAWEI-E5577-XXXX | Huawei E5577s-932 | 86685202 | 8 | The SSID matches with other Huawei router sub-model, which use different default key generation algorithm |
| VIVA-4G-LTE-XXXX | Huawei E5577Cs-321 | 86726202 | 6 | Prepend 'VIVA' to every candidate, eg. `sed 's/^/VIVA/'`. Practically doesn't reduce the keyspace |
| Orange-XXXX | Huawei E5577Cs-321 | 86726202 | 8 | The SSID matches with other Orange routers, which use different default key generation algorithms |
| 501HWa-XXXXXX | Huawei HWABJ1 | 86738102 | 7 | Append 'a' to every candidate, eg. `sed 's/$/a/'` |
| MTS8212FT_XXXX | Huawei B315s-22 | 86796203 | 8 | |
| 4G-Gateway-XXXX | Huawei B593 | 86803100 | 8 | |
| inwi Home 4GXXXXXX | Huawei B310s / Huawei B311-221 | 86846503 <br/> 86918004 | 8 | No space between 4G and the hex digits |
| ZTE MF90+ XXXXXX | ZTE MF90+ | 86852702 | 8 | |
| MTS411D_XXXX | TCT Mobile MTS 411D | 86852702 | 8 | |
| MTS835FT_XXXXXX | ZTE MTS 835FT | 86998103 | 8 | |

## Usage
```
$ git clone https://github.com/RealEnder/imeigen
$ cd imeigen
$ make
gcc -O3 -Wall -o imeigen imeigen.c
$ ./imeigen
IMEIgen v0.1 (c) Alex Stanev <alex@stanev.org>
Usage: ./imeigen [[8-digit TAC|SSID] [right digits count, default 8] | list]
```

Example usage with [hashcat](https://hashcat.net):
```
$ ./imeigen 35240810 | hashcat -a0 -m22000 vivacom.22000
$ ./imeigen 501HWa-123456 | sed 's/$/a/' | hashcat -a0 -m22000 501HWa.22000
```

You can extract the right hashes with the excellent [hcxtools](https://github.com/ZerBea/hcxtools):
```
$ hcxhashtool -i large_hashlist.22000 -o vivacom.22000 --essid-part "VIVACOM 4G WiFi"
```

ig-crack script is used to extract the supported networks from a large collection of m22000 hashes, which are then passed to hashcat for cracking using the password candidates from imeigen. It accounts for the special cases, used by some vendors.

## Contributing
Look at the label of your mobile broadband WIFI router and check if the default password is part of the IMEI. If this is the case and you can't find the device TAC on the list, please open an issue in this repository with the photo of the label. Many label photos can also be found on the Internet.

Submitting captures in [wpa-sec](https://wpa-sec.stanev.org) DB is another way to contribute to WIFI security research. We advise you to use [hcxdumptool](https://github.com/ZerBea/hcxdumptool) for best results.

## Tools
* [wpa-sec](https://wpa-sec.stanev.org) - distributed WPA-PSK cracker database
* [RouterKeygenPC](https://github.com/routerkeygen/routerkeygenPC) - default keys generators for various WIFI routers
* [hcxtools](https://github.com/ZerBea/hcxtools) - small set of tools to detect weak points within WIFI networks by analyzing hashes and captures. Take a look on hcxpsktool
* [hcxdumptool](https://github.com/ZerBea/hcxdumptool) - sophisticated WIFI attack tool