//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
    {"┇  ", "pactl get-sink-volume @DEFAULT_SINK@ | grep -o '[0-9]*%' | head -1", 2, 1},
	{" ", "brightnessctl -m | cut -d, -f4",                                  2, 2},
	{"", "if [ \"$(cat /sys/class/power_supply/BAT0/status)\" = Charging ]; then printf '^c#b8bb26^󰁹 ^d^'; else printf '󰁹 '; fi; printf '%s%%' \"$(cat /sys/class/power_supply/BAT0/capacity)\"",  15, 0},
	{" ", "date '+%m.%d'",                                                  60, 0},
	{" ", "date '+%I:%M %p'",                                                 5, 0},
	{"", "if [ \"$(nmcli -t -f STATE general 2>/dev/null)\" = connected ]; then printf ' '; else printf '󰖪 '; fi", 5, 0},
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " ┇ ";
static unsigned int delimLen = 7;
