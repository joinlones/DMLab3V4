#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;

// Функция для ввода матрицы смежности
vector<vector<int>> input_adjacency_matrix(int& vertices) {
    cout << "Введите количество вершин: ";
    cin >> vertices;
    vector<vector<int>> adjMatrix(vertices, vector<int>(vertices));
    cout << "Введите матрицу смежности (" << vertices << "x" << vertices << "):\n";
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            cin >> adjMatrix[i][j];
        }
    }
    return adjMatrix;
}

// Преобразование в матрицу инцидентности
void adjacency_to_incidence_matrix(const vector<vector<int>>& adjMatrix) {
    int vertices = adjMatrix.size();
    vector<vector<int>> incidenceMatrix(vertices);
    int edgeCount = 0;

    // Считаем количество рёбер
    for (int i = 0; i < vertices; ++i) {
        for (int j = i; j < vertices; ++j) {
            if (adjMatrix[i][j]) {
                ++edgeCount;
            }
        }
    }

    // Формируем матрицу инцидентности
    incidenceMatrix.assign(vertices, vector<int>(edgeCount, 0));
    int edgeIndex = 0;
    for (int i = 0; i < vertices; ++i) {
        for (int j = i; j < vertices; ++j) {
            if (adjMatrix[i][j]) {
                incidenceMatrix[i][edgeIndex] = 1;
                incidenceMatrix[j][edgeIndex] = 1;
                ++edgeIndex;
            }
        }
    }

    // Вывод матрицы инцидентности
    cout << "Матрица инцидентности:\n";
    for (const auto& row : incidenceMatrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
}

// Преобразование в список смежности
void adjacency_to_adjacency_list(const vector<vector<int>>& adjMatrix) {
    int vertices = adjMatrix.size();
    vector<list<int>> adjacencyList(vertices);

    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (adjMatrix[i][j]) {
                adjacencyList[i].push_back(j);
            }
        }
    }

    // Вывод списка смежности
    cout << "Список смежности:\n";
    for (int i = 0; i < vertices; ++i) {
        cout << i << ": ";
        for (int neighbor : adjacencyList[i]) {
            cout << neighbor << " ";
        }
        cout << "\n";
    }
}

// Преобразование в список инцидентности
void adjacency_to_incidence_list(const vector<vector<int>>& adjMatrix) {
    int vertices = adjMatrix.size();
    int edgeCount = 0;

    // Подсчитываем количество рёбер и создаём список инцидентности
    vector<pair<int, int>> incidenceList;
    for (int i = 0; i < vertices; ++i) {
        for (int j = i; j < vertices; ++j) {
            if (adjMatrix[i][j]) {
                incidenceList.push_back({ i, j });
            }
        }
    }

    // Вывод списка инцидентности
    cout << "Список инцидентности:\n";
    for (const auto& edge : incidenceList) {
        cout << edge.first << " - " << edge.second << "\n";
    }
}

// Проверка, существует ли эйлеров цикл
bool has_eulerian_cycle(const vector<vector<int>>& adjMatrix) {
    int vertices = adjMatrix.size();

    // Проверяем степень каждой вершины: все степени должны быть чётными
    for (int i = 0; i < vertices; ++i) {
        int degree = 0;
        for (int j = 0; j < vertices; ++j) {
            degree += adjMatrix[i][j];
        }
        if (degree % 2 != 0) {
            return false;
        }
    }
    return true;
}

// Построение эйлерова цикла
void find_eulerian_cycle(vector<vector<int>>& adjMatrix) {
    int vertices = adjMatrix.size();

    if (!has_eulerian_cycle(adjMatrix)) {
        cout << "Цикл Эйлера невозможен.\n";
        return;
    }

    stack<int> currPath;
    vector<int> eulerianCycle;
    int currVertex = 0;

    currPath.push(currVertex);
    while (!currPath.empty()) {
        currVertex = currPath.top();

        // Найдем вершину, смежную с currVertex
        bool hasEdges = false;
        for (int i = 0; i < vertices; ++i) {
            if (adjMatrix[currVertex][i] > 0) {
                // Если есть ребро, удаляем его и переходим к следующей вершине
                adjMatrix[currVertex][i]--;
                adjMatrix[i][currVertex]--;
                currPath.push(i);
                hasEdges = true;
                break;
            }
        }

        if (!hasEdges) {
            // Если ребер больше нет, добавляем вершину в цикл и удаляем её из стека
            eulerianCycle.push_back(currVertex);
            currPath.pop();
        }
    }

    // Вывод цикла Эйлера
    cout << "Цикл Эйлера: ";
    for (int vertex : eulerianCycle) {
        cout << vertex << " ";
    }
    cout << "\n";
}

int main() {
    int vertices;
    vector<vector<int>> adjMatrix = input_adjacency_matrix(vertices);

    int choice;
    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Матрица инцидентности\n";
        cout << "2. Список смежности\n";
        cout << "3. Список инцидентности\n";
        cout << "4. Цикл Эйлера\n";
        cout << "5. Выход\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            adjacency_to_incidence_matrix(adjMatrix);
            break;
        case 2:
            adjacency_to_adjacency_list(adjMatrix);
            break;
        case 3:
            adjacency_to_incidence_list(adjMatrix);
            break;
        case 4:
            find_eulerian_cycle(adjMatrix);
            break;
        case 5:
            return 0;
        default:
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    }
    return 0;
}