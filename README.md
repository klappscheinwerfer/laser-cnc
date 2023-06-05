## Controls

### Supported g-code and m-code commands

* G00 \[X] \[Y] \[F] - Absolute move (X,Y) at speed F
* G01 \[X] \[Y] \[F] - Relative move (X,Y) at speed F
* G90 - Absolute mode
* G91 - Relative mode
* G92 \[X] \[Y] - Change logical position

* M03 - Laser on
* M05 - Laser off

### Input

* `\n` - newline, end of command
* `\e` - escape, emergency stop

### Output

* `d:<debug_msg>` - debug message
* `e:<error_type>\n` - error with description
* `l:<line_number>\n` - line number
* `ready\n` - ready for the next command

## Development environment

### Visual Studio Code

* Open editor commands: `CTRL + SHIFT + P`
	* select controller,
	* select sketch (`laser-cnc.ino`),
	* select serial port,
	* install libraries (Arduino Library Manager)
* Verify sketch `CTRL + ALT + R`
* Upload sketch `CTRL + ALT + U`

### Troubleshooting

* "Programmer is not responding" - check if you're using the right serial port (e.g. ttyACM0)
	* If the port doesn't show up, try
		* unpluging and plugging in the arduino microcontroller again
		* restarting the editor and your computer
* "can't open device "/dev/ttyACM0": Permission denied" - give permissions to read and write to the port