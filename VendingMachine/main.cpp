#include "Automat.h"
#include <conio.h>

void menu(int x, Automat &Machine)
{
    switch (x)
    {
    case 1:
        Machine.showlist();
        cout << endl
             << "Taper sur un boutton pour continuer" << endl;
        getch();
        break;
    case 2:
        int choix, nbr_product;
        cout << "----------inserer Le numero du Slot---------" << endl;
        cout << "--> ";
        cin >> choix;
        cout << "----------inserer La quantite---------" << endl;
        cout << "--> ";
        cin >> nbr_product;
        Machine.fill(choix, nbr_product);

        break;
    case 3:
        Machine.fillAll();
        break;
    case 4:
        int slotId;
        slotId = Machine.getNumSlots();
        if (slotId != -1)
        { // verifier s'il sagit d'une petite snack ou grande snack
            int type;
            cout << "pour petite snack inserez 1 pour grande snack inserez 2:" << endl;
            cin >> type;
            if (Machine.getEmptySlots() >= type)
            {
                string prod_name;
                int price;
                cout << "-->le nom du produit: ";
                cin >> prod_name;
                cout << "-->le prix du produit: ";
                cin >> price;
                type == 1 ? Machine.addSlot(prod_name, slotId, price, slotId) : Machine.addSlot(prod_name, slotId, price, slotId, slotId + 1);
            }

            // Machine.addSlot();
        }
        break;
    case 5:
        exit(0);
        break;
    default:

        break;
    }
}
int main()
{
    Automat mach(20, 20);
    // le stock du machine est vide au debut et l'Admin qui peut le remplir
    mach.getmenu();

stage_one:
    system("CLS");

    cout << " __________________________________________" << endl
         << "|                                          |" << endl
         << "|    Bienvenue dans la Vending Machine     |" << endl
         << "| 1- vous etes ADMIN                       |" << endl
         << "| 2- vous voulez acheter                   |" << endl
         << "| 3- Quitter                               |" << endl
         << "|__________________________________________|" << endl
         << "---> ";

    int menu_choice;
    cin >> menu_choice;
    system("CLS");
    if (menu_choice == 1)
    {
    stage_two:
        // ----------Admin-----------------
        while (menu_choice != -1)
        {
            cout << " __________________________________________" << endl
                 << "|                                          |" << endl
                 << "|    Bienvenue Mr Admin                    |" << endl
                 << "| 1- Afficher menu                         |" << endl
                 << "| 2- Remplir un element                    |" << endl
                 << "| 3- Remplir toutes les elements           |" << endl
                 << "| 4- Retourner au menu principal           |" << endl
                 << "| 5- Quitter                               |" << endl
                 << "|__________________________________________|" << endl;
            cout << "--> ";

            cin >> menu_choice;
            if (menu_choice == 4)
                goto stage_one;
            system("CLS");
            menu(menu_choice, mach);
        }
        goto stage_one;
    }
    else if (menu_choice == 3)
    {
        exit(0);
    }
    else if (menu_choice != 2)
        goto stage_one;
stage_three:
    mach.showlist();
    int choice = mach.keypad.getSelection();

    if (choice == -1)
    {
        goto stage_one;
    }
    else
    { // après que l'utilisateur a choisi le snack

        if (mach.searchSlot(choice) == NULL)
        {
            cout << "----this snack doesn't exist----" << endl;
            goto stage_three;
        }

        if (mach.isAvailable(choice) == false)
        {
            cout << "!!!!!" << mach.cached->getProductName() << "est en rupture de stock!!!!!" << endl;
            cout << "Taper sur entrer pour continuer" << endl;
            getch();
            goto stage_three;
        }
        else
        {
            system("CLS");
            cout << "--------votre choix : " << mach.cached->getProductName() << "--------" << endl;
            int choice_price = mach.cached->getPrice();
            cout << "\n--------le prix est: " << choice_price << " cents-------" << endl;
            int inserted;
            while (choice_price > mach.coinslot.getCoinAmount() && inserted != -1)
            {
                inserted = mach.coinslot.updateCointAmount();
                if (inserted == -1)
                {
                    mach.coinslot.returnCoins(0);
                    goto stage_three;
                }
                else
                {
                    system("CLS");
                    cout << "    __________________________________" << endl;
                    cout << "votre sold: " << inserted << "---le prix du " << mach.cached->getProductName() << ": " << choice_price << " cents" << endl;
                    cout << "    __________________________________" << endl;
                }
            }
            system("CLS");
            mach.dropSlot(choice);
            mach.coinslot.returnCoins(mach.cached->getPrice());
            cout << endl
                 << "Taper entrer pour retourner au menu" << endl;
            getch();
            goto stage_three;
        }
    }
}