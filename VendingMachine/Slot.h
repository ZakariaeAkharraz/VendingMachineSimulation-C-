
#include "Motor.h"

class Slot
{   
    protected:
    string productName;
    int id;
    int numProducts;
    int price;
    Motor *motor1;
    Motor *motor2;

public:
    Slot(int slotId = 0, string productName = "unkown", int price = 0, int motor1Id = 0, int motor2Id = 0)
    {
        this->id = slotId;
        this->productName = productName;
        this->price = price;
        this->numProducts = 0;
        this->motor1 = new Motor();
        this->motor1->id = motor1Id;
        this->motor2 = new Motor();
        this->motor2->id = motor2Id;
    }
    virtual void drop()=0;
    int getPrice()
    {
        return this->price;
    }
    void setPrice(int price)
    {
        this->price = price;
    }
    int getNumProducts()
    {
        return this->numProducts;
    }
    void setNumProducts(int numProducts)
    {
        this->numProducts = numProducts;
    }
    int getId()
    {
        return this->id;
    }
    string getProductName()
    {
        return this->productName;
    }
    void setProductName(string productName)
    {
        this->productName = productName;
    }
    ~Slot()
    {
        free(motor1);
        free(motor2);
    }
};
class SmallSlot : public Slot
{
    Motor *motor1;

public:
    SmallSlot(int slotId, string productName, int price, int motor1Id)
    {
     id=slotId;
     this->productName=productName;
     this->price=price;
     motor1 = new Motor();
     motor1->id=motor1Id;
    }
    void drop()
    {
        motor1->trigger();
        cout << productName << " livre a partir du logement " << id << endl;
        setNumProducts(numProducts - 1);
    }
    ~SmallSlot(){
        free(motor1);
    }
};
class WideSlot : public Slot
{
    Motor *motor1;
    Motor *motor2;

public:
    WideSlot(int slotId, string productName, int price, int motor1Id,int motor2Id)
    {
     id=slotId;
     this->productName=productName;
     this->price=price;
     motor1 = new Motor();
     motor2 = new Motor();
     motor1->id=motor1Id;
     motor2->id=motor2Id;
    }
    void drop()
    {
        motor1->trigger();
        motor2->trigger();
        cout << productName << " livre a partir du logement " << id << endl;
        setNumProducts(numProducts - 1);
    }
    ~WideSlot(){
        free(motor1);
        free(motor2);
    }
};