#pragma once
#include "Clients.h"
const string UsersFileName = "Users.txt";
void ShowLoginScreen() {}
void ShowMangementMenue(){}
struct stUser {
	string UserName;
	string PassWord;
	int Permission = 0;
	bool MarkForDelete = false;
};
enum enMangementMenueOption { ListUsers = 1 , AddNewUser = 2 , DeleteUser = 3 , UpdateUser = 4 , FindUser = 5 , MainMenue = 6 };
bool FindUserByUserName(string UserName,vector<stUser>& vUsers,stUser & User)
{
	for (stUser U : vUsers)
	{
		if (U.UserName == UserName)
		{
			User = U;
			return true;
		}
	}
	return false;
}
bool CheckUserPassWord(string PassWord, vector<stUser>& vUsers, stUser& User) {
	for (stUser U : vUsers)
	{
		if (U.PassWord == PassWord)
		{
			User = U;
			return true;
		}
	}
	return false;
}
bool CheckValidUserNameOrPassWord(string PassWord ,string UserName, vector<stUser>& vUsers, stUser& User) {
	return FindUserByUserName(UserName, vUsers, User) && CheckUserPassWord(PassWord, vUsers, User);
}
string ReadUserName() {
	string UserName;
	cout << "Enter User Name ? ";
	cin >> UserName;
	return UserName;
}
string ReadPassWord() {
	string PassWord;
	cout << "Enter Pass Word ? ";
	cin >> PassWord;
	return PassWord;
}
bool ReadUserInformation() {
	vector<stUser> vUsers;
	stUser User;
	while (true) {
		string UserName = ReadUserName();
		string PassWord = ReadPassWord();
		if (CheckValidUserNameOrPassWord(PassWord , UserName , vUsers , User))
			break ;

		else {
			cout << "Invalid UserName/PassWord !" << endl;
			cout << "Try Again.";
		}
	}
}
void ShowLoginScreen() {
	system("cls");
	cout << "===========================================================" << endl;
	cout << "\t\t Main Menue Screen\n";
	cout << "===========================================================" << endl;
	ReadUserInformation();
}

