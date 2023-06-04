## Supported g-code and m-code commands

* G00 \[X] \[Y] \[F] - Absolute move (X,Y) at speed F
* G01 \[X] \[Y] \[F] - Relative move (X,Y) at speed F
* G90 - Absolute mode
* G91 - Relative mode
* G92 \[X] \[Y] - Change logical position

* M03 - Laser on
* M05 - Laser off

### VS Code

* Open editor commands: `CTRL + SHIFT + P`
	* select controller,
	* select sketch (`laser-cnc.ino`),
	* select serial port,
	* install libraries (Arduino Library Manager)
* Verify sketch `CTRL + ALT + R`
* Upload sketch `CTRL + ALT + U`

#### Troubleshooting

* "Programmer is not responding" - check if you're using the right serial port (I used ttyACM0)
* "can't open device "/dev/ttyACM0": Permission denied" - give permissions to read and write to the port