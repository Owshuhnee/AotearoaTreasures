#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>	
using namespace std;

//ADD USER ROLES HERE (CUSTOMER, ADMINISTRATOR)
//CLASS STORE HERE
//CLASS EMPLOYEE HERE

/*------------------------------------- CLASS PRODUCT START -------------------------------------*/
class product {
	int id;
	string name;
	double price;
	int stockLevel;
	string branch;

public:
	product (int id, string name, double price, int stockLevel, string branch) :
		id(id), name(name), price(price), stockLevel(stockLevel), branch(branch) {}

	// Getters
	int getId() const { return id; }
	string getName() const { return name; }
	double getPrice() const { return price; }
	int getStockLevel() const { return stockLevel; }
	string getbranch() const { return branch; }

	// Setters
	void setId(int newId) { id = newId; }
	void setName(const string& newName) { name = newName; }
	void setPrice(double newPrice) { price = newPrice; }
	void setStockLevel(int newStockLevel) { stockLevel = newStockLevel; }
	void setBranch(const string& newBranch) { branch = newBranch; }

	// Display product details
	void display() const {
		cout << "Branch: " << branch
			 << ", ID: " << id
			 << ", Name: " << name
			 << ", Price: $" << price
			 << ", Stock: " << stockLevel << endl;
	}
};
/*--------------------------------------- CLASS PRODUCT END --------------------------------------*/


/*--------------------------------- CLASS PRODUCT MANAGER START ----------------------------------*/
class productManager {
private: 
	vector<product> products;

public:
	productManager() {
		loadProductsFromDisk();
	}	

	// SAVE DATA
	void saveProductsToDisk() const {
		ofstream file("products.txt");
		if (!file) {
			cerr << "Error saving to file." << endl;
			return;
		}
		for (const auto& p : products) {
			file << p.getId() << ","
				<< p.getName() << ","
				<< p.getPrice() << ","
				<< p.getStockLevel() << ","
				<< p.getbranch() << "\n";
		}
		file.close();
	}

	//LOAD DATA
	void loadProductsFromDisk() {
		ifstream file("products.txt");
		if (!file) {
			cerr << "No existing product file found. Starting fresh." << endl;
			return;
		}

		products.clear();
		string line;
		while (getline(file, line)) {
			istringstream ss(line);
			string token;
			int id, stock;
			double price;
			string name, branch;

			getline(ss, token, ',');
			id = stoi(token);

			getline(ss, name, ',');

			getline(ss, token, ',');
			price = stod(token);

			getline(ss, token, ',');
			stock = stoi(token);

			getline(ss, branch);

			products.emplace_back(id, name, price, stock, branch);
		}
		file.close();
	}


	// FUNCTION TO GET PRODUCT COUNT/SZE
	int getProductCount() const {
		return static_cast<int>(products.size());
	}

	// FUNCTION TO ADD NEW PRODUCTS
	void addProduct(int id, const string& name, double price, int stockLevel, const string& branch) {
		for (const auto& p : products) {
			if (p.getId() == id && p.getbranch() == branch) {
                cout << "Product with ID " << id << " already exists in " << branch << "." << endl;
				return;
			}
		}
		products.emplace_back(id, name, price, stockLevel, branch);
		cout << "PRODUCT ADDED SUCCESSFULLY" << endl;

		saveProductsToDisk(); // Save
	}

	// FUNCTION TO DISPLAY ALL PRODUCTS
	void displayProducts() const {
		if (products.empty()) {
			cout << "No products available." << endl;
			return;
		}
		cout << "\nAvailable Products:" << endl;
		for (const auto& p : products) {
			p.display();
		}
	}

	// FUNCTION TO UPDATE THE PRODUCT DETAILS
	void updateProduct(int id, const string& branch) {
		for (auto& p : products) {
			if (p.getId() == id && p.getbranch() == branch) {
				string newName;
				double newPrice;
				int newStockLevel;
				cout << "Updating product ID " << id << " in " << branch << endl;
				cout << "Enter new name: ";
				cin.ignore();
				getline(cin, newName);
				p.setName(newName);
				cout << "Enter new price: ";
				cin >> newPrice;
				p.setPrice(newPrice);
				cout << "Enter new stock level: ";
				cin >> newStockLevel;
				p.setStockLevel(newStockLevel);
				cout << "Product updated successfully." << endl;

				saveProductsToDisk(); // Save
				return;
			}
		}
		cout << "Product with ID " << id << " not found in " << branch << "." << endl;
	}
		
	// FUNCTION TO DELETE A PRODUCT
	void deleteProduct(int id, const string& branch) {
		for (auto it = products.begin(); it != products.end(); ++it) {
			if (it->getId() == id && it->getbranch() == branch) {
				products.erase(it);
				cout << "Product with ID " << id << " in " << branch << " deleted successfully." << endl;
				
				saveProductsToDisk(); // Save
				return;
			}
		}
		cout << "Product with ID " << id << " not found in " << branch << "." << endl;
	}
	
};
/*---------------------------------- CLASS PRODUCT MANAGER END -----------------------------------*/


/*-------------------------------------- MENU FUNCTIONS START ------------------------------------*/
void mainMenu() {
	cout << "\n1. Customer" << endl;
	cout << "2. Administrator" << endl;
	cout << "3. Exit" << endl;
	cout << "Please select an option: ";
}

void storelocationMenu() {
	cout << "\n---------- STORE LOCATIONS ----------" << endl;
	cout << "\n1. Auckland" << endl;
	cout << "2. Wellington" << endl;
	cout << "3. Christchurch" << endl;
	cout << "4. All Branches" << endl;
	cout << "5. Back to previous menu" << endl;
	cout << "Please select an option: ";
}

void adminMenu() {
	cout << "\n------------ ADMIN MENU -----------" << endl;
	cout << "1. Manage Employees" << endl;
	cout << "2. Manage Products" << endl;
	cout << "3. View Low Stock products" << endl;
	cout << "4. Back to previous menu" << endl;
	cout << "Please select an option: ";
}

void manageProductsMenu() {
	cout << "\n--------- MANAGE PRODUCTS ---------" << endl;
	cout << "1. Add a Product" << endl;
	cout << "2. View Products" << endl;
	cout << "3. Update a Product" << endl;
	cout << "4. Delete a Product" << endl;
	cout << "5. Back to previous menu" << endl;
	cout << "Please select an option: ";
}

void customerMenu() {
	cout << "1. Buy Item" << endl;
	cout << "2. Back to Store selection" << endl;
	cout << "Please select an option: ";
}
/*------------------------------------ MENU FUNCTIONS END -----------------------------------*/


/*------------------------------------ MAIN FUNCTION START -----------------------------------*/
int main() {
	int choice;
	int storelocationChoice;
	int adminChoice;
	int customerChoice;
	productManager pm;

	cout << "Welcome to Aotearoa Treasures!" << endl;
	cout << "Your one stop shop for NZ Souvenirs" << endl;
	cout << "-----------------------------------" << endl;
	mainMenu();

	/*------------------ CUSTOMER FUNCTIONS HERE ------------------*/
	do {
		cin >> choice;

		if (choice == 1) {
			cout << "\nWelcome Customer!" << endl;
			
			do {
				storelocationMenu(); //Show Menu
				cin >> storelocationChoice;

				switch (storelocationChoice) {
				case 1: 
					cout << "\nYou have selected Auckland Store" << endl;
					cout << "This function is not yet implemented." << endl;
					// ADD FUNCTION TO DISPLAY PRODUCTS FOR AUCKLAND STORE
					storelocationMenu(); // Go back to store location menu
					break;

				case 2: 
					cout << "\nYou have selected Wellington Store" << endl;
					cout << "This function is not yet implemented." << endl;
					// ADD FUNCTION TO DISPLAY PRODUCTS FOR WELLINGTON STORE
					storelocationMenu(); // Go back to store location menu
					break;

				case 3: 
					cout << "\nYou have selected Christchurch Store" << endl;
					cout << "This function is not yet implemented." << endl;
					// ADD FUNCTION TO DISPLAY PRODUCTS FOR WELLINGTON STORE
					storelocationMenu(); // Go back to store location menu
					break;

				case 4: 
					cout << "\nYou have selected All Branches" << endl;
					pm.displayProducts(); // Display all products
					storelocationMenu(); // Go back to store location menu
					break;

				case 5: //BACK TO PREVIOUS MENU
					cout << "Returning to Main Menu" << endl;
					mainMenu();
					break;

				default:
					cout << "Invalid input. Please try again" << endl;
					storelocationMenu();
					break;
				}
			} while (storelocationChoice != 5);

			customerMenu(); // Show Menu
			cin >> customerChoice; // Customer enters choice

			do {
				if (customerChoice == 1) {
					cout << "Please enter ID" << endl; // ADD FUNCTION
					cout << "Please enter branch" << endl; // ADD FUNCTION
					cout << "Please enter quantity" << endl; // ADD FUNCTION
					// ADD FUNCTION TO DISPLAY NEW STOCK LEVEL
				}
				else if (customerChoice == 2) {
					storelocationMenu();
				}
				else {
					cout << "Invalid Choice. Please try again" << endl;
				}
			} while (customerChoice != 2);
		}
		
		
		/*------------------ ADMIN FUNCTIONS HERE ------------------*/
		
		else if (choice == 2) {
			int manageProductsChoice;
			int id, stock;
			string name, branch;
			double price;
			id = 0;
			stock = 0;
			price = 0.0;
			name = "";
			branch = "";
			adminMenu(); // Show Menu

			cout << "\nWelcome Administator!" << endl;
					
			do {
				
				cin >> adminChoice; // Admin enters choice for admin menu

				switch (adminChoice) {
				case 1: //ADD FUNCTION TO VIEW, ADD, UPDATE, CHANGE SHIFT TO EMPLOYEES
					cout << "Manage Employees" << endl;
					break;

				case 2: //ADD FUNCTION TO VIEW, ADD, UPDATE PRODUCTS
					manageProductsMenu(); // Show Menu
					cin >> manageProductsChoice; // Admin enters choice

						switch (manageProductsChoice) {

							// FUNCTION TO ADD NEW PRODUCTS
							case 1:	
								cout << "\n---------- ADD NEW PRODUCTS ----------" << endl;

								cout << "Please enter product ID: ";
								cin >> id;
								cin.ignore();

								cout << "Please enter product name: ";
								getline(cin, name);

								cout << "Please enter product price: ";
								cin >> price;

								cout << "Please enter product stock level: ";
								cin >> stock;
								cin.ignore();
								
								cout << "Please enter Store Branch: ";
								getline(cin, branch);
								
								pm.addProduct(id, name, price, stock, branch);
								manageProductsMenu();
								break;
							
							// FUNCTION TO DISPLAY PRODUCTS
							case 2: { // No Products to display
								if (pm.getProductCount() == 0) {
									cout << "NO PRODUCTS AVAILABLE" << endl;
									manageProductsMenu(); // Go back to product manager menu
								}
								else { // Products exist, display them
									pm.displayProducts();
									manageProductsMenu();
								}
								break;
							}

							case 3: { // FUNCTION TO UPDATE PRODUCTS
								cout << "Update Products" << endl;
								pm.displayProducts();

								cout << "Enter product ID to update: ";
								cin >> id;
								cin.ignore();

								cout << "Enter branch of the product: ";
								getline(cin, branch);

								pm.updateProduct(id, branch);
								manageProductsMenu(); 
								break;
							}
							case 4: // FUNCTION TO DELETE PRODUCTS
								cout << "Delete Products" << endl;
								cout << "Enter Product ID to delete :";
								cin >> id;
								cin.ignore();

								cout << "Enter the Store location: ";
								getline(cin, branch);

								pm.deleteProduct(id, branch);
								manageProductsMenu(); // Go back to product manager menu
								break;

							case 5: cout << "Back to previous menu:" << endl;
								adminMenu();
								break;
							default: cout << "Invalid input. Please try again" << endl;
								break;
						}
					break;

				case 3: //ADD FUNCTION TO VIEW LOW STOCK PRODUCTS for ALL STORE
					cout << "View Low Stock Products" << endl;
					break;

				case 4:// BACK TO MAIN MENU
					cout << "Back to Main Menu" << endl;
					mainMenu();
					break;

				default:
					cout << "Invalid input. Please try again" << endl;
					adminMenu();
					break;
				}
			} while (adminChoice != 4);
		}

		else if (choice == 3) {
			cout << "Exiting program." << endl;
			cout << "Thank you for using Aotearoa Treasures" << endl;
			return 0;
		}
		else {
			cout << "Invalid Input. Please try again" << endl;
			mainMenu();
		}
	} while (choice != 3);
	return 0;
}
/*------------------------------------ MAIN FUNCTION END -----------------------------------*/