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
        c = c * 100
    return c


def calculate_quarters(cash):
    if cash % 25 == 0:
        q = cash / 25
        print(f"q{q}")
        return q
    else:
        return


def calculate_dimes(cash):
    if cash % 10 == 0:
        d = cash / 10
        print(f"d{d}")
        return d
    else:
        return



def calculate_nickels(cash):
    if cash % 5 == 0:
        n = cash / 5
        print(f"n{n}")
        return n
    else:
        return



def calculate_cents(cash):
    c = cash / 1
    print(f"c{c}")
    return c

main()