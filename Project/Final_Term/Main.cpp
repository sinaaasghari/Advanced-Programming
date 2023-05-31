#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<Windows.h>
#include<unistd.h>
#include<cstdlib>
#include <conio.h>

using namespace std;

string start_menu = "1.Login\n2.Sign up\n3.Exit\nEnter your command : ";

string main_menu = "1.Verification and Setting\n2.Withraw and Deposit\n3.Log out\nEnter your command : ";

string main_menu_verified = "1.Edit and show information\n2.Withraw and Deposit\n3.Enter market\n4.Log out\nEnter your command : ";

string setting = "1.verification\n2.Edit information\n3.Back\nEnter your command : ";

string market_menu = "1.Buy stock\n2.Sell stock\n3.My portfolio\n4.All Stocks\n5.Back\nEnter your command : ";

string edit_menu = "1.Name\n2.ID\n3.Account Number\n4.IBAN\n5.Debt\n6.Account Balance\n7.Back\nEnter your command : ";



//Stock class
class stock{
    private:
        string symbol;
        string shortname;
        double price;
        double marketcap;
    public:
        stock(string _symbol, string _shortname, double _price, double _marketcap){
            symbol = _symbol;
            shortname = _shortname;
            price = _price;
            marketcap = _marketcap;
        }
        string getSymbol(){
            return symbol;
        }
        string getName(){
            return shortname;
        }
        double getPrice(){
            return price;
        }
        double getMarketCap(){
            return marketcap;
        }
};



class account{
    private:
        string user_name;
        string password;
        string name;
        string ID;    //code melli
        string account_number;
        string IBAN;    //shomare shaba
        double debt;    //bedehi
        double account_balance;    //mojoudi
        double asset;    //majmo darayi dar sabad saham
        vector<pair<string, int>> stocks;    //Stores user's stocks
        string is_verified;
    public:
        account(string _user_name, string _password, string verification){
            user_name = _user_name;
            password = _password;
            is_verified = verification;
        }
        //This function sets user's all information
        void set(){
            string _debt, _account_balance, _asset;
            ifstream user("./accounts/"+user_name+".txt");
            getline(user, name);
            getline(user, ID);
            getline(user, account_number);
            getline(user, IBAN);
            getline(user, _debt);
            getline(user, _account_balance);
            getline(user, _asset);
            debt = stod(_debt);
            account_balance = stod(_account_balance);
            asset = stod(_asset);
            string line, stock_symbol;
            int count;
            while(!user.eof()){
                getline(user, line);
                for(int i = 0; i < line.length(); i++){
                    if(line[i] == ','){
                        stock_symbol = line.substr(0, i);
                        count = stoi(line.substr(i+1, line.length() - i -1));
                        stocks.push_back(make_pair(stock_symbol, count));
                    }
                }
            }
            user.close();
        }
        //This function gets users's information and evaluates information
        void verify(string _name, string _ID, string _account_number, 
                    string _IBAN, double _debt, double _account_balance,double _asset){
            if(_name.length()<=40 && _ID.length()==10 && _account_number.length()==10 && 
              (_IBAN.length()==12 && _IBAN.substr(0,2)=="IR") && _debt<=1000000){
                name = _name;
                ID = _ID;
                account_number = _account_number;
                IBAN = _IBAN;
                debt = _debt;
                account_balance = _account_balance;
                asset = _asset;
                ofstream user("./accounts/" + user_name + ".txt");
                user << name << "\n" << ID << "\n" << account_number << "\n" << IBAN << "\n";
                user << debt << "\n" << account_balance << "\n" << asset << "\n";
                user.close();
                is_verified = "1";
                fstream users("users.txt");
                string _user_name, _password, _verification;
                int pos = 0;
                while(!users.eof()){
                    getline(users, _user_name);
                    getline(users, _password);
                    if(_user_name == user_name){
                        pos += _user_name.length()+_password.length()+4;
                        break;
                    }
                    getline(users, _verification);
                    pos += _user_name.length()+_password.length()+_verification.length()+6;
                }
                users.seekg(pos);
                users << "1";
                users.close();
            }
            else{
                cout << "Your information is not verified!\n"; 
                sleep(3);
                is_verified = "0";
            }
        }
        //This function Edits users infomations
        void edit(){
            int command;
            while(true){
                system("cls");
                cout << "Name : " << name << endl;
                cout << "ID : " << ID << endl;
                cout << "Account Number : " << account_number << endl;
                cout << "IBAN : " << IBAN << endl;
                cout << "Debt : " << debt << endl;
                cout << "Account Balance : " << account_balance << endl;
                cout << "Asset : " << asset << endl;
                cout << edit_menu;
                cin >> command;
                system("cls");
                if(command==1){
                    string new_name;
                    cout << "Enter new Name : ";
                    cin >> new_name;
                    if(new_name.length()<=40){
                        name = new_name;
                    }
                    else{
                        cout << "name is too large\n";
                        sleep(2);
                    }
                }
                else if(command==2){
                    string new_ID;
                    cout << "Enter new ID : ";
                    cin >> new_ID;
                    if(new_ID.length()==10){
                        ID = new_ID;
                    }
                    else{
                        cout << "ID is not correct\n";
                        sleep(2);
                    }
                }
                else if(command==3){
                    string new_account_number;
                    cout << "Enter new account number : ";
                    cin >> new_account_number;
                    if(new_account_number.length()==10){
                        account_number = new_account_number;
                    }
                    else{
                        cout << "account_number is not correct\n";
                        sleep(2);
                    }
                }
                else if(command==4){
                    string new_IBAN;
                    cout << "Enter new IBAN : ";
                    cin >> new_IBAN;
                    if(new_IBAN.length()==12 && new_IBAN.substr(0,2)=="IR"){
                        IBAN = new_IBAN;
                    }
                    else{
                        cout << "IBAN is not correct\n";
                        sleep(2);
                    }
                }
                else if(command==5){
                    double new_debt;
                    cout << "Enter new debt : ";
                    cin >> new_debt;
                    if(new_debt<=1000000){
                        debt = new_debt;
                    }
                    else{
                        cout << "debt is too much\n";
                        sleep(2);
                    }
                }
                else if(command==6){
                    double new_balance;
                    cout << "Enter Account Balance : ";
                    cin >> new_balance;
                    account_balance = new_balance;
                }
                else if(command == 7){
                    return;
                }
            }
        }
        //Set and Get functions
        string verified(){
            return is_verified;
        }
        vector<pair<string, int>>& getPortfolio(){
            return stocks;
        }
        double& getAccountBalance(){
            return account_balance;
        }
        double& getDebt(){
            return debt;
        }
        double& getAsset(){
            return asset;
        }
        string getUserName(){
            return user_name;
        }
        string getName(){
            return name;
        }
        string getID(){
            return ID;
        }
        string getAccountNumber(){
            return account_number;
        }
        string getIBAN(){
            return IBAN;
        }
};
void market(account &Account, vector<stock> &stocks);
//This function is main flow of program
void  main_stream(account &Account){
    //Here we load all stocks data and save it in a vector
    ifstream read_stocks("data.csv");
    vector<stock> stocks;
    string line, symbol, shortname, _price, _marketcap;
    while(!read_stocks.eof()){
        getline(read_stocks, line);
        int last = -1, n = 0;
        for(int i = 0; i < line.length(); i++){
            if(line[i] == ',' || i == line.length() - 1){
                if(n == 0){
                    symbol = line.substr(last + 1, i - last - 1);
                    n++;
                }
                else if(n == 1){
                    shortname = line.substr(last + 1, i - last - 1);
                    n++;
                }
                else if(n == 2){
                    _price = line.substr(last + 1, i - last - 1);
                    n++;
                }
                else if(n == 3){
                    _marketcap = line.substr(last + 1, i - last);
                }
                last = i;
            }
        }
        stock new_stock(symbol, shortname, stod(_price), stod(_marketcap));
        stocks.push_back(new_stock);
    }
    read_stocks.close();
    while(true){
        //For verified accounts
        if(Account.verified()=="1"){
            Account.set();
            int command;
            while(true){
                system("cls");
                cout << main_menu_verified;
                cin >> command;
                system("cls");
                //Edit information
                if(command == 1){
                    Account.edit();
                }
                //Withraw and Deposit
                else if(command == 2){
                    int cmd;
                    cout <<"1.Withraw\n2.Deposit\n3.Back\nEnter your command : ";
                    cin >> cmd;
                    system("cls");
                    if(cmd==1){
                        double amount;
                        cout << "How much : ";
                        cin >> amount;
                        if(amount > Account.getAccountBalance() && Account.getDebt() + (amount - Account.getAccountBalance())<1000000){
                            Account.getDebt() += amount - Account.getAccountBalance();
                            Account.getAccountBalance() = 0;
                        }
                        else{
                            Account.getAccountBalance() -= amount;
                        }
                    }
                    else if(cmd == 2){
                        double amount;
                        cout << "How much : ";
                        cin >> amount;
                        if(amount < Account.getDebt()){
                            Account.getDebt() -= amount;
                        }
                        else{
                            Account.getAccountBalance() += (amount - Account.getDebt());
                            Account.getDebt() = 0;
                        }
                    }
                }
                //Opens market
                else if(command == 3){
                    market(Account, stocks);
                }
                //Log out and save data
                else if(command == 4){
                    ofstream user("./accounts/" + Account.getUserName() + ".txt", ios::out);
                    user << Account.getName() << "\n" << Account.getID() << "\n" << Account.getAccountNumber() << "\n" << Account.getIBAN() <<"\n";
                    user << Account.getDebt() << "\n" << Account.getAccountBalance() << "\n" << Account.getAsset() << '\n';
                    for(auto x : Account.getPortfolio()){
                        user << x.first << ',' << x.second << '\n'; 
                    }
                    user.close();
                    return;
                }
            }
        }
        //For not verified accounts
        else{
            int command;
            while(true){
                system("cls");
                cout << main_menu;
                cin >> command;
                system("cls");
                if((command<1) || (command>4)){
                    cout << "command is wrong!\n";
                    sleep(2);
                    continue;
                }
                //Get and verifiy information
                else if(command==1){
                    string name;
                    string ID;    //code melli
                    string account_number;
                    string IBAN;    //shomare shaba
                    double debt;    //bedehi
                    double account_balance;    //mojoudi
                    double asset;    //majmo darayi dar sabad saham
                    cout << "Enter your name : ";
                    getline(cin >> ws, name);
                    cout << "Enter your ID : ";
                    getline(cin, ID);
                    cout << "Enter your Account number : ";
                    getline(cin, account_number);
                    cout << "Enter your IBAN : ";
                    getline(cin, IBAN);
                    cout << "Enter your debt : ";
                    cin >> debt;
                    cout << "Enter your Account balance : ";
                    cin >> account_balance;
                    cout << "Enter your Asset : ";
                    cin >> asset;
                    Account.verify(name, ID, account_number, IBAN, debt, account_balance, asset);
                    break;
                }
                //Withraw and Deposit
                else if(command==2){
                    int cmd;
                    cout <<"1.Withraw\n2.Deposit\n3.Back\nEnter your command : ";
                    cin >> cmd;
                    if(cmd==1){
                        double amount;
                        cout << "How much : ";
                        cin >> amount;
                        if(amount > Account.getAccountBalance() && Account.getDebt() + (amount - Account.getAccountBalance())<1000000){
                            Account.getDebt() += amount - Account.getAccountBalance();
                            Account.getAccountBalance() = 0;
                        }
                        else{
                            Account.getAccountBalance() -= amount;
                        }
                    }
                    else if(cmd == 2){
                        double amount;
                        cout << "How much : ";
                        cin >> amount;
                        if(amount < Account.getDebt()){
                            Account.getDebt() -= amount;
                        }
                        else{
                            Account.getAccountBalance() += (amount - Account.getDebt());
                            Account.getDebt() = 0;
                        }
                    }
                }
                //Log out and save data
                else if(command == 3){
                    ofstream user("./accounts/" + Account.getUserName() + ".txt", ios::out);
                    user << Account.getName() << "\n" << Account.getID() << "\n" << Account.getAccountNumber() << "\n" << Account.getIBAN() <<"\n";
                    user << Account.getDebt() << "\n" << Account.getAccountBalance() << "\n" << Account.getAsset() << '\n';
                    for(auto x : Account.getPortfolio()){
                        user << x.first << ',' << x.second << '\n'; 
                    }
                    user.close();
                    return;
                }
            }
        }
    }
}
//Market Function
void market(account &Account, vector<stock> &stocks){
    system("cls");
    int command;
    while(true){
        system("cls");
        cout << market_menu;
        cin >> command;
        system("cls");
        //Buy an specific stock
        if(command==1){
            string symbol;
            int count, flag = 0;
            cout << "Enter stock symbol : ";
            cin >> symbol;
            cout << "how many of " << symbol << " do you want : ";
            cin >> count;
            for(auto x : stocks){
                if(x.getSymbol() == symbol){
                    flag = 1;
                    if(Account.getAccountBalance() >= count * x.getPrice()){
                        int flag1 = 0;
                        for(auto y : Account.getPortfolio()){
                            if(y.first == symbol){
                                flag1 = 1;
                                y.second += count;
                            }
                        }
                        if(flag1 == 0){
                            Account.getPortfolio().push_back(make_pair(symbol, count));
                        }
                        Account.getAccountBalance() -= count*x.getPrice();
                        Account.getAsset() += count * x.getPrice();
                    }
                    else if(Account.getAccountBalance() < count * x.getPrice() &&
                     Account.getAccountBalance() + (1000000 - Account.getDebt()) >= count*x.getPrice()){
                         int flag1 = 0;
                        for(auto y : Account.getPortfolio()){
                            if(y.first == symbol){
                                flag1 = 1;
                                y.second += count;
                            }
                        }
                        if(flag1 == 0){
                            Account.getPortfolio().push_back(make_pair(symbol, count));
                        }
                        Account.getDebt() += count * x.getPrice() - Account.getAccountBalance();
                        Account.getAccountBalance() = 0;
                        Account.getAsset() += count * x.getPrice();
                    }
                    else{
                        cout << "You don't have enough money!\n";
                        sleep(3);
                    }
                }
            }
            if(flag==0){
                cout << "Inavlid stock\n";
                sleep(3);
            }
        }
        //Sell an specific stock
        else if(command==2){
            string symbol;
            int count, flag = 0;
            double income, price;
            cout << "Enter stock symbol : ";
            cin >> symbol;
            cout << "How many of them do you want to sell : ";
            cin >> count;
            for(auto iter = Account.getPortfolio().begin(); iter < Account.getPortfolio().end(); iter++){
                if(iter->first == symbol){
                    flag = 1;
                    for(auto y : stocks){
                        if(y.getSymbol() == symbol){
                            price = y.getPrice();
                        }
                    }
                    if(count <= iter->second){
                        income = count * price;
                        Account.getAccountBalance() += income;
                        Account.getAsset() -= income;
                        iter->second -= count;
                        if(iter->second == 0){
                            Account.getPortfolio().erase(iter);
                        }
                        break;
                    }
                    else{
                        cout << "You don't have enough stock!\n";
                        sleep(3);
                    }

                }
            }
            if(flag == 0){
                cout << "You don't have this stock or Invalid stock!\n";
                sleep(3);
            }
        }
        //Shows user's all stocks
        else if(command==3){
            cout << "Your portfolio : \n";
            for(auto x : Account.getPortfolio()){
                for(auto S : stocks){
                    if(S.getSymbol() == x.first){
                        cout << S.getSymbol() << " " << S.getName() << " " << S.getPrice() << " " << S.getMarketCap() << endl;
                        cout << "Count : " << x.second << endl;
                    }
                }
            }
            system("pause");
        }
        //Print all stocks in market
        else if(command==4){
            for(auto x : stocks){
                cout << x.getSymbol() << " " << x.getName() << " " << x.getPrice() << " " << x.getMarketCap() << "\n";
            }
            system("pause");

        }
        //Back to main menu
        else if(command==5){
            return;
        }
    }
}




//Start function of program
void start(){
    system("cls");
    int command;
    while(true){
        system("cls");
        cout << start_menu;
        cin >> command;
        system("cls");
        if(command>3 || command<1){
            cout << "command is not correct\n";
            sleep(2);
        }
        //Login
        else if(command==1){
            string user_name, password;
            int flag = 0;
            cout << "Enter Username : ";
            getline(cin >> ws, user_name);
            cout << "Enter Password : ";
            getline(cin, password);
            ifstream users("users.txt");
            while(!users.eof()){
                string _user_name, _password;
                string verification;
                getline(users, _user_name);
                getline(users, _password);
                getline(users, verification);
                if(user_name==_user_name && password==_password){
                    account Account(user_name, password, verification);
                    main_stream(Account);
                    flag = 1;
                    break;
                }
            }
            users.close();
            if(flag==0){
                cout << "incorrect username or password\n";
                sleep(2);
            }
        }
        //Sign up
        else if(command==2){
            string user_name, password;
            int flag = 1;
            cout << "Enter your Username : ";
            getline(cin >> ws, user_name);
            cout << "Enter your Password : ";
            getline(cin, password);
            fstream users("users.txt");
            while(!users.eof()){
                string _user_name, _password;
                string verification;
                getline(users, _user_name);
                getline(users, _password);
                getline(users, verification);
                if(user_name==_user_name){
                    flag = 0;
                    break;
                }
            }
            if(flag==1){
                users.close();
                fstream users("users.txt", ios::app);
                users << user_name << "\n" << password << "\n" << 0 << "\n";
            }
            else{
                cout << "Username already exists!\n";
                sleep(2);
            }
            users.close();
        }
        //Exit program
        else if(command == 3){
            return;
        }
    }
}
int main(){
    start();
    return 0;
}
