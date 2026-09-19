#include "dwmblocks.h"
#include "palette.h"

//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
    /* Icon */ /* Command */ /* Update Interval */ /* Update Signal */

    // Volume
    {
        " ",
        "if pactl get-sink-mute @DEFAULT_SINK@ | grep -q yes; then "
            "icon='󰖁'; "
        "else "
            "icon=''; "
        "fi; "
        "vol=$(pactl get-sink-volume @DEFAULT_SINK@ | grep -o '[0-9]*%' | head -1); "
        "printf '" DWM_BLOCKS_FG(DWM_BLOCKS_BLACK) DWM_BLOCKS_BG(DWM_BLOCKS_RED) " %s "
                   DWM_BLOCKS_FG(DWM_BLOCKS_WHITE) DWM_BLOCKS_BG(DWM_BLOCKS_GREY) " %s "
                   DWM_BLOCKS_BG(DWM_BLOCKS_BLACK) "' \"$icon\" \"$vol\"",
        2,
        0
    },

    // Brightness
    {
        "",
        "brightness=$(brightnessctl -m | cut -d, -f4); "
        "printf '" DWM_BLOCKS_FG(DWM_BLOCKS_BLACK) DWM_BLOCKS_BG(DWM_BLOCKS_YELLOW) "  "
                   DWM_BLOCKS_FG(DWM_BLOCKS_WHITE) DWM_BLOCKS_BG(DWM_BLOCKS_GREY) " %s "
                   DWM_BLOCKS_BG(DWM_BLOCKS_BLACK) "' \"$brightness\"",
        2,
        0
    },

    // Battery
    {
        "",
        "capacity=$(cat /sys/class/power_supply/BAT0/capacity); "
        "status=$(cat /sys/class/power_supply/BAT0/status); "
        "if [ \"$status\" = Charging ]; then "
            "printf '" DWM_BLOCKS_FG(DWM_BLOCKS_BLACK) DWM_BLOCKS_BG(DWM_BLOCKS_GREEN) " 󰁹 "
                       DWM_BLOCKS_FG(DWM_BLOCKS_WHITE) DWM_BLOCKS_BG(DWM_BLOCKS_GREY) " %s%% "
                       DWM_BLOCKS_BG(DWM_BLOCKS_BLACK) "' \"$capacity\"; "
        "else "
            "printf '" DWM_BLOCKS_FG(DWM_BLOCKS_BLACK) DWM_BLOCKS_BG(DWM_BLOCKS_RED) " 󰁹 "
                       DWM_BLOCKS_FG(DWM_BLOCKS_WHITE) DWM_BLOCKS_BG(DWM_BLOCKS_GREY) " %s%% "
                       DWM_BLOCKS_BG(DWM_BLOCKS_BLACK) "' \"$capacity\"; "
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
            "printf '" DWM_BLOCKS_FG(DWM_BLOCKS_BLACK) DWM_BLOCKS_BG(DWM_BLOCKS_BLUE) " 󰤨 "
                       DWM_BLOCKS_FG(DWM_BLOCKS_WHITE) DWM_BLOCKS_BG(DWM_BLOCKS_GREY) " Connected "
                       DWM_BLOCKS_BG(DWM_BLOCKS_BLACK) "'; "
        "else "
            "printf '" DWM_BLOCKS_FG(DWM_BLOCKS_BLACK) DWM_BLOCKS_BG(DWM_BLOCKS_RED) " 󰤭 "
                       DWM_BLOCKS_FG(DWM_BLOCKS_WHITE) DWM_BLOCKS_BG(DWM_BLOCKS_GREY) " Disconnected "
                       DWM_BLOCKS_BG(DWM_BLOCKS_BLACK) "'; "
        "fi",
        5,
        3
    },

    // Clock
    {
        "",
        "printf '" DWM_BLOCKS_FG(DWM_BLOCKS_BLACK) DWM_BLOCKS_BG(DWM_BLOCKS_DARKBLUE) " 󱑆 "
                   DWM_BLOCKS_FG(DWM_BLOCKS_BLACK) DWM_BLOCKS_BG(DWM_BLOCKS_BLUE) " %s "
                   DWM_BLOCKS_BG(DWM_BLOCKS_BLACK) "' \"$(date '+%b %d %I:%M %p')\"",
        5,
        31
    },
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " ";
static unsigned int delimLen = 7;
