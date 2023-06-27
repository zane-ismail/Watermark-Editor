from pyfiglet import Figlet
import sys
import random

figlet = Figlet()

if len(sys.argv) == 3:
    if sys.argv[1] == "-f" or sys.argv[1] == "--font":
        try:
            input = input("Input: ")
            figlet.setFont(font=sys.argv[2])
            print(f"Output: {figlet.renderText(input)}")
        except:
            print("Font not found ")
            sys.exit
    else:
        sys.exit

elif len(sys.argv) == 1:
    input = input("Input: ")
    figlet.setFont(font=random.choice(figlet.getFonts()))
    print(f"Output: {figlet.renderText(input)}")

else:
    print("Invalid usage")
    sys.exit







