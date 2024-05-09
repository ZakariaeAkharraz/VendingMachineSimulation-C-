
#include "Slot.h"
#include "CoinSlot.h"
#include "Keypad.h"
#include "DropCheck.h"
class Automat
{
    int numSlots;
    int numProductPerSlot;
    vector<Slot *> slots;

public:
    DropCheck dropcheck;
    Keypad keypad;
    CoinSlot coinslot;
    Slot *cached;
    Automat(int numSlots, int numProductPerSlot)
    {
        this->numProductPerSlot = numProductPerSlot;
        this->numSlots = numSlots;
    }
    int getEmptySlots(){
        return numSlots - slots.size();
    }
    void getmenu()
    {
        string line;
        string snackName;
        int id, price, motorId1, motorId2;
        ifstream file("stock.txt");

        while (getline(file, line))
        {
            stringstream sin;
            sin << line;
            getline(sin, snackName, ',');
            sin >> id;
            sin.ignore(1, ',');
            sin >> price;
            sin.ignore(1, ',');
            sin >> motorId1;
            sin.ignore(1, ',');
            sin >> motorId2;
            sin.ignore(1, ',');
            if (motorId2 == 0)
            {
                addSlot(snackName, id, price, motorId1);
            }
            else
            {
                addSlot(snackName, id, price, motorId1, motorId2);
            }
        }
        cached = slots.at(0);
    }
    void showlist()
    {
        cout << "----------Products list----------" << endl;
        for (int i = 0; i < slots.size(); i++)
        {
            cout << left << setw(4) << slots.at(i)->getId() << "_ " << left << setw(25) << slots.at(i)->getProductName() << " " << right << setw(5) << slots.at(i)->getPrice()<<" qte: "<<slots.at(i)->getNumProducts()  << endl;

        }
    }
    Slot *searchSlot(int slotId)
    {
        if (slotId == cached->getId())
        {
            return cached;
        }
        else
        {
            for (int i = 0; i < slots.size(); i++)
            {

                if (slots.at(i)->getId() == slotId)
                {
                    cached = slots.at(i);
                    return slots.at(i);
                }
            }

            return NULL;
        }
    }
    bool addSlot(string productName, int slotId, int price, int motorId1, int motorId2)
    {

        if (numSlots > slots.size())
        {
            Slot *temp = new WideSlot(slotId, productName, price, motorId1, motorId2);

            slots.push_back(temp);

            return true;
        }
        else
            cout << "no slots are left\n";
        return false;
    }
    bool addSlot(string productName, int slotId, int price, int motorId)
    {
        if (numSlots > slots.size())
        {
            cout << "done" << endl;
            Slot *temp = new SmallSlot(slotId, productName, price, motorId);
            slots.push_back(temp);
            return true;
        }
        else
            cout << "all the slots are occupied" << endl;
        return false;
    }
    int getNumSlots()
    {
        if (numSlots > slots.size())
            return slots.size();
        else
            return -1;
    }
    bool addSlot(Slot *slot)
    {
        if (numSlots > slots.size())
        {

            slots.push_back(slot);

            return true;
        }
        else
            return false;
    }
    void changeSlot(int slotId, string name, int price)
    {
        for (int i = 0; i < slots.size(); i++)
        {
            if (slots.at(i)->getId() == slotId)
            {
                slots.at(i)->setProductName(name);
                slots.at(i)->setPrice(price);
                break;
            }
        }
    }
    int getPrice(int slotId)
    {
        return searchSlot(slotId)->getPrice();
    }
    int getNumPieces(int slotId)
    {
        return searchSlot(slotId)->getNumProducts();
    }
    bool isAvailable(int slotId)
    {
        return getNumPieces(slotId) > 0 ? true : false;
    }
    bool dropSlot(int slotId)
    {
        if (dropcheck.productReleased() == true)
        {
            searchSlot(slotId)->drop();
            return true;
        }
        else
        {
            return false;
        }
    }
    void fillAll()
    {
        for (int i = 0; i < slots.size(); i++)
        {
            slots.at(i)->setNumProducts(numProductPerSlot);
        }
    }
    void fill(int slotId, int numProducts)
    {
        for (int i = 0; i < slots.size(); i++)
        {
            if (slots.at(i)->getId() == slotId)
                slots.at(i)->setNumProducts(numProducts);
            cout <<slots.at(i)->getProductName() <<" is filled\n";
            break;
        }
    }
    ~Automat()
    {
        for (int i = 0; i < slots.size(); i++)
        {
            free(slots.at(i));
        }
    }
};
