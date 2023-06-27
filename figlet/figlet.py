from pyfiglet import Figlet

input = input("Input: ")

figlet = Figlet()

figlet.getFonts()

figlet.setFont(font="5lineoblique")

print(f"Output: {figlet.renderText(input)}")


