from pyfiglet import Figlet
import sys
import random

if len(sys.argv) == 1 or len(sys.argv) == 3:
    input = input("Input: ")
    figlet = Figlet()
    figlet.getFonts()

    if len(sys.argv) == 3:
        if sys.argv[1] == "-f" or sys.argv[2] == "--font":
            figlet.setFont(font=sys.argv[2])
    else:
        figlet.setFont(font=random.choice(['basic', 'doom']))

    print(f"Output: {figlet.renderText(input)}")
else:
    print("Invalid usage")





