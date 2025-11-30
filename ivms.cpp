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
    int quantitySold;
};

struct Sale {
    int productID;
    int quantitySold;
    float totalPrice;
};


Item inventory[100];
Sale sales[1000];

fstream productFile;
fstream salesFile;

bool duplicateID(int ID, int itemCount) {            // made by Azhan

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == ID)
        {
            return true;
        }
    }
    return false;
}
//--------------------------------------------------------------------------FILE I/0 AREA ------------------------------------------------------------------------------------
void saveData(int itemCount) {                       // made by Azhan

    productFile.open("products.txt", ios::out);
    if (productFile.is_open()) {

        for (int i = 0; i < itemCount; i++) {
            productFile << inventory[i].name << "\n" << inventory[i].id << "\n" << inventory[i].quantity << "\n" << inventory[i].price << "\n" << inventory[i].category << "\n" << inventory[i].quantitySold << endl;

        }

        productFile.close();
    }

}

void loadData(int& itemCount) {                                      // made by Azhan

    productFile.open("products.txt", ios::in);
    if (productFile.is_open()) {

        while (true) {

            if (!getline(productFile, inventory[itemCount].name)) break;
            productFile >> inventory[itemCount].id;
            productFile >> inventory[itemCount].quantity;
            productFile >> inventory[itemCount].price;
            productFile.ignore(1000, '\n');

            getline(productFile, inventory[itemCount].category);
            productFile >> inventory[itemCount].quantitySold;
            productFile.ignore(1000, '\n');

            itemCount++;


        }


        productFile.close();
    }
}

void saveSales(int saleCount) { // Made by Azhan

    salesFile.open("sales.txt", ios::out);
    if (salesFile.is_open()) {

        for (int i = 0; i < saleCount; i++) {

            salesFile << sales[i].productID << " " << sales[i].quantitySold << " " << sales[i].totalPrice << endl;

        }

        salesFile.close();
    }

}

void loadSales(int& saleCount) { // Made by Azhan


    salesFile.open("sales.txt", ios::in);
    if (salesFile.is_open()) {

        while (salesFile >> sales[saleCount].productID >> sales[saleCount].quantitySold >> sales[saleCount].totalPrice)
            saleCount++;

        salesFile.close();
    }
}


//--------------------------------------------------------------------------inventory management------------------------------------------------------------------------

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
            cin.ignore(1000, '\n');
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
            cin.ignore(1000, '\n');
            cout << "Invalid Input!" << endl;
        }
        else if (inventory[itemCount].quantity >= 10000 || inventory[itemCount].quantity <= 0)
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
            cin.ignore(1000, '\n');
            cout << "Invalid Input!: " << endl;
        }
        else if (inventory[itemCount].price <= 0)
            cout << "Price cannot be negative or zero !";
        else break;

    } while (true);


    cout << "Enter category of the item: ";
    cin.ignore();
    getline(cin, inventory[itemCount].category);


    inventory[itemCount].quantitySold = 0; // zero quantity sold for new item set by default

    itemCount++;

    cout << "Item " << itemCount << " added successfully! " << endl;



}

void removeItem(int& itemCount)                                                    // Mufleh Wrote this function
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
            cin.ignore(1000, '\n');
            cout << "Invalid Input! ID must be a number\n";
            correctid = false;
        }
        else if (tempID < 0)
        {
            cout << "Invalid Input! ID cannot be negative\n";
            correctid = false;
        }
    } while (!correctid);

    /*   int sure = 1;
       cout << "Are you sure you want to delete this item? After you press (1) the whole stock of this item will be deleted!" << endl;
       cout << "Press (2) if you want to take your decision back" << endl;
       do {
           if (!cin >> sure) {
               cin.clear();
               cin.ignore();
               cout << "Invalid Input! " << endl;
           }
           else if (sure != 2 || sure != 1) {
               cout << "Invalid Input! " << endl;
           }
           else
               break;

       } while (true);*/


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
//-------------------------------------------------------------------------- tracking ------------------------------------------------------------------------
void searchItem(int itemCount) {                                                                        // made by Azhan
    int id;
    int i = 0;
    bool found = false;
    do {
        cout << "Enter the product id: ";
        if (cin >> id) {
            if (id < 0) {
                cout << "Id cannot be negative!" << endl;
            }
            else break;
        }
        else
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input!" << endl;
        }
    } while (true);

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

void viewItems(int itemCount)                                            // made by Azhan
{
    if (itemCount == 0) {
        cout << "Inventory is empty!" << endl;
        return;
    }

    cout << "\n================================= ITEMS LIST =================================\n\n";

    cout << left
        << setw(10) << "Item#"
        << setw(15) << "Category"
        << setw(20) << "Name"
        << setw(10) << "ID"
        << setw(10) << "Qty"
        << setw(10) << "Price"
        << endl;

    cout << "-------------------------------------------------------------------------------\n";

    for (int i = 0; i < itemCount; i++) {
        cout << left
            << setw(10) << i + 1
            << setw(15) << inventory[i].category
            << setw(20) << inventory[i].name
            << setw(10) << inventory[i].id
            << setw(10) << inventory[i].quantity
            << setw(10) << inventory[i].price
            << endl;
        cout << endl;
        cout << "-------------------------------------------------------------------------------\n";
    }

    cout << "-------------------------------------------------------------------------------\n";
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

void restock(int itemCount) {       // Made by Mufleh and Azhan

    cout << "=============================== RESTOCK ITEMS ==============================\n" << endl;
    if (itemCount == 0)
    {
        cout << "Inventory is empty! add items to restock\n";
        return;
    }
    int id;
    int qty;

    do {
        cout << "Enter the product ID to restock: ";
        if (cin >> id) {
            if (id < 0) {
                cout << "Id cannot be negative!" << endl;
            }
            else
                break;
        }
        else
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid Input!" << endl;
        }

    } while (true);

    int index = -1;
    for (int i = 0; i < itemCount; i++) {

        if (inventory[i].id == id) {
            index = i;
            break;
        }

    }

    if (index == -1) {
        cout << "Item not found!" << endl;
        return;
    }
    else
    {
        do {
            cout << "Enter the Quantity you want to add: ";
            if (cin >> qty) {
                if (qty < 0) {
                    cout << "Quantity cannot be negative!" << endl;
                }
                else
                    break;
            }
            else
            {
                cin.clear();
                cin.ignore();
                cout << "Invalid Input!" << endl;
            }

        } while (true);

        inventory[index].quantity += qty;

        cout << "Quantity Added! New quantity: " << inventory[index].quantity << endl;
        return;

    }

}
float applyDiscount(float price, float discountPercent) {    // Made by Mufleh
    int discounted;
    discounted = price * (1 - discountPercent / 100.0);;
    return discounted;
}
//--------------------------------------------------------------------------   SALES   -------------------------------------------------------------------------------


void recordSALE(int ItemCount, int& salesCount) {                                        // Made by Azhan

    cout << "=============================== SALES Management ===============================\n" << endl;

    int id;
    int qty;
    int i = 0;
    int final;
    float totalBill = 0.0;
    while (true) {

        cout << "Enter the ID of the product you want to sell: ";
        do {
            if (cin >> id) {
                break;
            }
            else {
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Invalid input!" << endl;
            }

        } while (true);

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
        while (true) {
            if (cin >> qty)
            {
                if (qty <= 0) {
                    cout << "Invalid Quantity!" << endl;
                }
                else break;
            }
            else {
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Invalid input ! enter again: " << endl;
            }
        }

        if ((inventory[i].quantity - qty) < 0) {
            cout << "Invalid quantity! only " << inventory[i].quantity << " " << inventory[i].name << " are available in stock" << endl;
            continue;
        }
        //discount logic by Mufleh 
        float discount= 0;
        int apply;
        cout << "Do You want To apply a discount to this item? [yes(1),No(2)]";
        do
        {
            cin >> apply;
        } while (apply != 1 && apply != 2);
        if (apply == 1)
        { 
            do
            {
                cout << "Enter Discount % (0-100) :";
                if (cin >> discount && discount >= 0 && discount <= 100)
                    break;
                else
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid Input! enter between 0 to 100 only! " << endl;

                }
            } while (true);
        }
        discount = applyDiscount(inventory[i].price, discount);

        inventory[i].quantity -= qty;
        sales[salesCount].productID = id;
        sales[salesCount].quantitySold = qty;
        sales[salesCount].totalPrice = qty * inventory[i].price;

        // record for top selling product
        inventory[i].quantitySold += qty;
        salesCount++;

        totalBill += qty * discount;
        cout << "Discounted Price per item: " << discount << " Rs\n";
        cout << "If bill is finalized press (1) if not press (2)";
        cin >> final;

        if (final == 1)
            break;

    }

    cout << "--------------------------------------------------------------------------------\n\n";
    cout << "\nYour Total Bill is " << totalBill << " .Rs\n\n";
    cout << "--------------------------------------------------------------------------------\n\n";

}

//--------------------------------------------------------------------------   STATS AND RECORD  -------------------------------------------------------------------------------

void displaysAllSales(int saleCount) {               // Made by Mufleh
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

void topSellingProduct(int saleCount, int itemCount) {          // Made by Azhan and Mufleh
    if (saleCount == 0) {
        cout << "No sales recorded yet." << endl;
        return;
    }
    int topIndex = 0;
    for (int i = 1; i < itemCount; i++) {
        if (inventory[i].quantitySold > inventory[topIndex].quantitySold) {
            topIndex = i;
        }
    }
    cout << "=============================== TOP SELLING PRODUCT ===============================\n" << endl;
    cout << "Product Name: " << inventory[topIndex].name << endl;
    cout << "Product category: " << inventory[topIndex].category << endl;
    cout << "Product ID: " << inventory[topIndex].id << endl;
    cout << "Quantity Sold: " << inventory[topIndex].quantitySold << endl;
    cout << "Total Price: " << inventory[topIndex].price * inventory[topIndex].quantitySold << " Rs\n";
    cout << "----------------------------------------\n";
}

void totalRevenue(int saleCount) {               // Made by Mufleh
    float total = 0;
    for (int i = 0; i < saleCount; i++) {
        total += sales[i].totalPrice;
    }
    cout << "=============================== TOTAL REVENUE ===============================\n" << endl;
    cout << "Total Revenue from Sales: " << total << " Rs\n";
    cout << "----------------------------------------\n";
}



//--------------------------------------------------------------------------   MENUS -------------------------------------------------------------------------------


int Mainmenu()                                                //made by Azhan
{
    int choice;
    cout << "======================================================  MENU ======================================================  \n\n";

    cout << setw(40) << "(1)" << "  Product management\n";
    cout << setw(40) << "(2)" << "  Inventory tracking\n";
    cout << setw(40) << "(3)" << "  Sales management\n";
    cout << setw(40) << "(4)" << "  Report and statistics\n";
    cout << setw(40) << "(5)" << "  Stocks related\n";
    cout << setw(40) << "(6)" << "  Exit\n";

    cout << "\n+--------------------------------------------------------------------------------------------------------------+\n\n";

    cout << "Your coice: ";

    do
    {

        if (cin >> choice)
        {
            if (choice > 6 || choice < 1) {
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
int pmMenu() {
    int choice;
    cout << "=============================================== Product Mangement ==============================================  \n\n";

    cout << setw(40) << "(1)" << "  Add Items\n";
    cout << setw(40) << "(2)" << "  Delete Items\n";
    cout << setw(40) << "(3)" << "  Edit Items\n";
    cout << setw(40) << "(4)" << "  Exit\n";

    cout << "\n+------------------------------------------------------------------------------------------------------------+\n\n";

    cout << "Your coice: ";

    do
    {

        if (cin >> choice)
        {
            if (choice > 4 || choice < 1) {
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

int ITmenu() {

    int choice;
    cout << "=============================================== Inventory Tracking ==============================================  \n\n";

    cout << setw(40) << "(1)" << "  View all products in stock\n";
    cout << setw(40) << "(2)" << "  Search product by id or name\n";
    cout << setw(40) << "(3)" << "  prevent negative stock\n";
    cout << setw(40) << "(4)" << "  Restock\n";
    cout << setw(40) << "(5)" << "  Exit\n";

    cout << "\n+------------------------------------------------------------------------------------------------------------+\n\n";

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

int salesMenu() {

    int choice;
    cout << "=============================================== Sales Menu ==============================================  \n\n";

    cout << setw(40) << "(1)" << "  Record sale\n";
    cout << setw(40) << "(2)" << "  Exit\n";

    cout << "\n+------------------------------------------------------------------------------------------------------------+\n\n";

    cout << "Your coice: ";

    do
    {

        if (cin >> choice)
        {
            if (choice > 2 || choice < 1) {
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

int rsMenu() {

    int choice;
    cout << "=============================================== Reports & Stats ==============================================  \n\n";

    cout << setw(40) << "(1)" << "  Display all sales made\n";
    cout << setw(40) << "(2)" << "  Show top-selling product(s)\n";
    cout << setw(40) << "(3)" << "  Display total revenue generated\n";
    cout << setw(40) << "(4)" << "  Exit\n";

    cout << "\n+------------------------------------------------------------------------------------------------------------+\n\n";

    cout << "Your coice: ";

    do
    {

        if (cin >> choice)
        {
            if (choice > 4 || choice < 1) {
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

int stocksMenu() {

    int choice;
    cout << "=============================================== Stocks Menu ==============================================  \n\n";

    cout << setw(40) << "(1)" << "  See notification [*] \n";
    cout << setw(40) << "(2)" << "  Restock\n";
    cout << setw(40) << "(3)" << "  Exit\n";

    cout << "\n+------------------------------------------------------------------------------------------------------------+\n\n";

    cout << "Your coice: ";

    do
    {

        if (cin >> choice)
        {
            if (choice > 3 || choice < 1) {
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

//--------------------------------------------------------------------------  MAIN  -------------------------------------------------------------------------------

int main()
{
    cout << "****************************************** INVENTORY MANAGEMENT ******************************************\n\n";

    int itemCount = 0;
    int saleCount = 0;

    loadData(itemCount);
    loadSales(saleCount);

    while (true)
    {
        system("cls");

        switch (Mainmenu())
        {

        case 1:
        {
            system("cls");

            switch (pmMenu())
            {
            case 1:
                system("cls");

                do {
                    int x;
                    addItem(itemCount);
                    cout << "If you want to continue adding items Press (1) and if you want to exit press (2)\n";
                    do {

                        if (cin >> x) {
                            if (!(x == 1 || x == 2))
                                cout << "Invalid choice!\n";
                            else break;
                        }
                        else
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Ivalid Input" << endl;
                        }


                    } while (true);
                    if (x == 1)
                    {
                        cout << "Adding another item: " << endl;
                    }
                    else
                        break;
                } while (true);
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;

            case 2:
                system("cls");
                removeItem(itemCount);
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;

            case 3:
                system("cls");
                editItem(itemCount);
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;

            case 4:

                break;
            }
            break;
        }


        case 2:
        {
            system("cls");

            switch (ITmenu())
            {
            case 1:
                system("cls");
                viewItems(itemCount);
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;

            case 2:
                system("cls");
                searchItem(itemCount);
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;

            case 3:
                system("cls");
                preventNegStock(itemCount);
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;

            case 4:
                system("cls");
                restock(itemCount);
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;

            case 5:

                break;
            }
            break;
        }


        case 3:
        {
            system("cls");

            switch (salesMenu())
            {
            case 1:
                system("cls");
                recordSALE(itemCount, saleCount);
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;

            case 2:

                break;
            }
            break;
        }


        case 4:
        {
            system("cls");

            switch (rsMenu())
            {
            case 1:
                system("cls");
                displaysAllSales(saleCount);
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;

            case 2:
                system("cls");
                topSellingProduct(saleCount, itemCount);
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;

            case 3:
                system("cls");
                totalRevenue(saleCount);
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;

            case 4:

                break;
            }
            break;
        }
        case 5:
        {
            system("cls");
            switch (stocksMenu()) {


            case 1: {

                system("cls");
                preventNegStock(itemCount);
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            }
            case 2: {

                system("cls");
                restock(itemCount);
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                break;

            }

            }

            break;

        }

        case 6:
        {
            cout << "Bye :)" << endl;
            return 0;
        }


        default:
            cout << "Invalid choice!";
        }

        saveSales(saleCount);
        saveData(itemCount);
    }

    return 0;
}












