#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
const string UsersFileName = "Users.txt";
void ShowLoginScreen();
void ShowMangementUsersMenue();
void ShowMainMenue(); // Add this function declaration above the Login function
struct stUser {
	string UserName;
	string PassWord;
	int Permission = 0;
	bool MarkForDelete = false;
};
enum enMangementMenueOption { ListUsers = 1 , AddNewUser = 2 , DeleteUser = 3 , UpdateUser = 4 , FindUser = 5 , BacktoMainMenue = 6 };
vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord;

	while ((pos = S1.find(Delim)) != string::npos)
	{
		sWord = S1.substr(0, pos);

		if (sWord != "")
			vString.push_back(sWord);

		S1.erase(0, pos + Delim.length());
	}

	if (S1 != "")
		vString.push_back(S1);

	return vString;
}

stUser ConvertLineToRecordForUser(string Line, string Separator = "#//#")
{
	stUser User;
	vector<string> vUserData = SplitString(Line, Separator);

	if (vUserData.size() < 3) return User;

	User.UserName = vUserData[0];
	User.PassWord = vUserData[1];

	try {
		User.Permission = stoi(vUserData[2]);
	} catch (const std::exception&) {
		User.Permission = 0; // or log/error out
	}

	return User;
}
string ConvertRecordToLineForUser(stUser User, string Separator = "#//#")
{
	string stUserRecord = "";

	stUserRecord += User.UserName + Separator;
	stUserRecord += User.PassWord + Separator;
	stUserRecord += to_string(User.Permission) + Separator;
	

	return stUserRecord;
}
vector<stUser> LoadUsersDataFromFile(string FileName)
{
	vector<stUser> vUsers;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stUser User;

		while (getline(MyFile, Line))
		{
			User = ConvertLineToRecordForUser(Line);
			vUsers.push_back(User);
		}

		MyFile.close();
	}

	return vUsers;
}
void SaveUsersDataToFile(string FileName, vector<stUser>& vUsers)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (stUser U : vUsers)
		{
			if (U.MarkForDelete == false)
			{
				MyFile << ConvertRecordToLineForUser(U) << endl;
			}
		}

		MyFile.close();
	}
}

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
	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	stUser User;
	while (true) {
		string UserName = ReadUserName();
		string PassWord = ReadPassWord();
		if (CheckValidUserNameOrPassWord(PassWord, UserName, vUsers, User)) {
			return true;
		}
		else {
			cout << "Invalid UserName/PassWord !" << endl;
			cout << "Try Again.";
		}
	}
}
void ShowLoginScreen() {
	system("cls");
	cout << "===========================================================" << endl;
	cout << "\t\t Login Screen\n";
	cout << "===========================================================" << endl;
}
short ReadMangementMenueOption() {
	short Choose;
	cout << " Choose What Do You Want To Do ? [1 to 6]?";
	cin >> Choose;
	return Choose;
}
void GoBackToMangementMenue() {
	cout << "\nPress Eny Key to Back to Mangement Menue...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
	ShowMangementUsersMenue();
}
void PrintUserRecord(stUser& User) {
	cout << "|" << setw(15) << left << User.UserName;
	cout << "|" << setw(10) << left << User.PassWord;
	cout << "|" << setw(10) << left << User.Permission;
}
void ShowAllUsersScreen() {
	vector<stUser>vUsers = LoadUsersDataFromFile(UsersFileName);
	system("cls");
	cout << "                      Users List " << vUsers.size() << " User (s)  " << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "|" << setw(15) << left << "User Name" << "|" << setw(10) << left << "Pass Word " << "|"
		<< setw(10) << left << "Permissions" << endl
		<< "-------------------------------------------------------------" << endl;
	for (stUser& User : vUsers) {
		PrintUserRecord(User);
		cout << endl;
	}
	cout << "-----------------------------------------------------------" << endl;
}
void PrintUserCard(stUser User)
{
	cout << "\nThe following are the User details:\n" << endl;
	cout << "User Name :" << User.UserName << endl;
	cout << "Pass Word : " << User.PassWord << endl;
	cout << "Permissions : " << User.Permission << endl;
}
bool MarkUserForDeleteByUserName(string UserName, vector<stUser>& vUser) {
	for (stUser& U : vUser) {
		if (U.UserName == UserName) {
			U.MarkForDelete = true;
		}
	}
	return false;
}

bool DeleteUserDataByUserName() {
	string UserName = ReadUserName();
	if (UserName == "Admin") {
		cout << "\nYou Can Not Delete This User." << endl;
		GoBackToMangementMenue();
	}
	vector<stUser> vUser = LoadUsersDataFromFile(UsersFileName);
	stUser User;
	char Answer = 'n';

	if (FindUserByUserName(UserName, vUser, User)) {
		PrintUserCard(User);
		cout << "\n\nAre You Sure You Want Delete This User (Y/N)?";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			MarkUserForDeleteByUserName(UserName, vUser);
			SaveUsersDataToFile(UsersFileName, vUser);
			vUser = LoadUsersDataFromFile(UsersFileName);
			cout << "\n\n User Deleted Successfully\n";
			return true;
		}
		return false;
	}
	else {
		cout << "User With Number  (" << UserName << ") is Notfound !" << endl;
		return false;
	}
}

void ShowDeleteUserScreen() {
	cout << "========================================\n";
	cout << "\t Delete Users Screen\n";
	cout << "========================================\n";
	DeleteUserDataByUserName();
}
void ShowFindUserScreen() {
	vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	stUser User;
	cout << "========================================\n";
	cout << "\t Find Clients Screen\n";
	cout << "========================================\n";
	string a = ReadUserName();
	if (FindUserByUserName(a, vUsers, User)) {
		PrintUserCard(User);
	}
	else {
		cout << "Client With Number  (" << a << ") is Notfound !" << endl;
	}
}
void PerformMangementMenueOption(enMangementMenueOption MangementMenueOption) {
	switch (MangementMenueOption) {
	case enMangementMenueOption::ListUsers: 
	{
		system("cls");
		ShowAllUsersScreen();
		GoBackToMangementMenue();
		break;
	}
	case enMangementMenueOption::AddNewUser:
	{


		break;
	}

	case enMangementMenueOption::DeleteUser:
	{
		system("cls");
		ShowDeleteUserScreen();
		GoBackToMangementMenue();
		break;
	}

	case enMangementMenueOption::UpdateUser:
	{


		break;
	}
	
	case enMangementMenueOption::FindUser:
	{
		system("cls");
		ShowFindUserScreen();
		GoBackToMangementMenue();
		break;
	}
	case enMangementMenueOption::BacktoMainMenue:
	{
		ShowMainMenue();
		break;
	}
	}
}

void Login() {
	ShowLoginScreen();
	if (ReadUserInformation())
		ShowMainMenue();
}
void ShowMangementUsersMenue(){
	system("cls");
	cout << "===========================================================" << endl;
	cout << "\t\t Mangement Screen\n";
	cout << "===========================================================" << endl;
	cout << "\t[1] Show Users List.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User Info.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Back To Main Menue.\n";
	cout << "===========================================================" << endl;
	PerformMangementMenueOption((enMangementMenueOption)ReadMangementMenueOption());
}









