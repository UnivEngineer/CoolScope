# CoolScope
Telescope fan controller

CoolScope is a diy 2-channel fan controller based on Arduino Nano. It is used to cool down (thermostabilize) the 12 inch Meade LX200 telescope, but can be adapted to any other scope. It is assembled in a 3D printed case and mounted on the back on the scope. The device features 2 channels for 12V PWM fans, 4 temperature sensors DS18B20 (mounted on the scope's primary mirror, inside the scope's tube, inside device's case, and one external sensor connected via 3.5 mm jack), and 1602 LCD/OLED display to show stats and menu. The device is powered by 12V external power source, and draws up to 400 mA (depending on used fans).

The project consists of three parts:

Telescope_fans - Arduino sketch source code.
PCB - KiCad files of circuit schematics and PCB.
Case - SolidWorks and STL files of 3D model of the case.

The device can use any 80 mm 1602 LCD module with parallel interface (4 data lines). The best choice for astronomy accessory is a module with red symbols on a black background. Even better choice is a red Winstar 1602 OLED (WEH001602A), fully compatible electrically with LCD modules. OLED display performance is perfect at freezing temperatures, unlike STN LCD. The device supports both types of displays, there is a jumper on the PCB to tell the software which type of display module is connected.

The Arduino Nano can either be soldered to the main PCB through its PLS pins, or installed in a DIP socket, but you have to cut and solder pins directly to Nano, otherwise it may not fit under the display module.

The device has the circuit which protects it against wrong power polarity, and power voltage monitor, which can be used to control telescope's battery charge, and also used by software to auto-save settings to EEPROM memory on power loss.

----------------------------------------------------------------------------------

Short usage manual (v 1.5)

Device has 4 buttons: [menu], [<], [>], [ok].

Once powered up, you will see the info screen. It displays current temperatures reported by sensors, fans speed and duty, and power supply voltage. You may scroll through info screen modes by pressing [<] and [>] buttons. Legend:

- A - ambient temperature, i.e. sensor inside the device
- E - external temperature, i.e. external sensor connected via jack
- M - mirror temperature
- T - tube temperature (air inside the tube)
- [battery symbol] - power supply voltage
- [rotating fan symbol] - max of (front, rear) fans duty/RPM
- F - front fan duty/RPM
- R - rear fan duty/RPM

Pressing [menu] or [ok] button will bring up the settings. Press buttons [<] or [>] to scroll through options or increase/decrease values, [ok] to enter sub-level, [menu] to return back to upper level. The settings menu hierarchy is the following:

Settings
- Cooling
  - Fans enabled [values are "off", "on"]
  - Mode once cooled [values are "Keep delta T", "Keep blowing", "Keep drawing", "Stop"]
  - Target delta T [values are 0.05, 0.1, 0.2 ... 3.0 °C]
  - Cooling speed [values are 5, 10, 15 ... 100 %]
  - Keeping speed [values are 5, 10, 15 ... 100 %]
  - Pos. pressure [values are 0, 5, 10, 15 ... 100 %]
- Sensors
  - Target delta T pair [values are "Mirror and Ambient", "Mirror and External", "Mirror and Tube"]
  - Assign sensors [scroll through list of detected DS18B20 addresses and press [menu] to assign]
    - Mirror
    - Tube
    - Ambient
    - External
- Display
  - Brightness [values are 0, 1, ... 10]
  - Contrast [LCD only; values are 1, ... 10]
  - Timeout [values are "Disabled", 5, 10, 15, ..., 120 seconds]
  - Test [all pixels of display are filled until [menu] is pressed]
- Information
  - Uptime [uptime in days hours:minutes:seconds]
  - Fan stuck alarm [values are "off", "on"]
  - Low battery alarm [values are "off", "on"]
  - Battery alarm voltage [values are 8.0, 8.1, ... 12.0 volts]
  - Power voltage [current power supply voltage]
  - About

Pressing and holding the menu button, while on the info screen, will disable/enable cooling (the message "Fans enabled"/"Fans disabled" is displayed for a few seconds). This is a quicker way to stop fans than accessing "Cooling->Fans enabled" menu.

Depending on "Display->Timeout" settings, the display may turn off after a while (if LCD is used, only back-light will turn off). To turn on it back, simply press any button.

The device will run fans at "Cooling->Cooling speed" duty until specified delta T is reached. After that, it will either stop fans or keep them spinning at "Cooling->Keeping speed". Typically, you need the primary mirror of your scope to be in thermal equilibrium with outside air, so the "Target delta T pair" must be set to "Mirror and External", and external DS18B20 sensor plugged into the 3.5 mm jack. The "Ambient" sensor is mounted inside the device, thus may report higher temperatures because of observer breathing. For a balcony observations, the "Mirror and Tube" pair may give better results, because air at balcony is warmer than the outside air anyway.

To protect interior of the scope from the dust, intake fans must be covered with dust filters (HEPA is the best solution). Also it is important to keep the pressure inside the tube a bit higher than the atmosphere, otherwise unfiltered air with dust particles may be sucked in from holes and slits. Thus intake fans must spin somewhat faster that exhaust fans. The "Cooling->Pos. pressure" menu sets the percentage of the exhaust fans speed in relation to intake fans speed. Typical value is 30-50%. You can find it experimentally using a plastic bag capping the eyepiece slot of your scope: the bag must inflate.

V 1.2 - added auto switch to external sensor, then plugged in; added CRC check of data read from sensors.
V 1.3 - added support for graphical Winstar OLED (100x16 pixels) as a define, switch OLED/LCD is not supported in this case.
V 1.4 - fixed bug with "About" menu not working properly.
V 1.5 - added exhaust fans duty adjust.