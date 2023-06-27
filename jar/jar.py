def main():
    jar = Jar()
    print(str(jar.capacity))
    print(str(jar))
    jar.deposit(2)
    print(str(jar))
    jar.withdraw(1)
    print(str(jar))

class Jar:
    def __init__(self, capacity=12):
        pass

    def __str__(self):
        pass
        # return("🍪")

    def deposit(self, n):
        jar.append(n)

    def withdraw(self, n):
        jar.remove(n)

    @property
    def capacity(self):
        # return (self.capacity)
        pass

    @property
    def size(self):
        # return (self.size)
        pass

main()