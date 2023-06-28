# TODO
height = 0
# Prompts user for height
try:
    while height < 1 or height > 8:
        # Takes input as integer
        height = int(input("Height: "))
# Only handles integer as input
except:
    height = int(input("Height: "))

j = height
for i in range(1, height + 1):
    j = j - 1
    print(" " * j + "#" * i)