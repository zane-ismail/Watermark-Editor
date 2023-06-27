from pyfiglet import Figlet
import sys

if sys.argc == 0 or sys.argc == 2:
    input = input("Input: ")
    figlet = Figlet()
    figlet.getFonts()
    figlet.setFont(font="5lineoblique")
    if sys.argv[2] == "-f" or sys.argv[2] == "--font":
        print(f"Output: {figlet.renderText(input)}")



