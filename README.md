# Atan-OS
**Thanks to @Volley24** for working on this with me!

Custom Coded Watch running "Atan OS". This is based on Spacehuhn's DSTIKE deauther watch, that has been reprogrammed

# Packages

/core: Core code that defines things such as the menus and the display system

/net: Code that defines anything that involves networking, such as creating a Wifi Network or connecting to one

# NOTES/NEXT STEPS:

-   Making it so it doesnt clear the entire display everytime you render, and only moves the current item x back, moves down the cursor and moves the new current item to the right

-   clock.cpp to manage time even offline (wont need this for things like weather)

-   incorporate our schedules using clock.cpp and date found with AccessPoint.getDate (still need to implement that)

-   Get menus inside menus working, maybe add their structure and not just menuA etc, at least build the general structure so you can navigate it

**PINS CAN BE FOUND UNDER SPACEHUHN A_CONFIG.H**