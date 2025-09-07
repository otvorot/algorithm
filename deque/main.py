class Deque:
    def __init__(self, m):
        self.deque = [None] * m
        self.tail = self.head = 0
        self.capacity = m
        
    def push_back(self, value):
        if not self.deque[self.tail]:
            self.deque[self.tail] = value
            self.tail = (self.tail + 1) % self.capacity
        else:
            print('error')
            
    def push_front(self, value):
        self.idx = (self.head - 1 + self.capacity) % self.capacity
        if not self.deque[self.idx]:
            self.head = self.idx
            self.deque[self.head] = value
        else:
            print('error')
    
    def pop_back(self):
        self.idx = (self.tail - 1 + self.capacity) % self.capacity
        if self.deque[self.idx]:
            self.tail = self.idx
            self.x, self.deque[self.tail] = self.deque[self.tail], None
            return int(self.x)
        return 'error'
        
    def pop_front(self):
        if self.deque[self.head]:
            self.x, self.deque[self.head] = self.deque[self.head], None
            self.head = (self.head + 1) % self.capacity
            return int(self.x)
        return 'error'


def main():
    n = int(input())
    deq = Deque(int(input()))
    
    for _ in range(n):
        command = input().split()
        if command[0] == 'push_back':
            deq.push_back(command[1])
            
        elif command[0] == 'push_front':
            deq.push_front(command[1])
            
        elif command[0] == 'pop_front':
            print(deq.pop_front())
            
        else:
            print(deq.pop_back())

if __name__ == '__main__':
    main()