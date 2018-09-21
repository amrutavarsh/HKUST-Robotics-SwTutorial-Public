# Program Flashing Guide

## Flash Program with UART

### Step 1: Connect UART to mainboard
1. **Make sure the mainboard is *NOT* in contact with any conductive surface (e.g. metal case of your notebook, carbon fiber)**
2. Locate the port `UART1` on the mainboard, below is a simple diagram of the pin configuration.
```
  _____
__|   |__
|V T R G|
---------
```
3. Connect uart to port `UART1` with:<br>
  5V  to V<br>
  RXD to T<br>
  TXD to R<br>
  GND to G
4. Plug the uart to any COM port of your computer. **UNPLUG** it at once if there is a **SHORT CIRCUIT** or when **NO LED IS ON**

### Step 2: Set up for Flash loader and Keil

#### Flash loader
1. Locate Flash loader on your computer:<br>
   `C:\Program Files (x86)\STMicroelectronics\Software\Flash Loader Demo\STMFlashLoader Demo.exe`
2. Create a shortcut on desktop because it is hard to find...
3. Ensure Flash loader is not operating before plugging the uart in
4. You can now plug the uart in

#### Keil
1. Plug the uart into the COM port you are going to use
2. Check which COM port is it in `Windows Setting\Devices`
3. Go back to Keil and select `Flash > Configure Flash Tools...`
4. Select `Utilities` at the top and then select `Use External Tool for Flash Programming`
5. Change the `Command` to `flash.bat`
5. Change the `Argument` to `./Objects/ustrobo18_internal.hex [your COM port id] 115200 STM32F1_Med-density_128K`. e.g. 4 if you are using COM4

### Step 3: Set the mainboard to BOOT mode
1. Set the mainboard to BOOT mode by toggling the BOOT mode switch
2. Check the BOOT mode led to see if it is on or not. If **NOT**, **UNPLUG** the uart at once and check the wire connection.
3. Press the SW1 button, which is the reset button for mainboard.`[TODO] confirm the reset button after the mainboard is done`

### Step 4: Flash your program to mainboard

#### Flashing via Flash loader
1. Switch on Flash loader
2. Select the corresponding COM port ID that the uart is connected to in the drop dowm menu `Port Name`.
3. Press `Next`
   * If it is `Not responding`, Here are some possible cause and their solution:
     - The mainboard is not in BOOT mode -> set it to BOOT mode, press reset button and go to 1.
     - If you have not press reset button -> press reset button and go to 1.
     - Incorrect COM port is being selected -> go to 1. and select the correct COM port
     - Wire connection is loose -> fix the wire connection and go to 1.
     - The Tx and Rx cables are flipped -> flip them back and go to 1.
     - You may try to switch to another COM port
   * If it moves on to the next page, go to 6.
4. Press `Next`
5. Press `Next`
6. Select `Download` and press `...` at the right to select the address
7. Select `.hex` file at the bottom-right corner
8. Select `ustrobo17_internal\Objects\ustrobo17_internal.hex` and press `Next`
9. Wait for it to finish flashing and press `Close`

#### Flashing via Keil
1. Ensure Flash loader is not running
2. Press F7 to compile the program
3. Press F8 to flash the program
   * If it stops flashing somewhere, check the error message to debug. Here are some possible cause and their solution:
     - The mainboard is not in BOOT mode -> set it to BOOT mode, press reset button and press F8
     - If you have not press reset button -> press reset button and press F8
     - The uart is not connected to the COM port set in the configuration -> connect it to the correct one / set it to current one and press F8
     - There might be an error in your program -> fix the error, press F7 and then F8
     - The Tx and Rx cables are flipped -> flip them back, press F7 and then F8
   * If there are a lot of `[OK]`, it is flashed successfully

### Step 5: Run the program
1. Exit BOOT mode by the toggling the BOOT mode switch
2. Press reset button
