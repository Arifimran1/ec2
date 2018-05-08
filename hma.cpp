#include <iostream>
#include <bits/stdc++.h>


using namespace std;


struct solution
{
    int w[1001];
    float PE = 999999;
};


solution sol[10001];
solution com_new_1, com_new_2;
solution minSol;
solution bestSol;



float cutofftime = 3600; ///3600s
int maxPopSize = 30;
int maxGen = 2000;
int n = 4; //number of vertex


map<int, int> cost_v;
map<int,map<int,map<int,int>>> weight_e;
int n_vertex, n_edge;


int obj_func(int* arr, int length);
void input(string str);
void popGen();
void common_cross(int num1,int num2);
int _inc(int* arr, int index);
int _alpha(int x);
void ITNS(int num);


int main()
{
    srand(time(0) * time(0));
    cout << setprecision(15) << showpoint << fixed;

    string str1;
    cout << "enter  filename: " ;
    cin >> str1;

    bestSol.PE = 9999999;
    int ittt = 20, g_sum = 0;
    while(ittt--)
    {

        input(str1);
        //input("30-100.txt");

        cout << "start pop" << endl;
        popGen();
        cout << "stop pop" << endl;


        int gen = 0, popSize = maxPopSize;
        double elapsetime = 0;
        clock_t begin = clock();

        while (gen <= maxGen && elapsetime <= cutofftime)
        {
            int p1 = 1 + rand() % popSize;
            int p2 = p1;
            while(p2 == p1)
                p2 = 1 + rand() % popSize;
            //cout << "p:" << p1 << " " << p2 << endl;
            //cout << "start com cross" << endl;
            common_cross(p1, p2);
            //cout << "stop com cross" << endl;

            //cout << "start itns1" << endl;
            ITNS(1);

            if(com_new_1.PE < bestSol.PE)
            {
                for(int i = 1; i <= n; i++)
                {
                    bestSol.w[i] = com_new_1.w[i];
                    popSize++;
                    sol[popSize].w[i] = bestSol.w[i];
                }
                bestSol.PE = com_new_1.PE;
                sol[popSize].PE = bestSol.PE;
            }
            //cout << "stop itns1" << endl;

            //cout << "start itns2" << endl;

            ITNS(2);
            if(com_new_2.PE < bestSol.PE)
            {
                for(int i = 1; i <= n; i++)
                {
                    bestSol.w[i] = com_new_2.w[i];
                    popSize++;
                    sol[popSize].w[i] = bestSol.w[i];
                }
                bestSol.PE = com_new_2.PE;
                sol[popSize].PE = bestSol.PE;
            }

            //cout << "stop itns2 " << endl;
            gen++;
            clock_t end = clock();
            elapsetime = double(end - begin) / CLOCKS_PER_SEC;

        }

        g_sum += bestSol.PE;
        cout << "iteration: " << (21 - ittt) << ": " << str1 << ": " << bestSol.PE << endl;
    }

    cout << "avg: " << (float)g_sum / 20 << endl;

    string s11;
    cin >> s11;

    return 0;
}


int obj_func(int* arr, int length)
{
    int d0 = 0, d1 = 0, d2 = 0, c = 0;
    //cout << c +1 << endl;
    for(int i = 1; i <= length; i++)
    {
        c += cost_v[i] * arr[i];
        //cout << c << endl << arr[i] << endl;
        if(arr[i] == 0)
        {
            for(int j = i+1; j <= length; j++)
            {
                if(arr[j] == 0)
                {
                    if(weight_e[i][j][0] != NULL)
                        d0 += weight_e[i][j][0];
                    //cout << d0 << endl;

                }
                else
                {
                    if(weight_e[i][j][1] != NULL)
                        d1 += weight_e[i][j][1];

                }
            }

        }
        else
        {
            for(int j = i+1; j <= length; j++)
            {
                if(arr[j] == 0)
                {
                    if(weight_e[i][j][1] != NULL)
                        d1 += weight_e[i][j][1];

                }
                else
                {
                    if(weight_e[i][j][2] != NULL)
                        d2 += weight_e[i][j][2];

                }
            }

        }
    }
    //cout << c << endl << d0 << endl << d1 << endl << d2 << endl;
    return c + d0 + d1 + d2;
}



void input(string str)
{
    FILE *fp;
    int v, c, st, en, d0, d1, d2;

    //int edge[1000][1000][3];



    fp = fopen(str.c_str(), "r");

    fscanf(fp, "%d %d", &n_vertex, &n_edge);

    n = n_vertex;

    for(int i = 1; i <= n_edge; i++)
    {
        fscanf(fp, "%d %d %d %d %d", &st, &en, &d0, &d1, &d2);
        weight_e[st][en][0] = d0;
        weight_e[st][en][1] = d1;
        weight_e[st][en][2] = d2;

    }
    for(int i = 1; i <= n_vertex; i++)
    {
        fscanf(fp, "%d %d", &v, &c);
        cost_v[v] = c;

    }

}




void popGen()
{
    for(int i = 1; i <= maxPopSize; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            sol[i].w[j] = rand() % 2;
            sol[i].PE = obj_func(sol[i].w, n);
        }
    }
}

void common_cross(int num1,int num2)
{
    int temp1[1001], common = 0, uncommon = 1, new1[1001], new2[1001], old1[1001],old2[1001], new_s_1[1001], new_s_2[1001];
    for (int i = 1; i <= n; i++)
    {
        if(sol[num1].w[i] == sol[num2].w[i])
        {
            temp1[i] = 1;
            new_s_1[i] = sol[num1].w[i];
            new_s_2[i] = new_s_1[i];
            common++;
        }
        else
        {
            temp1[i] = 0;
            old1[uncommon] = sol[num1].w[i];
            old2[uncommon] = sol[num2].w[i];
            uncommon++;

        }
    }

    uncommon--;

    float r = (float)(1 + rand() % 100) / 100; ///generate 0 1
    if(uncommon < 2)
        return;
    ///generate new1

    int flag = 1;
    while(flag)
    {
        for(int i = 1; i <= uncommon; i++)
        {
            r = (float)(1 + rand() % 100) / 100;
            if(r < 0.5)
                new1[i] = old1[i];
            else
                new1[i] = old2[i];
        }

        for(int i = 1; i <= uncommon; i++)
        {
            if(old1[i] != new1[i])
            {
                flag = 0;
                break;
            }
        }
        if(flag == 0)
        {
            flag = 1;
            for(int i = 1; i <= uncommon; i++)
            {
                if(old2[i] != new1[i])
                {
                    flag = 0;
                    break;
                }
            }
        }
    }

    ///generating new2
    flag = 1;
    while(flag)
    {
        for(int i = 1; i <= uncommon; i++)
        {
            r = (float)(1 + rand() % 100) / 100;
            if(r > 0.5)
                new2[i] = old1[i];
            else
                new2[i] = old2[i];
        }


        for(int i = 1; i <= uncommon; i++)
        {
            if(old1[i] != new2[i])
            {

                flag = 0;
                break;
            }
        }

        if(flag == 0)
        {
            flag = 1;
            for(int i = 1; i <= uncommon; i++)
            {
                if(old2[i] != new2[i])
                {
                    flag = 0;
                    break;
                }
            }
        }

        if(flag == 0)
        {
            flag = 1;
            for(int i = 1; i <= uncommon; i++)
            {
                if(new1[i] != new2[i])
                {
                    flag = 0;
                    break;
                }
            }
        }
    }

    common = 1;
    for(int i = 1; i <= n; i++)
    {
        if(temp1[i] == 0)
        {
            new_s_1[i] = new1[common];
            new_s_2[i] = new2[common];
            common++;
        }

        com_new_1.w[i] = new_s_1[i];
        com_new_2.w[i] = new_s_2[i];
    }
}

int _inc(int* arr, int index)
{
    if(arr[index] == 1)
        return 1;
    else
        return -1;
}

int _alpha(int x)
{
    if(x == 0)
        return 1;
    else
        return 0;
}


void ITNS(int num)
{

    if(num == 1)
    {
        ///com_new_1.w

        solution temp1, min_temp;
        min_temp.PE = 999999;

        for(int i = 1; i <= n; i++)
        {
            temp1 = com_new_1;
            if(temp1.w[i] == 1)
                temp1.w[i] = 0;
            else
                temp1.w[i] = 1;

            int sum = 0;
            for(int j = 1; j <= n; j++)
            {
                if(j != i)
                {
                    sum += _inc(temp1.w, i) * (-cost_v[i] + _alpha(_inc(temp1.w, j) +1) * weight_e[i][j][0] + _inc(temp1.w, j) * weight_e[i][j][1] - _alpha(_inc(temp1.w, j) * weight_e[i][j][2]));

                }


            }
            temp1.PE = sum;

            if(min_temp.PE > sum)
            {
                min_temp = temp1;
            }


        }

        com_new_1 = min_temp;




        com_new_1.PE = obj_func(com_new_1.w, n);

    }
    else if(num == 2)
    {

        solution temp1, min_temp;
        min_temp.PE = 999999;

        for(int i = 1; i <= n; i++)
        {
            temp1 = com_new_2;
            if(temp1.w[i] == 1)
                temp1.w[i] = 0;
            else
                temp1.w[i] = 1;

            int sum = 0;
            for(int j = 1; j <= n; j++)
            {
                if(j != i)
                {
                    sum += _inc(temp1.w, i) * (-cost_v[i] + _alpha(_inc(temp1.w, j) +1) * weight_e[i][j][0] + _inc(temp1.w, j) * weight_e[i][j][1] - _alpha(_inc(temp1.w, j) * weight_e[i][j][2]));

                }


            }
            temp1.PE = sum;

            if(min_temp.PE > sum)
            {
                min_temp = temp1;
            }


        }

        com_new_2 = min_temp;






        ///com_new_2
        com_new_2.PE = obj_func(com_new_2.w, n);
    }
    else
    {
        cout << "wrong number!!" << endl;
    }
}

