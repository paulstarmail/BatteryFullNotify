#!/bin/bash

# Flag to check if the alert has already been sent
alert_sent=false

# Loop to check battery status every 60 seconds
while true; do
  # Get the current battery charge percentage
  battery_percentage=$(cat /sys/class/power_supply/BAT0/capacity)

  # Check if the battery percentage is greater than or equal to 90% and if alert hasn't been sent yet
  if [ "$battery_percentage" -ge 90 ] && [ "$alert_sent" = false ]; then
    # Send a critical notification
	notify-send --urgency=critical --expire-time=0 "Battery Alert" "Battery is at $battery_percentage%. Please unplug the charger."
	espeak "Battery almost full."

    # Set the flag to true to prevent multiple alerts
    alert_sent=true
  fi

  # Reset the alert_sent flag if battery percentage drops below 90%
  if [ "$battery_percentage" -lt 90 ]; then
    alert_sent=false
  fi

  # Wait for 60 seconds before checking again
  sleep 60
done
