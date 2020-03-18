#!/usr/bin/env bash

# Mars portal launcher by seva@sevatech.com

export COUNT_X=3 # starting from 0 (meaning 1 vertical column)
export COUNT_Y=3 # starting from 0 (meaing 1 horizontal row)

export SIZE_X=320
export SIZE_Y=240

export BORDER_X=32
export BORDER_Y=24

# Do not edit below this line

export TOTAL_X=$(( $SIZE_X * ($COUNT_X+1) + $BORDER_X * $COUNT_X ))
export TOTAL_Y=$(( $SIZE_Y * ($COUNT_Y+1) + $BORDER_Y * $COUNT_Y ))

echo "Total size is $TOTAL_X by $TOTAL_Y"

for x in $( seq 0 $COUNT_X ); do
        for y in $( seq 0 $COUNT_Y ); do
                export TRANSLATE_X=$(( $x * ( $SIZE_X + $BORDER_X ) ))
                export TRANSLATE_Y=$(( $y * ( $SIZE_Y + $BORDER_Y ) ))
                export PORTAL="yes"
                $( dirname "${BASH_SOURCE[0]}" )/portal.app/Contents/MacOS/portal &
        done
done
