//为能够正确读出写入文件的各数据，各数据间最好要有分隔
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    double current_S = 0, best_S = 0;
    int MaxWidth, amount;
    int current_h = 0;
    cout << "Please input the final height:" << endl;
    cin >> current_h;
    fstream f("data.txt", ios::in);
    f >> MaxWidth >> amount;
    int i, w, h;
    for (i = 0; i < amount; i++)
    {
        f >> w >> h;
        best_S += w * h;
    }
    current_S = MaxWidth * current_h;
    double approximater = current_S / best_S;
    cout << "The approximater is:" << approximater << endl;
    system("pause");
    return 0;
}