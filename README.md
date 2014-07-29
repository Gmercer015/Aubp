breadPull
---------------------------------------------------

Purpose:

	Make the bread pull standarized across port of subs with an easy to use
	yet highly customizable program that saves time and is free of human 
	error. Currenty being dev'd on my own time in hopes of bettering the
	company when finished

Want to try out the current version?

	Check out the release tab to download setup.exe. Install breadPull 
	in whatever location you prefer and start it up!


Program stucture breakdown:

	Main-
		Initializes objects needed and links the window with the 
		given bread data object. Executes QT main loop.
	MainWindow-
		Parent window to all other widegts in the program. Mainwindow
		is the base of the program and provides input for bread as
		well as a window for the results overlay to display. Menu
		consists of value editing tab and tools that could prove
		useful during operation.
	BreadData-
		Bread and butter of the application. BreadData holds all
		bread related variables in a protected state as well as
		offering getter/setter methods for every single var.
		This class also is responsible for writing data to the
		log/format and reading data from the format.dat file.
	Settings-
		implemented to create a highly customizable enviroment, 
		hopefully  to encompass more than just store 100 of Port
		of Subs. Settings is a dialog window that will display all
		given values from an encrypted file and allow the user to 
		change them ONLY THROUGH THIS WINDOW.changing the file 
		will corrupt the program
	ResultsWnd-
		This is a widget that displays the results 
		of the bread pull.Instead of opening a new window the ResultsWnd
		replacing the screen by overlaying itself above MainWindow, then
		returning to MainWindow after the user hits 'return'
	Log-
		Attempts to keep track of all breadpulls done by the program and
		provide statistics to the user or serve to track down errors. The
		log is a window itself and writes to it's own file to avoid clutter
	Help-
		HTML written documents on how to use Aubp effectivly
