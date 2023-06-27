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
            sys.exit("Invalid usage")
    else:
        sys.exit("Invalid usage")

elif len(sys.argv) == 1:
    input = input("Input: ")
    figlet.setFont(font=random.choice(figlet.getFonts()))
    print(f"Output: {figlet.renderText(input)}")

else:
    sys.exit("Invalid usage")







