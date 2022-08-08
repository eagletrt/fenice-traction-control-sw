# Fenice Traction Control Software
This software runs on the Raspberry Pi that communicates with the DAS via UART to handle traction control.

The setup is divided in three steps:

- RPi setup
- Software compilation
- Software execution


### RPi Setup

##### Install TinyCore Linux

- Default user is `tc` and password is `piCore`
- Set password to `sborato` with `passwd`
- Since TC runs completely in RAM, changes are made permanent by editing `/opt/.filetool.lst` (a list of files to backup before shutdown and restore after boot). Make the password change permanent with `sudo echo '/etc/shadow' >> /opt/.filetool.lst`
- Trigger the backup with `filetool.sh -b`

##### Install GCC, Make etc
...

##### Configure SSH

- If it's not already installed, run `tce-load -wi openssh`
- To autostart it at every boot edit the startup script `sudo echo '/usr/local/etc/init.d/openssh start &' >> /opt/bootlocal.sh`
- The SSH keys are lost and regenerated after every reboot. Add them to the filetool list with `sudo echo '/usr/local/etc/ssh' >> /opt/.filetool.lst`
- Trigger the backup with `filetool.sh -b`


### Compiling
Makefile and libraries, ...

### Exeution
RPi autostart, ...