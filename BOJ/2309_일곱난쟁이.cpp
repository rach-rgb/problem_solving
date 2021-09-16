#include <iostream>
#include <algorithm>
using namespace std;

int main(){ 
    int heights[9];
    int hsum = 0;
    for(int i = 0; i < 9; i++){ cin >> heights[i]; hsum += heights[i]; }

    sort(heights, heights+9);

    for(int i = 0; i < 9; i++){
        for(int j = i + 1; j < 9; j++){
            if(heights[i] + heights[j] == hsum - 100)
            {
                for(int k = 0; k < 9; k++)
                {
                    if((k!=i)&&(k!=j))
                    {
                        cout << heights[k] << endl;
                    }
                }
                return 0;
            }
        }
    }

    return -1;
}
