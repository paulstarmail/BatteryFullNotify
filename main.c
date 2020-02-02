/*This file sets configurations for BatteryFullNofify.

Warning: This may take a maximum of ("NO_OF_ALERTS")*5 minutes to take effect if the battery charge is greater than or equal to "THRESHOLD".


The number of alerts shown with 5 minutes interval when battery charge goes over threshold. Recommended value is 2.*/

#define NO_OF_ALERTS 2

/*The threshold at and above which notification should be generated. Recommended value is 95.*/

#define THRESHOLD 95

/*Complete path to the PWD (Present Working Directory)*/

#define PWD "/home/kite/ProgramFiles/BatteryFullNotify"  //Do not remove the quotes.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *read_file;
    char buffer[500], adapter_state[10];
    int count = 0, power_percent;

    while(1)
    {
        read_file = popen("acpi -a | cut -d ' ' -f3","r");
        fgets(adapter_state, 10, read_file);
        pclose(read_file);

        read_file = popen("acpi | cut -d ',' -f2 | cut -d ' ' -f2 | cut -d '%' -f1","r");
        fgets(buffer, 500, read_file);
        pclose(read_file);
        power_percent = atoi(buffer);

        if(strcmp(adapter_state, "off-line\n") == 0 || power_percent < THRESHOLD)
        {
            count = 0;
        }

        while(count < NO_OF_ALERTS && strcmp(adapter_state, "on-line\n") == 0 && power_percent >= THRESHOLD)
        {
            sprintf(buffer, "notify-send -u critical -i '%s/battery-full.png' 'Battery Full' 'Level: %d%%'", PWD, power_percent);
            system(buffer);
            sprintf(buffer, "paplay %s/alert.ogg", PWD);
            system(buffer);

            system("sleep 300");  //5 minutes sleep.

            read_file = popen("acpi -a | cut -d ' ' -f3","r");
            fgets(adapter_state, 10, read_file);
            pclose(read_file);

            read_file = popen("acpi | cut -d ',' -f2 | cut -d ' ' -f2 | cut -d '%' -f1","r");
            fgets(buffer, 500, read_file);
            pclose(read_file);
            power_percent = atoi(buffer);

            count++;
        }
    }
    return 0;
}
