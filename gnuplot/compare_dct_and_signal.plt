
# Usage: gnuplot -persistent compare_dct_and_signal.plt
# or: gnuplot -persistent -e "file='1'" compare_dct_and_signal.plt

if (!exists("file")) file="0"

set multiplot layout 1,2 rowsfirst title "File: ".file font ",14"

set xtics 1000
set xlabel "Frequency (Hz)"
plot file.".dct" using 1:2 with impulses lw 1.5 title "DCT"

unset xtics
set xlabel "Time (s)"
plot file.".signal" using 1:2 with lines lw 2.5 title "Signal"

unset multiplot
