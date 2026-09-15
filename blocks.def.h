#include "dwmblocks.h"
#include "palette.h"

//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
    /* Icon */ /* Command */ /* Update Interval */ /* Update Signal */

    // Volume
    {
        "",
        "if pactl get-sink-mute @DEFAULT_SINK@ | grep -q yes; then "
            "icon='󰖁'; "
        "else "
            "icon=''; "
        "fi; "
        "vol=$(pactl get-sink-volume @DEFAULT_SINK@ | grep -o '[0-9]*%' | head -1); "
        "printf '" FG(BLACK) BG(GREEN) " %s "
                   FG(WHITE) BG(GREY) " %s "
                   BG(BLACK) "' \"$icon\" \"$vol\"",
        2,
        0
    },

    // Brightness
    {
        "",
        "brightness=$(brightnessctl -m | cut -d, -f4); "
        "printf '" FG(BLACK) BG(RED) "  "
                   FG(WHITE) BG(GREY) " %s "
                   BG(BLACK) "' \"$brightness\"",
        2,
        0
    },

    // Battery
    {
        "",
        "capacity=$(cat /sys/class/power_supply/BAT0/capacity); "
        "status=$(cat /sys/class/power_supply/BAT0/status); "
        "if [ \"$status\" = Charging ]; then "
            "printf '" FG(BLACK) BG(GREEN) " 󰁹 "
                       FG(WHITE) BG(GREY) " %s%% "
                       BG(BLACK) "' \"$capacity\"; "
        "else "
            "printf '" FG(BLACK) BG(RED) " 󰁹 "
                       FG(WHITE) BG(GREY) " %s%% "
                       BG(BLACK) "' \"$capacity\"; "
        "fi",
        15,
        0
    },

    // Network
    {
        "",
        "if [ \"$BUTTON\" = 1 ]; then "
            "nm-connection-editor >/dev/null 2>&1 & "
        "fi; "
        "if [ \"$(nmcli -t -f STATE general 2>/dev/null)\" = connected ]; then "
            "printf '" FG(BLACK) BG(BLUE) " 󰤨 "
                       FG(WHITE) BG(GREY) " Connected "
                       BG(BLACK) "'; "
        "else "
            "printf '" FG(BLACK) BG(RED) " 󰤭 "
                       FG(WHITE) BG(GREY) " Disconnected "
                       BG(BLACK) "'; "
        "fi",
        5,
        3
    },

    // Clock
    {
        "",
        "printf '" FG(BLACK) BG(DARKBLUE) " 󱑆 "
                   FG(BLACK) BG(BLUE) " %s "
                   BG(BLACK) "' \"$(date '+%b %d %I:%M %p')\"",
        5,
        31
    },
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " ";
static unsigned int delimLen = 7;
