#include <bits/stdc++.h>
using namespace std;

class CoinSlot
{
    int coinAmount;

public:
    const float coinValues[7] = {200, 100, 50, 20, 10, 5, 1};
    CoinSlot()
    {
        coinAmount = 0;
    }
    int updateCointAmount()
    {
        cout << "----Inserez des pieces dans la fente: "<<endl;
        cout<<  "--> ";
        int inserted;
        cin >> inserted;
        if (inserted == -1)
        {
            return -1;
        }
        else
        {
            coinAmount += inserted;
        }
        return coinAmount;
    }
    int getCoinAmount()
    {
        return coinAmount;
    }
    void clear()
    {
        coinAmount = 0;
    }
    void returnCoins(int price)
    {   
        coinAmount-=price;
        cout<<"--> ";
        for (int i = 0; i < 7; i++)
        {
            int count = 0;
            
            while (coinAmount >= coinValues[i])
            {
                count++;
                coinAmount -= coinValues[i];
            }
            if (count > 0)
                cout << count << "x" << float(coinValues[i])/100 << " euros,";
        }
        cout << endl;
    }
};