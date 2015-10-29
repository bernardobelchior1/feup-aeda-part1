#include "menus.h"

#include"class/menu/menu.h"
#include"class/advertisement/advertisement.h"
#include"class/advertisement/sale/sale.h"
#include"class/advertisement/purchase/purchase.h"
#include"class/data/data.h"
#include"class/menu/searchMenu/searchMenu.h"
#include<iostream>
#include<stdlib.h>
#include"class/menu/optionMenu/optionMenu.h"

/*Menu Presentation
 *
 * 1 - Search
 * 2 - Sign In
 * 3 - Sign Up
 * 4 - Exit
 */

void mainMenu(Data* data){
	OptionMenu menu(data, 20, 20, '?');
	menu.addOption("Search", &search);
	menu.addOption("Sign In", &signIn);
	menu.addOption("Sign Up", &signUp);
	menu.addOption("Exit", &exitApp);
	menu.createMenu();
}

void search(Data* data){
	string search;
	cout << "\nInsert what you would like to search for: ";
	getline(cin, search);
	vector<Advertisement* > results;
	results = data->searchForAds(search);
	SearchMenu menu(data,20,20,results);
	menu.createMenu();
}

void signIn(Data* data){
	string email, password;

	cout << "Email: ";
	getline(cin, email);

	cout << "\nPassword: ";
	getline(cin, password);

	cout << endl;

	if(data->signIn(email, password))
		signedInMenu(data);
	else
		cout << "Wrong email and password combination.";//program closes here, have to choose what to do next

}

void signUp(Data* data){
	string name, email, passwordOne = " ", passwordTwo = "", phoneNumber, location;

	cout << "\nWhat is your name?\n";
	getline(cin, name);

	unsigned int i = 0;
	do{
		if(i > 0)
			cout << "\nPlease introduce a valid email.";
		cout << "\nWhat is your email?\n";
		getline(cin, email);
		i++;
	}while(email.find("@") == -1 || email.find_last_of(".") == -1 || email.find("@") > email.find_last_of("."));

	i = 0;
	do{
		if(i > 0)
			cout << "\nYour passwords do not match.";
		cout << "\nWhat is your password?\n";
		getline(cin, passwordOne);
		cout << "\nPlease, repeat your password.\n";
		getline(cin, passwordTwo);
		i++;
	}while(passwordOne != passwordTwo);

	cout << "\nWhat is your phone number?\n";
	getline(cin, phoneNumber);

	cout << "\nWhere are you from? (City, county, district)\n";
	getline(cin, location);
	Location loc(location);

	Date signUpDate(25,10,2015);//still have to get date as of now

	data->addUser(User(email, name, passwordOne, phoneNumber, signUpDate, loc));
	cout << loc;
	cout << "\nYour profile has been created. You may now sign in.\n";
	mainMenu(data);
}

void exitApp(Data* data){
	exit(0);
}

void signedInMenu(Data* data){
	OptionMenu menu(data, 20, 50, '#');
	menu.addOption("Search", &search);
	menu.addOption("Manage advertisements", &manageAds);
	menu.addOption("Sign out", &signOut);
	menu.createMenu();
}

void manageAds(Data* data){
	OptionMenu menu(data, 20, 50, '#');
	menu.addOption("Create buying advertisement", &createBuyingAd);
	menu.addOption("Create selling advertisement", &createSellingAd);
	menu.addOption("Edit advertisement", &editAd);
	menu.addOption("Delete advertisement", &removeAd);
	menu.createMenu();
}

void createSellingAd(Data* data){
	string title, description = "", tmp = "", category, condition;

	cout << "Title: ";
	getline(cin, title);

	cout << "What category does your advertisement fit into?\n";
	do{
		getline(cin, category);
	}while(/*!isValidCategory(category)*/false); //TODO check if category is valid
	Category cat = Others;

	cout << "Insert description.\n";
	getline(cin, description);

	cin.clear();

	cout << "What is your product condition?\n";
	do{
		getline(cin, condition);
	}while(/*!isValidCategory(category)*/false); //TODO check if category is valid
	Condition cond = New;


	Advertisement* ad = new Sale(data->getSignedInUser(), title, cat, description,cond);
	data->getSignedInUser()->addAdvertisement(ad);
}

void createBuyingAd(Data* data){
	string title, description = "", tmp = "", category, condition;

	cout << "Title: ";
	getline(cin, title);

	cout << "What category does your advertisement fit into?\n";
	do{
		getline(cin, category);
	}while(/*!isValidCategory(category)*/false); //TODO check if category is valid
	Category cat = Others;

	cout << "Insert description.\n";
	getline(cin, description);

	cin.clear();

	Advertisement* ad = new Purchase(data->getSignedInUser(), title, cat, description);
	data->getSignedInUser()->addAdvertisement(ad);
}

void editAd(Data* data){
 //TODO implement function
}

void removeAd(Data* data){
	//temporary. will create a menu afterwards.
	string title;
	cout << "Insert the title of the advertisement you want to delete.\n";
	//data->getSignedInUser()->removeAdvertisement(title);
}

void signOut(Data* data){
	data->signOut();
	mainMenu(data);
}