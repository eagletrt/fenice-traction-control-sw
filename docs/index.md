# Fenice ECU: Traction Control Software

The traction control software relies on the following components:

- The **Matlab model** (refer to the dynamics team)
- The **Raspberry PI** hosting the model and updating it with sensor data from the DAS
- The **DAS module** that reads and writes a UART channel with the RPi to communicate with the model

!!! note
    The choice of running the model on a separate device is for reliability purposes. The car must be able to run even if the model crashes or the RPi breaks / has issues.

This documentation is organized in the following sections:

- [Setting up the correct environment on the Raspberry Pi](rpi-setup.md)
- [Compiling and running the traction control server](compiling.md)
