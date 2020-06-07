//
//  SWEA_5644_RE.cpp
//  Algorithm
//
//  Created by 박세은 on 2020/06/07.
//  Copyright © 2020 박세은. All rights reserved.
//

// 5644. [모의 SW 역량테스트] 무선 충전 다시풀기2

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

struct Battery
{
   int r, c, len, power;
   Battery() {}
   Battery(int rr, int cc, int ll, int pp)
   {
      r = rr; c = cc; len = ll; power = pp;
   }
};

int M, A;
vector<int> board[11][11];
vector<Battery> bc;
vector<int> person[2];
int dr[5] = { 0,-1,0,1,0 };
int dc[5] = { 0, 0, 1,0,-1 };

int r1 = 1;
int c1 = 1;
int r2 = 10;
int c2 = 10;
int answer = 0;

int abs(int a)
{
   if (a < 0) return -a;
   else return a;
}

void set_battery()
{
   for (int i = 1; i <= 10; i++)
   {
      for (int j = 1; j <= 10; j++)
      {
         board[i][j].clear();
         for (int b = 0; b < bc.size(); b++)
         {
            int r = bc[b].r;
            int c = bc[b].c;
            int len = bc[b].len;

            if (abs(r - i) + abs(c - j) <= len)
            {
               board[i][j].push_back(b);
            }
         }
      }
   }

   /*for (int i = 1; i <= 10; i++)
   {
      for (int j = 1; j <= 10; j++)
      {
         cout << board[i][j].size() << ' ';
      }
      cout << endl;
   }*/
}

void start()
{
   answer = 0;
   for (int t = -1; t < M; t++)
   {
      /*if (t == 10)
      {
         cout << "";
      }*/
      if (t == -1)
      {
          r1 = 1;
          c1 = 1;
          r2 = 10;
          c2 = 10;
      }
      else
      {
         r1 += dr[person[0][t]];
         c1 += dc[person[0][t]];
         r2 += dr[person[1][t]];
         c2 += dc[person[1][t]];
      }
      int s1 = board[r1][c1].size();
      int s2 = board[r2][c2].size();

      if (s1 >= 1 && s2 >= 1)
      {
         int max = 0;
         for (int i = 0; i < s1; i++)
         {
            for (int j = 0; j < s2; j++)
            {
               if (board[r1][c1][i] == board[r2][c2][j])
               {
                  if (max < bc[board[r1][c1][i]].power)
                     max = bc[board[r1][c1][i]].power;
               }
               else
               {
                  if (max < bc[board[r1][c1][i]].power + bc[board[r2][c2][j]].power)
                     max = bc[board[r1][c1][i]].power + bc[board[r2][c2][j]].power;
               }
            }
         }
         answer += max;
      }
      else
      {
         if (s1 > 0)
         {
            int max = 0;
            for (int i = 0; i < s1; i++)
            {
               if (max < bc[board[r1][c1][i]].power)
                  max = bc[board[r1][c1][i]].power;
            }
            answer += max;
         }
         if (s2 > 0)
         {
            int max = 0;
            for (int i = 0; i < s2; i++)
            {
               if (max < bc[board[r2][c2][i]].power) max = bc[board[r2][c2][i]].power;
            }
            answer += max;
         }
      }
      /*cout << answer << endl;
      cout << r1 << "," << c1 << " " << r2 << "," << c2 << endl;*/
      //cout << answer << endl;

   }
}

int main(int argc, char** argv)
{
   int test_case;
   int T;
   freopen("input.txt", "r", stdin);
   cin >> T;
   for (test_case = 1; test_case <= T; ++test_case)
   {
      person[0].clear();
      person[1].clear();
      bc.clear();
      cin >> M >> A;
      for (int i = 0; i < 2; i++)
      {
         for (int j = 0; j < M; j++)
         {
            int tmp;
            cin >> tmp;
            person[i].push_back(tmp);
         }
      }
      for (int i = 0; i < A; i++)
      {
         int rr, cc, ll, pp;
         cin >> cc >> rr >> ll >> pp;
         bc.push_back(Battery(rr, cc, ll, pp));
      }
      set_battery();
      start();
      printf("#%d %d\n", test_case, answer);
   }
   return 0;
}
