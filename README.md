# arduino_dct
A handwritten discrete cosine transformation hopefully able to run on an arduino

Here is a plotted example of a run through sqaurewaves with changing frequencies.
 
![Plot](https://github.com/stoertebeker23/arduino_dct/blob/master/documentation/squarewave-f.png)

The first line is a transformation of a 156Hz square wave while the last is a transformation of a 5Khz square wave.

![Plot](https://github.com/stoertebeker23/arduino_dct/blob/master/documentation/example1.png)
![Plot](https://github.com/stoertebeker23/arduino_dct/blob/master/documentation/example2.png)
![Plot](https://github.com/stoertebeker23/arduino_dct/blob/master/documentation/example3.png)
![Plot](https://github.com/stoertebeker23/arduino_dct/blob/master/documentation/example4.png)

Here is a [paper](http://www.egr.msu.edu/waves/people/Ali_files/DCT_TR802.pdf) about the implementation of DCTs 

## Compression:

![Plot](https://github.com/stoertebeker23/arduino_dct/blob/master/documentation/compression.png)

In this plot I tested multiple "compression factors". The first graph shows the original DCT of a signal and the inverse of that DCT. It is, except small deviation equal to the original signal.
The second plot omit the last 86 values and replaces them with zeros. The third one only keeps 10(!) values and replaces the first 15 and the last 99 with zeros. Its now possible to see the compression loss pretty clearly. 

Now we have to think of ways to implement compression. If we use our own software, we could save chunks with information on how much of the window is ommitted and where the omission is happening.