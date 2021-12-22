# Flight Simulation Control
<img src="images/cesna.png">

#### Developers: SDido and RoyzLevy

## How to Run
I. Make sure you have Flight Gear installed.

II. look for a.out (or create one with g++ *.cpp *.h -std=c++14 -pthread)

III. Run a.out flight.txt (or any other legit script file that follow our rules)

IV. Enjot the take off and autonomous flight!

## Introduction
<a href="https://www.flightgear.org/">Fight Gear</a> is a cross platform free flight simulator written in C and C++.
Flight Gear allows telnet connection via termnial or shell thus
in this project we have established an autopilot feature for Flight Gear.

By writing a file with flight commands and conditions written in a script format 
our program can then take this file to translate and communicate it to Flight Gear.

This project was delegated to communication part and the language part.

## Creating the script
First we have decided upon the grammer and syntax of our language.
For example in order to assign a two way connection between values '= bind'
i.e. 
  var aileron = bind "/controls/flight/aileron"
When our variable changes programmatically it will 
send a message to the simulation to move the aileron in the plane.
Our goal is to automate a take off so we write the following script:
  while alt < 1000 {
  rudder = (h-heading)/80
  aileron = - roll/70
  elevator = pitch / 50
  sleep 250
  }

Look at <a href="https://github.com/SDIdo/FlightSimulation/blob/master/flight.txt">flight.txt</a> in this repo for the full script.

Now, with the goal language we had to come up with a proper Lexer, Parser and 
a script commands lookup table in order to translate the file into a C++ code. 
Upon implementing that all we had left was communication and threading.


## Communication - read and write
We have to be able to open a two way communication with Flight Gear.
This in order to give commands and also analyze and be notified about
the plane's condition and it's surroundings.
The connection had to be TCP because we care for the order and precision 
of the commands. 


