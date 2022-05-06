# Operating System
In order to obtain maximum performance from the small RPi's CPU, the OS needs to be as lightweight as possible, and needs to support nothing more that a C compiler and serial communication. **Core Linux** is a distro that ships just a kernel and some core utilities in under 20Mb. Also, it runs completely from RAM, therefore strongly limiting the possibility of failure from SD card wear.

## Step 1: Download
Go to Core Linux's home page and download the Raspberry Pi port, called **PiCore**: [http://www.tinycorelinux.net](http://www.tinycorelinux.net/). If you're not familiar with operating on this type of stripped-down OS, read the booklet or the wiki, both accessible from their website.

## Step 2: Flash The OS
Insert an SD card and flash PiCore with `dd`:

    sudo dd if=piCore-13.1.0.img of=/dev/mmcblk0

## Step 3: Extend SD Partition
By default the storage partition is rather small, so in order to accomodate GCC and other extensions we need to expand it to the full available size:

- Boot the RPi and log in with user `tc` and password `piCore`
- Run `fdisk /dev/mmcblk0` as root
    - Print existing partitions with `p` and take note of the starting cylinder of the second partition
    - Delete the second partition with `d` and recreate it with `n`
    - Use the same starting cylinder as the old partition and maximum available size
    - Write the partition table with `w`
- Reboot to make the kernel aware of the changes
- Now resize the existing filesystem to fill the partition with `resize2fs /dev/mmcblk0p2`

## Step 4: Configure Linux
- First, set a password that everyone working on the project can remember easily with `passwd`, like `sborato`.
- Since Core runs completely in RAM, such changes won't normally remain after boot, so to make them permanent we need to instruct `filetool` to backup and restore some files across reboots. To do so, just add their path to `/opt/.filetool.lst` and trigger a backup by calling `filetool.sh -b`. In this case, we need to run `echo '/etc/shadow' >> /opt/.filetool.lst` and trigger the backup.

## Setp 5: Configure SSH
- If it's not already installed, run `tce-load -wi openssh`.
- To autostart it at every boot, add it to the startup script with `sudo echo '/usr/local/etc/init.d/openssh start &' >> /opt/bootlocal.sh`
- Since the filesystem is not persistent, the encryption keys are lost and regenerated at every boot. To make them permanent, add them to the filetool list with `sudo echo '/usr/local/etc/ssh' >> /opt/.filetool.lst`
- Trigger the backup with `filetool.sh -b`

## Step 6: Disable Bluetooth to Access The Primary UART
In RPis with embedded Bluetooth and WiFi, the primary UART is connected to those modules and cannot be used by the user. To remedy that, add `dt-overlay=diable-bt` and `enable_uart=1` to `/boot/config.txt`. Now, a device named `/dev/ttyAMA0` will be available to the user to access the serial interface.
