#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct bot
{
    int weight;
    int h;
    int b;

    double va = h / weight;
};


int main()
{
    int n;
    cin >> n;

    vector<bot> data;
    vector<bot> h_more(n); int h_count = 0;
    vector<bot> b_more(n); int b_count = 0;

    int b_weight = 0;
    int h_weight = 0;

    int b_happy = 0;
    int h_happy = 0;

    for (int i = 0; i < n; i++)
    {
         cin >> data[i].weight >> data[i].h >> data[i].b;

         if(data[i].h <= data[i].b)
         {
            b_more[b_count].weight = data[i].weight;
            b_more[b_count].h = data[i].h;
            b_more[b_count].b = data[i].b;
            b_count++;
            b_weight += data[i].weight;
            b_happy += data[i].b;
         }
         else
         {
            h_more[h_count].weight = data[i].weight;
            h_more[h_count].h = data[i].h;
            h_more[h_count].b = data[i].b;
            h_count++;
            h_weight += data[i].weight;
            h_happy += data[i].h;
         }
    }

    sort(h_more.begin(), h_more.begin() + h_count, [](const bot &a, const bot &b) {
        return a.va > b.va;
    });

}