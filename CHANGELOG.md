# CHANGELOG:

Date is in YYYY/MM/DD format.

**v.A.B.C**

**A**: Major Feature / Major Bug Fix

**B**: Minor Feature / Minor Bug Fix

**C**: Refactoring / Tiny Feature

**D**: Patch / Very Minor Thing

## [v.1.0.3] - 2024-01-05

**Author:** Max & Antoine
-   Fixed battery implementations with `Fully charged` and `charging` being displayed
-   Changed the incrementation from +1 sec to milliseconds for more accuracy (hasn't been tested)

## [v.1.0.2] - 2024-01-02

**Author:** Max & Antoine
-   Added battery percentage to clock face
-   Battery is linearly proportional to voltage for now, might get changed later
-   Displays when charging

## [v.1.0.1] - 2024-01-02

**Author:** Antoine
-   fixed time option in main menu bug (wouldn't clear the screen)
-   implemented the date
-   implemented the flashlight
-   changes time before epochtime++
-   ***REMOVED EEPROM due to its lifespan and since we dont need it*** (also increments every second)  
-   now requests an NTP packet every 10 mins on low and off power mode
-   fixed bug where it doesnt change lastclockupdate after ntppacket
**Compiles and runs**

## [v.1.0.0] - 2023-12-30

**Author:** Antoine

-   Fixed Memory leaks, still one remaining
-   Now properly connects to Networks and displays time after 10 seconds
-   Changed font for watch face
-   Added packet checking (received) before changing the time and writing to on board memory
-   ***EEPROM now works and correctly saves the previous current time but NOT date*** (also increments every second)  
**Compiles and runs**


## [v.0.1.7] - 2023-08-21

**Author:** Antoine

-   Changed time since last update to time since last update attempt, if it fails at connecting it will endlessly scan and try connected which is bad.
-   Added strcmp to switching menus (prob one reason it wouldnt work)
-   added sleeptime before it goes to clock menu
-   Changed parameter menu name to char*
-   Added changing fonts to terminal.cpp
-   Made minutes seconds etc in clock static so when you create object clock in menu.cpp it will retain its info/ NEVERMIND forgot it saves it to eeprom and read it on construction anyways so it shouldnt matter hopefully
### Compiles doesn't run

## [v.0.1.6] - 2023-08-19

**Author:** Antoine

-   Added `EEPROM` to clock works ish idk what happens if it fails to get anything back from ntp

## [v.0.1.5.1] - 2023-08-19

**Author:** Antoine

### PLEASE USE HEADER FILES. IT SOLVES SO MANY PROBLEMS
Board still crashing I'm assuming haven't tried it.
-   Fixed code for the clockmenu (forgot to change name and size from mainmenu)
-   Added `override` whatever that means dont ask me ask my ghost writer
-   Added header files for most cpp files

## [v.0.1.5] - 2023-08-19

**Author:** Max

### ButtonManager

-   Added `bind(int index, Function function)` method to bind a method to a button press.
-   As a consequence, `update_all()` will also call the methods associated with the button.
-   Added support for two new buttons on the watch. The indicies for these are defined in ButtonManager, and the variable names are **back_button_index** and **button_2_index**.
-   Button_2 is the button which turns on a blue light, which is kinda annoying and might drain battery.

## [v.0.1.4.1] - 2023-08-19

**Author:** Max

-   Commented out `Battery` and `Clock` initializers in `Main.ino` as they are causing the watch to reset.

## [v.0.1.4] - 2023-08-18

**Author:** Antoine

-   Added functions like addsec min h day to clock.cpp
-   added timesincelastupdate to automatically turn on/off wifi and update time and date (for now weather etc to be done afterwards). Turns off wifi right after to save battery
-   made clock update manually in main as well, regardless of wifi
-   Fixed size of date and time arrays along with types (byte deoesnt work?)
-   Added scan::getNetworks (returns array of obj AccessPoint)
-   Added weekday variable to clock in order to get the weekday (for schedule)
-   Added daylightsavings functionality using EEPROM to clock.cpp (commented out since not too sure if ntpclient already handles it)
    **_DO NOT USE MEMORY ADDRESS 0 THAT MIGHT BE USED BY DAYLIGHTSAVINGS!!!!!_**

## [v.0.1.3] - 2023-08-18

**Author:** Antoine

-   **_Submitted a question to spacehuhn github about if there is a connection from battery to analog pin for reading voltage_**
-   **_PINS CAN BE FOUND UNDER `SPACEHUHN>A_CONFIG.H`_**
-   Added `battery.h` and `battery.cpp`
-   Added sleep modes, altho im not too sure that they work
-   No clue if reading the voltage is going to be possible but we can try

## [v.0.1.2] -2023-08-13

**Author:** Antoine

-   Replaced connected networks obj array to non-static (Why did i do that i have no clue)
-   Made AccessPoint connectedNetwork static
-   Added versions to libraries imported
-   Removed shifting text on scroll
-   Made `pos_x = text_begin_x` on clear so that first line is ALSO 8 characters pushed to the right
-   Added `accesspoint.geth sec and min()`
-   Added `clock.update()` and stuff
-   **Changed the range indexs from using integers to using linesperpage. this is a temporary fix, if there is a menu item that needs more than one line of space, linesperpage might get reduced, unless we decide to hardcode it and it justs cuts off after a certain amount of characters (which is what it does rn).**

## [v.0.1.1] - 2023-08-13

**Author:** Max

-   Moved button state logic to it's own class.
-   Added `CHANGELOG.MD`.

## [v.0.1] - 2023-08-12

**Author:** Antoine

-   Made the mainmenu properly display
-   Made the navigation work (changing pages not submenus)
    atan
