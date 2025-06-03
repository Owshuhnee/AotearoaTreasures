#include <iostream>
#include <string>
#include <vector>	
using namespace std;

//ADD USER ROLES HERE (CUSTOMER, ADMINISTRATOR)
//CLASS STORE HERE
//CLASS PRODUCT HERE
//CLASS EMPLOYEE HERE

void mainMenu() {
	cout << "\n1. Customer" << endl;
	cout << "2. Administrator" << endl;
	cout << "3. Exit" << endl;
	cout << "Please select an option: ";
}
void storelocationMenu() {
	cout << "\n1. Auckland" << endl;
	cout << "2. Wellington" << endl;
	cout << "3. Christchurch" << endl;
	cout << "4. Back to previous menu" << endl;
	cout << "Please select an option: ";
}

void adminMenu() {
	cout << "\n1. Manage Employees" << endl;
	cout << "2. Manage Products" << endl;
	cout << "3. View Low Stock products" << endl;
	cout << "4. Back to previous menu" << endl;
	cout << "Please select an option: ";
}

int main() {
	int choice;
	int storelocationChoice;
	int adminChoice;
	int customerChoice;

	cout << "Welcome to Aotearoa Treasures!" << endl;
	cout << "Your one stop shop for NZ Souvenirs" << endl;
	cout << "----------------------------------------" << endl;
	mainMenu(); //DISPLAY MAIN MENU (CUSTOMER, ADMIN, EXIT)

	/*-----------------------------------------CUSTOMER FEATURE-----------------------------------------*/
	
	do {
		cin >> choice;

		if (choice == 1) {
			cout << "\nWelcome Customer" << endl;
			cout << "Please select a store to browse" << endl;
			storelocationMenu(); //DISPLAY STORE SELECTION MENU (AUCKLAND, WELLINGTON, CHRISTCHURCH) (CAN POTENTIALLY BE USED FOR ADMIN VIEW PRODUCTS FUNCTION)

			do {
				cin >> storelocationChoice;

				switch (storelocationChoice) {
				case 1: 
					cout << "You have selected Auckland Store" << endl;
					// ADD FUNCTION TO DISPLAY PRODUCTS
					break;
				case 2: 
					cout << "You have selected Wellington Store" << endl;
					// ADD FUNCTION TO DISPLAY PRODUCTS
					break;
				case 3: 
					cout << "You have selected Christchurch Store" << endl;
					// ADD FUNCTION TO DISPLAY PRODUCTS
					break;
				case 4: //BACK TO PREVIOUS MENU
					cout << "Returning to Main Menu" << endl;
					mainMenu();
					break;
				default:
					cout << "Invalid input. Please try again" << endl;
					storelocationMenu();
					break;
				}
			} while (storelocationChoice != 4);

			cout << "\n1.Buy Item" << endl;
			cout << "2.Back to Store selection" << endl;
			cout << "Please select an option: ";
			cin >> customerChoice;

			do {
				if (customerChoice == 1) {
					cout << "Please enter ID" << endl; // ADD FUNCTION
					cout << "Please enter quantity" << endl; // ADD FUNCTION
					// ADD FUNCTION TO PROCESS PURCHASE
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
		/*-------------------------------------------ADMIN FEATURE--------------------------------------------*/
		
		else if (choice == 2) {
			cout << "\nWelcome Administator" << endl;
			cout << "What would you like to do?" << endl;
			adminMenu();

			do {
				cin >> adminChoice;

				switch (adminChoice) {
				case 1: //ADD FUNCTION TO VIEW, ADD, UPDATE, CHANGE SHIFT TO EMPLOYEES
					cout << "Manage Employees" << endl;
					break;
				case 2: //ADD FUNCTION TO VIEW, ADD, UPDATE for ALL or PER STORE
					cout << "Manage Products" << endl;
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

		/*------------------------------------------EXIT PROGRAM-------------------------------------------*/
		else if (choice == 3) {
			cout << "Exiting program." << endl;
			cout << "Thank you for using Aeteroa Souv" << endl;
			return 0;
		}
		else {
			cout << "Invalid Input. Please try again" << endl;
			mainMenu();
		}
	} while (choice != 3);
	return 0;
}
