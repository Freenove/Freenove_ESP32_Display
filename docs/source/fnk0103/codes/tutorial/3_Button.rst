##############################################################################
Chapter 3 Button
##############################################################################

The Boot button on the Freenove ESP32 Display can be configured as a regular input button after the program starts.

Project 3.1 Button RGB
***************************

In the previous chapter, we learned about RGB LEDs. In this section, we will further explore how to integrate RGB LEDs with buttons.

Related Knowledge
===========================

Button
---------------------------

In embedded systems, buttons are one of the most common human-machine input devices. When a button is not pressed, its opposing contacts are connected while adjacent contacts remain disconnected. Conversely, when the button is pressed, adjacent contacts connect while opposing contacts disconnect.

**Usage of the Boot Button on the Freenove CYD Board:**

**Manual Entry into Download Mode:**

When the board is powered on or reset, pressing and holding the Boot button forces the board into download mode.

In this mode, users can upload programs to the board via the serial port.

**Use as a Regular Input Button:**

If the Boot button is not pressed during power-on or reset, the board enters normal operation mode.

Once in operation mode, the Boot button can function as GPIO0, typically configured as a standard input button for user interaction.

.. image:: ../_static/imgs/3_Button/Chapter03_00.png
    :align: center

Pull-up Resistor
---------------------------

The primary function of a pull-up resistor is to ensure that the button maintains a stable high-level state when not pressed, preventing false triggering caused by floating pins or signal noise. The pull-up resistor is connected between the GPIO pin and VCC.

.. image:: ../_static/imgs/3_Button/Chapter03_01.png
    :align: center

When the button is not pressed, Vcc is connected to GPIO0 through the resistor, resulting in a high-level signal at this pin.

When the button is pressed, GPIO0 is connected to GND, resulting in a low-level signal.

Therefore, by reading the GPIO0 pin state, we can determine whether the button is pressed or not.

Component List 
===========================

.. table:: 
    :align: center
    :width: 80%
    :class: table-line

    +----------------------------+----------------+
    | Freenove ESP32 Display x 1 | USB cable x1   |
    |                            |                |
    | |Chapter01_02|             | |Chapter01_03| |
    +----------------------------+----------------+

.. |Chapter01_02| image:: ../_static/imgs/1_Serial/Chapter01_02.png
.. |Chapter01_03| image:: ../_static/imgs/1_Serial/Chapter01_03.png

Circuit
========================

Connect Freenove ESP32 Display to the computer with USB cable. 

.. image:: ../_static/imgs/1_Serial/Chapter01_04.png
    :align: center

Sketch
========================

Open **"Sketch_03.1_Button_RGB"** folder under **"Freenove_ESP32_Display\\Sketch"** and double-click **"Sketch_03.1_Button_RGB.ino".**

Sketch_03.1_Button_RGB
------------------------

The following is the program code:

.. literalinclude:: ../../../freenove_Kit/Sketches/Sketch_03.1_Button_RGB/Sketch_03.1_Button_RGB.ino
   :linenos:
   :language: c
   :dedent:

Code Explanation
------------------------

Define the pins for the button and the RGB LED.

.. literalinclude:: ../../../freenove_Kit/Sketches/Sketch_03.1_Button_RGB/Sketch_03.1_Button_RGB.ino
   :linenos:
   :language: c
   :lines: 8-11
   :dedent:

Initialize the RGB LED and the button. 

.. literalinclude:: ../../../freenove_Kit/Sketches/Sketch_03.1_Button_RGB/Sketch_03.1_Button_RGB.ino
   :linenos:
   :language: c
   :lines: 55-56
   :dedent:

Control the color of the RGB LED through the button.

.. literalinclude:: ../../../freenove_Kit/Sketches/Sketch_03.1_Button_RGB/Sketch_03.1_Button_RGB.ino
   :linenos:
   :language: c
   :lines: 61-71
   :dedent:

Click **"Upload"** to upload the code to Freenove_ESP32_Display.

.. image:: ../_static/imgs/3_Button/Chapter03_02.png
    :align: center

Press the button and the RGB LED will change color in the sequence of red -> blue -> green -> OFF.

.. image:: ../_static/imgs/3_Button/Chapter03_03.png
    :align: center