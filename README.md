breadPull
=========

breadPull GUI app for port of subs.

Program stucture breakdown:
	Main-
		core file, initializes object needed and links the window with
		our data object. executes QApp's main loop to run GUI
	MainWindow-
		parent window, and most likely the only window to be used at this
		stage in development. Mainwindow handles the back end of the program
		and makes calls to the data object to receive values to display
	BreadData-
		most specific file currently. this object holds all information
		specific to the breadcount including daily numbers, last bread
		count received, number of sticks and more to make the bread pull
		easier for everyone. obect requires linking to a window before being
		used, so in theroy one could emply this program as a side option
		for a much larger program by linking the object with a child window.
