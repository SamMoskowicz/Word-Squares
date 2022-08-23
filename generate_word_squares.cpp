#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

char grid[23][23];

char res[4000000][23][23];
int resLen;

int trie[300000][26];
int trieSize;

int lastNodes[24][24] = {};

void dfs(int i, int j, int node, int size)
{
    if (j == size)
    {
        i++;
        j = i;
        node = lastNodes[i][j];
    }
    if (i == size)
    {
        if (resLen >= 4000000)
            return;
        // std::cout << "found square for size: " << size << std::endl;
        for (int r = 0; r < size; r++)
            for (int c = 0; c < size; c++)
                res[resLen][r][c] = grid[r][c];
        resLen++;
        // for (std::string word : curr)
        //     std::cout << word << std::endl;
        // std::cout << std::endl;
        return;
    }
    // if (j < i)
    // {
    //     node = 0;
    //     while (j < i)
    //     {
    //         node = trie[node][grid[i][j++] - 'a'];
    //         if (node == -1)
    //             return;
    //     }
    // }
    for (int nxt = 0; nxt < 26; nxt++)
    {
        if (trie[node][nxt] == -1)
            continue;
        grid[i][j] = nxt + 'a';
        grid[j][i] = nxt + 'a';
        lastNodes[i + 1][j] = trie[lastNodes[i][j]][grid[i][j] - 'a'];
        if (lastNodes[i + 1][j] == -1)
            continue;
        dfs(i, j + 1, trie[node][nxt], size);
        if (resLen >= 4000000)
            return;
    }
}

int main()
{
    double totalSeconds = 0;
    for (int i = 7; i <= 22; i++)
    {
        if (i == 8 || i == 9)
            continue;
        std::cout << "starting " << i << std::endl;
        std::ifstream trieFile("./tries3/" + std::to_string(i));
        trieFile >> trieSize;
        for (int r = 0; r < trieSize; r++)
            for (int c = 0; c < 26; c++)
                trieFile >> trie[r][c];
        trieFile.close();
        resLen = 0;
        auto startTime = std::chrono::high_resolution_clock::now();
        dfs(0, 0, 0, i);
        auto endTime = std::chrono::high_resolution_clock::now();
        double currSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / 1000.0;
        totalSeconds += currSeconds;
        std::ofstream resFile("./res3/" + std::to_string(i));
        for (int j = 0; j < resLen; j++)
        {
            for (int k = 0; k < i; k++)
            {
                for (int l = 0; l < i; l++)
                {
                    resFile << res[j][k][l] << " ";
                }
                resFile << "\n";
            }
            resFile << "\n";
        }
        std::cout << "finished " << i << std::endl;
        std::cout << "total " << i << " found: " << resLen << std::endl;
        std::cout << "total seconds to calculate " << i << ": " << currSeconds << std::endl;
        std::cout << std::endl;
    }
    std::cout << "total seconds to calculate all: " << totalSeconds << std::endl;
}