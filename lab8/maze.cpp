#include <bits/stdc++.h>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

void get_way(vector<vector<int>> &distances, vector<char> &path, pair<int, int> &start_point, pair<int, int> current_point, pair<int, int> &finish_point, int shift, int vertical_size, int horizontal_size)
{
    int n = vertical_size, m = horizontal_size;
    int i = current_point.first, j = current_point.second;
    int i_start = start_point.first, j_start = start_point.second;
    int i_finish = finish_point.first, j_finish = finish_point.second;

    if (distances[i][j] != 0)
    {
        if (i > 0 && i < n && j >= 0 && j < m && distances[i - 1][j] == distances[i_finish][j_finish] - shift)
        {
            path.push_back('D');
            get_way(distances, path, start_point, {i - 1, j}, finish_point, shift + 1, n, m);
        }
        else if (i >= 0 && i < n - 1 && j >= 0 && j < m && distances[i + 1][j] == distances[i_finish][j_finish] - shift)
        {
            path.push_back('U');
            get_way(distances, path, start_point, {i + 1, j}, finish_point, shift + 1, n, m);
        }
        else if (i >= 0 && i < n && j > 0 && j < m && distances[i][j - 1] == distances[i_finish][j_finish] - shift)
        {
            path.push_back('R');
            get_way(distances, path, start_point, {i, j - 1}, finish_point, shift + 1, n, m);
        }
        else if (i >= 0 && i < n && j >= 0 && j < m - 1 && distances[i][j + 1] == distances[i_finish][j_finish] - shift)
        {
            path.push_back('L');
            get_way(distances, path, start_point, {i, j + 1}, finish_point, shift + 1, n, m);
        }
    }
    else
        return;
}

int bfs(vector<vector<int>> &maze_map, vector<vector<int>> &distances, pair<int, int> start_point, pair<int, int> finish_point)
{
    int vertical_size = maze_map.size(), horizontal_size = maze_map[0].size();

    vector<vector<bool>> visited(100, vector<bool>(100, false));
    queue<pair<int, int>> queue_for_check;

    distances[start_point.first][start_point.second] = 0;
    visited[start_point.first][start_point.second] = true;
    queue_for_check.push({start_point.first, start_point.second});

    while (!queue_for_check.empty())
    {
        int first_coord = queue_for_check.front().first, second_coord = queue_for_check.front().second;
        queue_for_check.pop();

        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
            {
                if (abs(i) + abs(j) != 1)
                    continue;

                if (first_coord + i >= 0 && first_coord + i < vertical_size && second_coord + j >= 0 && second_coord + j < horizontal_size)
                {
                    if (maze_map[first_coord + i][second_coord + j] != 0 && !visited[first_coord + i][second_coord + j])
                    {
                        visited[first_coord + i][second_coord + j] = true;
                        distances[first_coord + i][second_coord + j] = distances[first_coord][second_coord] + 1;
                        queue_for_check.push({first_coord + i, second_coord + j});
                    }
                }
            }
    }

    if (distances[finish_point.first][finish_point.second] == -1)
        return -1;

    out << distances[finish_point.first][finish_point.second] << '\n';

    vector<char> path;
    get_way(distances, path, start_point, {finish_point.first, finish_point.second}, finish_point, 1, vertical_size, horizontal_size);

    for (int i = path.size() - 1; i >= 0; i--)
        out << path[i];

    return 0;
}

int main()
{
    char cell_status;
    int vertical_side, horizontal_side;

    in >> vertical_side >> horizontal_side;
    vector<vector<int>> maze_map(vertical_side, vector<int>(horizontal_side));

    pair<int, int> start_point = {-1, -1}, finish_point = {-1, -1};
    for (int i = 0; i < vertical_side; i++)
        for (int j = 0; j < horizontal_side; j++)
        {
            in >> cell_status;

            if (cell_status == '#')
                maze_map[i][j] = 0;

            else
            {
                maze_map[i][j] = 1;

                if (cell_status == 'S')
                    start_point = {i, j};

                if (cell_status == 'T')
                    finish_point = {i, j};
            }
        }

    if (start_point.first == start_point.second && start_point.first == -1 || finish_point.first == finish_point.second && finish_point.first == -1)
    {
        out << -1;
        return 0;
    }

    vector<vector<int>> distances(vertical_side, vector<int>(horizontal_side, -1));

    if (bfs(maze_map, distances, start_point, finish_point) == -1)
    {
        out << -1;
        return 0;
    }

    return 0;
}