#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
struct Item {
    int id;
    string name;
    int quantity;
    float price;
    string category;
};

Item inventory[100];

void addItem(int& itemCount)
{
    cout << "****************************************** ADDING ITEMS ******************************************" << endl;


    if (itemCount > 100) {
        cout << "\nInventory full! delete previous items to store new ones\n";
        return;
    }

    cout << "Enter the name of item: ";
    cin.ignore();
    getline(cin, inventory[itemCount].name);

    cout << "Enter the quantity of item: ";
    cin >> inventory[itemCount].quantity;

    cout << "Enter item id: ";
    cin >> inventory[itemCount].id;

    cout << "Enter price of the item: ";
    cin >> inventory[itemCount].price;

    cout << "Enter category of the item: ";
    cin.ignore();
    getline(cin, inventory[itemCount].category);
    

    itemCount++;
    
    cout << "Item " << itemCount << " added successfully! " << endl;



}

void removeItem(int& itemCount) //Mufleh Wrote this function
{
	cout << "***************************************** REMOVING ITEMS ******************************************" << endl;
    if (itemCount == 0) 
    {
        cout << "Inventory is empty! add items to delete\n";
        return;
    }
        int tempID;
        bool correctid;
        do
        {
            correctid = true;
            cout << "Enter the id of item: ";
            if (!(cin >> tempID))
            {
                cin.clear();
                cin.ignore();
                cout << "Invalid Input! ID must be a number\n";
                correctid = false;
            }
            else if (tempID < 0)
            {
                cout << "Invalid Input! ID cannot be negative\n";
                correctid = false;
            }
        } while (!correctid);
        inventory[itemCount].id = tempID;

        for (int i = 0; i < itemCount; i++) {
            if (inventory[i].id == tempID)
            {
                for (int j = i; j < itemCount - 1; j++) {
                    inventory[j] = inventory[j + 1];
                }
                itemCount--;
                cout << "Item with ID " << tempID << " removed successfully!\n";
                return;
            }
        }
    }




    int menu()
{
    int choice;
    cout << "Menu is below: \n";
    cout << "Press (1) to add items: \n";
    cout << "Press (2) to delete items: \n";
    cout << "Press (3) to edit items: \n";
    cout << "Press (4) to view items: \n";
    cout << "Press (5) to Exit: \n";

    cout << "Your coice: ";

    do
    {
  
            if (cin >> choice)
            {
                if (choice > 5 || choice < 1) {
                    cout << "Invalid Input!\n";
                    continue;
                }
                break;
            }
            else
                {
                cin.clear();
                cin.ignore();
                cout << "Invalid Input!\n";
                continue;
            }

    } while (true);

    return choice;
} 

int main()
{
    cout << "****************************************** INVENTORY MANAGEMENT ******************************************\n\n" << endl;

    int itemCount = 0;

    while (true)
    {
        switch (menu())
        {
        case 1:
        {
            int k;
            while (true) {
                addItem(itemCount);
                cout << "Do you want to continue adding items or exit to menu? \n";
                cout << "Press (1) for continue adding items and press (2)  to exit to main menu \n";
                 
                do {

                    if (cin >> k)
                        break;
                    else
                    {
                        cin.clear();
                        cin.ignore();
                        cout << "Invalid Input!\n";
                        continue;
                    }


                } while (true);

                if (k == 1)
                {
                    continue;
                }
                else
                    break;
            }

            break;
            
        }
        case 2:
        {
			removeItem(itemCount);
            break;
        }
        case 4:
        {
            cout << "Under devloped! comeback late\n";
            break;
        }
        case 5:
        {
            cout << "Under devloped! comeback late\n";
            break;
        }

        }
    }
   
   

}
