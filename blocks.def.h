//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
    {"┇ ", "if pactl get-sink-mute @DEFAULT_SINK@ | grep -q yes; then printf '󰖁 '; else printf ' '; fi; pactl get-sink-volume @DEFAULT_SINK@ | grep -o '[0-9]*%' | head -1", 2, 1},
	{" ", "brightnessctl -m | cut -d, -f4",                                  2, 2},
	{"", "capacity=$(cat /sys/class/power_supply/BAT0/capacity); if [ \"$(cat /sys/class/power_supply/BAT0/status)\" = Charging ]; then printf '^c#b8bb26^󰁹 ^d^'; elif [ \"$capacity\" -le 10 ]; then printf '^c#fb4934^󰁹 ^d^'; elif [ \"$capacity\" -le 20 ]; then printf '^c#fabd2f^󰁹 ^d^'; else printf '󰁹 '; fi; printf '%s%%' \"$capacity\"",  15, 0},
	{" ", "date '+%m.%d'",                                                  60, 0},
	{" ", "date '+%I:%M %p'",                                                 5, 0},
	{"", "if [ \"$(nmcli -t -f STATE general 2>/dev/null)\" = connected ]; then printf ' '; else printf '󰖪 '; fi", 5, 0},
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " ┇ ";
static unsigned int delimLen = 7;
