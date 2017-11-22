#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 gnuplot_data.dat"
    echo "(gnuplot_data.dat is a file with x and y values)"
    exit 1
fi

# The directory this script lies in
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

sed -i -e '2s|.*|plot "'"$1"'" with linespoints ls 1|' $DIR/test.plt

# The trailing - is for interactive input, so the window stays open
# gnuplot test.plt -

gnuplot -persist $DIR/test.plt
