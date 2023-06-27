from pyfiglet import Figlet
import sys
import random

if len(sys.argv) == 1 or len(sys.argv) == 3:
    input = input("Input: ")
    figlet = Figlet()
    figlet.getFonts()
    figlet.setFont(font="5lineoblique")
    if len(sys.argv) == 3:
        if sys.argv[3] == "-f" or sys.argv[3] == "--font":
            print(f"Output: {figlet.renderText(input)}")
    else:
        print(f"Output: {figlet.renderText(random.choice(['basic', 'doom', 'moo']))}")





