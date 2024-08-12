
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_SIZE = 100;

struct Accessory {
    int id;
    string name;
    float price;
    string category;  // New category field

    void readAccessory(istream& stream) {
        stream >> id;
        stream.ignore();
        getline(stream, name);
        stream >> price;
        stream.ignore();
        getline(stream, category);  // Read the category from the stream
    }

    void writeAccessory(ostream& stream) const {
        stream << id << endl;
        stream << name << endl;
        stream << price << endl;
        stream << category << endl;  // Write the category to the stream
    }
};

class AccessoriesManagementSystem {
private:
    fstream file;
    int hashTable[MAX_SIZE];

public:
    AccessoriesManagementSystem() {
        for (int i = 0; i < MAX_SIZE; i++)
            hashTable[i] = -1;
    }

    bool isAccessoryIdExists(int accessoryId) const {
        int index = accessoryId % MAX_SIZE;
        return (hashTable[index] != -1 && hashTable[index] != -2);
    }

    void insertAccessory(const Accessory& accessory) {
        file.open("accessories.txt", ios::out | ios::app);
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }

        accessory.writeAccessory(file);
        file << endl;

        int index = accessory.id % MAX_SIZE;
        if (hashTable[index] == -1)
            hashTable[index] = file.tellp();

        file.close();
    }

    void deleteAccessory(int accessoryId) {
        int index = accessoryId % MAX_SIZE;
        if (hashTable[index] == -1) {
            cout << "Accessory not found!" << endl;
            return;
        }

        // Mark the accessory as deleted
        hashTable[index] = -2;
        cout << "Accessory marked as deleted!" << endl;
    }

    void modifyAccessory(int accessoryId, const Accessory& newAccessory) {
        int index = accessoryId % MAX_SIZE;
        if (hashTable[index] == -1) {
            cout << "Accessory not found!" << endl;
            return;
        }

        file.open("accessories.txt", ios::in | ios::out);
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }

        Accessory accessory;
        bool found = false;
        int currentPosition = file.tellp();

        while (!file.eof()) {
            accessory.readAccessory(file);

            if (accessory.id == accessoryId && hashTable[accessoryId % MAX_SIZE] != -2) {
                found = true;
                file.seekp(currentPosition);
                newAccessory.writeAccessory(file);
                break;
            }

            currentPosition = file.tellp();
        }

        file.close();

        if (!found) {
            cout << "Accessory not found!" << endl;
        } else {
            cout << "Accessory modified successfully!" << endl;
        }
    }

    void searchAccessory(int accessoryId) {
        file.open("accessories.txt", ios::in);
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }

        Accessory accessory;
        bool found = false;

        while (!file.eof()) {
            accessory.readAccessory(file);

            if (accessory.id == accessoryId && hashTable[accessoryId % MAX_SIZE] != -2) {
                cout << "Accessory ID: " << accessory.id << endl;
                cout << "Accessory Name: " << accessory.name << endl;
                cout << "Accessory Price: Rs." << accessory.price << endl;
                cout << "Accessory Category: " << accessory.category << endl;

                found = true;
                break;
            }
        }

        file.close();

        if (!found) {
            cout << "Accessory not found!" << endl;
        }
    }

    void displayAccessories() {
        file.open("accessories.txt", ios::in);
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }

        Accessory accessory;
        int count = 0;

        while (!file.eof()) {
            accessory.readAccessory(file);

            if (accessory.id != -1 && hashTable[accessory.id % MAX_SIZE] != -2 && file.peek() != EOF) {
                cout << "Accessory " << count + 1 << ":" << endl;
                cout << "ID: " << accessory.id << endl;
                cout << "Name: " << accessory.name << endl;
                cout << "Price: Rs." << accessory.price << endl;
                cout << "Category: " << accessory.category << endl;
                cout << "--------------------------------" << endl;

                count++;
            }
        }

        file.close();

        if (count == 0) {
            cout << "No accessories found!" << endl;
        }
    }

    void displayAllAccessories() {
        file.open("accessories.txt", ios::in);
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }

        Accessory accessory;
        int count = 0;

        while (!file.eof()) {
            accessory.readAccessory(file);

            if (file.peek() != EOF) {
                cout << "Accessory " << count + 1 << ":" << endl;
                cout << "ID: " << accessory.id << endl;
                cout << "Name: " << accessory.name << endl;
                cout << "Price: Rs." << accessory.price << endl;
                cout << "Category: " << accessory.category << endl;
                cout << "--------------------------------" << endl;

                count++;
            }
        }

        file.close();

        if (count == 0) {
            cout << "No accessories found!" << endl;
        }
    }
};

int main() {
    AccessoriesManagementSystem ams;
    int option;
    Accessory accessory;
    cout << "-----------------------------------------------------------" << endl;

    cout << "\t\tAccessories Management System " << endl;
    cout << "\t\tSubramanya (2BL20ISO37)  " << endl;
    cout << "      \t\t\t And          " << endl;
    cout << "\t\tSushanth (2BL20IS041)" << endl;
    cout << "-----------------------------------------------------------" << endl;

    do {
        cout << "\n--- Options ---" << endl;
        cout << "1. Insert Accessory" << endl;
        cout << "2. Delete Accessory" << endl;
        cout << "3. Modify Accessory" << endl;
        cout << "4. Search Accessory" << endl;
        cout << "5. Display Accessories" << endl;
        cout << "6. Display All Accessories" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your option: ";
        cin >> option;

        switch (option) {
            case 1: {
                cout << "\nEnter Accessory ID: ";
                cin >> accessory.id;

                if (ams.isAccessoryIdExists(accessory.id)) {
                    cout << "Accessory ID already exists!" << endl;
                   break;
                }

                cout << "Enter Accessory Name: ";
                cin.ignore();
                getline(cin, accessory.name);
                cout << "Enter Accessory Price: Rs.";
                cin >> accessory.price;
                cout << "Enter Accessory Category: ";
                cin.ignore();
                getline(cin, accessory.category);

                ams.insertAccessory(accessory);
                cout << "Accessory inserted successfully!" << endl;
                break;
            }
            case 2: {
                int accessoryId;
                cout << "\nEnter Accessory ID to delete: ";
                cin >> accessoryId;

                ams.deleteAccessory(accessoryId);
                break;
            }
            case 3: {
                int accessoryId;
                cout << "\nEnter Accessory ID to modify: ";
                cin >> accessoryId;

                if (ams.isAccessoryIdExists(accessoryId)) {
                    Accessory newAccessory;
                    cout << "Enter new Accessory ID: ";
                    cin >> newAccessory.id;

                    if (ams.isAccessoryIdExists(newAccessory.id)) {
                        cout << "New Accessory ID already exists!" << endl;
                        break;
                    }

                    cout << "Enter new Accessory Name: ";
                    cin.ignore();
                    getline(cin, newAccessory.name);
                    cout << "Enter new Accessory Price: Rs.";
                    cin >> newAccessory.price;
                    cout << "Enter new Accessory Category: ";
                    cin.ignore();
                    getline(cin, newAccessory.category);

                    ams.modifyAccessory(accessoryId, newAccessory);
                } else {
                    cout << "Accessory ID not found!" << endl;
                }

                break;
            }
            case 4: {
                int accessoryId;
                cout << "\nEnter Accessory ID to search: ";
                cin >> accessoryId;

                ams.searchAccessory(accessoryId);
                break;
            }
            case 5: {
                ams.displayAccessories();
                break;
            }
            case 6: {
                ams.displayAllAccessories();
                break;
            }
            case 7: {
                cout << "\nExiting the program. Goodbye!" << endl;
                break;
            }
            default: {
                cout << "\nInvalid option. Please try again." << endl;
                break;
            }
        }
    } while (option != 7);

    return 0;
}
