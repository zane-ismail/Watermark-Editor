def main():
    jar = Jar()
    print(str(f"Capacity: {jar.capacity}"))
    jar.deposit(3)
    jar.withdraw(1)
    print(str(f"Size: {jar.size}"))
    print(str(jar))

class Jar:
    def __init__(self, capacity=12):
        if self.capacity < 0 or self.capacity > 12:
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
        self._size += n

    def withdraw(self, n):
        if self._size < n:
            raise ValueError("There aren't enough cookies")
        self._size -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

main()