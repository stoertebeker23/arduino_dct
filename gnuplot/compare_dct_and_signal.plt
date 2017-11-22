
set multiplot layout 1,2 rowsfirst

set xlabel "Frequency (Hz)"
plot "1.dct" using 1:2 with impulses lw 2.5 title "DCT"

set xlabel "Time (s)"
plot "1.signal" using 1:2 with lines lw 2.5 title "Signal"

unset multiplot
