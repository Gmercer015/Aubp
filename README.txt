breadPull
=========
Purpose:

	Make the bread pull standarized across port of subs with an easy to use
	yet highly customizable program that saves time and is free of human 
	error. Currenty being dev'd on my own time in hopes of bettering the
	company when finished


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
	Settings-
		implemented to create a highly customizable enviroment, hopefully to
		encompass more than just store 100 of Port of Subs. Settings is a
		dialog window that will display all given values from an encrypted file
		and allow the user to change them ONLY THROUGH THIS WINDOW. changing the
		file will corrupt the program
	ResultsWnd-
		self explanatory. this is a widget that displays the results of the bread
		pull. Instead of opening a new window the ResultsWnd replacing the screen
		by overlaying itself above MainWindow, then  returning to MainWindow after
		the user hits 'return'
