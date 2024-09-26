
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Product {
    string name;
    string manufacturer;
    string type;
    string unit;
    double weight;
    double price_per_unit;
};


void Input(Product**& products, int& count) {
    Product* newProduct = new Product;
    cout << "Enter product name: ";
    cin >> newProduct->name;
    cout << "Enter manufacturer: ";
    cin >> newProduct->manufacturer;
    cout << "Enter product type : ";
    cin >> newProduct->type;
    cout << "Enter unit of measurement: ";
    cin >> newProduct->unit;
    cout << "Enter weight: ";
    cin >> newProduct->weight;
    cout << "Enter price per unit: ";
    cin >> newProduct->price_per_unit;

    Product** newProducts = new Product * [count + 1];
    for (int i = 0; i < count; ++i) {
        newProducts[i] = products[i];
    }
    newProducts[count] = newProduct;

    delete[] products;
    products = newProducts;
    ++count;
}


void example(Product**& products, int& count) {
    Product* product1 = new Product{ "Milk", "A", "Drinks", "liter", 1.0, 30.5 };
    Product* product2 = new Product{ "Bread", "B", "Bakery", "piece", 0.5, 15.0 };
    Product* product3 = new Product{ "Chicken", "C", "Meat", "kilogram", 2.0, 120.0 };

    Product** newProducts = new Product * [count + 3];
    for (int i = 0; i < count; ++i) {
        newProducts[i] = products[i];
    }
    newProducts[count] = product1;
    newProducts[count + 1] = product2;
    newProducts[count + 2] = product3;

    delete[] products;
    products = newProducts;
    count += 3;
}


void display(Product** products, int count) {
    for (int i = 0; i < count; ++i) {
        cout << "Name: " << products[i]->name << ", Manufacturer: " << products[i]->manufacturer;
        cout << ", Type: " << products[i]->type << ", Unit: " << products[i]->unit;
        cout << ", Weight: " << products[i]->weight << ", Price per unit: " << products[i]->price_per_unit;
            cout << endl;
    }
}


void searchByManufacturer(Product** products, int count, const string& manufacturer) {
    for (int i = 0; i < count; ++i) {
        if (products[i]->manufacturer == manufacturer) {
            cout << "Found product: " << products[i]->name << endl;
        }
    }
}


void searchByType(Product** products, int count, const string& type) {
    for (int i = 0; i < count; ++i) {
        if (products[i]->type == type) {
            cout << "Found product: " << products[i]->name << endl;
        }
    }
}


void sortByManufacturer(Product** products, int count) {
    sort(products, products + count, [](Product* a, Product* b) {
        return a->manufacturer < b->manufacturer;
        }
    );
}


void sortByType(Product** products, int count) {
    sort(products, products + count, [](Product* a, Product* b) {
        return a->type < b->type;
        }
    );
}


double calculateTotalWeight(Product** products, int count) {
    double totalWeight = 0.0;
    for (int i = 0; i < count; ++i) {
        totalWeight += products[i]->weight;
    }
    return totalWeight;
}
 
void menu(Product**& products, int& count) {
    int choice;
    do {
        cout << "1. Enter data manually\n";
        cout << "2. Example\n";
        cout << "3. Display data\n";
        cout << "4. Search\n";
        cout << "5. Sort\n";
        cout << "6. Calculate total weight\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            Input(products, count);
            break;
        case 2:
            example(products, count);
            break;
        case 3:
            display(products, count);
            break;
        case 4: {
            int searchChoice;
            cout << "1. Search by manufacturer\n";
            cout << "2. Search by product type\n";
            cout << "Your choice: ";
            cin >> searchChoice;
            if (searchChoice == 1) {
                string manufacturer;
                cout << "Enter manufacturer: ";
                cin >> manufacturer;
                searchByManufacturer(products, count, manufacturer);
            }
            else if (searchChoice == 2) {
                string type;
                cout << "Enter product type: ";
                cin >> type;
                searchByType(products, count, type);
            }
            break;
        }
        case 5: {
            int sortChoice;
            cout << "1. Sort by manufacturer\n";
            cout << "2. Sort by product type\n";
            cout << "Your choice: ";
            cin >> sortChoice;
            if (sortChoice == 1) {
                sortByManufacturer(products, count);
            }
            else if (sortChoice == 2) {
                sortByType(products, count);
            }
            break;
        }
        case 6:
            cout << "Total weight of purchase: " << calculateTotalWeight(products, count) << " kg\n";
            break;
        case 0:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}


void cleanup(Product**& products, int count) {
    for (int i = 0; i < count; ++i) {
        delete products[i];
    }
    delete[] products;
}

int main() {
    Product** products = nullptr; 
    int count = 0;
    menu(products, count);
    cleanup(products, count); 
    return 0;
}
