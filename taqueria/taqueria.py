import sys


menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

total = float(0.00)

while True:
    try:
        item = input("Item: ").title()
        for i, p in menu.items():
            if i == item:
                total += p
        print(f"${total:.2f}")

    except EOFError:
        print("\n")
        sys.exit()



