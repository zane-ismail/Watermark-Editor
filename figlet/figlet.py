from pyfiglet import Figlet
import sys
from random import random

if len(sys.argv) == 0 or len(sys.argv) == 2:
    input = input("Input: ")
    figlet = Figlet()
    figlet.getFonts()
    figlet.setFont(font="5lineoblique")
    if sys.argv[2] == "-f" or sys.argv[2] == "--font":
        print(f"Output: {figlet.renderText(input)}")
    else:
        print(f"Output: {figlet.renderText(random.choice("basic", "doom", "moo"))}")





