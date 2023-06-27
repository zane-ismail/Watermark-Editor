def main():
    jar = Jar()
    print(str(f"Capacity: {jar.capacity}"))
    jar.deposit(4)
    jar.withdraw(1)
    print(str(f"Size: {jar.size}"))
    print(str(jar))

class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError("Wrong capacity")
        self._capacity = capacity
        self._size = 0

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