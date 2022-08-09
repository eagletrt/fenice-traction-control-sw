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
To compile this software you need to clone the repo and run the `all` Makefile recipe.

1. SSH into the RPi
2. Run `git clone git@github.com:eagletrt/fenice-traction-control-sw.git`
    - If the repo is still private, you'll need to register the RPi's ssh key in your Github settings to gain remote access
3. `cd` into the repo
4. Before compiling, you need to include the Matlab code of the models:
    - Option one is to pull the `fenice-vehicle-model` submodule, but it's extremely heavy (~1Gb) and you only need a dozen of files from it (sborerebbe solo l'RPi per la minchia)
    - Option two is copying over the needed files via `scp` from a local computer (or `rsync`, but `scp` comes automatically with the ssh package). Therefore, clone said repo in your PC and transfer the files with `scp -r fenice-vehicle-model/C_code tc@192.168.1.104:/home/tc/fenice-traction-control-sw/fenice-vehicle-model/C_code`
4. Run `make all`
    - If the Makefile hasn't done this for you (it should have), also pull the `micro-libs` submodule into its folder with `git submodule update micro-libs`.
    - Don't run `git submodule update` without also specifying `micro-libs` otherwise it will pull the matlab bloat from the other submodule too
5. In the `build` folder you should now have:
    - The main binary: `fenice-traction-control`
    - The velocity estimation dynamic library: `libctrl-ve.so`
    - The four dynamic libs for the models: `libctrl-{no,sc,tc,all}.so`
    - A binary that loads the models and tests them with the CSVs from the `test-data` folder: `test-models`

### Exeution
To execute the binary, `cd` into the build folder and run `./fenice-traction-control`. Note that you need to call the binary from within its folder otherwise it won't find the dynamic libraries.

At the end, if you need to analyze or gather control data, use `scp` to copy back the log files it produced (`build/*.csv`) otherwise at shoutdown they will be lost.