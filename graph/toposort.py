class Vertex:
    def __init__(self, v):
        self.v = v
        self.heap = [0]
        self.last = 0
    def push(self, w):
        self.last += 1
        self.heap.append(w)
        self.sift_up(self.last)
    def sift_up(self, last):
        if last == 1:
            return
        parent = last // 2
        if self.heap[last] < self.heap[parent]:
            self.heap[last], self.heap[parent] = self.heap[parent], self.heap[last]
            self.sift_up(parent)
    def pull(self):
        if self.last == 0:
            return None
        self.heap[1], self.heap[self.last] = self.heap[self.last], self.heap[1]
        back = self.heap.pop()
        self.last -= 1
        self.sift_down(1, self.last)
        return back
    def sift_down(self, first, last):
        left, right = first * 2, first * 2 + 1
        if left > last:
            return
        smallest = right if right <= last and self.heap[right] < self.heap[left] else left
        if self.heap[first] < self.heap[smallest]:
            return
        self.heap[first], self.heap[smallest] = self.heap[smallest], self.heap[first]
        self.sift_down(smallest, last)

def trvrse(v, colors, vertice, prima):
    stack = []
    stack.append(v)
    while stack:
        now = stack.pop()
        if not colors[now.v]:
            colors[now.v] = 1
            stack.append(now)
            next = now.pull()
            while next:
                if not colors[next]:
                    stack.append(vertice[next])
                next = now.pull()
        elif colors[now.v] == 1:
            colors[now.v] = 2
            prima.append(now.v)
            

def main():
    vs, es = map(int, input().split())
    colors = [0] * (vs + 1)
    vertice = [0] * (vs + 1)
    prima = []
    for _ in range(es):
        v, w = map(int, input().split())
        if not vertice[v]:
            vertice[v] = Vertex(v)
        if not vertice[w]:
            vertice[w] = Vertex(w)
        vertice[v].push(w)
    for i in range(1, vs + 1):
        if not colors[i] and not vertice[i]:
            prima.append(i)
            colors[i] = 2
        elif not colors[i] and vertice[i]:
            trvrse(vertice[i], colors, vertice, prima)
    print(*prima[::-1])

if __name__ == '__main__':
    main()