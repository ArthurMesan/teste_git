import sys
import random

def generator(vertices, density, max_portals):
    input_data = []

    for portals in range(0, int(max_portals)): 
        total_edges = density * vertices * (vertices - 1)

        if total_edges < portals:
            raise ValueError("A quantidade de portais escolhida ultrapassa o limite de arcos")

        edges = int(total_edges - portals)

        E = set()
        while len(E) < edges:
            u = random.randint(0, vertices - 1)
            v = random.randint(0, vertices - 1)
            if u != v:
                E.add((u, v))

        P = set()
        while len(P) < portals:
            u = random.randint(0, vertices - 1)
            v = random.randint(0, vertices - 1)
            if u != v and (u, v) not in E:
                P.add((u, v))

        coordinates = [(i,i) for i in range(vertices)]

        energy = random.uniform(0, 100)
        portal_usage = random.randint(0, portals)

        input_data.append(f"{vertices} {edges} {portals}")

        for x, y in coordinates:
            input_data.append(f"{x:.3f} {y:.3f}")

        for e in E:
            input_data.append(f"{e[0]} {e[1]}")

        for p in P:
            input_data.append(f"{p[0]} {p[1]}")

        input_data.append(f"{energy:.3f} {portal_usage}")

    return "\n".join(input_data)

def main():
#    if len(sys.argv) != 3:
#        print("Uso: python3 generator.py <vertices> <densidade>")
#        return
#
#    vertices = int(sys.argv[1])
#    density = float(sys.argv[2])
    
#    max_portals = density * vertices * (vertices - 1)
    input_data = generator(3, 1, 6)
    print(input_data)

    filename = "input.txt"
    counter = 1
    while True:
        try:
            with open(filename, 'x') as file:
                file.write(input_data)
                break
        except FileExistsError:
            filename = f"input_{counter}.txt"
            counter += 1

if __name__ == "__main__":
    main()