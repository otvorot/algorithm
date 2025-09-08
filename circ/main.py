def circ_check(start, graph, colors):
    stack = []
    stack.append(start)
    while stack:
        u = stack.pop()
        if u not in colors:
            colors[u] = 1
            stack.append(u)
            for v in graph[u]:
                if v not in colors:
                    stack.append(v)
                elif colors[v] == 1:
                    return True
        elif colors[u] == 1:
            colors[u] = 2
 

 
def main():
    n = int(input())
    graph = [[] for _ in range(n + 1)]
    colors = [0] * (n + 1)
    for u in range(1, n):
        string = input()
        for v, way in enumerate(string, start=u+1):
            if way == 'R':
                graph[u].append(v)
            else:
                graph[v].append(u)
    for i in range(1, n):
        if not colors[i]:
            if circ_check(i, graph, colors):
                return 'NO'
 
    return 'YES'
 

 
if __name__ == '__main__':
    print(main())