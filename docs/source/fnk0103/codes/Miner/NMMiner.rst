##############################################################################
NMMiner
##############################################################################

This project utilizes Freenove ESP32 Display and NMMiner to implement Bitcoin mining. It requires some programming background and a basic understanding of digital currencies.

Project Introduction
****************************************

NMMiner (https://github.com/NMminer1024/NMMiner) is an excellent BTC mining firmware specifically designed for ESP32 development boards. It breaks away from the traditional mining requirements of massive electricity consumption and high hash rates by adopting a SOLO mining mode. In this mode, every computation has the chance to independently win the entire block reward. NMMiner supports all cryptocurrencies based on the SHA256d algorithm, such as BTC, BCH, XEC, and DGB. Freenove has successfully ported this project to run on the Freenove ESP32 Display. 

This tutorial will guide you through the process of running the project on the Freenove ESP32 Display.

NMMiner offers two management tools: 

1. NMController Client: Windows desktop application

2. NMController Web: A cross-platform web client designed with Python, compatible with both Windows and macOS systems.

Precautions
****************************************

* Cost
  
  - NMMiner is currently a paid service. Each device requires a unique license for activation. Therefore, you will need to purchase a separate activation code for every development board you plan to use in order to complete the activation process.

* Security Precautions  

  - Never disclose your wallet's private key or recovery phrase to anyone. The only information you need to provide is your public cryptocurrency receiving address.

* Troubleshooting

  - If you have followed the tutorial but are still unable to use the miner, please feel free to contact us for assistance. (support@freenove.com)

Compatibility Description
****************************************

At the time of writing this guide, the Freenove ESP32 Display is available in five different models. Although they vary in terms of screen drivers, resolutions, and screen sizes, all of them can be set up using this tutorial to learn how to use NMMiner.

.. table:: 
    :class: zebra
    :align: center

    +--------------+------------+----------+------------------+
    | Models       | Specifications        | Effect           |
    +==============+============+==========+==================+
    | FNK0103F_2P8 | Size       | 2.8 inch | Fully Compatible |
    |              +------------+----------+                  |
    |              | Resolution | 240x320  |                  |
    |              +------------+----------+                  |
    |              | Driver     | ILI9341  |                  |
    +--------------+------------+----------+------------------+
    | FNK0103B_2P8 | Size       | 2.8inch  | Fully Compatible |
    |              +------------+----------+                  |
    |              | Resolution | 240x320  |                  |
    |              +------------+----------+                  |
    |              | Driver     | ST7789   |                  |
    +--------------+------------+----------+------------------+
    | FNK0103L_3P2 | Size       | 3.2inch  | Color Inversion  |
    |              +------------+----------+                  |
    |              | Resolution | 240x320  |                  |
    |              +------------+----------+                  |
    |              | Driver     | ST7789   |                  |
    +--------------+------------+----------+------------------+
    | FNK0103N_3P5 | Size       | 3.5inch  | Fully Compatible |
    |              +------------+----------+                  |
    |              | Resolution | 320x480  |                  |
    |              +------------+----------+                  |
    |              | Driver     | ST7796   |                  |
    +--------------+------------+----------+------------------+
    | FNK0103S_4P0 | Size       | 4.0inch  | Fully Compatible |
    |              +------------+----------+                  |
    |              | Resolution | 320x480  |                  |
    |              +------------+----------+                  |
    |              | Driver     | ST7796   |                  |
    +--------------+------------+----------+------------------+

How to Use
*****************************************

Firmware Flashing and Activating
=========================================

1. Open the `NMMiner Flash ESPTool <https://flash.nmminer.com/>`_ interface, click to select the device.

.. image:: ../_static/imgs/NMMiner/NMMiner00.png
    :align: center

2. Select the device corresponding to your display according to the table below.

.. table:: 
    :class: zebra
    :align: center

    +--------------+-------------------------+
    | Models       | Device Name             |
    +==============+=========================+
    | FNK0103F_2P8 | esp32-2432s028r-ili9341 |
    +--------------+-------------------------+
    | FNK0103B_2P8 | esp32-2432s028r-st7789  |
    +--------------+-------------------------+
    | FNK0103L_3P2 | esp32-2432s024          |
    +--------------+-------------------------+
    | FNK0103N_3P5 | esp32-3248s035          |
    +--------------+-------------------------+
    | FNK0103S_4P0 | esp32-3248s035          |
    +--------------+-------------------------+

**If you have any concerns, please feel free to contact us via** support@freenove.com

3. Connect the Freenove ESP32 Display to your computer.

.. image:: ../_static/imgs/NMMiner/NMMiner01.png
    :align: center

4.	Click “**Connect and Program**”, select the correct port in the pop-up window, and click “**Connect**”.

**Please note:**

- The port may vary among computers

- Generally, COM1 is not the serial port of the ESP32.

.. image:: ../_static/imgs/NMMiner/NMMiner02.png
    :align: center

5. The firmware starts to flash into the Freenove ESP32 Display. :red:`Do NOT remove power supply during this process.`

.. image:: ../_static/imgs/NMMiner/NMMiner03.png
    :align: center

6. Click “**Get License Code**” after the firmware successfully flashes.

.. image:: ../_static/imgs/NMMiner/NMMiner04.png
    :align: center

7. Click “**PayPal Activate**” to make payment.

.. image:: ../_static/imgs/NMMiner/NMMiner05.png
    :align: center

8.	Please securely store the generated License (important). :combo:`red font-bolder:If the License is lost, it will need to be repurchased.`

When generating the license, the website will automatically download a CSV file containing the License information. You may also save the current webpage URL, as it can be reopened later.

.. image:: ../_static/imgs/NMMiner/NMMiner06.png
    :align: center

:combo:`red font-bolder:Please note: Each device requires a unique license code for activation. Therefore, you will need to purchase a separate activation code for every development board you plan to use in order to complete the activation process.`

9. Enter the License Code and click “Activation the device”.

.. image:: ../_static/imgs/NMMiner/NMMiner07.png
    :align: center

10.	Now the device is successfully activated.

.. image:: ../_static/imgs/NMMiner/NMMiner08.png
    :align: center

**If you have any concerns, please feel free to contact us via** support@freenove.com

Wi-Fi Configuration
========================================

1. Connect the Freenove ESP32 Display to your computer. If the firmware has not been flashed yet, please navigate back to the :ref:`previous section <fnk0103/codes/miner/nmminer:how to use>` to do it.

.. image:: ../_static/imgs/NMMiner/NMMiner09.png
    :align: center

2. Turn ON WLAN, locate and click “nmap-2.4g”.

.. image:: ../_static/imgs/NMMiner/NMMiner10.png
    :align: center

3. Wait for it to pop up the following interface, click “Configure WiFi”.

.. image:: ../_static/imgs/NMMiner/NMMiner11.png
    :align: center

4. Select your network. Please note that ESP32 only supports 2.4GHz network.

.. image:: ../_static/imgs/NMMiner/NMMiner12.png
    :align: center

5. Enter the correct WiFi password.

.. image:: ../_static/imgs/NMMiner/NMMiner13.png
    :align: center

6. **Enter the mining pool information. If the mining efficiency is unsatisfactory, you can switch to** `other mining pools <https://github.com/BitMaker-hub/NerdMiner_v2?tab=readme-ov-file#pool-selection>`_ **as needed.**

.. image:: ../_static/imgs/NMMiner/NMMiner14.png
    :align: center

7. Enter the correct BTC address. If you do not have a BTC address yet, please refer to :ref:`Obtaining the BTC Receiving Address <fnk0103/codes/miner/obtaining_the_btc_receiving_address:obtaining the btc receiving address>` Section to get it. 

.. image:: ../_static/imgs/NMMiner/NMMiner15.png
    :align: center

8. Enter the correct time zone.

.. image:: ../_static/imgs/NMMiner/NMMiner16.png
    :align: center

9. Click “Save” to save the configuration.

.. image:: ../_static/imgs/NMMiner/NMMiner17.png
    :align: center

10.	Now the NMMiner project begins to work.

.. image:: ../_static/imgs/NMMiner/NMMiner18.png
    :align: center

Management Tools
*****************************

NMController Client
======================================

.. note::
    
    :combo:`red font-bolder:1) MController Client only works on Windows.`
    
    :combo:`red font-bolder:2) The NMController client, which is downloaded from NMMiner official, may trigger false positives from antivirus programs, incorrectly flagging it as a virus.  If you do not trust it, you can use alternative methods provided in this document to manage your device.`

1. Click to open the `NMMiner GitHub website <https://github.com/NMminer1024/NMMiner>`_, click **Code** -> **Download ZIP**

.. image:: ../_static/imgs/NMMiner/NMMiner19.png
    :align: center

2. Extract the downloaded files, click **tool** -> **nmcontroller_client**, double click “**NMControllerSetup_x64.msi**” to open it.

.. image:: ../_static/imgs/NMMiner/NMMiner20.png
    :align: center

3. Click “**Next**”.

.. image:: ../_static/imgs/NMMiner/NMMiner21.png
    :align: center

4. Click “**Browse**” to select the installation location, check “**Just me**”, and click “**Next**”.

.. image:: ../_static/imgs/NMMiner/NMMiner22.png
    :align: center

5.	Close the window when the installation completes.

.. image:: ../_static/imgs/NMMiner/NMMiner23.png
    :align: center

Open the installed NMController Client and you can see the current device data.

.. image:: ../_static/imgs/NMMiner/NMMiner24.png
    :align: center

**If you have any concerns, please feel free to contact us via** support@freenove.com

NMController Web
======================================

**NMController Web**: A cross-platform web client designed with Python, compatible with both Windows and macOS systems.

1. Click to open the `NMMiner GitHub website <https://github.com/NMminer1024/NMMiner>`_, click **Code** -> **Download ZIP**

.. image:: ../_static/imgs/NMMiner/NMMiner19.png
    :align: center

2. Extract the downloaded files, click **tool** -> **nmcontroller_web**, select the folder based on your computer's OS.

.. image:: ../_static/imgs/NMMiner/NMMiner26.png
    :align: center

3. Double click to run the program.
   
   (1) You can access the management interface by visiting http://localhost:7877 on the current device.
   
   (2) Devices in the same LAN can access the management interface by visiting http://192.168.1.24:7877

.. note::

    - :combo:`red font-bolder:The following interface must NOT be closed when using NMController Web.`

    - :combo:`red font-bolder:The COM port may vary among devices. Please refer to the printed information for the correct port number.`

4. Access the corresponding address to open the management tool.

.. image:: ../_static/imgs/NMMiner/NMMiner27.png
    :align: center

IP Address Management
======================================

In the NMMiner interface, there is an IP address displayed. Devices connected to the same local network can access this IP address to open the management interface.

.. image:: ../_static/imgs/NMMiner/NMMiner28.png
    :align: center

Public Pool
======================================

When the mining pool public-pool.io:21496 is selected, you can manage it via the web interface using the link (ttps://web.public-pool.io/#/).

1. Open public-pool

.. image:: ../_static/imgs/NMMiner/NMMiner29.png
    :align: center

2. Enter BTC receiving address, and click “**My Workers**”.

.. image:: ../_static/imgs/NMMiner/NMMiner30.png
    :align: center

3. You can view the current working status of the worker.

.. image:: ../_static/imgs/NMMiner/NMMiner31.png
    :align: center

:combo:`red font-bolder:Please note: This webpage only detects and manages miners currently working in the Public Pool that use your BTC address as the login or payout address. Once the pool is changed, this webpage will no longer be accessible for management.`