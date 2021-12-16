def dfs(visited, graph, node, output):
    if node not in visited:
        output.append(visited)
        visited.add(vertex)
        for adj in graph[vertex]:
            dfs(visited, graph, adj, output)


dict = {}
visited = set()
output = []
with open("cfg.txt", 'r') as file:
    for line in file:
        bb1, bb2 = line.split("->")
        bb_1 = int(bb1[2:])
        bb_2 = int(bb2[2:])
        if bb_1 in dict:
            dict[bb_1].append(bb_2)
        else:
            dict[bb_1] = []

for vertex in dict:
    dict[vertex].sort()

dfs(visited, dict, 0, output)

with open("index.txt", "w") as out:
    for item in output:
        out.write(str(item) +"\n")



