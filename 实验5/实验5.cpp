#define MaxSize 100
#define Size 8
#include <iostream>
using namespace std;


// 迷宫问题
typedef struct
{
    int i;
    int j;
}Box;

typedef struct
{
    Box data[MaxSize];
    int length;
}PathType;


int mg[Size + 2][Size + 2] = { {1,1,1,1,1,1,1,1,1,1},{1,0,0,1,0,0,0,1,0,1},
    {1,0,0,1,0,0,0,1,0,1},{1,0,0,0,0,1,1,0,0,1},{1,0,1,1,1,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,1},{1,0,1,0,0,0,1,0,0,1},{1,0,1,1,1,0,1,1,0,1},
    {1,1,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1,1} };

void mgPath(int xi, int yi, int xe, int ye, PathType path)
{
    int count = 0;
    int di, k, i, j;
    if (xi == xe && yi == ye) {
        path.data[path.length].i = xi;
        path.data[path.length].j = yi;
        path.length++;
        ++count;
        cout << "迷宫路径如下：" << endl;
        for (k = 0; k < path.length; k++) {
            cout << "\t(" << path.data[k].i << ',' << path.data[k].j << ')';
            if ((k + 1) % 5 == 0) {
                cout << endl;
            }
        }
        cout << endl;
    }
    else {
        if (mg[xi][yi] == 0) {
            di = 0;
            while (di < 4) {
                switch (di)
                {
                case 0:
                    i = xi - 1; j = yi; break;
                case 1:
                    i = xi; j = yi + 1; break;
                case 2:
                    i = xi + 1; j = yi; break;
                case 3:
                    i = xi; j = yi - 1; break;
                }
                path.data[path.length].i = xi;
                path.data[path.length].j = yi;
                path.length++;
                mg[xi][yi] = -1;
                mgPath(i, j, xe, ye, path);

                path.length--;
                mg[xi][yi] = 0;
                di++;
            }
        }
    }
}



// N皇后问题
int q[Size];

int place(int k, int j) 
{
    int i = 1;
    while (i < k) 
    {
        if ((q[i] == j) || (abs(q[i] - j) == abs(k - i)))
            return 0;
        i++;
    }
    return 1;
}

void queen(int k, int n)
{
    int j;
    if (k > n)
    {
        for (int i = 1; i <= n; i++)
            cout << q[i];
        cout << endl;
    }
    else
    {
        for(j=1;j<=n;j++)
            if (place(k, j))   //在第k行寻找一个可以存放的位置
            {
                q[k] = j;
                queen(k + 1, n);
            }
    }
}

void queen(int n)
{
    queen(1, n);
}

int main() {
    queen(6);
}