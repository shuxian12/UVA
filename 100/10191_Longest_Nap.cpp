#include<iostream>
#include<vector>
#include<algorithm>

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1132

using namespace std;

struct Time{
    int start_hour, start_minute, end_hour, end_minute;
};

bool cmp(const Time& a, const Time& b){
    if(a.start_hour != b.start_hour)
        return a.start_hour < b.start_hour;
    else
        return a.start_minute < b.start_minute;
}

int main(){
    int num, start_hour, start_minute, end_hour, end_minute, count = 1;
    char c, d;
    while(cin >> num){
        vector<Time> times;
        // vector<sleep_time> sleep_times;
        while(num--){
            string line;
            cin >> start_hour >> c >> start_minute >> end_hour >> d >> end_minute;
            getline(cin, line);
            // cout<< start_hour << ":" << start_minute << " " << end_hour << ":" << end_minute << endl;
            Time t;
            t.start_hour = start_hour, t.start_minute = start_minute, t.end_hour = end_hour, t.end_minute = end_minute;
            times.push_back(t);
        }
        sort(times.begin(), times.end(), cmp);
        // for(Time a : times){
        //     cout<< a.start_hour << ":" << a.start_minute << " " << a.end_hour << ":" << a.end_minute << endl;
        // }

        Time t, nap;
        t.start_hour = 10, t.start_minute = 0;
        int duration = 0;

        for(Time task : times){
            if(task.start_hour > t.start_hour || (task.start_hour == t.start_hour && task.start_minute > t.start_minute)){
                if((task.start_hour - t.start_hour) * 60 + (task.start_minute - t.start_minute) > duration){
                    duration = (task.start_hour - t.start_hour) * 60 + (task.start_minute - t.start_minute);
                    nap.start_hour = t.start_hour, nap.start_minute = t.start_minute;
                }
            }
            t.start_hour = task.end_hour, t.start_minute = task.end_minute;
        }
        if((18 - t.start_hour) * 60 + (0 - t.start_minute) > duration){
            duration = (18 - t.start_hour) * 60 + (0 - t.start_minute);
            nap.start_hour = t.start_hour, nap.start_minute = t.start_minute;
        }

        string hour = to_string(nap.start_hour).size() > 1 ? to_string(nap.start_hour) : "0" + to_string(nap.start_hour);
        string min = to_string(nap.start_minute).size() > 1 ? to_string(nap.start_minute) : "0" + to_string(nap.start_minute);
        cout << "Day #" << count++ << ": the longest nap starts at " << hour << ":" << min << " and will last for ";
        if(duration / 60 == 0)
            cout << duration << " minutes." << endl;
        else
            cout << duration / 60 << " hours and " << duration % 60 << " minutes." << endl;

        times.clear();
    }
}

