def main():
    jar = Jar(1)
    print(str(f"Capacity: {jar.capacity}"))
    jar.deposit(3)
    jar.withdraw(1)
    print(str(f"Size: {jar.size}"))
    print(str(jar))

class Jar:
    def __init__(self, capacity=12):
        if capacity < 0 or self.size > 12:
            raise ValueError("Wrong capacity")
        self.capacity = capacity
        self.size = 0

    def __str__(self):
        return "🍪" * self.size

    def deposit(self, n):
        if n > self.capacity:
            raise ValueError("Exceeds capacity")
        if self.size + n > self.capacity:
            raise ValueError("Exceeds capacity")
        self.cookies += n

    def withdraw(self, n):
        if self.size < n:
            raise ValueError("There aren't enough cookies")
        self.size -= n

    @property
    def capacity(self):
        return self.capacity

    @property
    def size(self):
        return self.size

main()