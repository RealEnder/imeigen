# IMEIgen
Simple WPA-PSK default password candidates generator for mobile broadband WIFI routers, based on IMEI.

## Background
In their conquest for more users, some ISPs and vendors tend to trade security for ease of use.

Default WIFI router passwords often use some of the device-bound constants like WAN MAC address, BSSID, serial number or combination from those. The developers invent some (not so)sophisticated obfuscation algorithms or hash functions to generate the default WPA-PSK password.

When the device has mobile broadband interface there is another constant - the [IMEI](https://en.wikipedia.org/wiki/International_Mobile_Equipment_Identity) number. In it's general form IMEI has 15 digits with the following form:

| TAC      | Serial | Check digit |
| :------: | :----: | :---------: |
| TTTTTTTT | SSSSSS | C           |

When given device uses part of the IMEI for password and we know the *TAC* used, we can bruteforce 6-digit *Serial* and compute the *Check digit* with [Luhn algorithm](https://en.wikipedia.org/wiki/Luhn_algorithm). In most cases, where vendors use the last 8 digits of the IMEI, we can shrink the password candidates keyspace 100 times.

## Known devices
These devices were confirmed via various images, found on Internet and validated against [wpa-sec](https://wpa-sec.stanev.org) submissions. Please note some models phased out this insecure password generation in their latest revisions and there may be more TACs used.

| SSID mask | Model | TAC | Length | Notes |
| --------- | ----- | --- | :----: | ----- |
| VINNWiFi_XXXX[_5G] | TCL/Alcatel MW40V1 | 35178309 | 8 | |
| BeelineS23_XXXX | Beeline S23 | 35232010 | 8 | |
| pocketwifi-xxxx | Huawei E585 | 35239804 <br/> 35730904 | 8 | |
| VIVACOM 4G WiFi_XXXX[_5G] | TCL/Alcatel MW40V1 | 35240810 | 8 | |
| MTN MiFi E5830S | Huawei E5830S | 35410303 | 8 | |
| BeelineSM25_XXXX | Beeline SM25 | 35595810 | 8 | |
| OptusWiFi E5331 xxxx | Huawei E5531 | 86066701 | 8 | |
| Globe_LTE MIFI_XXXX | YOUWIN M022T | 86066701 | 8 | |
| inwi Home 4G XXXXXX | ZTE MF253V | 86074303 <br/> 86658004 | 8 | Note the space after 4G |
| Orange Airbox-XXXX | Huawei E5573 | 86259802 <br/> 86742202 | 8 | |
| My Broadband-xxxx | Huawei E589 | 86303001 <br/> 86723101 | 8 | |
| Connect4G | Huawei B593 | 86316801 | 11 | |
| VIVACOM 4G WI-FI | Huawei E5573 | 86398103 | 8 | |
| 501HWa-XXXXXX | Huawei HWABJ1 | 86738102 | 7 | Add 'a' to every candidate, eg. `sed 's/$/a/'` |
| 4G-Gateway-XXXX | Huawei B593 | 86803100 | 8 | |
| inwi Home 4GXXXXXX | Huawei B310s | 86846503 | 8 | No space between 4G and hex digits |

## Usage
```
$ git clone https://github.com/RealEnder/imeigen
$ cd imeigen
$ make
gcc -O3 -Wall -o imeigen imeigen.c
$ ./imeigen
IMEIgen v0.1 (c) Alex Stanev <alex@stanev.org>
Usage: ./imeigen [8-digit TAC|SSID] [right digits count, default 8]
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

## Contributing
Look at the label of your mobile broadband WIFI router and check if the default password is part of the IMEI. If this is the case and you can't find the device TAC on the list, please open an issue in this repository with photo of the label. Many label photos can also be found on the Internet.

Submitting captures in [wpa-sec](https://wpa-sec.stanev.org) DB is another way to contribute to WIFI security research. We advise to use [hcxdumptool](https://github.com/ZerBea/hcxdumptool) for best results.

## Tools
* [wpa-sec](https://wpa-sec.stanev.org) - distributed WPA-PSK cracker database
* [RouterKeygenPC](https://github.com/routerkeygen/routerkeygenPC) - default keys generators for various WIFI routers
* [hcxtools](https://github.com/ZerBea/hcxtools) - small set of tools to detect weak points within WIFI networks by analyzing hashes and captures. Take a look on hcxpsktool
* [hcxdumptool](https://github.com/ZerBea/hcxdumptool) - sophisticated WIFI attack tool