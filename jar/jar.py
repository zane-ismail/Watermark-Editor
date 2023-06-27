def main():
    jar = Jar()
    print(str(jar.capacity))
    # print(str(jar))
    jar.deposit(3)
    jar.withdraw(0)
    print(str(jar.size))
    # print(str(jar))
    print(str(jar))

class Jar:
    def __init__(self, capacity=12):
        self.cookies = 0

    def __str__(self):
        if self.cookies < 0 or self.cookies > 12:
            raise ValueError
        return "🍪" * self.cookies

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