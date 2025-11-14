##############################################################################
NerdMiner_v2
##############################################################################

This project utilizes Freenove ESP32 Display and NerdMiner_v2 to implement Bitcoin mining. It requires some programming background and a basic understanding of digital currencies.

Project Introduction
****************************************

NerdMiner_v2 (https://github.com/BitMaker-hub/NerdMiner_v2)is an excellent open-source BTC mining firmware designed for ESP32 development boards. Its goal is to allow users to experience the process of "mining a Bitcoin block" using a small piece of hardware. The primary aim of this project is to help more people learn about cryptocurrency mining while owning an aesthetically pleasing desktop accessory.

NerdMiner_v2 supports mining on **solo pools** by implementing the **Stratum protocol** (by default, it connects to **public-pool.io**, which supports Nerdminer devices, but the pool address can be customized). Freenove has ported this project to run on the Freenove ESP32 Display.

This tutorial will guide you through the process of running the project on the Freenove ESP32 Display.

Precautions
**************************************

* Cost

  - As of the time of writing this document, NerdMiner_v2 is temporarily free to use.

* Security Precautions  

  - Never disclose your wallet's private key or recovery phrase to anyone. The only information you need to provide is your public cryptocurrency receiving address.

* Troubleshooting  
  
  - If you have followed the tutorial but are still unable to use the miner, please feel free to contact us for assistance. (support@freenove.com）

Compatibility Description
**************************************

At the time of writing this guide, the Freenove ESP32 Display is available in five different models. Although they vary in terms of screen drivers, resolutions, and screen sizes, all of them can be set up using this tutorial to learn how to use NerdMiner_v2.

.. table::
    :class: zebra
    :align: center

    +--------------+------------+----------+----------------------------+
    | Models       | Specifications        | Effect                     |
    +==============+============+==========+============================+
    | FNK0103F_2P8 | Size       | 2.8 inch | Color Inversion by Default |
    +              +------------+----------+                            +
    |              | Resolution | 240x320  |                            |
    +              +------------+----------+                            +
    |              | Driver     | ILI9341  |                            |
    +--------------+------------+----------+----------------------------+
    | FNK0103B_2P8 | Size       | 2.8inch  | Fully Compatible           |
    +              +------------+----------+                            +
    |              | Resolution | 240x320  |                            |
    +              +------------+----------+                            +
    |              | Driver     | ST7789   |                            |
    +--------------+------------+----------+----------------------------+
    | FNK0103L_3P2 | Size       | 3.2inch  | Incorrect Color            |
    +              +------------+----------+                            +
    |              | Resolution | 240x320  |                            |
    +              +------------+----------+                            +
    |              | Driver     | ST7789   |                            |
    +--------------+------------+----------+----------------------------+
    | FNK0103N_3P5 | Size       | 3.5inch  | Not Full Screen            |
    +              +------------+----------+                            +
    |              | Resolution | 320x480  |                            |
    +              +------------+----------+                            +
    |              | Driver     | ST7796   |                            |
    +--------------+------------+----------+----------------------------+
    | FNK0103S_4P0 | Size       | 4.0inch  | Not Full Screen            |
    +              +------------+----------+                            +
    |              | Resolution | 320x480  |                            |
    +              +------------+----------+                            +
    |              | Driver     | ST7796   |                            |
    +--------------+------------+----------+----------------------------+

How to Use
******************************

Firmware Flashing 
==============================

1. Open the `Bitronics flasher <https://flasher.bitronics.store/>`_ interface and click “**Select your device**”.

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner00.png
    :align: center

2. Select “**Nerdminer**”.

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner01.png
    :align: center

3. Select the correct firmware for your display based on the table below.

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner02.png
    :align: center

.. table::
    :class: zebra
    :align: center

    +--------------+-------------------------+
    | Models       | Board Version           |
    +==============+=========================+
    | FNK0103F_2P8 | ESP32-2432S028R         |
    +--------------+-------------------------+
    | FNK0103B_2P8 | ESP32-2432S028R         |
    +--------------+-------------------------+
    | FNK0103L_3P2 | ESP32-2432S024          |
    +--------------+-------------------------+
    | FNK0103N_3P5 | ESP32-2432S024          |
    +--------------+-------------------------+
    | FNK0103S_4P0 | ESP32-2432S024          |
    +--------------+-------------------------+

**If you have any concerns, please feel free to contact us via** support@freenove.com

4. Select the latest firmware version. 

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner03.png
    :align: center

5. Connect the Freenove ESP32 Display to your computer.

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner04.png
    :align: center

6. Click “**Connect**”.

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner05.png
    :align: center

7.	Select the port of your ESP32.

.. note::

    - The port number may vary among devices.

    - Generally, COM1 is not the port of ESP32.

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner06.png
    :align: center

8. Click “Start Flashing”.

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner07.png
    :align: center

9.	The firmware starts to flash into the Freenove ESP32 Display. :combo:`red font-bolder:Do NOT remove power supply during this process.`

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner08.png
    :align: center

10. The following message indicates successfully firmware flashing.

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner09.png
    :align: center

Wi-Fi Configuration
==================================

1.	Connect the Freenove ESP32 Display to your computer. If the firmware has not been flashed yet, please navigate back to the :ref:`Firmware Flashing Section <fnk0103/codes/miner/nerdminer_v2:how to use>` to do it.

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner10.png
    :align: center

2. Turn ON WLAN and connect to NerdMinerAP

WiFi SSID: :red:`NerdMinerAP`

PASSWORD: :red:`MineYourCoins`

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner11.png
    :align: center

3. Click “**Configure WiFi**”

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner12.png
    :align: center

4. Select your network. Please note that ESP32 only supports 24.GHz network.

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner13.png
    :align: center

5. Configure device information.

6. If you do not have a BTC address yet, please refer to Obtaining the BTC Receiving Address Section to get it. 

7. If the mining efficiency is unsatisfactory, you can switch to other mining pools as needed.

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner14.png
    :align: center

Management Tool
********************************

Public Pool
================================

When using the pool public-pool.io:21496, you can manage it via the web link https://web.public-pool.io/#/.

1. Open public-pool

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner15.png
    :align: center

2.	Enter your BTC receiving address, and click “**My Workers**”.

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner16.png
    :align: center

3.	You can view the current working status of the worker.

.. image:: ../_static/imgs/NerdMiner_v2/NerdMiner17.png
    :align: center

:combo:`red font-bolder:Please note: This webpage only detects and manages miners currently working in the Public Pool that use your BTC address as the login or payout address. Once the pool is changed, this webpage will no longer be accessible for management.`