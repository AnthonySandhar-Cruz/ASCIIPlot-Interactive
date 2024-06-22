# ASCIIPlot-Interactive
An interactive command line tool to make ASCII plots.

# Important Notes
This project utilizes [tinyexpr](https://github.com/codeplea/tinyexpr) for parsing math in order to produce plots.

This project was built for Linux. To use this with Windows, I recommend installing the Windows Subsystem for Linux (WSL). This project has not been tested on MacOS.

# Downloading
An executable file is provided in the repository (ap-int) that you can download and run. Ensure the executable has permission to run using `chmod +x ap-int`. If you want to compile the project yourself, follow these steps:

1. Clone the repository and enter the repository directory
```
git clone https://github.com/AnthonySandhar-Cruz/ASCIIPlot-Interactive && cd ASCIIPlot-Interactive
```
2. Run the following command to build the project (assumes you have gcc installed)
```
gcc ap-int.c ascii_plot.c tinyexpr.c -lncurses -lm -o ap-int
```
3. Ensure the executable has permission to run using
```
chmod +x ap-int
```
4. You can now run the code using
```
./ap-int
```
5. (optional) Add the following line to your `.bashrc` file to be able to run this program from anywhere using `ap-int`
```
alias ap-int='/path/to/ap-int'
```
Make sure to replace `/path/to/` with the path to the `ap-int` executable.

# Usage
The options menu on the left shows the available parameters. Press the key shown to the left of the corresponding option to modify the option. Enter the desired value, then press enter. Here is a brief description of the available options:

 - domain: a single value of type double representing the domain of the function that goes from -domain to domain. The range of the function is calculated according to the maximum and minimum y-values on the domain, so the range does not need to (and cannot currently) be set. Examples: '5', '4.2', ...
 - function: string representation of a function. Only the variable 'x' is supported. Ex: 'sin(x^2)+3'.
 - marker: a singular character which will be used to create the line of the function. Ex: '*'.
 - colour: colour of the function line. Available options are: 'red', 'blue', or 'green'.

The controls for the program are shown at the bottom of the options. Press the key shown to the left of the corresponding control to perform that action. Here is a brief description of the controls:

- plot: plots using the parameters set in the options menu. This will fail if no function is set.
- save: saves the currently displayed plot (must plot before saving) to a text file. The name of the text file is a timestamp of when it was saved.
- exit: exits the program. Note that it does not save the plot displayed when exiting, so if you want to save it, do so before exiting.
