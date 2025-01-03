# How to flash

`make flash` errors

```
To update your keyboard's firmware, hold down the 'Prog' key on your keyboard. (When flashing starts, you can release it.) ***If you are upgrading from the factory firmware or a build from before October 2022, disconnect your Model 100 from the computer and hold down the 'Prog' key while plugging it back in.***

When you're ready to proceed, press 'Enter'.


Skipping 1200-bps touch reset: no serial port selected!
dfu-util 0.11

Copyright 2005-2009 Weston Schmidt, Harald Welte and OpenMoko Inc.
Copyright 2010-2021 Tormod Volden and Stefan Schmidt
This program is Free Software and has ABSOLUTELY NO WARRANTY
Please report bugs to http://sourceforge.net/p/dfu-util/tickets/

dfu-util: Cannot open DFU device 3496:0005 found on devnum 28 (LIBUSB_ERROR_ACCESS)
dfu-util: No DFU capable USB device available
Failed uploading: uploading error: exit status 74
make: *** [/home/arnau/projects/Kaleidoscope/etc/makefiles/sketch.mk:204: flash] Error 1
```

The workaround is to connect the USB to the Keyboardio Model100 while pressing the key `PROG` and then

```sh
sudo dfu-util -l
make compile # generates /tmp/kaleidoscope-arnau/output/XXXX-Model100.ino/Model100.ino.bin
sudo dfu-util --device 0x3496:0x0005 -D /tmp/kaleidoscope-arnau/output/2189642165-Model100.ino/Model100.ino.bin -R
```
