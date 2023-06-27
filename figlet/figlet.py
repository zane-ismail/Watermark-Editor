from pyfiglet import Figlet
import sys
import random

if len(sys.argv) == 1 or len(sys.argv) == 3:
    input = input("Input: ")
    figlet = Figlet()
    figlet.getFonts()

    if len(sys.argv) == 3:
        if sys.argv[2] == "-f" or sys.argv[2] == "--font":
            figlet.setFont(font=sys.argv[2])
            print(f"Output: {figlet.renderText(input)}")
    else:
        figlet.setFont(font=random.choice(['basic', 'doom', 'moo']))
        print(f"Output: {figlet.renderText(input)}")
else:
    print("Invalid usage")





