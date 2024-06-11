//*************************** My Solution ***************************
#include <iostream>
#include <string>
#include <fstream>  
#include <vector>
#include <iomanip>


using namespace std;
const string ClientsFileName = "Clients.txt";

struct sClient {
    string PinCode;
    string AccountNumber;
    string Phone;
    string Name;
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

enum enMainMenuOptions {enShowClientList = 1, enAddNewClient = 2, enDeleteClient = 3, enUpdateClient = 4, enFindClient = 5, enTransactions = 6, enExit = 7};

enum enTransactionsOptions { enDeposit = 1, enWithdraw = 2, enTotalBalances = 3, enMainMenu = 4 };

void TakeUserToMenu();
void PrintClientCard(sClient Client);
string ReadClientAccountNumber();
void TakeUserToTransactionMenu();
vector <string> Split(string S, string delimiter = " ") {

    vector <string> words;

    // delimiter (Alfasel)
    short position = 0;
    string sWord; // define a string variable

    // use find() function to get the position of the delimiters
    while ((position = S.find(delimiter)) != std::string::npos) {
        // npos means there is no spaces in the string;
        sWord = S.substr(0, position); // store the word
        if (sWord != "") {
            words.push_back(sWord);
        }
        S.erase(0, position + delimiter.length()); // erase() until positon and move to next word (remove all spaces after the word);
    }

    if (S != "") {
        words.push_back(S);
    }
    return words;
}

sClient ConvertRecordToStruct(string Record, string Seperator = "#//#") {
    sClient Client;
    vector <string> Data = Split(Record, Seperator);

    Client.AccountNumber = Data[0];
    Client.PinCode = Data[1];
    Client.Name = Data[2];
    Client.Phone = Data[3];
    // Cast string to double
    Client.AccountBalance = stod(Data[4]);

    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
    string sClientRecord = "";
    sClientRecord += Client.AccountNumber + Seperator;
    sClientRecord += Client.PinCode + Seperator;
    sClientRecord += Client.Name + Seperator;
    sClientRecord += Client.Phone + Seperator;
    sClientRecord += to_string(Client.AccountBalance);

    return sClientRecord;
}

void GoBackToMainMenu();

void VectorToFile(string FileName, vector <sClient> vClients) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open()) {
        for (sClient& Client : vClients) {
            if (Client.MarkForDelete == false) {
                MyFile << ConvertRecordToLine(Client) << endl;
            }
        }
        MyFile.close();
    }
}

vector <sClient> FileToVector(string FileName) {
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    vector <sClient> vClients;
    sClient Client;

    if (MyFile.is_open()) {
        string line;
        while (getline(MyFile, line)) {
            Client = ConvertRecordToStruct(line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void PrintClientRecord(sClient Client) {
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector <sClient> vClients) {
    system("cls");
    vClients = FileToVector(ClientsFileName);
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (sClient Client : vClients) {
        PrintClientRecord(Client);
        cout << endl;
    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}


void PrintClientBalancesInfo(sClient Client) {
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllBalancesData(vector <sClient> vClients) {
    system("cls");
    int BalancesSum = 0;
    vClients = FileToVector(ClientsFileName);
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (sClient Client : vClients) {
        PrintClientBalancesInfo(Client);
        BalancesSum += Client.AccountBalance;
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\n\t\t\t\t\tTotal Balances = " << BalancesSum << endl;
}

string LowerAWord(string S) {
    for (short i = 0; i < S.length(); i++) {
        S[i] = tolower(S[i]);
    }
    return S;
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients) {

    for (sClient C : vClients) {
        if (C.AccountNumber == AccountNumber) {
            return true;
        }
    }
    return false;
}

bool FindClientByAccountNumberAndCopyAccount(string AccountNumber, vector <sClient> vClients, sClient& Client) {

    for (sClient C : vClients) {
        if (C.AccountNumber == AccountNumber) {
            Client = C;
            return true;
        }
    }
    return false;
}

sClient ReadClientData(string AccountNumber) {
    sClient Client;
    Client.AccountNumber = AccountNumber;
    Client.MarkForDelete = false;

    cout << "\n\nPlease Enter PinCode: ";
    getline(cin >> ws, Client.PinCode);

    cout << "Please Enter Name: ";
    getline(cin, Client.Name);

    cout << "Please Enter Phone: ";
    getline(cin, Client.Phone);

    cout << "Please Enter AccountBalance: ";
    cin >> Client.AccountBalance;

    return Client;
}

sClient ReadNewClient(vector <sClient> vClients) {
    sClient Client;

    do {
        cout << "Please Enter Account Number: ";
        getline(cin >> ws, Client.AccountNumber);
        if (FindClientByAccountNumber(Client.AccountNumber, vClients))
            cout << "Client with [" << Client.AccountNumber << "] already exists, Enter Another Account Number? ";
    } while (FindClientByAccountNumber(Client.AccountNumber, vClients));
    

    cout << "Please Enter PinCode: ";
    getline(cin, Client.PinCode);

    cout << "Please Enter Name: ";
    getline(cin, Client.Name);

    cout << "Please Enter Phone: ";
    getline(cin, Client.Phone);

    cout << "Please Enter AccountBalance: ";
    cin >> Client.AccountBalance;

    return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClient) {
    for (sClient& Client : vClient) {
        if (Client.AccountNumber == AccountNumber) {
            Client.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

bool DeleteAccountByAccountNumber(string AccountNumber, vector <sClient>& vClients) {
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumberAndCopyAccount(AccountNumber, vClients, Client)) {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            VectorToFile(ClientsFileName, vClients);

            //To Refresh clients vector and upload the new data
            vClients = FileToVector(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
        else {
            cout << "\n\nWelcome :-)\n";
            return false;
        }
    }
    else {
        cout << "\nClient With Account Number (" << AccountNumber << ") is Not Found!";
        GoBackToMainMenu();
        return false;
    }
}

void DeleteClientFunction(vector <sClient>& vClients) {
    system("cls");
    cout << "\n\n--------------------------------------------\n";
    cout << "\t\tDelete Client Screen\n";
    cout << "--------------------------------------------\n\n";
    string AccountNumber = ReadClientAccountNumber();
    DeleteAccountByAccountNumber(AccountNumber, vClients);
}


bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients) {
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumberAndCopyAccount(AccountNumber, vClients, Client)) {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want to update this client? y/n?";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {
            //Here we used by reference to update the real client in the vector;
            for (sClient& C : vClients) {
                if (C.AccountNumber == AccountNumber) {
                    C = ReadClientData(AccountNumber);
                    //The break here is important to improve the performance, so we don't have to check all Client after we find out goal client;
                    break;
                }
            }
            VectorToFile(ClientsFileName, vClients);

            //Refresh Clients
            vClients = FileToVector(ClientsFileName);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }
        else {
            cout << "\n\nWelcome.";
        }
    }
    else {
        cout << "\n\nClient With Account Number (" << AccountNumber << ") Not Found!";
    }
}

void UpdateClientFunction(vector <sClient>& vClients) {
    system("cls");
    cout << "\n\n--------------------------------------------\n";
    cout << "\t\tUpdate Client Info Screen\n";
    cout << "--------------------------------------------\n\n"; 
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void FindClientFunction(vector <sClient>& vClients) {
    sClient Client;
    system("cls");
    cout << "\n\n--------------------------------------------\n";
    cout << "\t\tFind Client Screen\n";
    cout << "--------------------------------------------\n\n";
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumberAndCopyAccount(AccountNumber, vClients, Client)) {
        PrintClientCard(Client);
    }
    else {
        cout << "Client With Account Number [" << AccountNumber << "] Not Found!";
    }

}

void PrintClientCard(sClient Client) {
    cout << "\nThe following are the client detalis: \n";
    cout << "--------------------------------------------\n";
    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "Pin Code       : " << Client.PinCode << endl;
    cout << "Name           : " << Client.Name << endl;
    cout << "Phone          : " << Client.Phone << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
    cout << "--------------------------------------------\n";
}

string ReadClientAccountNumber() {
    string AccountNumber = "";
    cout << "\nPlease Enter Account Number: ";
    cin >> AccountNumber;
    return AccountNumber;
}

void AddNewClient(vector <sClient>& vClient) {
    sClient Client;
    Client = ReadNewClient(vClient);
    vClient.push_back(Client);
    VectorToFile(ClientsFileName, vClient);
}

void AddClients(vector <sClient>& vClient) {
    string Answer;

    do {
        cout << "Adding New Client: \n\n";
        AddNewClient(vClient);
        cout << "\nClient Added Successfully, do you want to add more clients? yes/no\n";
        cin >> Answer;
    } while (LowerAWord(Answer) == "yes");
}

void AddNewClientFunction(vector <sClient>& vClient) {
    system("cls");
    cout << "\n\n--------------------------------------------\n";
    cout << "\t\tAdd New Clients Screen\n";
    cout << "--------------------------------------------\n";
    AddClients(vClient);
}

void ShowTransactionScreen() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menu.\n";
    cout << "===========================================\n";

}


int TakeUserChoice(string Message) {
    int Input;
    cout << Message;
    cin >> Input;
    return Input;
}

void ShowMainMenu() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client.\n";
    cout << "\t[5] Find Client\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "===========================================\n";

}

void GoBackToMainMenu() {
    cout << "\n\nPress Any Key To Go Back To Main Menu...";
    system("pause>0");
    TakeUserToMenu();
}


void GoBackToTransactionsMenu() {
    cout << "\n\nPress Any Key To Go Back To Transactions Menu...";
    system("pause>0");
    TakeUserToTransactionMenu();
}

void PrintEndScreen() {
    system("cls");
    cout << "\n\n--------------------------------------------\n";
    cout << "\t\tProgram Ends :-)\n";
    cout << "--------------------------------------------\n\n";
}

void TakeUserToMenu() {
    vector <sClient> vClient = FileToVector(ClientsFileName);
    ShowMainMenu();
    int UserChoice = TakeUserChoice("Choose what do you want to do: [1 to 7] : ");

    switch (UserChoice)
    {
    case enMainMenuOptions::enShowClientList:
        PrintAllClientsData(vClient);
        GoBackToMainMenu();
        break;

    case enMainMenuOptions::enAddNewClient:
        AddNewClientFunction(vClient);
        GoBackToMainMenu();
        break;

    case enMainMenuOptions::enDeleteClient:
        DeleteClientFunction(vClient);
        GoBackToMainMenu();
        break;

    case enMainMenuOptions::enUpdateClient:
        UpdateClientFunction(vClient);
        GoBackToMainMenu();
        break;

    case enMainMenuOptions::enFindClient:
        FindClientFunction(vClient);
        GoBackToMainMenu();
        break;

    case enMainMenuOptions::enTransactions:
        TakeUserToTransactionMenu();
        break;

    case enMainMenuOptions::enExit:
        PrintEndScreen();
        break;
    }
}


void Deposit(vector <sClient>& vClient) {
    string AccountNumber;
    sClient Client;
    int DepositAmount = 0;
    char Answer = 'n';
    do {
         AccountNumber = ReadClientAccountNumber();
         if (!FindClientByAccountNumberAndCopyAccount(AccountNumber, vClient, Client)) {
             cout << "Client with [" << AccountNumber << "] does not exist.";
         }
    } while (!FindClientByAccountNumber(AccountNumber, vClient));

    PrintClientCard(Client);
    cout << "Please Enter Deposit Amount: ";
    cin >> DepositAmount;
    cout << "\n\nAre you sure you want to perform this transaction? y/n?";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        for (sClient& C : vClient) {
            if (C.AccountNumber == AccountNumber) {
                C.AccountBalance += DepositAmount;
                Client = C;
            }
        }
        cout << "Done Successfully!, New balance is: " << Client.AccountBalance;
        VectorToFile(ClientsFileName, vClient);
    }
    else {
        cout << "Welcome!!!";
    }
    
}


void ShowDepositFunctionScreen(vector <sClient>& vClient) {
    system("cls");
    cout << "\n\n--------------------------------------------\n";
    cout << "\t\tDeposit Screen\n";
    cout << "--------------------------------------------\n\n";
    Deposit(vClient);
}

void Withdraw(vector <sClient>& vClient) {
    string AccountNumber;
    sClient Client;
    int WithdrawAmount = 0;
    char Answer = 'n';
    do {
        AccountNumber = ReadClientAccountNumber();
        if (!FindClientByAccountNumberAndCopyAccount(AccountNumber, vClient, Client)) {
            cout << "Client with [" << AccountNumber << "] does not exist.";
        }
    } while (!FindClientByAccountNumber(AccountNumber, vClient));

    PrintClientCard(Client);
    do {
    cout << "Please Enter Withdraw Amount: ";
    cin >> WithdrawAmount;
    if (WithdrawAmount > Client.AccountBalance) {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
    }
    } while (WithdrawAmount > Client.AccountBalance);
    
    cout << "\n\nAre you sure you want to perform this transaction? y/n?";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        for (sClient& C : vClient) {
            if (C.AccountNumber == AccountNumber) {
                C.AccountBalance -= WithdrawAmount;
                Client = C;
            }
        }
        cout << "Done Successfully!, New balance is: " << Client.AccountBalance;
        VectorToFile(ClientsFileName, vClient);
    }
    else {
        cout << "Welcome!!!";
    }
}

void ShowWithdrawFunctionScreen(vector <sClient>& vClient) {
    system("cls");
    cout << "\n\n--------------------------------------------\n";
    cout << "\t\tWithdraw Screen\n";
    cout << "--------------------------------------------\n\n";
    Withdraw(vClient);
}

void TakeUserToTransactionMenu() {
    vector <sClient> vClients = FileToVector(ClientsFileName);
    ShowTransactionScreen();
    int UserChoice = TakeUserChoice("Choose what do you want to do? [1 to 4]?");

    switch (UserChoice) {
    case enTransactionsOptions::enDeposit:
        ShowDepositFunctionScreen(vClients);
        GoBackToTransactionsMenu();
        break;
    case enTransactionsOptions::enWithdraw:
        ShowWithdrawFunctionScreen(vClients);
        GoBackToTransactionsMenu();
        break;

    case enTransactionsOptions::enTotalBalances:
        PrintAllBalancesData(vClients);
        GoBackToTransactionsMenu();
        break;

    case enTransactionsOptions::enMainMenu:
        GoBackToMainMenu();
        break;
    }
}

int main() {
    TakeUserToMenu();
    system("pause>0");
    return 0;
}
