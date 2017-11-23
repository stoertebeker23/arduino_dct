# arduino_dct
A handwritten discrete cosine transformation hopefully able to run on an arduino

Here is a plotted example of a run through sqaurewaves with changing frequencies.
 
![Plot](https://github.com/stoertebeker23/arduino_dct/blob/master/documentation/squarewave-f.png)

Commands and call paramerters:

Make the build executable with 
```
chmod +x ./Arduino_dct
```
Now these are the arguments you can configure
-  -f: [string]  input file --> Define the file you want to apply a dct to. Format is a column of values
-  -s: [integer] sample rate --> The samplerate which the values in your file where read, this is only important for x-axis scaling
-  -l: [integer] dct size --> The length of you dct window
-  -a: [integer] averaging --> Averages windows with x previously calculated windows
-  -q: [boolean] squareroot --> decide wether you want to squareroot the result or not. 
-  -i: [boolean] include inverse --> calculate the inverse too. Only for validation
-  -d: [string] format --> choose the output format for the result files. This can be "own"(plots in gnuplot) or "matlab"

The first line is a transformation of a 156Hz square wave while the last is a transformation of a 5Khz square wave.

![Plot](https://github.com/stoertebeker23/arduino_dct/blob/master/documentation/example1.png)
![Plot](https://github.com/stoertebeker23/arduino_dct/blob/master/documentation/example2.png)
![Plot](https://github.com/stoertebeker23/arduino_dct/blob/master/documentation/example3.png)
![Plot](https://github.com/stoertebeker23/arduino_dct/blob/master/documentation/example4.png)

Here is a [paper](http://www.egr.msu.edu/waves/people/Ali_files/DCT_TR802.pdf) about the implementation of DCTs 
