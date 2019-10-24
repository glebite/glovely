avrdude -p m2560 -c wiring -P /dev/ttyUSB0 -b 115200 -F -U flash:w:glovely.hex:i -D
