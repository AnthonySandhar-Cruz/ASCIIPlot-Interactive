# ASCIIPlot-Interactive
An interactive command line tool to make ASCII plots.

# Important Note
This project utilizes [tinyexpr]{https://github.com/codeplea/tinyexpr} for parsing math in order to produce plots.

# Downloading
An executable file is provided in the repository (ap-int) that you can download and run. If you want to compile the project yourself, follow these steps:

1. Clone the repository
```
git clone https://github.com/AnthonySandhar-Cruz/ASCIIPlot-Interactive
```
2. Run the following command to build the project (assumes you have gcc installed)
```
gcc ap-int.c ascii_plot.c tinyexpr.c -lncurses -lm -o ap-int
```
3. You can now run the code using
```
./ap-int
```
