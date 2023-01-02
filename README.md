# thandor-reschanger
change Resolution for "Thandor - Die Invasion" to arbitary value eg. 1920x1080

## How to use

Copy `thandor-reschanger.exe` to the Thandor installation directory and double click on int.
You can also specify the path to the `thandor.dat` on the command line or drag the `thandor.dat` file on the `thandor-reschanger.exe`


## What it does

If no parameters are given, it opens the `thandor.dat` file, which contains your settings from the current *working directory*. If a parameter is given, it is used as the path to the configuration file instead.
Then it reads bytes 4-7, which contains the horizontal resolution, and bytes 8-11, which contain the vertical resolution in little endian.
After displaying the current resolution, it asks you for the new resolution and writes it back.
