# How to flash

I couldn't make `make flash` compile nor with `arduino` IDE.

What I did is to connect the keyboardio to the USB-C while pressing the key `PROG`, and:

``` sh
sudo dfu-util -l
make compile # generates /tmp/kaleidoscope-arnau/output/XXXX-Model100.ino/Model100.ino.bin
sudo dfu-util --device 0x3496:0x0005 -D /tmp/kaleidoscope-arnau/output/2189642165-Model100.ino/Model100.ino.bin -R
```
