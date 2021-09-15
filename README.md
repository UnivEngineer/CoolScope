# CoolScope
Telescope fan controller

CoolScope v 1.0 is a diy 2-channel fan controller based on Arduino Nano. It is used to cool down (thermostabilize) the 12 inch Meade LX200 telescope. It is assembed in a 3D pronted case and mounted on the back on the scope. Device feature 2 channels for 12V PWM fans, 4 temperature sensors (DS18B20): mounted on the scope's primary mirror, inside the scope's tube, inside device's case, and one external sensor connected via 3.5 mm jack, and 1602 LCD/OLED display to show stats and menu. The device is powered by 12V external power source, and draws up to 400 mA (depending on used fans).

The project consists of three parts:

Telescope_fans - Arduino sketch source code.
PCB - KiCad files for circut schematcis and PCB.
Case - SolidWorks and STL files of 3D model of the case.

----------------------------------------------------------------------------------

Short usage manual (v 1.0)

Device has 4 buttons: [menu], [<], [>], [ok].

Once powered up, you will see an info screen. It displays current temperature of variaous sensors, fans speed and duty, and additional info. You may scroll several info screens by pressing [<] [>] buttons. Legend:
A - ambient temperature, i.e. sensor inside the device.
E - expternal temperature, i.e. external sensor connected via jack.
M - mirror temperature.
T - tube temperature (air inside the tube).
F - front fans speed/duty.
R - rear fans speed/duty.

Pressing [menu] or [ok] button will bring up settings. Press buttons [<] or [>] to scroll throug optoins or increase/decrease values, [ok] to enter sub-level, [menu] to return back to upper level. The settings menu heirarchy is the following:

Settings
- Cooling
  - Mode once cooled [values are "Keep delta T", "Keep blowing", "Keep drawing", "Stop", "Cooling is off"]
  - Target delta T [values are 0.05, 0.1, 0.2 ... 3.0 °C]
  - Cooling speed [values are 5, 10, 15 ... 100 %]
  - Keeping speed [values are 5, 10, 15 ... 100 %]
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
- Information
  - Uptime
  - Power voltage
  - Fan stuck alarm [values are "off", "on"]
  - About

