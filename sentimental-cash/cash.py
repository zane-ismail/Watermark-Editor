# TODO
import cs50

def main():
    cash = get_cash()
    print(cash)
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

def get_cash():
    c = -1
    while c < 0:
        c = cs50.get_float("Change owed: ")
    return c


def calculate_quarters(cash):
    q = cash / 25
    return q


def calculate_dimes(cash):
    d = cash / 10
    return d


def calculate_nickels(cash):
    n = cash / 5
    return n


def calculate_cents(cash):
    c = cash / 1
    return c

main()