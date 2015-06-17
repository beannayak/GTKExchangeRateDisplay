# GTK Exchange Rate Display

Project Uses GIMP toolkit to create GUI.
GUI is used as display(view) layer only, and an console application is used service layer.
This project uses inter-process communication to get data from console application, and then 
formats that data in a nice way to display in GUI. 

This program can:
  1. Display exchange rate of current day. 
  2. Converts date from AD to BS(Bikram Sambat).
  3. Has an inbuilt simple calculator.

A. All required shared libraries and binaries for this program to run in windows is located in "Windows Binary" folder. 
B. Can be compiled in Linux as :
    gcc currencyconverterGUI.c `pkg-config gtk+-3.0 --cflags` `pkg-config gtk+-3.0 --libs`
