#include<iostream>
#include<vector>
#include<set>

using namespace std;

char image[255][255];

void fill_color(vector<vector<char>> &image, char C, int x, int y, int horizontal, int vertical){
  for(int i = y ; i < y + vertical; i++)
    for(int j = x ; j < x + horizontal; j++)
      image[i][j] = C;
}

void I(vector<vector<char> > &image, int m, int n) {
    image.resize(m);
    for (int i = 0; i < m; i++) {
        image[i].resize(n, 'O');
    }
}

void C(vector<vector<char> > &image) {
    for (int i = 0; i < image.size(); i++) {
        for (int j = 0; j < image[i].size(); j++) {
            image[i][j] = 'O';
        }
    }
}

void L(vector<vector<char> > &image, int x, int y, char c) {
    image[y - 1][x - 1] = c;
}

void V(vector<vector<char> > &image, int x, int y1, int y2, char c) {
    if (y1 > y2) {
        int temp = y1;
        y1 = y2;
        y2 = temp;
    }
    for (int i = y1 - 1; i < y2; i++) {
        image[i][x - 1] = c;
    }
}

void H(vector<vector<char> > &image, int x1, int x2, int y, char c) {
    if (x1 > x2) {
        int temp = x1;
        x1 = x2;
        x2 = temp;
    }
    for (int i = x1 - 1; i < x2; i++) {
        image[y - 1][i] = c;
    }
}

void K(vector<vector <char> > &image, int x1, int y1, int x2, int y2, char c){
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    for(int i = y1 - 1; i < y2; i++){
        for(int j = x1 - 1; j < x2; j++){
            image[i][j] = c;
        }
    }
}

void fill(vector<vector<char> > &image, int x, int y, char p, char c) {
    if (x < 1 || x > image[0].size() || y < 1 || y > image.size() || image[y][x] != p) return;
    image[y][x] = c;
    fill(image, x + 1, y, p, c);
    fill(image, x - 1, y, p, c);
    fill(image, x, y + 1, p, c);
    fill(image, x, y - 1, p, c);
}

void F(vector<vector<char> > &image, int x, int y, char c) {
    if (image[y - 1][x - 1] == c) {
        return;
    }
    char old = image[y - 1][x - 1];
    image[y - 1][x - 1] = c;
    if (x > 1) {
        if (image[y - 1][x - 2] == old) {
            F(image, x - 1, y, c);
        }
    }
    if (x < image[y - 1].size()) {
        if (image[y - 1][x] == old) {
            F(image, x + 1, y, c);
        }
    }
    if (y > 1) {
        if (image[y - 2][x - 1] == old) {
            F(image, x, y - 1, c);
        }
    }
    if (y < image.size()) {
        if (image[y][x - 1] == old) {
            F(image, x, y + 1, c);
        }
    }
}

void S(vector<vector<char> > &image, string name) {
    cout<<name<<endl;
    for(int i = 0; i < image.size(); i++){
        for(int j = 0; j < image[0].size(); j++){
            cout<<image[i][j];
        }
        cout<<endl;
    }
}

int main(){
    int x1,x2,y1,y2;
    char c, command;
    string name;
    vector<vector<char> > image;
    // set<char> commandMap;
    // commandMap.insert('I');
    // commandMap.insert('C');
    // commandMap.insert('L');
    // commandMap.insert('V');
    // commandMap.insert('H');
    // commandMap.insert('K');
    // commandMap.insert('F');
    // commandMap.insert('S');
    // commandMap.insert('X');

    // while(cin>>command){
    //     if(commandMap.find(command) == commandMap.end()){
    //         continue;
    //     }
    //     else if(command == 'I'){
    //         cin>>x1>>y1;
    //         I(image, y1, x1);
    //     }
    //     else if(command == 'C'){
    //         C(image);
    //     }
    //     else if(command == 'L'){
    //         cin>>x1>>y1>>c;
    //         L(image, x1, y1, c);
    //     }
    //     else if(command == 'V'){
    //         cin>>x1>>y1>>y2>>c;
    //         V(image, x1, y1, y2, c);
    //     }
    //     else if(command == 'H'){
    //         cin>>x1>>x2>>y1>>c;
    //         H(image, x1, x2, y1, c);
    //     }
    //     else if(command == 'K'){
    //         cin>>x1>>y1>>x2>>y2>>c;
    //         K(image, x1, y1, x2, y2, c);
    //     }
    //     else if(command == 'F'){
    //         cin>>x1>>y1>>c;
    //         F(image, x1, y1, c);
    //     }
    //     else if(command == 'S'){
    //         cin>>name;
    //         S(image, name);
    //     }
    //     else if(command == 'X'){
    //         break;
    //     }
    // }
    while(cin>>command){
        if(command == 'X')
            break;
            
        switch (command)
        {
        case 'I':
            cin>>x1>>y1;
            fill_color(image, '0', 1, 1, x1, y1);
            break;
        case 'C':
            for (int i = 0; i < image.size(); i++) {
                for (int j = 0; j < image[i].size(); j++) {
                    image[i][j] = 'O';
                }
            }
            break;
        case 'L':
            cin>>x1>>y1>>c;
            image[y1 - 1][x1 - 1] = c;
            break;
        case 'V':
            cin>>x1>>y1>>y2>>c;
            if (y1 > y2) {
                int temp = y1;
                y1 = y2;
                y2 = temp;
            }
            for (int i = y1 - 1; i < y2; i++) {
                image[i][x1 - 1] = c;
            }
            break;
        case 'H':
            cin>>x1>>x2>>y1>>c;
            if (x1 > x2) {
                int temp = x1;
                x1 = x2;
                x2 = temp;
            }
            for (int i = x1 - 1; i < x2; i++) {
                image[y1 - 1][i] = c;
            }
            break;
        case 'K':
            cin>>x1>>y1>>x2>>y2>>c;
            for(int i = y1 - 1; i < y2; i++){
                for(int j = x1 - 1; j < x2; j++){
                    image[i][j] = c;
                }
            }
            break;
        case 'F':
            cin>>x1>>y1>>c;
            F(image, x1, y1, c);
            break;
        case 'S':
            cin>>name;
            cout<<name<<endl;
            for(int i = 0; i < image.size(); i++){
                for(int j = 0; j < image[0].size(); j++){
                    cout<<image[i][j];
                }
                cout<<endl;
            }
            break;
        default:
            break;
        }
    }
}