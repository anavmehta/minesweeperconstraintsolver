#include<bits/stdc++.h>
using namespace std;

int N, M;
#define MAXM 100
#define MAXN 100
bool mines[MAXM][MAXN];
bool grid[MAXM][MAXN];
bool visited[MAXM][MAXN];
int status[MAXM][MAXN];
int dx[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
int dy[9] = {0, 0, 0, -1, -1, -1, 1, 1, 1};

bool isValid(int x, int y){
    return (x >= 0 && y >= 0 && x < N && y < N);
}

void printGrid1(){
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(mines[i][j]) cout << "x ";
            else cout << "_ ";
        }
        cout << endl;
    }
}

void printGrid(bool grid[MAXN][MAXM], int status[MAXN][MAXM])
{
    for (int row = 0; row < N; row++) {
       for (int col = 0; col < M; col++) {
            if(grid[row][col]) cout << "x";
            else cout <<  status[row][col];
       }
       cout << endl;
    }
}


bool isSafe(bool grid[MAXN][MAXM], int status[MAXN][MAXM], int x, int y) {
    if(!isValid(x,y)) return false;
    for(int i=0;i<9;i++){
        if(isValid(x+dx[i], y+dy[i]) && (status[x+dx[i]][y+dy[i]] - 1 < 0)) return(false);
    }
    for(int i=0;i<9;i++){
        if(isValid(x+dx[i],y+dy[i])) status[x+dx[i]][y+dy[i]]--;
    }
    return true;
}
bool findUnvisited(bool visited[MAXN][MAXM], int &x, int &y){
    for (x = 0; x < N; x++)
        for (y = 0; y < N; y++)
            if (!visited[x][y]) return(true);
    return(false);
}

bool isDone(int status[MAXN][MAXM], bool visited[MAXN][MAXM]) {
    bool done = true;
    bool allvisited = true;
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++) {
            done = done && (status[i][j] == 0);
            allvisited=allvisited && visited[i][j];
        }

    if(allvisited) return(done);
    return (false);
}

bool SolveMinesweeper(bool grid[MAXN][MAXM], int status[MAXN][MAXM], bool visited[MAXN][MAXM]) {
    int x, y;


    bool done=isDone(status, visited);
    if(done) return true;
    if(!findUnvisited(visited, x, y)) return false;


    visited[x][y] = true;
    if (isSafe(grid, status, x, y)) {
        grid[x][y] = true;
        if(SolveMinesweeper(grid, status, visited)) return true;
        grid[x][y] = false;
        for(int i=0;i<9;i++){
            if(isValid(x+dx[i],y+dy[i])) status[x+dx[i]][y+dy[i]]++;
        }
    }
    if(SolveMinesweeper(grid, status, visited)) return true;

    visited[x][y] = false;


    return false;
}











int main() {
    int P, rand_val;

    memset(grid, false, sizeof(grid));
    memset(visited, false, sizeof(visited));
    M=100;
    N=100;
    P=50;
   for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            mines[i][j] = false;
            rand_val = rand() % (M*N);
            if (rand_val < M*N*P/100) mines[i][j] = true;
            //else cout << rand_val << endl;
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            status[i][j] = 0;
            for(int k=0;k < 9;k++) {
                if(isValid(i+dx[k], j+dy[k]) && (mines[i+dx[k]][j+dy[k]])) status[i][j]++;
            }
            cout << status[i][j] << " ";
        }
        cout << endl;
    }
    printGrid1();
    if (SolveMinesweeper(grid, status, visited)) {
        printGrid(grid, status);
        return 0;
    } else
        printf("No solution exists\n");

    return 0;
}
