#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Item {
public:
    int itemCode;
    string itemName;
    int quantity;

    void display() const {
        cout << "Item Code: " << itemCode << ", Name: " << itemName << ", Quantity: " << quantity << endl;
    }
};

vector<Item> inventory;

// Add new item
void addItem() {
    Item item;
    cout << "Enter item code: ";
    cin >> item.itemCode;
    cin.ignore();

    cout << "Enter item name: ";
    getline(cin, item.itemName);

    cout << "Enter quantity: ";
    cin >> item.quantity;
    cin.ignore();

    inventory.push_back(item);
    cout << "Item added successfully.\n";
}

// Display all items
void displayItems() {
    cout << "\nAll Inventory Items:\n";
    for (const auto& item : inventory) {
        item.display();
    }
}

// Search item by item code
void searchItem() {
    int code;
    cout << "Enter item code to search: ";
    cin >> code;
    cin.ignore();

    for (const auto& item : inventory) {
        if (item.itemCode == code) {
            item.display();
            return;
        }
    }
    cout << "Item not found.\n";
}

// Delete item by item code
void deleteItem() {
    int code;
    cout << "Enter item code to delete: ";
    cin >> code;
    cin.ignore();

    auto it = remove_if(inventory.begin(), inventory.end(),
                        [code](const Item& item) { return item.itemCode == code; });
    if (it != inventory.end()) {
        inventory.erase(it, inventory.end());
        cout << "Item deleted successfully.\n";
    } else {
        cout << "Item not found.\n";
    }
}

// Shreyas's contribution: Display top 3 items by quantity
void displayTop3ItemsByQuantity() {
    if (inventory.empty()) {
        cout << "No items available.\n";
        return;
    }

    vector<Item> sortedItems = inventory;
    sort(sortedItems.begin(), sortedItems.end(),
         [](const Item& a, const Item& b) { return a.quantity > b.quantity; });

    cout << "\nTop 3 Items by Quantity:\n";
    for (size_t i = 0; i < min(sortedItems.size(), size_t(3)); ++i) {
        sortedItems[i].display();
    }
}

// Chinami's contribution: Search item by name
void searchItemByName() {
    string name;
    cout << "Enter item name to search: ";
    getline(cin, name);

    bool found = false;
    for (const auto& item : inventory) {
        if (item.itemName == name) {
            item.display();
            found = true;
        }
    }
    if (!found) {
        cout << "No item found with the name \"" << name << "\".\n";
    }
}

// Suhas's contribution: Update item quantity by item code
void updateItemQuantity() {
    int code;
    cout << "Enter item code to update quantity: ";
    cin >> code;
    cin.ignore();

    for (auto& item : inventory) {
        if (item.itemCode == code) {
            int newQuantity;
            cout << "Enter new quantity: ";
            cin >> newQuantity;
            cin.ignore();
            item.quantity = newQuantity;
            cout << "Quantity updated successfully.\n";
            return;
        }
    }
    cout << "Item not found.\n";
}

// Prajwal's contribution: Sort items by item code
void sortItemsByCode() {
    if (inventory.empty()) {
        cout << "No items available to sort.\n";
        return;
    }

    sort(inventory.begin(), inventory.end(),
         [](const Item& a, const Item& b) { return a.itemCode < b.itemCode; });

    cout << "Items sorted by item code.\n";
}

// Sudharshan's contribution: Password authentication
bool authenticate() {
    string password;
    cout << "Enter password to access Inventory Management System: ";
    getline(cin, password);

    if (password == "admin123") {
        cout << "Access granted.\n";
        return true;
    } else {
        cout << "Access denied. Wrong password.\n";
        return false;
    }
}

void mainMenu() {
    int choice;
    while (true) {
        cout << "\nInventory Management System Menu:\n";
        cout << "1. Add Item\n";
        cout << "2. Display All Items\n";
        cout << "3. Search Item by Item Code\n";
        cout << "4. Delete Item\n";
        cout << "5. Display Top 3 Items by Quantity (Shreyas)\n";
        cout << "6. Search Item by Name (Chinami)\n";
        cout << "7. Update Item Quantity (Suhas)\n";
        cout << "8. Sort Items by Item Code (Prajwal)\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addItem(); break;
            case 2: displayItems(); break;
            case 3: searchItem(); break;
            case 4: deleteItem(); break;
            case 5: displayTop3ItemsByQuantity(); break;
            case 6: searchItemByName(); break;
            case 7: updateItemQuantity(); break;
            case 8: sortItemsByCode(); break;
            case 9: cout << "Exiting...\n"; return;
            default: cout << "Invalid choice! Try again.\n"; break;
        }
    }
}

int main() {
    cout << "Welcome to Inventory Management System\n";
    if (authenticate()) {
        mainMenu();
    }
    return 0;
}
