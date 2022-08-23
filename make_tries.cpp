#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> makeTrie(std::vector<std::string> &words)
{
    std::vector<std::vector<int>> trie(1, std::vector<int>(26, -1));
    for (std::string &word : words)
    {
        int node = 0;
        for (char c : word)
        {
            if (trie[node][c - 'a'] == -1)
            {
                trie[node][c - 'a'] = trie.size();
                trie.push_back(std::vector<int>(26, -1));
            }
            node = trie[node][c - 'a'];
        }
    }
    return trie;
}

int main()
{
    for (int i = 1; i <= 22; i++)
    {
        std::ifstream wordsFile("./rearranged_words3/" + std::to_string(i));
        int wordsLen;
        wordsFile >> wordsLen;
        std::vector<std::string> words;
        std::string currWord;
        while (getline(wordsFile, currWord))
            words.push_back(currWord);
        wordsFile.close();
        std::vector<std::vector<int>> currTrie = makeTrie(words);
        std::ofstream trieFile("./tries3/" + std::to_string(i));
        trieFile << currTrie.size() << "\n";
        for (int i = 0; i < (int)currTrie.size(); i++)
        {
            for (int j = 0; j < 26; j++)
                trieFile << currTrie[i][j] << " ";
            trieFile << "\n";
        }
        trieFile.close();
    }
}