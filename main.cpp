#include <iostream>
#include<bits/stdc++.h>

using namespace std;

map<int, int> cost_v;
map<int,map<int,map<int,int> > > weight_e;

int obj_func(int arr[], int length)
{
    int d0 = 0, d1 = 0, d2 = 0, c = 0;
    //cout << c +1 << endl;
    for(int i = 1; i <= length; i++)
    {
        //c += cost_v[i] * arr[i];
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
    return d0 + d1 + d2;
}


int main()
{
    srand(time(0) * time(0));
    int v, e;
    string fname;
    cout << "input V, E: " << endl;
    freopen("ip.txt","r",stdin);
    cin >> v >> e;


    int n_e = (v * (v-1) * .5);

//    string fname = a + "-" + b + ".txt";



    /*
    for(int j = 0; j < 100; j++)
    {
        int zero = 0, one = 0;
        for(int i = 0; i < 200; i = i + 2)
            if(rand() % 2 == 0)
                zero++;
            else
                one++;
            cout << zero << " " << one << endl;

    }
    */
    if(e >= n_e)
        cout << "instance cant be created, #edges are too large." << endl;
    else
    {
        cout << "name of file:" << endl;
        cin >> fname;
        FILE *fp = fopen(fname.c_str(), "w+");
        fprintf(fp, "%d %d\n", v, e);

        //int arr1[e];
        //map<int, map<int, map<int, int>>> edges;
        for(int i = 1; i <= e; i++)
        {
            //cout << "start" << endl;
            int a = (rand() % (v-1)) +1;
            //cout << a << endl;
            int b = (a + rand() % (v-a)) +1;
            //cout << b << endl;
            //cout << a << " " << b << endl;

            if(weight_e[a][b][0] == NULL)
            {
                int d0 = rand() % 101;
                int d2 = rand() % (d0+1);
                int d1 = d2 + rand() % (((d0+d2)/2)+1-d2);
                weight_e[a][b][0] = d0;
                weight_e[a][b][1] = d1;
                weight_e[a][b][2] = d2;
                cout << a << " " << b << " " << d0 << " " << d1 << " " << d2 << "  \t" << float(i * 100) / e << "%" << endl;
                fprintf(fp, "%d %d %d %d %d\n", a,b,d0,d1,d2);


            }
            else
                i--;
            //cout << "pass: half" << endl;
        }

        //cout << "pass: 1" << endl;

        int arr2[v+1];
        cout << "cost:" << endl;
        for(int i = 1; i <= v; i++)
        {

            int avg_gain = 0;

            for(int j = 0; j < 100; j++)
            {
                cout << string(30, '\b');
                //cout << string(4, ' ');

                cout << j << "% " ;
                for(int k = 1; k <= v; k++)
                    arr2[k] = rand() % 2;
                cout << j << " ";
                clock_t begin = clock();
                arr2[i] = 0;
                int tmp1 = obj_func(arr2, v);
                clock_t end = clock();
                double e = double(end - begin) / CLOCKS_PER_SEC;
                cout << j << ":"<< e << " ";
                begin = clock();
                arr2[i] = 1;
                avg_gain += tmp1 - obj_func(arr2, v);
                end = clock();
                e = double(end - begin) / CLOCKS_PER_SEC;
                cout << j << ":" << e << " ";

            }
            avg_gain = ceil(avg_gain /100);
            cost_v[i] = avg_gain;

            cout << endl << i << " " << cost_v[i] << endl;
            fprintf(fp, "%d %d\n", i, cost_v[i]);
        }
    }






    cout << "end generating" << fname << endl;
    char ch;
    cin  >> ch;
    return 0;
}
