#include <iostream>
#include <fstream>
#include <string>

struct node {

    char simbolo;
    int x;
    int y;
    bool visited;

};

const int size1 = 142;
const int size2 = 142;

node maze[size1][size2];

node* find_adj(const node &n) {
    
    char simbolo = n.simbolo;
    int adj_node_x = 0;
    int adj_node_y = 0;
    int adj_node2_x = 0;
    int adj_node2_y = 0;

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
    // std::fstream file("inputs/day10_2_input_example.txt");
    
    node* start;

    if (file.is_open()) {

        std::string line;
        int riga = 0;

        while (std::getline(file, line)) {
             
            for (int i = 0; i < size2; i++) {

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

    int result = my_dfs(start);

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {

            if (maze[i][j].visited == false) {
                maze[i][j].simbolo = '.';
            }

        }
    }

    int sum = 0;

    for (int i = 0; i < size1; i++) {

        bool is_in_region = false;
        char corner = '\0';

        for (int j = 0; j < size2; j++) {

            if (maze[i][j].visited == true) {
                    
                switch(maze[i][j].simbolo) {
                    case '-':
                            break;
                    case '|':
                            is_in_region = !is_in_region;
                            break;
                    case 'F':
                            corner = 'F';    
                            break;
                    case 'L':
                            corner = 'L';
                            break;
                    case 'J':
                            if (corner == 'F') {
                                is_in_region = !is_in_region;
                                corner = '\0';
                            }
                            break;

                    case '7':
                            if (corner == 'L') {
                                is_in_region = !is_in_region;
                                corner = '\0';
                            }
                            break;

                    case 'S':
                            break;
                            
                    default:
                            break;
                    
                }

            } else {

                if (is_in_region) {
                    sum++;
                }

            }
                
        }           

    }

    std::cout << sum << std::endl;

    return 0;

}