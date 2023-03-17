#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include<sstream>
#include<algorithm>
// #include<cctype>
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1135
using namespace std;

struct Team{
    string name;
    int point, win, tie, loss, goals_scored, goals_against, goal_difference;
    Team(string n){
        name = n;
        point = win = tie = loss = goals_scored = goals_against = goal_difference = 0;
    }
};
// unordered_map<string, Team*> teams;
// map<string, int> team_idx;
// vector<Team> teams;

// void calculate(string team1, string team2, int score1, int score2) {
//     int idx1 = team_idx[team1];
//     int idx2 = team_idx[team2];
//     teams[idx1].goals_scored += score1;     //總進球數
//     teams[idx1].goals_against += score2;    //總失球數
//     teams[idx1].goal_difference = teams[idx1].goals_scored - teams[idx1].goals_against;   //進球差
//     teams[idx2].goals_scored += score2;
//     teams[idx2].goals_against += score1;
//     teams[idx2].goal_difference = teams[idx2].goals_scored - teams[idx2].goals_against;
//     if (score1 > score2) {
//         teams[idx1].point += 3;
//         teams[idx1].win++, teams[idx2].loss++;
//     } else if (score1 < score2) {
//         teams[idx2].point += 3;
//         teams[idx2].win++, teams[idx1].loss++;
//     } else {
//         teams[idx1].point++, teams[idx2].point++;
//         teams[idx1].tie++, teams[idx2].tie++;
//     }
// }

bool cmp(Team* a, Team* b){
    if(a->point != b->point) return a->point > b->point;
    if(a->win != b->win) return a->win > b->win;
    if(a->goal_difference != b->goal_difference) return a->goal_difference > b->goal_difference;
    if(a->goals_scored != b->goals_scored) return a->goals_scored > b->goals_scored;
    if((a->win + a->loss + a->tie) != (b->win + b->loss + b->tie)) return (a->win + a->loss + a->tie) < (b->win + b->loss + b->tie);
    string a_name = a->name;
    string b_name = b->name;
    transform(a_name.begin(), a_name.end(), a_name.begin(), ::tolower);
    transform(b_name.begin(), b_name.end(), b_name.begin(), ::tolower);

    // for(int i = 0; i < min(a.name.size(), b.name.size()); i++) {
    //     if (tolower(a.name[i]) != tolower(b.name[i])) return tolower(a.name[i]) < tolower(b.name[i]);
    // }
    return a_name < b_name;
}

int main(){
    int N;
    cin >> N;
    cin.ignore();
    while(N--){
        // teams.clear();  //team_idx.clear(), 
        string contest, team_name;
        getline(cin, contest);
        cout << contest << endl;
        int team_num, play_num;
        unordered_map<string, Team*> teams;
        cin >> team_num;
        cin.ignore();
        for(int i = 0; i < team_num; i++){
            getline(cin, team_name);
            teams[team_name] = new Team(team_name);
            // team_idx[team_name] = i;
            // teams.push_back(Team(team_name));
        }
        cin >> play_num;
        cin.ignore();
        for(int i = 0; i < play_num; i++){
            getline(cin, contest);
            string team1 = contest.substr(0, contest.find('#'));
            string s1 = contest.substr(contest.find('#') + 1, contest.find('@') - contest.find('#') - 1);
            string s2 = contest.substr(contest.find('@') + 1, contest.find('#', contest.find('@')) - contest.find('@') - 1);
            string team2 = contest.substr(contest.rfind('#') + 1);
            char c;
            // cout<<team1<<" "<<score<<" "<<team2<<endl;
            int score1 = stoi(s1), score2 = stoi(s2);
            // istringstream iss(score);
            // iss >> score1 >> c >> score2;
            teams[team1]->goals_scored += score1;     //總進球數
            teams[team1]->goals_against += score2;    //總失球數
            teams[team2]->goals_scored += score2;     //總進球數
            teams[team2]->goals_against += score1;    //總失球數
            if(score1 > score2){
                teams[team1]->win++, teams[team2]->loss++;
            }
            else if(score1 < score2){
                teams[team2]->win++, teams[team1]->loss++;
            }
            else{
                teams[team1]->tie++, teams[team2]->tie++;
            }
            // calculate(team1, team2, score1, score2);
        }
        vector<Team*> v;
        for(auto& p : teams){
            p.second->goal_difference = p.second->goals_scored - p.second->goals_against;
            p.second->point = p.second->win * 3 + p.second->tie;
            v.push_back(p.second);
        }

        sort(v.begin(), v.end(), cmp);

        for(int i = 0; i < team_num; i++){
            cout << i + 1 << ") " << v[i]->name << " " << v[i]->point << "p, " << v[i]->win + v[i]->loss + v[i]->tie << "g (" << v[i]->win << "-" << v[i]->tie
                << "-" << v[i]->loss << "), " << v[i]->goal_difference << "gd (" << v[i]->goals_scored << "-" << v[i]->goals_against << ")" << endl;
        }
        if(N)
            cout << endl;
    }
}

// int main(){
//     string a = "Brazil#2@1#Scotland";
//     string b = a.substr(0, a.find('#'));
//     string c = a.substr(a.find('#') + 1, 3);
//     string d = a.substr(a.rfind('#')+1);
//     cout<<b<<endl;
//     cout<<c<<endl;
//     cout<<d<<endl;
// }

// struct sleep_time {
//     int start_hour, start_minute;
//     int duration;
// };

// bool cmp2(const sleep_time &a, const sleep_time &b){
//     if(a.duration == b.duration){
//         if(a.start_hour == b.start_hour)
//             return a.start_minute < b.start_minute;
//         else
//             return a.start_hour < b.start_hour;
//     }
//     else
//         return a.duration > b.duration;
// }

        // if(times[0].start_hour != 10 || times[0].start_minute != 0){
        //     sleep_time s;
        //     s.start_hour = 10, s.start_minute = 0, s.duration = times[0].start_hour * 60 + times[0].start_minute - 600;
        //     sleep_times.push_back(s);
        // }
        // 
        // for(int i = 1; i < times.size() - 1; i++){
        //     if(times[i].end_hour == times[i+1].start_hour && times[i].end_minute == times[i+1].start_minute)
        //         continue;
        //     else{
        //         sleep_time s;
        //         s.start_hour = times[i].end_hour, s.start_minute = times[i].end_minute;
        //         s.duration = times[i+1].start_hour * 60 + times[i+1].start_minute - times[i].end_hour * 60 - times[i].end_minute;
        //         sleep_times.push_back(s);
        //     }
        // }
        //
        // if(times[times.size() - 1].end_hour != 18 || times[times.size() - 1].end_minute != 0){
        //     sleep_time s;
        //     s.start_hour = times[times.size() - 1].end_hour, s.start_minute = times[times.size() - 1].end_minute;
        //     s.duration = 1080 - times[times.size() - 1].end_hour * 60 - times[times.size() - 1].end_minute;
        //     sleep_times.push_back(s);
        // }
        //
        // sort(sleep_times.begin(), sleep_times.end(), cmp2);
        //  
        // for(sleep_time a : sleep_times){
        //     cout<< a.start_hour << ":" << a.start_minute << " " << a.duration << endl;
        // }
