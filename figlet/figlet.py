from pyfiglet import Figlet
import sys
import random

figlet = Figlet()

if len(sys.argv) == 3:
    input = input("Input: ")
    if sys.argv[1] == "-f" or sys.argv[1] == "--font":
        try:
            figlet.setFont(font=sys.argv[2])
        except FontNotFound(font):
            print("Font not found ")
    else:
        sys.exit

elif len(sys.argv) == 1:
    input = input("Input: ")
    figlet.setFont(font=random.choice(figlet.getFonts()))

else:
    print("Invalid usage")
    sys.exit

print(f"Output: {figlet.renderText(input)}")





