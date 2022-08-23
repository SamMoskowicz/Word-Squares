#include <fstream>
#include <iostream>
#include <vector>

bool isLetter(char c)
{
    return tolower(c) >= 'a' && tolower(c) <= 'z';
}

std::string rearrangeWord(std::string &word)
{
    std::string res;
    for (char c : word)
    {
        if (!isLetter(c))
            return "";
        res += tolower(c);
    }
    return res;
}

int main()
{
    std::ifstream wordsFile("words3");
    std::vector<std::vector<std::string>> rearrangedWords;
    std::string currWord;
    while (getline(wordsFile, currWord))
    {
        std::string rearranged = rearrangeWord(currWord);
        if (!rearranged.length())
            continue;
        if (rearranged.length() >= rearrangedWords.size())
            rearrangedWords.resize(rearranged.length() + 1);
        rearrangedWords[rearranged.length()].push_back(rearranged);
    }
    wordsFile.close();
    for (int i = 1; i < (int)rearrangedWords.size(); i++)
    {
        std::ofstream currFile("./rearranged_words4/" + std::to_string(i));
        currFile << std::to_string(rearrangedWords[i].size()) << "\n";
        for (std::string &word : rearrangedWords[i])
            currFile << word << "\n";
        currFile.close();
        std::cout << "wrote " << rearrangedWords[i].size() << " " << i << " letter words to file "
                  << "/rearranged_words/" + std::to_string(i) << std::endl;
    }
}