/************************************
File: map.h
Author:
Create Date: 2023/04/18
Editor: Ayr
Update Date: 2023/04/19
Description:
************************************/
#include <iostream>
#include <vector>
#include <cmath>
#include "Pipe.h"
#include "Position.h"
#include "Color.h"

using namespace std;


class map
{
    private:
        vector<vector<Pipe>> data;
        vector<Position> route;
        Position start, end;
        int col = 0, row = 0;
        int direction = -1;   //-1:up, 1:down

    public:
        void setsize(int input_col, int input_row)
        {
            col = input_col;
            row = input_row;
        }
        void setstart()
        {
            start.pos_x = 0;
            start.pos_y = rand() % row;
        }
        void setstart(int input_x, int input_y)
        {
            start.pos_x = input_x;
            start.pos_y = input_y;
        }
        void setend()
        {
            end.pos_x = col - 1;
            end.pos_y = rand() % row;
        }
        void setend(int input_x, int input_y)
        {
            end.pos_x = input_x;
            end.pos_y = input_y;
        }
        void randmap()
        {
            vector<Pipe> temp;
            for (int i = 0; i < col; i++)
            {
                for (int j = 0; j < row; j++)
                {
                    Pipe x;
                    pshape psh = CROSS;
                    int rand_num = rand() % 4;
                    switch(rand_num)
                    {
                        case 0:
                            psh = CROSS;
                            break;
                        case 1:
                            psh = STRA;
                            break;
                        case 2:
                            psh= TEE;
                            break;
                        case 3:
                            psh = ELBOW;
                            break;
                        default:
                            break;
                    }
                    x.SetShape(psh);
                    x.SetRotation(rand() % 4);
                    temp.push_back(x);
                }
                data.push_back(temp);
            }
        }
        void randroute()
        {
            Position current = start;
            if(start.pos_y < end.pos_y)
            {
                direction = 1;
            }
            else
            {
                direction = -1;
            }
            route.push_back(start);
            for (int i = 0;;i++)
            {
                int rand_num = rand() % 2;
                switch(rand_num)
                {
                    case 0:
                        if(current.pos_x != end.pos_x)
                        {
                            current.pos_x = current.pos_x + 1;
                        }
                        else
                        {
                            current.pos_y = current.pos_y + direction;
                        }
                        break;
                    case 1:
                        if(current.pos_y != end.pos_y)
                        {
                            current.pos_y = current.pos_y + direction;
                        }
                        else
                        {
                            current.pos_x = current.pos_x + 1;
                        }
                        break;
                    default:
                        break;
                }
                route.push_back(current);
                //cout << current.pos_x << "  " << end.pos_x << "  " << current.pos_y << "  " << end.pos_y << endl;
                if (current == end)
                {
                    break;
                }
            }
            for (int i = 0; i < route.size(); i++)
            {
                data[route[i].pos_y][route[i].pos_x].setcolor(176);
            }
            for (int i = 2; i < route.size() / 2; i++)
            {
                int forward = 0;
                int mid = (forward + i) / 2;
                Position judge = route[forward] - route[i];
                pshape psh;
                int rnad_num = rand() % 3;
                if (judge.pos_x == 0 || judge.pos_y == 0)
                {
                    switch(rnad_num)
                    {
                        case 0:
                            psh = CROSS;
                            break;
                        case 1:
                            psh = STRA;
                            break;
                        case 2:
                            psh = TEE;
                            break;
                    }
                }
                else
                {
                    switch(rnad_num)
                    {
                        case 0:
                            psh = CROSS;
                            break;
                        case 1:
                            psh = TEE;
                            break;
                        case 2:
                            psh = ELBOW;
                            break;
                    }
                }
                data[route[mid].pos_y][route[mid].pos_x].SetShape(psh);
            }
        }
        void printdata() //test
        {
            for (int i = 0; i < row;i++)
            {
                for (int j = 0; j < col;j++)
                {
                    SetColor(data[i][j].GetColor());
                    switch (data[i][j].GetShape())
                    {
                        case CROSS:
                            cout << "C";
                            break;
                        case STRA:
                            cout << "S";
                            break;
                        case TEE:
                            cout << "T";
                            break;
                        case ELBOW:
                            cout << "E";
                            break;
                    }
                }
                cout << endl;
            }
        }
};