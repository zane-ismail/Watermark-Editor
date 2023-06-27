def main():
    jar = Jar()
    print(str(jar.capacity))
    # print(str(jar))
    jar.deposit(5)
    print(str(jar))
    # jar.withdraw(1)
    # print(str(jar))

class Jar:
    def __init__(self, capacity=12):
        capacity=12

    def __str__(self):
        return("🍪" )

    def deposit(self, n):
        self=+n

    def withdraw(self, n):
        self=-n

    @property
    def capacity(self):
        # return (self.capacity)
        pass

    @property
    def size(self):
        # return (self.size)
        pass

main()