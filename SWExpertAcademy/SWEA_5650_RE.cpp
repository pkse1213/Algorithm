//
//  SWEA_5650_RE.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/05.
//  Copyright © 2020 박세은. All rights reserved.
//

// 5650. [모의 SW 역량테스트] 핀볼 게임 다시풀기2


#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
struct holeInfo {
    int r, c, n;
    holeInfo() {}
    holeInfo(int rr, int cc, int nn)
    {
        r = rr; c = cc; n = nn;
    }
};
int T, N, answer, board[101][101];
vector<holeInfo> hole;
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };




int reverseDir(int d)
{
    if (d == 0) return 1;
    if (d == 1) return 0;
    if (d == 2) return 3;
    if (d == 3) return 2;
}

int checkDir(int type, int d)
{
    if (type == 1)
    {
        if (d == 1) return 3;
        else if (d == 2) return 0;
        else return reverseDir(d);
    }
    if (type == 2)
    {
        if (d == 0) return 3;
        else if (d == 2) return 1;
        else return reverseDir(d);
    }
    if (type == 3)
    {
        if (d == 3) return 1;
        else if (d == 0) return 2;
        else return reverseDir(d);
    }
    if (type == 4)
    {
        if (d == 3) return 0;
        else if (d == 1) return 2;
        else return reverseDir(d);
    }
}



void gameStart(int sr, int sc, int d)
{
    int r = sr;
    int c = sc;
    int score = 0;
    while (1)
    {
        r += dr[d];
        c += dc[d];
        //cout << r << ' ' << c << ' ' << d << endl;

        if (r < 0 || r > N - 1 || c < 0 || c > N - 1 || board[r][c] == 5)
        {
            score++;
            r -= dr[d];
            c -= dc[d];
            d = reverseDir(d);
        }
        // 홀이나 시작위치
        if ((board[r][c] == -1) || (r == sr && c == sc))
        {
            if (score > answer) answer = score;
            return;
        }
        else if (1 <= board[r][c] && board[r][c] <= 4)
        {
            score++;
            d = checkDir(board[r][c], d);
        }
        else if (6 <= board[r][c] && board[r][c] <= 10)
        {
            for (int i = 0; i < (int)hole.size(); i++)
            {
                if (board[r][c] == hole[i].n && !(r == hole[i].r && c == hole[i].c))
                {
                    r = hole[i].r;
                    c = hole[i].c;
                    break;
                }
            }
        }
    }
}

int main()
{
    //freopen("input.txt", "r", stdin);
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        hole.clear();
        answer = 0;
        cin >> N;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> board[i][j];
                if (6 <= board[i][j] && board[i][j] <= 10)
                {
                    hole.push_back(holeInfo(i, j, board[i][j]));
                }
            }
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (board[i][j] == 0)
                {
                    for (int d = 0; d < 4; d++)
                    {
                        gameStart(i, j, d);
                    }
                }
            }
        }

        printf("#%d %d\n", t, answer);

    }
    return 0;
}
