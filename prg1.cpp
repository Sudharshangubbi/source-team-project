// added search for products by name.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Item {
public:
    int id;
    string name;
    int quantity;
    double price;

    Item(int i, string n, int q, double p) : id(i), name(n), quantity(q), price(p) {}

    void display() {
        cout << "Item ID: " << id << "\nName: " << name
             << "\nQuantity: " << quantity << "\nPrice: " << price << "\n";
    }
};

class InventoryManagement {
private:
    vector<Item> items;
    int nextId = 1;

    static string toLower(const string &str) {
        string lower = str;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return lower;
    }

public:
    void addItem(string name, int quantity, double price) {
        items.push_back(Item(nextId++, name, quantity, price));
        cout << "Item added.\n";
    }

    Item* findItem(int id) {
        for (auto &i : items)
            if (i.id == id) return &i;
        return nullptr;
    }

    void updateItem(int id, string name, int quantity, double price) {
        Item* item = findItem(id);
        if (!item) {
            cout << "Item not found.\n";
            return;
        }
        item->name = name;
        item->quantity = quantity;
        item->price = price;
        cout << "Item updated.\n";
    }

    void deleteItem(int id) {
        auto it = remove_if(items.begin(), items.end(), [id](Item &i) { return i.id == id; });
        if (it != items.end()) {
            items.erase(it, items.end());
            cout << "Item deleted.\n";
        } else {
            cout << "Item not found.\n";
        }
    }

    void displayAll() {
        if (items.empty()) {
            cout << "No items in inventory.\n";
            return;
        }
        cout << "Inventory Items:\n";
        for (auto &i : items) {
            i.display();
            cout << "----\n";
        }
    }

    void displayLowStock(int threshold) {
        bool found = false;
        cout << "Items with stock less than or equal to " << threshold << ":\n";
        for (auto &i : items) {
            if (i.quantity <= threshold) {
                i.display();
                cout << "----\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No items found under threshold.\n";
        }
    }

    void searchItemByName(const string& keyword) {
        string key = toLower(keyword);
        bool found = false;
        cout << "Search results for \"" << keyword << "\":\n";
        for (auto &i : items) {
            if (toLower(i.name).find(key) != string::npos) {
                i.display();
                cout << "----\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No items found matching the keyword.\n";
        }
    }
};

void showMenu() {
    cout << "\n--- Inventory Management System ---\n";
    cout << "1. Add Item\n";
    cout << "2. Update Item\n";
    cout << "3. Delete Item\n";
    cout << "4. Display All Items\n";
    cout << "5. Display Low Stock Items\n";
    cout << "6. Search Item by Name\n";
    cout << "7. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    InventoryManagement inv;
    int choice;

    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 7) break;

        switch (choice) {
            case 1: {
                string name;
                int quantity;
                double price;
                cout << "Enter item name: ";
                getline(cin, name);
                cout << "Enter quantity: ";
                cin >> quantity;
                cout << "Enter price: ";
                cin >> price;
                cin.ignore();
                inv.addItem(name, quantity, price);
                break;
            }
            case 2: {
                int id, quantity;
                double price;
                string name;
                cout << "Enter item ID to update: ";
                cin >> id;
                cin.ignore();
                cout << "Enter new name: ";
                getline(cin, name);
                cout << "Enter new quantity: ";
                cin >> quantity;
                cout << "Enter new price: ";
                cin >> price;
                cin.ignore();
                inv.updateItem(id, name, quantity, price);
                break;
            }
            case 3: {
                int id;
                cout << "Enter item ID to delete: ";
                cin >> id;
                cin.ignore();
                inv.deleteItem(id);
                break;
            }
            case 4:
                inv.displayAll();
                break;
            case 5: {
                int threshold;
                cout << "Enter stock threshold: ";
                cin >> threshold;
                cin.ignore();
                inv.displayLowStock(threshold);
                break;
            }
            case 6: {
                string keyword;
                cout << "Enter name or part of name to search: ";
                getline(cin, keyword);
                inv.searchItemByName(keyword);
                break;
            }
            default:
                cout << "Invalid choice.\n";
        }
    }

    cout << "Exiting...\n";
    return 0;
}

