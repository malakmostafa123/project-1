#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Customer Class
class Customer {
private:
    string name;
    string address;
    string mobileNumber;
    double paidAmount;
    double dueAmount;
    string paymentDate;

public:
    Customer(const string& name, const string& address, const string& mobileNumber,
        double paidAmount, double dueAmount, const string& paymentDate)
        : name(name), address(address), mobileNumber(mobileNumber),
        paidAmount(paidAmount), dueAmount(dueAmount), paymentDate(paymentDate) {}

    // Getter
    string getName() const { return name; }
    string getAddress() const { return address; }
    string getMobileNumber() const { return mobileNumber; }
    double getPaidAmount() const { return paidAmount; }
    double getDueAmount() const { return dueAmount; }
    string getPaymentDate() const { return paymentDate; }

    // Setter
    void setName(const string& newName) { name = newName; }
    void setAddress(const string& newAddress) { address = newAddress; }
    void setMobileNumber(const string& newMobileNumber) { mobileNumber = newMobileNumber; }
    void setPaidAmount(double newPaidAmount) { paidAmount = newPaidAmount; }
    void setDueAmount(double newDueAmount) { dueAmount = newDueAmount; }
    void setPaymentDate(const string& newPaymentDate) { paymentDate = newPaymentDate; }


    void display() const {
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Mobile Number: " << mobileNumber << endl;
        cout << "Paid Amount: " << paidAmount << endl;
        cout << "Due Amount: " << dueAmount << endl;
        cout << "Payment Date: " << paymentDate << endl;
    }
};

// CustomerManager Class
class CustomerManager {
private:
    vector<Customer> customers;
    string filename;

public:
    CustomerManager(const string& filename) : filename(filename) {}

    void addCustomer(const Customer& customer) {
        customers.push_back(customer);
    }

    void editCustomer(const string& name, const Customer& newCustomer) {
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].getName() == name) {
                customers[i] = newCustomer;
                break;
            }
        }
    }

    Customer* getCustomerByName(const string& name) {
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].getName() == name) {
                return &customers[i];
            }
        }
        return NULL;
    }

    void loadFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            string name, address, mobileNumber, paymentDate;
            double paidAmount, dueAmount;
            while (file >> name >> address >> mobileNumber >> paidAmount >> dueAmount >> paymentDate) {
                customers.push_back(Customer(name, address, mobileNumber, paidAmount, dueAmount, paymentDate));
            }
            file.close();
        }
        else {
            cout << "Unable to open file: " << filename << endl;
        }
    }

    void saveToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < customers.size(); i++) {
                const Customer& customer = customers[i];
                file << customer.getName() << " " << customer.getAddress() << " "
                    << customer.getMobileNumber() << " " << customer.getPaidAmount() << " "
                    << customer.getDueAmount() << " " << customer.getPaymentDate() << endl;
            }
            file.close();
        }
        else {
            cout << "Unable to open file: " << filename << endl;
        }
    }
};

// Main Application Class
class BillingSystem {
private:
    CustomerManager customerManager;

public:
    BillingSystem(const string& filename) : customerManager(filename) {}

    void displayMenu() {

        cout << "1. Add Customer" << endl;
        cout << "2. Edit Customer" << endl;
        cout << "3. View Customer" << endl;
        cout << "4. Save Data" << endl;
        cout << "5. Load Data" << endl;
        cout << "6. Exit" << endl;
    }

    void addCustomerOption() {
        string name, address, mobileNumber, paymentDate;
        double paidAmount, dueAmount;

        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Address: ";
        cin >> address;
        cout << "Enter Mobile Number: ";
        cin >> mobileNumber;
        cout << "Enter Paid Amount: ";
        cin >> paidAmount;
        cout << "Enter Due Amount: ";
        cin >> dueAmount;
        cout << "Enter Payment Date: ";
        cin >> paymentDate;

        Customer newCustomer(name, address, mobileNumber, paidAmount, dueAmount, paymentDate);
        customerManager.addCustomer(newCustomer);
        cout << "Customer added successfully!" << endl;
    }

    void editCustomerOption() {
        string name;
        cout << "Enter the name of the customer you want to edit: ";
        cin >> name;

        Customer* customer = customerManager.getCustomerByName(name);
        if (customer != NULL) {
            string newName, newAddress, newMobileNumber, newPaymentDate;
            double newPaidAmount, newDueAmount;

            cout << "Enter New Name: ";
            cin >> newName;
            cout << "Enter New Address: ";
            cin >> newAddress;
            cout << "Enter New Mobile Number: ";
            cin >> newMobileNumber;
            cout << "Enter New Paid Amount: ";
            cin >> newPaidAmount;
            cout << "Enter New Due Amount: ";
            cin >> newDueAmount;
            cout << "Enter New Payment Date: ";
            cin >> newPaymentDate;

            Customer newCustomer(newName, newAddress, newMobileNumber, newPaidAmount, newDueAmount, newPaymentDate);
            customerManager.editCustomer(name, newCustomer);
            cout << "Customer details updated successfully!" << endl;
        }
        else {
            cout << "Customer not found!" << endl;
        }
    }

    void viewCustomerOption() {
        string name;
        cout << "Enter the name of the customer you want to view: ";
        cin >> name;

        Customer* customer = customerManager.getCustomerByName(name);
        if (customer != NULL) {
            customer->display();
        }
        else {
            cout << "Customer not found!" << endl;
        }
    }

    void saveDataOption() {
        customerManager.saveToFile();
        cout << "Data saved successfully!" << endl;
    }

    void loadDataOption() {
        customerManager.loadFromFile();
        cout << "Data loaded successfully!" << endl;
    }

    void start()
    {
        int choice;
        do {
            cout << "_\n" << endl;
            cout << "Customer Manager Main Menu \n";
            cout << "_" << endl;
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addCustomerOption();
                break;
            case 2:
                editCustomerOption();
                break;
            case 3:
                viewCustomerOption();
                break;
            case 4:
                saveDataOption();
                break;
            case 5:
                loadDataOption();
                break;
            case 6:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        } while (choice != 6);
    }
};

int main() {
    BillingSystem billingSystem("C:\\Users\\sango\\Desktop\\file.txt");
    billingSystem.start();
    return 0;
}