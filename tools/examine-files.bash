#!/bin/bash --

bold_font=$(tput bold)
normal_font=$(tput sgr0)
red_font=$(tput setaf 1)
green_font=$(tput setaf 2)
yellow_font=$(tput setaf 3)

declare -A COLORS_MAP

LOG_DIR=/var/log

list() {
    for nodeRoot in $(ls -d files-*); do
        echo -n $bold_font$green_font
        echo $nodeRoot:$normal_font$bold_font
        printf "%-10s %-50s %-3s\n" PID CMD EXIT_STATUS
        echo -n $normal_font

        for process in $(ls ${nodeRoot}${LOG_DIR} | grep '^[0-9]*$'); do
            local procDir=$nodeRoot$LOG_DIR/$process
            local cmd=$(cat $procDir/cmdline)
            local statusCode=$(cat $procDir/status | grep Exit | sed -E 's/^.*Exit \(([0-9]+)\)$/\1/')

            printf "%-10s %-50s %-3s\n" $process "$cmd" $statusCode
        done
    done
}

list
