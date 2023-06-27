def main():
    jar = Jar()
    print(str(jar.capacity))

class Jar:
    def __init__(self, capacity=12):
        pass

    def __str__(self):
        return("🍪")

    def deposit(self, n):
        jar.append(n)

    def withdraw(self, n):
        jar.remove(n)

    @property
    def capacity(self):
        return (self.capacity)

    @property
    def size(self):
        return (self.size)

main()