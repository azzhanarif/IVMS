#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<limits>
using namespace std;
struct Item {
    int id;
    string name;
    int quantity;
    float price;
    string category;
};

Item inventory[100];
fstream productFile;

bool duplicateID(int ID, int itemCount) {            // made by Azhan

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == ID)
        {
            return true;
        }
    }
    return false;
}

void saveData(int itemCount) {                       // made by Azhan

    productFile.open("products.txt", ios::out);
    if (productFile.is_open()) {

        for (int i = 0; i < itemCount; i++) {
            productFile << inventory[i].name << " " << inventory[i].id << " " << inventory[i].quantity << " " << inventory[i].price << " " << inventory[i].category << endl;

        }

        productFile.close();
    }

}

void loadData(int& itemCount) {                                      // made by Azhan

    productFile.open("products.txt", ios::in);
    if (productFile.is_open()) {

        
        while (productFile >> inventory[itemCount].name >> inventory[itemCount].id >> inventory[itemCount].quantity >> inventory[itemCount].price >> inventory[itemCount].category) {
            itemCount++;
        }

        productFile.close();
    }
}


void addItem(int& itemCount) // Add item function made by Azhan
{
    cout << "****************************************** ADDING ITEMS ******************************************" << endl;


    if (itemCount > 100) {
        cout << "Inventory full! delete previous items to store new ones\n";
        return;
    }


    cout << "Enter the name of item: ";
    cin.ignore();
    getline(cin, inventory[itemCount].name);


    do {
        cout << "Enter item id: ";
        cin >> inventory[itemCount].id;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid Input! item ID must be in numbers " << endl;
        }
        else if (inventory[itemCount].id < 0)
            cout << "Item id cannot be negative! " << endl;
        else if (duplicateID(inventory[itemCount].id, itemCount)) {
            cout << "Id already exists! Enter a different id" << endl;
        }
        else break;

    } while (true);


    do {
        cout << "Enter the quantity of item: ";
        cin >> inventory[itemCount].quantity;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid Input!" << endl;
        }
        else if (inventory[itemCount].quantity >= 100 || inventory[itemCount].quantity <= 0)
        {
            cout << "Invalid Input! " << endl;
        }
        else break;

    } while (true);


    do {
        cout << "Enter price of the item: ";
        cin >> inventory[itemCount].price;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid Input!: " << endl;
        }
        else if (inventory[itemCount].price <= 0)
            cout << "Price cannot be negative or zero !";
        else break;

    } while (true);


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

    //inventory[itemCount].id = tempID;  // Mufleh, ye line fazool kee hai thats why i removed it ~Azhan

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

void editItem(int itemCount)          //Mufleh Wrote this function
{
    cout << "****************************************** EDITING ITEMS ******************************************" << endl;

    if (itemCount == 0)
    {
        cout << "Inventory is empty! Add items first.\n";
        return;
    }
    int tempID;
    bool correctid;

    do
    {
        correctid = true;
        cout << "Enter the ID of the item you want to edit: ";
        if (!(cin >> tempID))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input! ID must be a number.\n";
            correctid = false;
        }
        else if (tempID < 0)
        {
            cout << "Invalid Input! ID cannot be negative.\n";
            correctid = false;
        }
    } while (!correctid);

    int index = -1;
    for (int i = 0; i < itemCount; i++)
    {
        if (inventory[i].id == tempID)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        cout << "Item with ID " << tempID << " not found!\n";
        return;
    }
    cout << "\nCurrent Details:\n";
    cout << "Name: " << inventory[index].name << endl;
    cout << "Quantity: " << inventory[index].quantity << endl;
    cout << "Price: " << inventory[index].price << endl;
    cout << "Category: " << inventory[index].category << endl;
    cout << "\nEnter new name: ";
    cin.ignore();
    getline(cin, inventory[index].name);
    cout << "Enter new quantity: ";
    cin >> inventory[index].quantity;
    cout << "Enter new price: ";
    cin >> inventory[index].price;
    cout << "Enter new category: ";
    cin.ignore();
    getline(cin, inventory[index].category);
    cout << "\nItem updated successfully!\n";
}

void viewItems(int itemCount) // this functoin made by Azhan
{

    if (itemCount == 0) {
        cout << "Inventory is empty! ";
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        cout << "---------------------------------------------------------------------------------------------------";
        cout << "\n\n";

        cout << "                                   Item number " << i + 1 << endl;

        cout << "Item name: " << inventory[i].name << endl;
        cout << "Item id: " << inventory[i].id << endl;
        cout << "Item price: " << inventory[i].price << endl;
        cout << "Item qty: " << inventory[i].quantity << endl;
        cout << "Item category: " << inventory[i].category << endl;

        cout << "\n\n";
    }

}



int menu() // Menu Function made by Azhan
{
    int choice;
    cout << "****************************************** MENU ****************************************** \n\n";
    cout << "Press (1) to add items: \n";
    cout << "Press (2) to delete items: \n";
    cout << "Press (3) to edit items: \n";
    cout << "Press (4) to view all items: \n";
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
    loadData(itemCount);

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
        case 3:
        {
            editItem(itemCount);
            break;
        }
        case 4:
        {
            viewItems(itemCount);
            break;
        }
        case 5:
        {
            cout << "Bye!";
            return 0;
        }

        }

        saveData(itemCount);
    }



}







