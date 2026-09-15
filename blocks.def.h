//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
    {"┇ ", "if pactl get-sink-mute @DEFAULT_SINK@ | grep -q yes; then printf '󰖁 '; else printf ' '; fi; pactl get-sink-volume @DEFAULT_SINK@ | grep -o '[0-9]*%' | head -1", 2, 0},
	{" ", "brightnessctl -m | cut -d, -f4",                                  2, 0},
    {
        "",
        "capacity=$(cat /sys/class/power_supply/BAT0/capacity); "
        "status=$(cat /sys/class/power_supply/BAT0/status); "
        "if [ \"$status\" = Charging ]; then "
            "printf '^b#fb4934^^c#b8bb26^ 󰁹 ^c#fbf1c7^%s%% ^d^' \"$capacity\"; "
        "else "
            "printf '^b#fb4934^^c#fbf1c7^ 󰁹 %s%% ^d^' \"$capacity\"; "
        "fi",
        15,
        0
    },
    {
        "",
        "if [ \"$BUTTON\" = 1 ]; then nm-connection-editor >/dev/null 2>&1 & fi; "
        "if [ \"$(nmcli -t -f STATE general 2>/dev/null)\" = connected ]; "
        "then printf '^c#1d2021^^b#b8bb26^  Connected ^d^'; "
        "else printf '^c#fbf1c7^^b#fb4934^ 󰖪 Disconnected ^d^'; fi",
        5,
        3
    },
    {
        "",
        "printf '^c#1d2021^^b#458588^ 󱑆 '; "
        "printf '^c#1d2021^^b#83a598^ %s ^d^' \"$(date '+%b %d  %I:%M %p')\"",
        5,
        0
    },
	// {" ", "date '+%m.%d'",                                                  60, 31},
	// {" ", "date '+%I:%M %p'",                                                 5, 0},
    // {"", "if [ \"$(nmcli -t -f STATE general 2>/dev/null)\" = connected ]; then printf ' '; else printf '󰖪 '; fi", 5, 0},
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " ┇ ";
static unsigned int delimLen = 7;
