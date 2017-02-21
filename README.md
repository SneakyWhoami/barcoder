# barcoder
Cheap, nasty tool to put clipboard or stdin into a barcode (so you can copy to a smartphone)

I really just developed this for myself. You're welcome to debug it, package it, redistribute it, refactor it...
You could re-jig the whole thing to use `prison` instead of wastefully spawning extra processes.

But for what I wanted, it works.
Example setup for klipper:
* Right-click on klipper in your system tray
* Select "Configure" from the context menu
* In the "Actions" tab, under "Action List", add a new action.
* For the regular expression, enter `.*` to capture everything.
* For description, write "Show Barcode" (or whatever you want)
* Add a command. In the command entry field, write `echo "%s"|barcoder` (where "barcoder" is the path to your barcoder executable)

Now, any time that you want klipper to generate a barcode like it used to in the good old days (a couple years ago):
* Left-click klipper in your system tray
* hover over the clip you want to share
* Press the little square icon which is supposed to represent clipboard actions
* Click "Show Barcode" (this is your description from earlier)
* Open your phone's barcode scanner and point it at the barcode
* voila, depending on your phone's setup, you now have the text info on your phone ready to paste where you want

To make:
* follow your normal qmake procedure
* OR
* use qtcreator
* adapt to your fancy cmake thingy

Requirements:
*  NEEDED               libQt5Widgets.so.5
*  NEEDED               libQt5Gui.so.5
*  NEEDED               libQt5Core.so.5
*  NEEDED               libstdc++.so.6
*  NEEDED               libgcc_s.so.1
*  NEEDED               libc.so.6
  
  If you have qt5 installed, you can probably run this with no issues. I'm lazy and just stuck it into /usr/bin or some other place
  in my path.
  
  To get the actual barcoding functionality there are two additional binaries you need, for now: `dmtxwrite` and `qrencode`.
  You can install both on ubuntu or similar by typing:
`sudo apt-get install dmtx-utils qrencode`
