##############################################################################
Chapter 14 LVGL Picture
##############################################################################

Project 14.1 LVGL Picture
*****************************************

Component List 
============================

.. table:: 
    :align: center
    :width: 80%
    :class: table-line

    +----------------------------+----------------+
    | Freenove ESP32 Display x 1 | USB cable x1   |
    |                            |                |
    | |Chapter01_02|             | |Chapter01_03| |
    +----------------------------+----------------+
    | Stylus x 1                                  |
    |                                             |
    | |Chapter11_00|                              |
    +---------------------------------------------+

.. |Chapter01_02| image:: ../_static/imgs/1_Serial/Chapter01_02.png
.. |Chapter01_03| image:: ../_static/imgs/1_Serial/Chapter01_03.png
.. |Chapter11_00| image:: ../_static/imgs/11_TFT_Touch_Calibration/Chapter11_00.png

Circuit
========================

Before connecting the USB cable, insert the SD card into the SD card slot on the back of the ESP32-S3.

.. image:: ../_static/imgs/7_Play_MP3/Chapter07_00.png
    :align: center

Connect Freenove ESP32-S3 to the computer using the USB cable.

.. image:: ../_static/imgs/7_Play_MP3/Chapter07_02.png
    :align: center

Sketch
========================

Open **“Sketch_14.1_Lvgl_Picture”** folder under **“Freenove_ESP32_Display\\Sketch”** and double-click **“Sketch_14.1_Lvgl_Picture.ino”**. 

Sketch_14.1_Lvgl_Picture
---------------------------

The following is the program code:

.. literalinclude:: ../../../freenove_Kit/Sketches/Sketch_14.1_Lvgl_Picture/Sketch_14.1_Lvgl_Picture.ino
   :linenos:
   :language: c
   :dedent:

Code Explanation
----------------------------

Include the header files.

.. literalinclude:: ../../../freenove_Kit/Sketches/Sketch_14.1_Lvgl_Picture/Sketch_14.1_Lvgl_Picture.ino
   :linenos:
   :language: c
   :lines: 7-9
   :dedent:

Define the pins.

.. literalinclude:: ../../../freenove_Kit/Sketches/Sketch_14.1_Lvgl_Picture/Sketch_14.1_Lvgl_Picture.ino
   :linenos:
   :language: c
   :lines: 13-16
   :dedent:

Set the baud rate to 115200

.. literalinclude:: ../../../freenove_Kit/Sketches/Sketch_14.1_Lvgl_Picture/Sketch_14.1_Lvgl_Picture.ino
   :linenos:
   :language: c
   :lines: 20-20
   :dedent:

Initialize configuration.

.. literalinclude:: ../../../freenove_Kit/Sketches/Sketch_14.1_Lvgl_Picture/Sketch_14.1_Lvgl_Picture.ino
   :linenos:
   :language: c
   :lines: 23-24
   :dedent:

Create and load the interface.

.. literalinclude:: ../../../freenove_Kit/Sketches/Sketch_14.1_Lvgl_Picture/Sketch_14.1_Lvgl_Picture.ino
   :linenos:
   :language: c
   :lines: 31-32
   :dedent:

LVGL Task Processor

.. literalinclude:: ../../../freenove_Kit/Sketches/Sketch_14.1_Lvgl_Picture/Sketch_14.1_Lvgl_Picture.ino
   :linenos:
   :language: c
   :lines: 38-38
   :dedent:

Copy the Picture folder under the **Freenove_ESP32_Display\\Sketch\\Sketch_14.1_Lvgl_Picture** directory to the SD card root directory.

.. image:: ../_static/imgs/14_LVGL_Picture/Chapter14_00.png
    :align: center

Click “Upload” to upload the code to Freenove ESP32 Display. Set the baud rate to 115200

.. image:: ../_static/imgs/14_LVGL_Picture/Chapter14_01.png
    :align: center

Custom image display
-----------------------------

You can customize the image displayed on the display according to your personal preferences.

First, open **Freenove_ESP32_Display\\Sketch\\Sketch_14.1_Lvgl_Picture\\Freenove Image Tool.exe**.

.. image:: ../_static/imgs/14_LVGL_Picture/Chapter14_02.png
    :align: center

Click “Add File”

.. image:: ../_static/imgs/14_LVGL_Picture/Chapter14_03.png
    :align: center

Select any image you like.

.. image:: ../_static/imgs/14_LVGL_Picture/Chapter14_04.png
    :align: center

The image files from your folder will now appear in the Pending File List.

.. image:: ../_static/imgs/14_LVGL_Picture/Chapter14_05.png
    :align: center

Click “Select...” to choose the image saving location.

.. image:: ../_static/imgs/14_LVGL_Picture/Chapter14_06.png
    :align: center

Select BMP for the format, set the resolution to 240x240 or 320x320 based on your screen, and then click Start Processing.

.. image:: ../_static/imgs/14_LVGL_Picture/Chapter14_07.png
    :align: center

Wait for the progress bar to complete.

Copy or replace the generated image to the folder corresponding to the Picture folder in the root directory of the SD card.

If the screen resolution is **240x320**, put the image in **Picture_240x240**

If the screen resolution is **320x480**, put the image in **Picture_320x320**

.. image:: ../_static/imgs/14_LVGL_Picture/Chapter14_08.png
    :align: center