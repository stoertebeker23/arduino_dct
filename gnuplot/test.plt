FILES = system("ls -1 *.dct")
plot for [file in FILES] file using 1:2 with lines
