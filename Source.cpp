#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Clients.txt";
void ShowMainMenue();
void ShowTransactionsMenue();
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

enum enMainMenueOption { ShowClientList = 1, AddClient = 2, DeleteClient = 3, UpdateClientInfo = 4, FindClient = 5, Transactions=6 , Exit = 7 };
enum enTransactionsScreen{ Deposit =1 , Withdraw =2 , TotalBalances = 3 , BackToMainMenue = 4};
double ReadPositiveNumber(string Message)
{
    double Number;

    while (true)
    {
        cout << Message;
        cin >> Number;

        if (cin.fail() || Number <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Number, Try Again!\n";
        }
        else
        {
            return Number;
        }
    }
}

string ReadClientAccountNumber()
{
    string AccountNumber;
    cout << "\nPlease enter Account Number: ";
    cin >> AccountNumber;
    return AccountNumber;
}

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

bool FindClientByAccountNumber(string AccountNumber,
    vector<sClient>& vClients,
    sClient& Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

sClient ConvertLineToRecord(string Line, string Separator = "#//#")
{
    sClient Client;
    vector<string> vClientData = SplitString(Line, Separator);

    if (vClientData.size() < 5)
        return Client;

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;
}

string ConvertRecordToLine(sClient Client, string Separator = "#//#")
{
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Separator;
    stClientRecord += Client.PinCode + Separator;
    stClientRecord += Client.Name + Separator;
    stClientRecord += Client.Phone + Separator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

vector<sClient> LoadClientsDataFromFile(string FileName)
{
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;
}

void SaveClientsDataToFile(string FileName, vector<sClient>& vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                MyFile << ConvertRecordToLine(C) << endl;
            }
        }

        MyFile.close();
    }
}

sClient FillNewClientData(sClient& client) {
    vector<sClient>vClients = LoadClientsDataFromFile(ClientsFileName);
    sClient c;
    cout << "Adding New Client :\n\n";
    cout << "Enter Account Number?\n";
    getline(cin >> ws, client.AccountNumber);
    while (FindClientByAccountNumber(client.AccountNumber, vClients, c)) {
        cout << "Client With [" << client.AccountNumber << "] already exists , Enter Another Account Number ?";
        getline(cin >> ws, client.AccountNumber);
    }
    cout << "Enter PinCode?\n";
    getline(cin, client.PinCode);

    cout << "Enter The Name?\n";
    getline(cin, client.Name);

    cout << "Enter The Phone Number?\n";
    getline(cin, client.Phone);

    cout << "Enter Account Balance?\n";
    cin >> client.AccountBalance;

    return client;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "Pin Code       : " << Client.PinCode << endl;
    cout << "Name           : " << Client.Name << endl;
    cout << "Phone          : " << Client.Phone << endl;
    cout << "Balance        : " << Client.AccountBalance << endl;
}

void ShowExitMessage() {
    cout << "   GGGGG   OOOOO   OOOOO   DDDDD   BBBBB   Y   Y   EEEEE\n";
    cout << "  G       O     O O     O  D    D  B    B   Y Y    E\n";
    cout << "  G  GGG  O     O O     O  D     D BBBBB     Y     EEEE\n";
    cout << "  G     G O     O O     O  D    D  B    B    Y     E\n";
    cout << "   GGGGG   OOOOO   OOOOO   DDDDD   BBBBB     Y     EEEEE\n\n";
    cout << "===========================================================\n";
    cout << "        THANK YOU FOR USING THE PROGRAM\n";
    cout << "                SEE YOU SOON!\n";
    cout << "===========================================================\n";
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;

    cout << "\nEnter PinCode: ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name: ";
    getline(cin, Client.Name);

    cout << "Enter Phone: ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance: ";
    cin >> Client.AccountBalance;

    return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClient) {
    for (sClient& C : vClient) {
        if (C.AccountNumber == AccountNumber) {
            C.MarkForDelete = true;
        }
    }
    return false;
}

void GoBackToMainMenue() {
    cout << "\nPress Eny Key to Back to Main Menue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    ShowMainMenue();
}
void GoBackToTransactionsMenue() {
    cout << "\nPress Eny Key to Back to Transactions Menue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    ShowTransactionsMenue();
}
bool DeleteClientDataByAccNumber() {
    string AccountNumber = ReadClientAccountNumber();
    vector<sClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    sClient client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClient, client)) {
        PrintClientCard(client);
        cout << "\n\nAre You Sure You Want Delete This Client (Y/N)?";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClient);
            SaveClientsDataToFile(ClientsFileName, vClient);
            vClient = LoadClientsDataFromFile(ClientsFileName);
            cout << "\n\n Client Deleted Successfully\n";
            return true;
        }
        return false;
    }
    else {
        cout << "Client With Number  (" << AccountNumber << ") is Notfound !" << endl;
        return false;
    }
}

void ShowDeleteClientScreen() {
    cout << "========================================\n";
    cout << "\t Delete Clients Screen\n";
    cout << "========================================\n";
    DeleteClientDataByAccNumber();
}

bool UpdateClientByAccountNumber()
{
    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    sClient Client;
    char Answer = 'n';
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\nAre you sure you want to update this client? y/n : ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveClientsDataToFile(ClientsFileName, vClients);
            cout << "\nClient Updated Successfully.\n";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!\n";
    }

    return false;
}

void ShowUpdateClientDataScreen() {
    cout << "========================================\n";
    cout << "\t Update Clients Screen\n";
    cout << "========================================\n";
    UpdateClientByAccountNumber();
}

void PrintClientRecord(sClient& client) {
    cout << "|" << setw(15) << left << client.AccountNumber;
    cout << "|" << setw(10) << left << client.PinCode;
    cout << "|" << setw(35) << left << client.Name;
    cout << "|" << setw(15) << left << client.Phone;
    cout << "|" << setw(10) << left << client.AccountBalance;
}

void PrintClientBalance(sClient& client) {
    cout << "|" << setw(15) << left << client.AccountNumber;
    cout << "|" << setw(35) << left << client.Name;
    cout << "|" << setw(10) << left << client.AccountBalance;
}

void ShowAllClientsScreen() {
    vector<sClient>vClients = LoadClientsDataFromFile(ClientsFileName);
    system("cls");
    cout << "                      Clients List " << vClients.size() << " Client (s)  " << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "|" << setw(15) << left << "Account Number " << "|" << setw(10) << left << "Pin Code  " << "|"
        << setw(35) << left << "Client Name" << "|" << setw(15) << left << "Phone " << "|" << setw(10) << left << "Balance  " << endl
        << "-----------------------------------------------------------------------------------------------" << endl;
    for (sClient& client : vClients) {
        PrintClientRecord(client);
        cout << endl;
    }
    cout << "-----------------------------------------------------------------------------------------------" << endl;
}

void ShowAllClientsBalances() {
    vector<sClient>vClients = LoadClientsDataFromFile(ClientsFileName);
    int TotalBalances = 0;
    system("cls");
    cout << "                      Balancess List " << vClients.size() << " Client (s)  " << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "|" << setw(15) << left << "Account Number " << "|"
        << setw(35) << left << "Client Name" << "|"  << setw(10) << left << "Balance  " << endl
        << "-----------------------------------------------------------------------------------------------" << endl;
    for (sClient& client : vClients) {
        PrintClientBalance(client);
        TotalBalances += client.AccountBalance;
        cout << endl;
    }
    cout << "-----------------------------------------------------------------------------------------------\n" << endl;
    cout << "\t\t\tTotal Balances = " << TotalBalances << endl;
}

void SaveNewClientToFile(sClient& client, string FileName = "Clients.txt") {
    fstream File;
    File.open(FileName, ios::out | ios::app);
    if (File.is_open()) {
        File << ConvertRecordToLine(client, "#//#") << endl;
        File.close();
    }
}

void AddNewClient(vector<sClient>& vClients)
{
    sClient Client;
    FillNewClientData(Client);
    vClients.push_back(Client);
    SaveNewClientToFile(Client);
}
void AddDeposit(double Deposit, string AccountNumber)
{
    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    char Answer = 'n';
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n\nAre You Sure You Want Perform This Transaction ? (Y/N)? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y') {

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Deposit;
                cout << "\nDone Successfully, New Balance Is: "
                    << C.AccountBalance << endl;
                break;
            }
        }
    }
    else {
        GoBackToTransactionsMenue();
    }

    SaveClientsDataToFile(ClientsFileName, vClients);
}
void AddWithdraw(double Withdraw, string AccountNumber)
{
    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    char Answer = 'n';

    cout << "\n\nAre You Sure You Want Perform This Transaction ? (Y/N)? ";
    cin >> Answer;

    if (Answer != 'y' && Answer != 'Y')
        return;

    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            if (Withdraw > C.AccountBalance)
            {
                cout << "\nAmount Exceeds Balance!\n";
                return;
            }

            C.AccountBalance -= Withdraw;
            cout << "\nDone Successfully, New Balance Is: "
                << C.AccountBalance << endl;
            break;
        }
    }

    SaveClientsDataToFile(ClientsFileName, vClients);
}

void AddNewClients()
{
    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    char AddMore = 'Y';
    do
    {
        system("cls");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        AddNewClient(vClients);
        cout << "\nClient Added Succfully Do You Want To Add More Clients? (Y/N): ";
        cin >> AddMore;
    } while (AddMore == 'Y' || AddMore == 'y');
}
void ShowAddNewClientsScreen() {
    cout << "========================================\n";
    cout << "\t Add New Clients Screen\n";
    cout << "========================================\n";
    AddNewClients();
}

void ShowDepositScreen()
{
    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    sClient Client;

    cout << "========================================\n";
    cout << "\t Deposit Screen\n";
    cout << "========================================\n";

    string AccountNumber;

    while (true)
    {
        AccountNumber = ReadClientAccountNumber();

        if (FindClientByAccountNumber(AccountNumber, vClients, Client))
            break;

        cout << "Client With Number (" << AccountNumber << ") is Not Found!\n\n";
    }
    system("cls");
    PrintClientCard(Client);

    double Deposit = ReadPositiveNumber("Please Enter Deposit Amount : ");
    AddDeposit(Deposit, Client.AccountNumber);
}

void ShowWithdrawScreen() {
    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    sClient Client;

    cout << "========================================\n";
    cout << "\t Withdraw Screen\n";
    cout << "========================================\n";

    string AccountNumber;

    while (true)
    {
        AccountNumber = ReadClientAccountNumber();

        if (FindClientByAccountNumber(AccountNumber, vClients, Client))
            break;

        cout << "Client With Number (" << AccountNumber << ") is Not Found!\n\n";
    }
    system("cls");
    PrintClientCard(Client);

    int Withdraw = ReadPositiveNumber("Please Enter Withdraw Amount : ");
    AddWithdraw(Withdraw, Client.AccountNumber);
}
void ShowFindClientScreen() {
    vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    sClient Client;
    cout << "========================================\n";
    cout << "\t Find Clients Screen\n";
    cout << "========================================\n";
    string a = ReadClientAccountNumber();
    if (FindClientByAccountNumber(a, vClients, Client)) {
        PrintClientCard(Client);
    }
    else {
        cout << "Client With Number  (" << a << ") is Notfound !" << endl;
    }
}

short ReadTransactionsMenueOption() {
    short Choose;
    cout << " Choose What Do You Want To Do ? [1 to 4]?";
    cin >> Choose;
    return Choose;
}

short ReadMainMenueOption() {
    short Choose;
    cout << " Choose What Do You Want To Do ? [1 to 7]?";
    cin >> Choose;
    return Choose;
}
void PerformTransactionsMenueOption(enTransactionsScreen TransactionsOption) {
    switch (TransactionsOption) {
    case enTransactionsScreen::Deposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsScreen::Withdraw:
    {
        system("cls");
        ShowWithdrawScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsScreen::TotalBalances:
    {
        system("cls");
        ShowAllClientsBalances();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsScreen::BackToMainMenue:
    {
        ShowMainMenue();
        break;
    }
    default:
    {
        system("cls");
        cout << "Invalid Choice Try Again\n\n";
        GoBackToTransactionsMenue();
        break;
    }

    }
}
void PerformMainMenueOption(enMainMenueOption MainMenueOption) {
    switch (MainMenueOption) {
    case enMainMenueOption::ShowClientList:
    {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOption::AddClient:
    {
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOption::DeleteClient:
    {
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOption::UpdateClientInfo:
    {
        system("cls");
        ShowUpdateClientDataScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOption::FindClient:
    {
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOption::Transactions:
    {
        system("cls");
        ShowTransactionsMenue();
        break;
    }

    case enMainMenueOption::Exit:
    {
        system("cls");
        ShowExitMessage();
        break;
    }
    default:
    {
        system("cls");
        cout << "Invalid Choice Try Again\n\n";
        GoBackToMainMenue();
        break;
    }
    }
}
void ShowTransactionsMenue() {
    system("cls");
    cout << "========================================\n";
    cout << "\t\t Transactions Menue Screen\n";
    cout << "========================================\n";
    cout << "\t [1] Deposit.\n";
    cout << "\t [2] Widthraw.\n";
    cout << "\t [3] Total Balances.\n";
    cout << "\t [4] Back To Main Menue.\n";
    cout << "========================================\n";
    PerformTransactionsMenueOption((enTransactionsScreen)ReadTransactionsMenueOption());
}
void ShowMainMenue() {
    system("cls");
    cout << "===========================================================" << endl;
    cout << "\t\t Main Menue Screen\n";
    cout << "===========================================================" << endl;
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "===========================================================" << endl;
    PerformMainMenueOption((enMainMenueOption)ReadMainMenueOption());
}

int main()
{
    ShowMainMenue();
    system("pause>0");
    return 0;

}
