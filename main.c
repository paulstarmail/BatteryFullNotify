#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *read_file;
    char buffer[500], path[500], adapter_state[10];
    int i, count = 0, no_of_alerts, threshold, power_percent;

    while(1)
    {

        read_file = popen("grep 'Number of alerts' config | sed -n 2p | cut -d '=' -f2","r");
        fgets(buffer, 500, read_file);
        pclose(read_file);
        no_of_alerts = atoi(buffer);

        read_file = popen("grep 'Threshold' config | cut -d '=' -f2","r");
        fgets(buffer, 500, read_file);
        pclose(read_file);
        threshold = atoi(buffer);

        read_file = popen("acpi -a | cut -d ' ' -f3","r");
        fgets(adapter_state, 10, read_file);
        pclose(read_file);

        read_file = popen("acpi | cut -d ',' -f2 | cut -d ' ' -f2 | cut -d '%' -f1","r");
        fgets(buffer, 500, read_file);
        pclose(read_file);
        power_percent = atoi(buffer);

        if(strcmp(adapter_state, "off-line\n") == 0 && power_percent < threshold)
        {
            count = 0;
        }

        while(count++ < no_of_alerts && strcmp(adapter_state, "on-line\n") == 0 && power_percent >= threshold)
        {
            read_file = popen("pwd","r");
            fgets(buffer, 500, read_file);
            pclose(read_file);
            for(i = 0; buffer[i] != '\n'; i++)
            {
                path[i] = buffer[i];
            }
            path[i] = '\0';

            sprintf(buffer, "notify-send -u critical -i '%s/battery-full.png' 'Battery Full' 'Level: %d%%'", path, power_percent);
            system(buffer);
            sprintf(buffer, "paplay %s/alert.ogg", path);
            system(buffer);

            system("sleep 300");  //5 minutes sleep.
        }
    }
    return 0;
}
