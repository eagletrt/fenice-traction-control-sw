# Fenice Traction Control Software

This software runs on the Raspberry Pi that communicates with the DAS via UART to handle traction control.

The setup is divided in three steps:

- [RPi setup](#rpi-setup)
- [Software compilation](#compile-the-code)
- [Software execution](#execute-the-software)

## RPi Setup

### Install TinyCore Linux

- Default user is `tc` and password is `piCore`
- Set password to `sborato` with `passwd`
- Since TC runs completely in RAM, changes are made permanent by editing `/opt/.filetool.lst` (a list of files to backup before shutdown and restore after boot). Make the password change permanent with `sudo echo '/etc/shadow' >> /opt/.filetool.lst`
- Trigger the backup with `filetool.sh -b`

#### Install GCC, Make etc

...

#### Configure SSH

- If it's not already installed, run `tce-load -wi openssh`
- To autostart it at every boot edit the startup script `sudo echo '/usr/local/etc/init.d/openssh start &' >> /opt/bootlocal.sh`
- The SSH keys are lost and regenerated after every reboot. Add them to the filetool list with `sudo echo '/usr/local/etc/ssh' >> /opt/.filetool.lst`
- Trigger the backup with `filetool.sh -b`

## Compile the Code

To compile this software you need to clone the repo and run the `all` Makefile recipe.

1. SSH into the RPi
    - Username: `tc`
    - Password: `sborato`
2. Pull the code
    - If the repo is not already present, clone the repo

        ```
        git clone git@github.com:eagletrt/fenice-traction-control-sw.git
        ```

    - Otherwise, just `cd` into it and run `git pull`
3. Update the submodules (`micro-libs` and `fenice-vehicle-model`). \
    While the first submodule is small and could be pulled normally, the second contains the whole Matlab model which is massive. Since we only care about the `.c` files inside the `C_code` folder, what I usually do is pull the two modules on my machine and copy over only the relevant files with scp:
    - `git submodule init`
    - `git submodule update --remote --recursive`
    - `scp -r fenice-vehicle-model/C_code tc@controllo-sborato:/home/tc/fenice-traction-control-sw/fenice-vehicle-model/C_code`
    - `scp -r micro-libs tc@controllo-sborato:/home/tc/fenice-traction-control-sw`
4. Compile the code with `make all`
5. In the `build` folder you should now have:
    - The main binary: `fenice-traction-control`
    - The velocity estimation dynamic library: `libctrl-ve.so`
    - The four dynamic libs for the models: `libctrl-{no,sc,tc,all}.so`
    - A binary that loads the models and tests them against a provided dataset

## Execute the Software

To execute the binary, `cd` into the build folder and run `./fenice-traction-control`. Note that you need to call the binary from within its folder otherwise it won't find the dynamic libraries.

At the end, if you need to analyze or gather control data, use `scp` to copy back the log files it produced (they're located inside the `build` folder) otherwise at shoutdown they will be lost.

```shell
scp tc@controllo-sborato:/home/tc/fenice-traction-control-sw/build/\*.csv ./logs/
```
