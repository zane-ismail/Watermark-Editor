from pyfiglet import Figlet
import sys
import random

figlet = Figlet()

if len(sys.argv) == 3:
    input = input("Input: ")
    if sys.argv[1] == "-f" or sys.argv[2] == "--font":
        figlet.setFont(font=sys.argv[2])
    else:
        sys.exit
elif len(sys.argv) == 1:
    input = input("Input: ")
    figlet.setFont(font=random.choice(figlet.getFonts()))
else:
    print("Invalid usage")
    sys.exit
print(f"Output: {figlet.renderText(input)}")





