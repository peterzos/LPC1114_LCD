Hardware:
- LPC-Link: LPC1114/301 
- LCD: HD44780 
- temp sensor:DS18B20

In case LPCXpresso does not recognize the LPC-Link "No compatible emulators available" take a look at
>https://www.lpcware.com/content/faq/lpcxpresso/booting-lpc-link

and enter the command:
>dfu-util -d 0x471:0xdf55 -c 0 -t 2048 -R -D LPCXpressoWIN.enc



