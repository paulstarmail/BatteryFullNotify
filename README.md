# BatteryFullNotify

Ubuntu application that notifies when the battery is full.

----Instructions to Install----

1. Open Terminal in the directory.
2. Install by running "sudo apt-get install acpi" in Terminal.
3. Run "gcc main.c -o BatteryFullNotify".
4. Run "pwd" and copy the output.
5. Run "gnome-session-properties".
6. Click "Add" and fill in with the following details.
   Name: "BatteryFullNotify"
   Command: "<paste the output of step 4>/BatteryFullNotify"
   Comment: "Notifies when the battery is full"
7. Click "Add".
8. Restart the Computer.
