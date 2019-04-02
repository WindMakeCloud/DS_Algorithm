#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

// 给定一个map，它包含一些单词作为Key，和只在
// 一个字母上彼此互异的一些单词vector对象作为
// Value，输出那些具有minWords个或更多的通过
// 单字母替换所得单词中的单词。
void printHighChangeables(
    const map<string, vector<string>> & adjacentWords,
    int minWords = 15)
    {
        for (auto & entry : adjacentWords)
        {
            const vector<string> & words = entry.second;
            if (words.size() >= minWords)
            {
                cout << entry.first << " (" << words.size() << "): ";
                for (auto & str : words)
                    cout << " " << str;
                cout << endl;
            }
        }
    }

// 如果word1和word2具有相同的长度
// 并且只有一个字母不同，则返回true
bool oneCharOff(const string & word1, const string & word2)
{
    if (word1.length() != word2.length())
        return false;
    
    int  diffs = 0;

    for (int i = 0; i < word1.length(); ++i)
        if (word1[i] != word2[i])
            if (++diffs > 1)
                return false;
    
    return diffs == 1;
}

// one map:计算map对象，其中关键字为单词，而值则是一些
// 只在一个字母上与对应关键字不同的单词组成的向
// 量，使用一个二次的算法
map<string, vector<string>> fstComputeAdjWords(const vector<string> & words)
{
    map<string, vector<string>> adjWords;

    for (int i = 0; i < words.size(); ++i)
        for (int j = i+1; j < words.size(); ++j)
            if (oneCharOff(words[i], words[j]))
            {
                adjWords[words[i]].push_back(words[j]);
                adjWords[words[j]].push_back(words[i]);
            }
    
    return adjWords;
}

// two map:计算map对象，其中Key是单词，Value是单词组成的向量
// 向量中的单词只在一个字母上与对应的Key不同
// 使用一个二次算法，通过保留一个附加的map加速处理过程
// 这个附加的map按长度将单词分组
map<string, vector<string>> secComputeAdjWords(const vector<string> & words)
{
    map<string, vector<string>> adjWords;
    map<int, vector<string>> wordsByLength;

    // 按长度将单词分组
    for (auto & thisWord : words)
        wordsByLength[thisWord.length()].push_back(thisWord);

    // 对每组分别进行处理
    for (auto & entry : wordsByLength)
    {
        const vector<string> & groupsWords = entry.second;

        for (int i = 0; i < groupsWords.size(); ++i)
            for (int j = i+1; j < groupsWords.size(); ++j)
                if (oneCharOff(groupsWords[i], groupsWords[j]))
                {
                    adjWords[groupsWords[i]].push_back(groupsWords[j]);
                    adjWords[groupsWords[j]].push_back(groupsWords[i]);
                }
    }

    return adjWords;
}

// 计算map对象，其中Key为单词，Value为单词的vector
// vector中的单词只在一个子母上不同于对应的Key
// 使用一个高效的算法，该算法用到一个map运行时间为
// O(NlogN)
map<string, vector<string>> thrComputeAdjWords(const vector<string> & words)
{
    map<string, vector<string>> adjWords;
    map<int, vector<string>> wordsByLength;

    // 将单词按长度分组
    for (auto & str : words)
        wordsByLength[str.length()].push_back(str);

    // 对每组分别处理
    for (auto & entry : wordsByLength)
    {
        const vector<string> & groupWords = entry.second;
        int groupNum = entry.first;

        // 对每组的每一个位置进行处理
        for (int i = 0; i < groupNum; ++i)
        {
            // 删除特定位置的字母，算出代表
            // 具有相同代表的单词是相邻的；填充map
            map<string, vector<string>> repToWords;

            for (auto & str : groupWords)
            {
                string rep = str;
                rep.erase(i, 1);
                repToWords[rep].push_back(str);
            }

            // 然后查找那些具有多于一个串的map值
            for (auto & entry : repToWords)
            {
                const vector<string> & clique = entry.second;
                if (clique.size() >= 2)
                    for (int p = 0; p < clique.size(); ++p)
                        for (int q = p+1; q < clique.size(); ++q)
                        {
                            adjWords[clique[p]].push_back(clique[q]);
                            adjWords[clique[q]].push_back(clique[p]);
                        }
            }
        }
    }

    return adjWords;
}