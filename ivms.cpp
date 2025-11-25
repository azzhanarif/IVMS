#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
struct Item {                                        // Made by Azhan
    int id;
    string name;
    int quantity;
    float price;
    string category;
};
struct Sale {                                        // Made by Mufleh
    int productID;
	int quantitySold;
	float totalPrice;
};
Sale sales[500];
int saleCount = 0;


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


void addItem(int& itemCount)                                           // made by Azhan
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

void removeItem(int& itemCount)                                                    //Mufleh Wrote this function
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

void editItem(int itemCount)                                                                    //Mufleh Wrote this function
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

void searchItem(int itemCount) {                                                                        // made by Azhan
    int id;
    int i = 0;
    bool found = true;
    cout << "Enter the product id: ";
    cin >> id;

    for (i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            found = true;
            break;
        }

    }

    if (found)
    {
        cout << "Item found! " << endl;

        cout << "Item name: " << inventory[i].name << endl;
        cout << "Item id: " << inventory[i].id << endl;
        cout << "Item price: " << inventory[i].price << endl;
        cout << "Item qty: " << inventory[i].quantity << endl;
        cout << "Item category: " << inventory[i].category << endl;

    }
    else {
        cout << "Item not not found!";
    }



}

void preventNegStock(int ic) {                     // made by Azhan

    bool found = false;

    for (int i = 0; i < ic; i++) {
        if (inventory[i].quantity <= 5) {
            found = true;
            cout << inventory[i].name << " is running out of stock please refill!" << endl;
        }
    }

    if (!found) {
        cout << "No stock need to be refilled! " << endl;
    }
}


void recordSALE(int ItemCount) {                                        // Made by Azhan

    cout << "=============================== SALES Management ===============================\n" << endl;

    int id;
    int qty;
    int i = 0;
    int final;
    float totalBill = 0.0;
    while (true) {

        cout << "Enter the ID of the product you want to sell: ";
        cin >> id;

        bool found = false;
        for (i = 0; i < ItemCount; i++) {  // This loop for determining item
            if (inventory[i].id == id) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Item not found!" << endl;
            continue;
        }

        cout << "Enter the quantity of the item you want to sell: ";
        cin >> qty; // add input validator

        if ((inventory[i].quantity - qty) < 0) {
            cout << "Invalid quantity! only " << inventory[i].quantity << " " << inventory[i].name << " are available in stock" << endl;
            continue;
        }

        inventory[i].quantity -= qty;


        totalBill = totalBill + (qty * inventory[i].price);

		sales[saleCount].productID = id;
		sales[saleCount].quantitySold = qty;
		sales[saleCount].totalPrice = qty * inventory[i].price;
		saleCount++;

        cout << "If bill is finalized press (1) if not press (2)";
        cin >> final;

        if (final == 1)
            break;

    }

    cout << "--------------------------------------------------------------------------------\n\n";
    cout << "\nYour Total Bill is " << totalBill << " .Rs\n\n";
    cout << "--------------------------------------------------------------------------------\n\n";

}

void viewItems(int itemCount)                                            // made by Azhan
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



int menu()                                                //made by Azhan and Mufleh
{
    int choice;
    cout << "========================================  MENU ======================================== \n\n";
    cout << "Press (1) to add items \n";
    cout << "Press (2) to delete items \n";
    cout << "Press (3) to edit items \n";
    cout << "Press (4) to view  items \n";
    cout << "Press (5) to see notifications \n";
    cout << "Press (6) to Enter sales management \n";
    cout << "Press (7) for Reports and Statistics \n";
    cout << "Press (8) to restock \n";
	cout << "Press (9) to exit \n";

    cout << "Your coice: ";

    do
    {

        if (cin >> choice)
        {
            if (choice > 7 || choice < 1) {
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
void displaysAllSales() {               // Made by Mufleh
    cout << "=============================== SALES RECORDS ===============================\n" << endl;
    if (saleCount == 0) {
        cout << "No sales recorded yet." << endl;
        return;
    }
    for (int i = 0; i < saleCount; i++) {
        cout << "Sale " << i + 1 << ":\n";
        cout << "Product ID: " << sales[i].productID << endl;
        cout << "Quantity Sold: " << sales[i].quantitySold << endl;
        cout << "Total Price: " << sales[i].totalPrice << " Rs\n";
        cout << "----------------------------------------\n";
    }
}

void topSellingProduct() {          // Made by Mufleh
    if (saleCount == 0) {
        cout << "No sales recorded yet." << endl;
        return;
    }
    int topIndex = 0;
    for (int i = 1; i < saleCount; i++) {
        if (sales[i].quantitySold > sales[topIndex].quantitySold) {
            topIndex = i;
        }
    }
    cout << "=============================== TOP SELLING PRODUCT ===============================\n" << endl;
    cout << "Product ID: " << sales[topIndex].productID << endl;
    cout << "Quantity Sold: " << sales[topIndex].quantitySold << endl;
    cout << "Total Price: " << sales[topIndex].totalPrice << " Rs\n";
    cout << "----------------------------------------\n";
}

void totalRevenue() {               // Made by Mufleh
    float total = 0;
    for (int i = 0; i < saleCount; i++) {
        total += sales[i].totalPrice;
    }
    cout << "=============================== TOTAL REVENUE ===============================\n" << endl;
    cout << "Total Revenue from Sales: " << total << " Rs\n";
    cout << "----------------------------------------\n";
}
void restock(int itemCount) {       // Made by Mufleh
			 
	cout << "=============================== RESTOCK ITEMS ==============================\n" << endl;
    if (itemCount == 0)
    {
        cout << "Inventory is empty! add items to restock\n";
		return;
    }
    int id;
    int qty;
	cout << "Enter the product ID to restock: ";
	cin >> id;
	if (id < 0) {
        cout << "Invalid Input! ID cannot be negative\n";
        return;
    }
	if (id >= 0) {
        for (int i = 0; i < itemCount; i++) {
            if (inventory[i].id == id) {
                cout << "Enter the quantity to add: ";
                cin >> qty;
                if (qty <= 0) {
                    cout << "Invalid Input! Quantity must be positive\n";
                    return;
                }
                inventory[i].quantity += qty;
                cout << "Item with ID " << id << " restocked successfully! New quantity: " << inventory[i].quantity << "\n";
                return;
            }
        }
        cout << "Item with ID " << id << " not found!\n";
    }
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
            int view;
            do {
                cout << "===== VIEW MENU =====\n";
                cout << "1. View list of all items\n";
                cout << "2. Search product by ID\n";
                cout << "Enter your choice (1 or 2): ";
                if (cin >> view) {
                    if (view == 1 || view == 2)
                        break;
                }
                else {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid input!" << endl;
                }
            } while (true);

            if (view == 1) {
                viewItems(itemCount);
                break;
            }
            if (view == 2) {
                searchItem(itemCount);
                break;
            }
            break;

        }
        case 5:
        {
            cout << "======== Notifications [*] ========" << endl;
            cout << "stock related: " << endl;
            preventNegStock(itemCount);
            break;

        }
        case 6:
        {
            recordSALE(itemCount);
            break;

        }
        case 7:
        {
            int rep;
			cout << "===== REPORTS AND STATISTICS MENU =====\n";
			cout << "1. View all sales records\n";
			cout << "2. View top-selling product\n";    
			cout << "3. View total revenue from sales\n";
			cout << "Enter your choice (1, 2 or 3): ";
            cin >> rep;
            if(rep==1)
                displaysAllSales();
            else if(rep==2)
                topSellingProduct();
            else if(rep==3)
                totalRevenue();
            else
				cout << "Invalid Input!";
            break;
        }
        case 8:
        {
			restock(itemCount);
        }
        case 9:
        {
            cout << "Bye!";
			saveData(itemCount);
            return 0;
        }
        }

        saveData(itemCount);
    }

    return 0;

}








