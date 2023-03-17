#include<iostream>
#include<vector>
#include<map>
#include<string>

using namespace std;

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=970
// https://www.twblogs.net/a/5b8276612b717766a1e85dd8

map<string, int > wordMap;
vector<string> wordList;
// int dp[N];

int main(){
    int max_len = 0, num = 0;
    string word;
    while(cin >> word){
        wordList.push_back(word);
    }
    vector<int> dp(wordList.size() + 1, 0);     //dp[i] = the longest edit step ladder ending at wordList[i]
    for(int i = 0; i < wordList.size(); i++){
        for(int j = 0; j < wordList[i].size(); j++){
            string newWord = wordList[i];
            newWord[j] = '*';   //只需要紀錄 * 的位置，因為 * 可以代表任何字母
            if(wordMap.find(newWord) != wordMap.end())
                dp[i] = max(dp[i], dp[wordMap[newWord]] + 1);   // 可以從newWord轉換而來
            wordMap[newWord] = i;   //要求最長的，所以要更新，因為i會越來越大   newword 可由第i個字串轉換而來

            newWord = wordList[i].substr(0, j) + '*' + wordList[i].substr(j);   //插入 刪除 等價
            if(wordMap.find(newWord) != wordMap.end()) //代表有字串可以由newWord轉換而來
                dp[i] = max(dp[i], dp[wordMap[newWord]] + 1);
            wordMap[newWord] = i;
        }
        string newWord = wordList[i] + '*';
        if(wordMap.find(newWord) != wordMap.end())
            dp[i] = max(dp[i], dp[wordMap[newWord]] + 1);
        wordMap[newWord] = i;
        max_len = max(max_len, dp[i] + 1);  //要記得加1，因為dp[i]是從0開始算的
    }
    cout << max_len << endl;        // the number of words in the longest edit step ladder
}


// cout << word.insert(0, 1,'k') << endl;
// cout << word.insert(0, 1,'p') << endl;
// cout << word << endl;
// cout << word.substr(0, 0) + "__" + word.substr(0) << endl;
// cout << word.substr(0, 2) + "__" + word.substr(2) << endl;
// while(cin >> word){
    // int step = 1;
    // dp.push_back(dp.size());
    // wordMap[word] = dp.size()-1;
    // // insert c berfore word[i]
    // for(int i = 0; i <= word.size(); i++){
    //     string newWord = word.substr(0, i) + '*' + word.substr(i);
    //     // if(newWord > word){
    //     //     break;
    //     // }
    //     if(wordMap.find(newWord) != wordMap.end()){
    //         // step = max(step, wordMap[newWord] + 1);
    //         dp[]
    //     }
    //     // for(char c = 'a'; c <= 'z'; c++){
    //     //     string newWord = word.substr(0, i) + c + word.substr(i);
    //     //     if(newWord > word){
    //     //         break;
    //     //     }
    //     //     if(wordMap.find(newWord) != wordMap.end()){
    //     //         step = max(step, wordMap[newWord] + 1);
    //     //     }
    //     // }
    // }

    // //delete word[i]
    // // for(int i = 0; i < word.size(); i++){
    // //     string newWord = word.substr(0, i) + word.substr(i + 1);
    // //     // if(newWord > word){
    // //     //     break;
    // //     // }
    // //     if(wordMap.find(newWord) != wordMap.end()){
    // //         step = max(step, wordMap[newWord] + 1);
    // //     }
    // // }

    // //replace word[i] with c
    // for(int i = 0; i < word.size(); i++){
    //     string newWord = word;
    //     newWord[i] = '*';
    //     // if(newWord > word){
    //     //     break;
    //     // }
    //     if(wordMap.find(newWord) != wordMap.end()){
    //         step = max(step, wordMap[newWord] + 1);
    //     }
    //     // for(char c = 'a'; c <= 'z'; c++){
    //     //     string newWord = word;
    //     //     newWord[i] = c;
    //     //     if(newWord > word){
    //     //         break;
    //     //     }
    //     //     if(wordMap.find(newWord) != wordMap.end()){
    //     //         step = max(step, wordMap[newWord] + 1);
    //     //     }
    //     // }
    // }
    // wordMap[word] = step;
    // max_len = max(max_len, step);
// }