# TODO
import cs50


def main():
    cash = get_cash()
    quarters = calculate_quarters(cash)
    cash = cash - quarters * 25
    dimes = calculate_dimes(cash)
    cash = cash - dimes * 10
    nickels = calculate_nickels(cash)
    cash = cash - nickels * 5
    cents = calculate_cents(cash)
    cash = cash - cents * 1

    coins = quarters + dimes + nickels + cents
    print(coins)


# Asks the user how much change is owed
def get_cash():
    # Re-prompt the user for a valid amount until the user provides a non-negative value
    cash = -1
    while cash < 0:
        cash = cs50.get_float("Change owed: ")
        # Convert input into an integer for rounding down
        cash = int(cash * 100)
    return cash


# Calculates amount of quarters
def calculate_quarters(cash):
    q = int(cash / 25)
    return q


# Calculates amount of dimes
def calculate_dimes(cash):
    d = int(cash / 10)
    return d


# Calculates amount of nickels
def calculate_nickels(cash):
    n = int(cash / 5)
    return n


# Calculates amount of cents
def calculate_cents(cash):
    c = int(cash / 1)
    return c


main()