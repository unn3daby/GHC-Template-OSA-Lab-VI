#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
class Dijkstra
{
private:
	vector<std::vector<int>> _graphMatrix;
	vector<int> _shortestDistances;
	vector<int> _shortestPaths;
public:
	Dijkstra(vector<vector<int>> graphMatrix)
	{
		_graphMatrix = graphMatrix;
		_shortestDistances = vector<int>(_graphMatrix[0].size());
		_shortestPaths = vector<int>(_graphMatrix[0].size());
	}

	void calculateDistancesAndPaths(int startVertex)
	{
		int verticesAmount = _graphMatrix[0].size();

		vector<bool> visited(verticesAmount);

		for (int vertex = 0; vertex < verticesAmount; vertex++)
		{
			_shortestDistances[vertex] = INT_MAX;
			visited[vertex] = false;
		}

		_shortestDistances[startVertex] = 0;
		_shortestPaths[startVertex] = -1;

		for (int i = 1; i < verticesAmount; i++)
		{
			int nearestVertex = -1;
			int shortestDistance = INT_MAX;
			for (int vertex = 0; vertex < verticesAmount; vertex++)
			{
				if (!visited[vertex] && _shortestDistances[vertex] < shortestDistance)
				{
					nearestVertex = vertex;
					shortestDistance = _shortestDistances[vertex];
				}
			}

			visited[nearestVertex] = true;

			for (int vertex = 0; vertex < verticesAmount; vertex++)
			{
				int distance = _graphMatrix[nearestVertex][vertex];

				if (distance > 0 && ((shortestDistance + distance) < _shortestDistances[vertex]))
				{
					_shortestPaths[vertex] = nearestVertex;
					_shortestDistances[vertex] = shortestDistance + distance;
				}
			}
		}
	}

	vector<int> getShortestDistances()
	{
		return _shortestDistances;
	}

	vector<int> getShortestPaths()
	{
		return _shortestPaths;
	}
};

void printPath(int vertex, vector<int> paths)
{
	if (vertex == -1) {
		return;
	}
	printPath(paths[vertex], paths);
	cout << vertex << ' ';
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int n, start, finish;

	ifstream inputFile("matrix.txt"); inputFile >> n;
	cout << "Матрица смежности графа:" << endl;
	vector<vector<int>> graphMatrix(n, vector <int>(n));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			inputFile >> graphMatrix[i][j];
			cout << std::setw(5) << setfill(' ') << graphMatrix[i][j];
		}
		cout << std::endl;
	}

	cout << endl;
	cout << "Введите начальную вершину: "; cin >> start;
	cout << "Введите конечную вершину: "; cin >> finish;
	cout << endl;

	Dijkstra dijkstra(graphMatrix);
	dijkstra.calculateDistancesAndPaths(start);
	vector<int> distances = dijkstra.getShortestDistances();
	vector<int> paths = dijkstra.getShortestPaths();

	cout << "Направление\t Расстояние\tПуть\n";
	cout << start << " -> " << finish << "\t\t ";
	cout << distances[finish] << "\t\t";
	printPath(finish, paths);

	return 0;
}
