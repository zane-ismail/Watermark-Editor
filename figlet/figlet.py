from pyfiglet import Figlet

input = input("Input: ")

figlet = Figlet()

figlet.getFonts()

figlet.setFont(font="5lineoblique")

if argv[2] == "-f":
    print(f"Output: {figlet.renderText(input)}")
elif argv[2] == "-font":
    


