#include "dwmblocks.h"
#include "palette.h"

//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
    /* Icon */ /* Command */ /* Update Interval */ /* Update Signal */

    // Volume
    {
        " ",
        "if [ \"$BUTTON\" = 1 ]; then "
            "pactl set-sink-mute @DEFAULT_SINK@ toggle; "
        "fi; "

        "if pactl get-sink-mute @DEFAULT_SINK@ | grep -q yes; then "
            "icon='󰖁'; "
        "else "
            "icon=''; "
        "fi; "

        "vol=$(pactl get-sink-volume @DEFAULT_SINK@ | grep -o '[0-9]*%' | head -1); "

        "printf '" DWM_BLOCKS_FG(DWM_BLOCKS_BLACK)
                   DWM_BLOCKS_BG(DWM_BLOCKS_RED) " %s "
                   DWM_BLOCKS_FG(DWM_BLOCKS_WHITE)
                   DWM_BLOCKS_BG(DWM_BLOCKS_GREY) " %s "
                   DWM_BLOCKS_BG(DWM_BLOCKS_BLACK)
                   "' \"$icon\" \"$vol\"",
        2,
        1
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
        "state_file=${XDG_RUNTIME_DIR:-/tmp}/dwm-battery-state; "
        "last=NONE; "
        "[ -f \"$state_file\" ] && read -r last < \"$state_file\"; "

        "if [ \"$status\" = Full ]; then "
            "[ \"$last\" = FULL ] || notify-send 'Battery full'; "
            "printf 'FULL\\n' > \"$state_file\"; "
        "elif [ \"$status\" = Discharging ] && [ \"$capacity\" -le 15 ]; then "
            "[ \"$last\" = CRITICAL ] || notify-send -u critical \"Battery very low: $capacity%\"; "
            "printf 'CRITICAL\\n' > \"$state_file\"; "
        "elif [ \"$status\" = Discharging ] && [ \"$capacity\" -le 20 ]; then "
            "[ \"$last\" = LOW ] || notify-send \"Battery low: $capacity%\"; "
            "printf 'LOW\\n' > \"$state_file\"; "
        "else "
            "printf 'NONE\\n' > \"$state_file\"; "
        "fi; "

        "if [ \"$status\" = Charging ]; then "
            "printf '" DWM_BLOCKS_FG(DWM_BLOCKS_BLACK)
                       DWM_BLOCKS_BG(DWM_BLOCKS_GREEN) " 󰁹 "
                       DWM_BLOCKS_FG(DWM_BLOCKS_WHITE)
                       DWM_BLOCKS_BG(DWM_BLOCKS_GREY) " %s%% "
                       DWM_BLOCKS_BG(DWM_BLOCKS_BLACK)
                       "' \"$capacity\"; "
        "else "
            "printf '" DWM_BLOCKS_FG(DWM_BLOCKS_BLACK)
                       DWM_BLOCKS_BG(DWM_BLOCKS_RED) " 󰁹 "
                       DWM_BLOCKS_FG(DWM_BLOCKS_WHITE)
                       DWM_BLOCKS_BG(DWM_BLOCKS_GREY) " %s%% "
                       DWM_BLOCKS_BG(DWM_BLOCKS_BLACK)
                       "' \"$capacity\"; "
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

    "if [ \"$(nmcli radio wifi)\" = disabled ]; then "
        "printf '" DWM_BLOCKS_FG(DWM_BLOCKS_BLACK)
                   DWM_BLOCKS_BG(DWM_BLOCKS_RED) " 󰤭 "
                   DWM_BLOCKS_BG(DWM_BLOCKS_BLACK) "'; "
    "else "
        "signal=$(nmcli -t -f IN-USE,SIGNAL dev wifi | awk -F: '$1 == \"*\" {print $2; exit}'); "

        "if [ -z \"$signal\" ]; then "
            "icon='󰤯'; "
        "elif [ \"$signal\" -ge 75 ]; then "
            "icon='󰤨'; "
        "elif [ \"$signal\" -ge 50 ]; then "
            "icon='󰤥'; "
        "elif [ \"$signal\" -ge 25 ]; then "
            "icon='󰤢'; "
        "else "
            "icon='󰤟'; "
        "fi; "

        "printf '" DWM_BLOCKS_FG(DWM_BLOCKS_BLACK)
                   DWM_BLOCKS_BG(DWM_BLOCKS_BLUE) " %s "
                   DWM_BLOCKS_BG(DWM_BLOCKS_BLACK) "' \"$icon\"; "
    "fi",
    5,
    3
},

    // Clock
    {
        "",
        "printf '" DWM_BLOCKS_FG(DWM_BLOCKS_BLACK) DWM_BLOCKS_BG(DWM_BLOCKS_DARKGREEN) " 󱑆 "
                   DWM_BLOCKS_FG(DWM_BLOCKS_BLACK) DWM_BLOCKS_BG(DWM_BLOCKS_GREEN) " %s "
                   DWM_BLOCKS_BG(DWM_BLOCKS_BLACK) "' \"$(date '+%b %d %I:%M %p')\"",
        5,
        31
    },
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " ";
static unsigned int delimLen = 7;
