#set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5
#plot "plotting_data.dat" with linespoints ls 1

#FILES = system("ls -1 *.dat")
#plot for [data in FILES] data u 1:2 w p pt 1 lt rgb 'black' notitle

FILES = system("ls -1 *.dat")
plot for [file in FILES] file using 1:2 with lines
