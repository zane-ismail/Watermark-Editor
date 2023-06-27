def main():
    jar = Jar()
    print(str(jar.capacity))
    # print(str(jar))
    # jar.deposit(5)
    # print(str(jar))
    jar.withdraw(1)
    print(str(jar))

class Jar:
    def __init__(self, capacity=12):
        self.cookies=0

    def __str__(self):
        for c in range(self.cookies-1):
            print("🍪")
        return("🍪")

    def deposit(self, n):
        self.cookies+=n

    def withdraw(self, n):
        self.cookies-=n

    @property
    def capacity(self):
        return 12

    @property
    def size(self):
        return self.cookies

main()