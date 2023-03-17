#include<iostream>
#include<vector>
#include<sstream>
#include<cstring>
#include<map>
#include<iomanip>
#include<algorithm>

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1079

using namespace std;

struct car_data{
    string license;
    string time;
    int fee;
    int type;
    int entrance;
};

int account_fee = 200, trip_fee = 100;


bool cmp(car_data& a, car_data& b){
    if(a.license != b.license)
        return a.license < b.license;
    return a.time < b.time;     //時間可以直接比較字串
}


int main(){
    int n;
    cin >> n;
    while(n--){
        vector<int> toll;
        vector<car_data> cars;
        for(int i = 0; i < 24; i++){
            int temp;
            cin >> temp;
            toll.push_back(temp);
        }
        cin.ignore();

        map<string, int> ans;
        string line;
        while(getline(cin, line) && line.length() > 0){
            istringstream iss(line);
            car_data temp;
            string time, type;
            iss >> temp.license >> time;
            temp.time = time;

            // temp.time = atoi(time.substr(3, 2).c_str()) * 24 * 60 
            //         + atoi(time.substr(6, 2).c_str()) * 60 
            //         + atoi(time.substr(9, 2).c_str());

            iss >> type >> temp.entrance;

            temp.type = (type[1] == 'n') ? 1 : 0;
            temp.fee = toll[atoi(time.substr(6, 2).c_str())];
            cars.push_back(temp);
        }
        sort(cars.begin(), cars.end(), cmp);
        // for(int i = 0; i < cars.size(); i++){
        //     cout<< cars[i].license << " " << cars[i].time << " " << cars[i].type << " " << cars[i].entrance << " " << cars[i].fee << endl;
        // }

        car_data tmp;
        for(int i = 0; i < cars.size(); i++){
            if(cars[i].type == 1)
                tmp = cars[i];
            else{
                if(tmp.type != -1 && cars[i].license == tmp.license){
                    ans[tmp.license] += abs(cars[i].entrance - tmp.entrance) * tmp.fee + trip_fee;
                    tmp.type = -1;
                }
                else if(tmp.type != -1) tmp.type = -1;
            }
        }

        for(auto it = ans.begin(); it != ans.end(); it++){
            cout << it->first << " $" << fixed << setprecision(2) << (float)(it->second + 200) / 100 << endl;
            // cout << it->first << " $" << (it->second + 200) / 100 << "." << (it->second + 200) % 100 << endl;
        }
        if(n)   cout << endl;
    }
}