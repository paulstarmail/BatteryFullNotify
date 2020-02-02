# BatteryFullNotify

Ubuntu application that notifies when the battery is full.

----Instructions to Install----

1. Open Terminal in the directory.
2. Install by running "sudo apt-get install acpi" in Terminal.
3. Run "pwd" and copy the output.
4. Open "main.c" file in text editor and set "#define PWD <paste the output of step 3>"
5. Run "gcc main.c -o BatteryFullNotify".
6. Run "gnome-session-properties".
7. Click "Add" and fill in with the following details.
   Name: "BatteryFullNotify"
   Command: "<paste the output of step 3>/BatteryFullNotify"
   Comment: "Notifies when the battery is full"
8. Click "Add".
9. Restart the Computer.

----Optional----

Application behaviour can be changed by changing the #define values of "main.c" file.
