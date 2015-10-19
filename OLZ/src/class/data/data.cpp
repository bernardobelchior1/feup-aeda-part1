#include "data.h"

#include<fstream>

Data::Data(){

}

Data::Data(string path) : path(path){

}

bool Data::loadUsers(){
	ifstream userFile;
	userFile.open(path.c_str(), ofstream::in);

	if(!userFile.is_open())
		return false;

	while(!userFile.eof()){
		User user;
		//userFile >> user;
		users.push_back(user);
	}
	return true;
}

bool Data::saveUsers(){
	char separationChar = '\n';
	ofstream userFile;
	userFile.open(path.c_str(), ofstream::out | ofstream::trunc);

	if(!userFile.is_open())
		return false;

	for(unsigned int i = 0; i < users.size(); i++){
		userFile << users[i].getEmail() << separationChar << users[i].getName() << separationChar
				<< users[i].getPhoneNumber() << separationChar << users[i].getLocationString() << separationChar;
	}
	return true;
}

void Data::removeAdvertisement(unsigned int id)
{
	unsigned int i;
	for(i=0; i < advertisements.size(); i++)
		if (advertisements[i]->getId() == id)
			break;

	if(i != advertisements.size()){
		delete advertisements[i];
		advertisements.erase(advertisements.begin() + i);
	}
}

void Data::addAdvertisement(Advertisement* ad){
	advertisements.push_back(ad);
}

vector<Advertisement*> Data::searchForAds(string text){
	vector<Advertisement*> results;

	for(unsigned int i = 0; i < advertisements.size(); i++){
		if(advertisements[i]->searchForText(text))
			results.push_back(advertisements[i]);
	}

	return results;
}
