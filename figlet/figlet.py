from pyfiglet import Figlet
if argc == 0 or argc == 2:
    input = input("Input: ")
    figlet = Figlet()
    figlet.getFonts()
    figlet.setFont(font="5lineoblique")
    if argv[2] == "-f" or argv[2] == "--font":
        print(f"Output: {figlet.renderText(input)}")



