#include <iostream>
#include <fstream>

struct node {

    char simbolo;
    int x;
    int y;
    bool visited;

};

const int size = 142;
// const int size = 7;

node maze[size][size];

node* find_adj(const node &n) {
    
    char simbolo = n.simbolo;
    int adj_node_x = 0;
    int adj_node_y = 0;
    int adj_node2_x = 0;
    int adj_node2_y = 0;

    std::cout << simbolo << " ";

    switch(simbolo) {
        case '|':
            adj_node_x = n.x + 1;
            adj_node_y = n.y;
            adj_node2_x = n.x - 1;
            adj_node2_y = n.y;
            break;
        case '-':
            adj_node_x = n.x;
            adj_node_y = n.y + 1;
            adj_node2_x = n.x;
            adj_node2_y = n.y - 1;
            break;
        case 'F':
            adj_node_x = n.x;
            adj_node_y = n.y + 1;
            adj_node2_x = n.x + 1;
            adj_node2_y = n.y;
            break;
        case 'J':
            adj_node_x = n.x - 1;
            adj_node_y = n.y;
            adj_node2_x = n.x;
            adj_node2_y = n.y - 1;
            break;
        case '7':
            adj_node_x = n.x;
            adj_node_y = n.y - 1;
            adj_node2_x = n.x + 1;
            adj_node2_y = n.y;
            break;
        case 'L':
            adj_node_x = n.x;
            adj_node_y = n.y + 1;
            adj_node2_x = n.x - 1;
            adj_node2_y = n.y;
            break;
        case 'S':
            adj_node_x = n.x;
            adj_node_y = n.y + 1;
            adj_node2_x = n.x + 1;
            adj_node2_y = n.y;
            break;
    
    }

    node* ptr;

    bool first_visited = maze[adj_node_x][adj_node_y].visited;
    bool second_visited = maze[adj_node2_x][adj_node2_y].visited;

    if (!first_visited) {
        ptr = &maze[adj_node_x][adj_node_y];
    } else if (!second_visited) {
        ptr = &maze[adj_node2_x][adj_node2_y];
    } else {
        if (maze[adj_node_x][adj_node_y].simbolo == 'S') {
            ptr = &maze[adj_node_x][adj_node_y];
        } else {
            ptr = &maze[adj_node2_x][adj_node2_y];
        }
    }

    return ptr;

}

int my_dfs(node *n) {

    if (n->simbolo == 'S' && n->visited) {
        return 0;
    }

    int distanza = 0;
    n->visited = true;

    node* next = find_adj(*n);

    distanza = 1 + my_dfs(next);

    return distanza;
    
}

int main() {

    // added padding '.'
    std::fstream file("inputs/day10_input.txt");
    // std::fstream file("inputs/day10_input_example.txt");
    
    node* start;

    if (file.is_open()) {

        std::string line;
        int riga = 0;

        while (std::getline(file, line)) {
             
            for (int i = 0; i < size; i++) {

                node n;
                n.simbolo = line[i];
                n.x = riga;
                n.y = i;
                n.visited = false;

                maze[riga][i] = n;

                if (line[i] == 'S') {
                    start = &maze[riga][i];
                }

            }

            riga++;

        }

    }

    file.close();

    int risultato = my_dfs(start);

    std::cout << risultato/2 << std::endl;

    return 0;

}