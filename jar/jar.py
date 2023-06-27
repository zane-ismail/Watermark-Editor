def main():
    jar = Jar()
    print(str(f"Capacity: {jar.capacity}"))
    jar.deposit(3)
    jar.withdraw(1)
    print(str(f"Size: {jar.size}"))
    print(str(jar))

class Jar:
    def __init__(self, capacity=12):
        if self._capacity < 0 or self._capacity > 12:
            raise ValueError("Wrong capacity")
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        return "🍪" * self._size

    def deposit(self, n):
        if n > self._capacity:
            raise ValueError("Exceeds capacity")
        if self.size + n > self._capacity:
            raise ValueError("Exceeds capacity")
        self.cookies += n

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