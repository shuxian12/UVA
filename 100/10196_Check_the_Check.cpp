#include<iostream>
#include<cstring>
using namespace std;

// https://zerojudge.tw/ShowProblem?problemid=d368

char board[8][8];

// x 都同值，y 不同值
bool check_p(int x, int y, int kingx, int kingy){
    if(x - kingx == 1 && abs(y - kingy) == 1)
        return true;
    return false;
}

bool check_n(int x, int y, int kingx, int kingy){
    if(abs(x - kingx) == 2 && abs(y - kingy) == 1)
        return true;
    if(abs(x - kingx) == 1 && abs(y - kingy) == 2)
        return true;
    return false;
}

bool check_r(int x, int y, int kingx, int kingy){
    if(x == kingx){
        int miny = min(y, kingy);
        int maxy = max(y, kingy);
        for(int i = miny + 1; i < maxy; i++)
            if(board[x][i] != '.')
                return false;
        return true;
    }
    if(y == kingy){
        int minx = min(x, kingx);
        int maxx = max(x, kingx);
        for(int i = minx + 1; i < maxx; i++)
            if(board[i][y] != '.')
                return false;
        return true;
    }
    return false;
}

bool check_b(int x, int y, int kingx, int kingy){
    if(abs(x - kingx) == abs(y - kingy)){
        int directX = x - kingx > 0 ? -1 : 1;
        int directy = y - kingy > 0 ? -1 : 1;
        int step = abs(x - kingx);
        while(step > 1){
            x += directX;
            y += directy;
            if(board[x][y] != '.')
                return false;
            step--;
        }
        return true;
    }
    return false;
}

bool check_q(int x, int y, int kingx, int kingy){
    return check_r(x, y, kingx, kingy) || check_b(x, y, kingx, kingy);
}

void check(int count){
    int whiteKingx, whiteKingy, blackKingx, blackKingy;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] == 'K'){
                whiteKingx = i;
                whiteKingy = j;
            }
            if(board[i][j] == 'k'){
                blackKingx = i;
                blackKingy = j;
            }
        }
    }
    // cout<<whiteKingx<<" "<<whiteKingy<<" "<<blackKingx<<" "<<blackKingy<<endl;
    bool whiteCheck = false, blackCheck = false;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] == 'P')
                blackCheck = check_p(i, j, blackKingx, blackKingy);
            else if(board[i][j] == 'p')
                whiteCheck = check_p(whiteKingx, whiteKingy, i, j);
            else if(board[i][j] == 'N')
                blackCheck = check_n(i, j, blackKingx, blackKingy);
            else if(board[i][j] == 'n')
                whiteCheck = check_n(i, j, whiteKingx, whiteKingy);
            else if(board[i][j] == 'R')
                blackCheck = check_r(i, j, blackKingx, blackKingy);
            else if(board[i][j] == 'r')
                whiteCheck = check_r(i, j, whiteKingx, whiteKingy);
            else if(board[i][j] == 'B')
                blackCheck = check_b(i, j, blackKingx, blackKingy);
            else if(board[i][j] == 'b')
                whiteCheck = check_b(i, j, whiteKingx, whiteKingy);
            else if(board[i][j] == 'Q')
                blackCheck = check_q(i, j, blackKingx, blackKingy);
            else if(board[i][j] == 'q')
                whiteCheck = check_q(i, j, whiteKingx, whiteKingy);

            if(whiteCheck){
                cout << "Game #" << count << ": white king is in check." << endl;
                return;
            }
            if(blackCheck){
                cout << "Game #" << count << ": black king is in check." << endl;
                return;
            }
        }
    }
    cout << "Game #" << count << ": no king is in check." << endl;
}

bool read(){
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            cin >> board[i][j];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] != '.')  // 有棋子
                return true;
        }
    }
    return false;
}

int main(){
    string line;
    int gamecount = 1, j = 0;
    bool test = read();

    while(test){
        check(gamecount);
        // cout<<board[1][3]<<" "<<board[7][6]<<" "<<board[1][7]<<endl;
        // cout<<check_q(1, 3, 1, 7)<<endl;
        gamecount++;
        getline(cin, line);
        test = read();
    }
    // while(getline(cin, line)){
    //     if(line != ""){
    //         for(int i = 0; i < 8; i++)
    //             board[j++][i] = line[i];
    //     }
    //     else{
    //         for(int i = 0; i < 8; i++){
    //             for(int j = 0; j < 8; j++){
    //                 if(board[i][j] != '.')
    //                     test = true;
    //             }
    //         }
    //         if(test){
    //             check(gamecount++);
    //             test = false;
    //         }
    //         else
    //             break;;
    //         j = 0;
    //     }
    // }
}