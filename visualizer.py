import sys
import matplotlib.pyplot as plt
import numpy as np

def read(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
    
    vertices, edges, portals = map(int, lines[0].split())
    
    V = []
    for i in range(1, vertices + 1):
        x, y = map(float, lines[i].split())
        V.append((x, y))
    
    E = []
    for i in range(vertices + 1, vertices + 1 + edges):
        u, v = map(int, lines[i].split())
        E.append((u, v))
    
    P = []
    for i in range(vertices + 1 + edges, vertices + 1 + edges + portals):
        u, v = map(int, lines[i].split())
        P.append((u, v))
    
    return V, E, P

def plot_graph(V, E, P):
    plt.figure(figsize=(8, 6))
    
    for u, v in E:
        x1, y1 = V[u]
        x2, y2 = V[v]
        plt.arrow(x1, y1, x2 - x1, y2 - y1, head_width=10, head_length=15, fc='g', ec='g')
    
    for u, v in P:
        x1, y1 = V[u]
        x2, y2 = V[v]
        plt.arrow(x1, y1, x2 - x1, y2 - y1, head_width=10, head_length=15, fc='r', ec='r', linestyle='dashed')
    
    for i, (x, y) in enumerate(V):
        plt.plot(x, y, 'go', markersize=8)
        plt.text(x, y, f' {i}', fontsize=12, ha='right')
    
    plt.title('Visualização do grafo')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.grid(True)
    plt.show()

def plot_matrix(matrix):
    plt.figure(figsize=(8, 6))
    plt.imshow(matrix, cmap='viridis', interpolation='none')
    plt.colorbar(label='Distance')
    plt.title('Matriz de adjacência distâncias')
    plt.xlabel('Vértice')
    plt.ylabel('Vértice')
    plt.show()

def adjacency_matrix(V, E, P):
    n = len(V)
    matrix = np.full((n, n), np.inf)
    
    for u, v in E:
        x1, y1 = V[u]
        x2, y2 = V[v]
        distance = np.sqrt((x2 - x1)**2 + (y2 - y1)**2)
        matrix[u][v] = distance
    
    for u, v in P:
        matrix[u][v] = 0
    
    return matrix

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Uso: python3 visualizer.py filename.txt")
        sys.exit(1)
    
    filename = sys.argv[1]
    V, E, P = read(filename)
    plot_graph(V, E, P)
    
    matrix = adjacency_matrix(V, E, P)
    plot_matrix(matrix)

