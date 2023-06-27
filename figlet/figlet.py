from pyfiglet import Figlet
import sys
import random

figlet = Figlet()

if len(sys.argv) == 3:
    if sys.argv[1] == "-f" or sys.argv[1] == "--font":
        try:
            figlet.setFont(font=sys.argv[2])
            input = input("Input: ")
            print(f"Output: {figlet.renderText(input)}")
        except:
            sys.exit("Font not found")
    else:
        sys.exit("Invalid usage")

elif len(sys.argv) == 1:
    figlet.setFont(font=random.choice(figlet.getFonts()))
    input = input("Input: ")
    print(f"Output: {figlet.renderText(input)}")

else:
    sys.exit("Invalid usage")







