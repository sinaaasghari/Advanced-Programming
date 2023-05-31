#include<iostream>
#include<fstream>
#include<math.h>
#include<string>
#include<vector>
#include<map>
#include<Windows.h>
#include<unistd.h>
#include<cstdlib>
using namespace std;

string start_menu = "1.Login\n2.Sign up\n3.Exit\nEnter your command : ";
string main_menu = "1.User information\n2.Upload article\n3.verification\n4.Check All Articles\n5.back\nEnter your command: ";


bool startWithCapSentence(string ID){
    string line;
    ifstream Text("./accounts/" + ID + ".txt");
    string name;                                                //checks a sententence statrts with capital latter    
    string date;
    string author;
    int article_id;
    string _article_id;
    string _references_count, _reference, _is_verified;
    int references_count;
    int reference;
    vector<int> references;
    string text;
    int is_verified;
    getline(Text, name);
    getline(Text, date);
    getline(Text, author);
    getline(Text, _article_id);
    getline(Text, _references_count);
    article_id = stoi(_article_id);
    references_count = stoi(_references_count);
    for(int i = 0; i<references_count; i++){
        getline(Text, _reference);
        reference = stoi(_reference);
        references.push_back(reference);
    }
    getline(Text, _is_verified);
    is_verified = stoi(_is_verified);
    //to halghe paeen check mikonim
    while(!Text.eof()){
        getline(Text, line);
        if(islower(line[0])) return false;
        for(int i = 0; i < line.length(); i++){
            if(line[i] == '.' && islower(line[i+2])){
                return false;
            }
        }
    }
    return true;
}
bool correctSigns(string ID){
    ifstream Text("./accounts/" + ID + ".txt");                 //Checks signs occurance
    string name;
    string date;
    string author;
    int article_id;
    string _article_id;
    string _references_count, _reference, _is_verified;
    int references_count;
    int reference;
    vector<int> references;
    string line, text;
    int is_verified;
    getline(Text, name);
    getline(Text, date);
    getline(Text, author);
    getline(Text, _article_id);
    getline(Text, _references_count);
    article_id = stoi(_article_id); //string to integer
    references_count = stoi(_references_count);
    for(int i = 0; i<references_count; i++){
        getline(Text, _reference);
        reference = stoi(_reference);
        references.push_back(reference);
    }
    getline(Text, _is_verified);
    is_verified = stoi(_is_verified);
    map<char, int> signs;
    signs['.'] = 1;
    signs[','] = 1;
    signs['!'] = 1;
    signs['?'] = 1;
    while(!Text.eof()){
        int flag = 0;
        getline(Text, line);
        for(int i = 0 ; i < line.length()-1 ; i++){
            //har line 2 ta 2 ta substr migirim
            string sub = line.substr(i, 2);
            if(signs[sub[0]] && signs[sub[1]]) return false;            //sign tekrari posht ham nayad
            if(signs[line[i]] && line[i+1] != ' ') return false;        //baed sign space bashe
            if(sub == "  ") return false;                               //baed sign 2 ta space nabashe
        }
    }
    return true ;  
}
bool correctParentheses(string ID){
    ifstream Text("./accounts/" + ID + ".txt");
    string name;
    string date;
    string author;
    int article_id;
    string _article_id;
    string _references_count, _reference, _is_verified;
    int references_count;
    int reference;
    vector<int> references;
    string line, text;
    int is_verified;                                                    //Checks if paranthese are balanced or not
    getline(Text, name);
    getline(Text, date);
    getline(Text, author);
    getline(Text, _article_id);
    getline(Text, _references_count);
    article_id = stoi(_article_id);
    references_count = stoi(_references_count);
    for(int i = 0; i<references_count; i++){
        getline(Text, _reference);
        reference = stoi(_reference);
        references.push_back(reference);
    }
    getline(Text, _is_verified);
    is_verified = stoi(_is_verified);
    int check = 0;                                                  
    while(!Text.eof()){
        getline(Text, line);
        for(int i = 0; i < line.length(); i++){
            if(line[i] == '('){
                check++;
            }
            else if(line[i] == ')'){
                check--;
            }
            if(check < 0){
                return false;                                       
            }
        }
        if(check > 0){
            return false;                                           
        }
    }
    return true;
}
bool numberOfLine(string ID){                                       
    ifstream Text("./accounts/" + ID + ".txt");
    string name;
    string date;                                                          //This function checks if article has more than 3 parantheses
    string author;
    int article_id;
    string _article_id;
    string _references_count, _reference, _is_verified;
    int references_count;
    int reference;
    vector<int> references;
    string line, text;
    int is_verified;
    getline(Text, name);
    getline(Text, date);
    getline(Text, author);
    getline(Text, _article_id);
    getline(Text, _references_count);
    article_id = stoi(_article_id);
    references_count = stoi(_references_count);
    for(int i = 0; i<references_count; i++){
        getline(Text, _reference);
        reference = stoi(_reference);
        references.push_back(reference);
    }
    getline(Text, _is_verified);
    is_verified = stoi(_is_verified);
    int lines = 0;
    // ba getline teded line ha ro mishmorim
    while(!Text.eof()){
        getline(Text, line);
        lines++;
    }
    if(lines >= 3){
        return true;
    }
    return false;
}

bool checkArticleName(string article_name){                             //article name must have at most 12 words
    int words = 1;
    for(int i = 0; i < article_name.size(); i++){
        if(article_name[i] == ' '){
            words++;
        }
    }
    if(words > 12){
        return false;
    }
    return true;
}
int RatePass(string& input){
    int hasLower = 0, hasUpper = 0;
    int hasDigit = 0, specialChar = 0;
    string normalChars = "abcdefghijklmnopqrstu"
        "vwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
 
    for (int i = 0; i < input.length(); i++) {
        if (islower(input[i]))
            hasLower = 1;
        if (isupper(input[i]))
            hasUpper = 1;
        if (isdigit(input[i]))
            hasDigit = 1;
 
        size_t special = input.find_first_not_of(normalChars);
        if (special != string::npos)
            specialChar = 1;
    }
    return hasLower + hasUpper + hasDigit + specialChar;
}
class user;
class article{
    private:
        string name;
        string date;
        string author;
        int article_id;
        string text;
        int references_count;
        vector<int> references;
        map<string, int> mapped;                                        // baraye shomaresh kalame ha zadim
        int is_verified;
    public:
        article(string _name, string _date, string _author, int _article_id,
                 string _text, int count, vector<int> _references){
            name = _name;
            date = _date;
            author = _author;
            article_id = _article_id;
            text = _text;      
            references_count = count;
            for(int  i = 0; i<_references.size(); i++){
                references.push_back(_references[i]);                   //dar vector references ha inaro mirizim
            }
            //Mapping article text
            string tmp = "";
            for(int i = 0; i<text.length(); i++){
                if(isalpha(text[i])) tmp.push_back(text[i]);
                else{
                    if(tmp.length()>0){
                        mapped[tmp]++;                                  //tekrar har kalame shomrde mishe
                        tmp = "";
                    }
                }
            }
            is_verified = 0;
        }
        friend ofstream & operator <<(ofstream & stream, article A);
        //checking similarity of two articles using cosine similarity algorithm
        float similarity(article A){
            vector<int> vector_1, vector_2;
            map<string, int> Union;                                     //Union map is union of two articles' words
            for(auto element : mapped){
                if(!Union[element.first]){
                    Union[element.first]++;
                }
            }
            for(auto element : A.mapped){
                if(!Union[element.first]){
                    Union[element.first]++;
                }
            }
            for(auto element : Union){
                vector_1.push_back(mapped[element.first]);              //vecotr bordar e matn ha ast
                vector_2.push_back(A.mapped[element.first]);
            }
            int sum_1 = 0, sum_2 = 0;
            for(auto x:vector_1){
                sum_1 += (x*x);                                         //Measure of vector_1
            }   
            for(auto x:vector_2){
                sum_2 += (x*x);                                         //Measure of vector_2
            }
            double percentage = 0;
            for(int i = 0; i<vector_1.size(); i++){
                percentage += vector_1[i] * vector_2[i];                //Dot product of two articles (article_1 • article_2)
            }
            percentage = percentage * 100/sqrt(sum_1 * sum_2);          //Computes similarity percentage of two articles
            return percentage;
        }
        void verify(vector<article> all_articles){
            int words_count = 0, flag = 1;
            for(auto W : mapped){
                words_count += W.second;
                if(W.second>50){                                        //ye kalame 50 bar tekrar nashode bashe
                    flag = 0;
                }
            }
            string id = to_string(article_id);
            sleep(3);
            if(flag == 1 && words_count <= 5000 && words_count >= 100 &&
                numberOfLine(id) && checkArticleName(name) && startWithCapSentence(id)&& 
                correctSigns(id) && correctParentheses(id)){            //Checking all conditions for verifying article
                int flag1 = 1;
                for(auto A : all_articles){
                    if(this->similarity(A)>50){
                        is_verified = 0;
                        flag1 = 0;
                        break;
                    }
                }
                if(flag1 == 1){
                    is_verified = 1;
                }
            }
            else{
                is_verified = 0;
            }
        }
        
        int getID(){
            return article_id;                                      
        }
        int isVerified(){
            return is_verified;
        }

};




ofstream & operator <<(ofstream & stream, article A){
    stream << A.name << '\n' << A.date << '\n' << A.author << '\n';
    stream << A.article_id << '\n' << A.references_count << '\n';
    for(auto x : A.references){                                         //Overloaded operator << for writing article in file
        stream << x << '\n';
    }
    stream << A.is_verified;
    stream << A.text;
    return stream;
}
class user{                                                             //User class
    private:
        string user_name;
        string password;
        string name;
        int articles_count;
        vector<int> articles_ID;
        vector<article> articles;
    public:
        user(string _name, string _user_name, string _password, int _articles_count){
            user_name = _user_name;
            password = _password;                                   
            name = _name;
            articles_count = _articles_count;
        }
        
        void addArticle(article Article, int flag = 1){
            articles.push_back(Article);
            articles_ID.push_back(Article.getID());
            articles_count += 1;
        }

        void display(){                                                 //This function Displays User data
            cout << "Username : " << user_name << "\n";
            cout << "Name : " << name << "\n";
            cout << "Articles count : " << articles_count << "\n";
            for(int i = 0; i<articles_count; i++){
                cout << articles_ID[i] << " ";
            }
            cout << endl;
        }
        string getUsername(){                                           //Encapsulation                                      
            return user_name;
        }
        string getPassword(){
            return password;                                            
        }
        string getName(){
            return name;
        }
        int getArticlesCount(){
            return articles_count;
        }
        vector<int> getArticlesID(){
            return articles_ID;
        }
        vector<article> getArticles(){
            return articles;
        }
};
vector<user> all_users;

string input(){
    string tmp, line;
    getline(cin, line);                                             //This function gets multi-line input from input stram
    while(line!=""){
        tmp = tmp + "\n" + line;
        getline(cin, line);

    }
    return tmp;
}

article getArticle(string file_name){
    ifstream Article("./accounts/" + file_name +".txt");
    string name;
    string date;                                                   //This function returns an article saved in a specific path
    string author;
    int article_id;
    string _article_id;
    string _references_count, _reference, _is_verified;
    int references_count;
    int reference;
    vector<int> references;
    string line, text;
    int is_verified;
    getline(Article, name);
    getline(Article, date);
    getline(Article, author);
    getline(Article, _article_id);
    getline(Article, _references_count);
    article_id = stoi(_article_id);
    references_count = stoi(_references_count);
    for(int i = 0; i<references_count; i++){
        getline(Article, _reference);
        reference = stoi(_reference);
        references.push_back(reference);
    }
    getline(Article, _is_verified);
    is_verified = stoi(_is_verified);
    while(!Article.eof()){
        getline(Article, line);
        text += "\n" + line;
    }
    Article.close();
    article A(name, date, author, article_id, text, references_count, references);
    return A;
}

vector<article> getAllArticles(){
    vector<article> all_articles;
    ifstream users("users.txt");                                 //This function returns a vector of all published articles
    string name, user_name, password, count;
    int articles_count;
    while(!users.eof()){
        getline(users, name);
        getline(users, user_name);
        getline(users, password);
        getline(users, count);
        articles_count = stoi(count);
        if(articles_count > 0){
            ifstream user_articles("./accounts/" + user_name + ".txt");
            string id;
            while(!user_articles.eof()){
                user_articles >> id;
                all_articles.push_back(getArticle(id));
            }
            user_articles.close();
        }
    }
    users.close();
    return all_articles;
}

vector<article> all_articles = getAllArticles();


void main_stream(user &User){
    int command;
    while(true){
        system("cls");
        cout << main_menu;                                       //This function is main stream of program
        cin >> command;
        system("cls");                                          
        if(command == 1){                                       
            User.display();                                      //Shows user information
            sleep(3);
        }
        else if(command == 2){      
            string name;
            string date;                                
            string author, _id;                                  
            int article_id;                                      //Uploading article
            string text;
            int references_count = 0;
            vector<int> references;
            cout << "Enter article Name : ";
            ws(cin);
            getline(cin, name);
            cout << "Enter Date : ";
            getline(cin, date);
            cout << "Enter author Name : ";
            getline(cin, author);
            cout << "Enter article id : ";
            getline(cin, _id);
            string path = "./accounts/" + _id + ".txt";
            article_id = stoi(_id);
            cout << "Enter references count : ";
            getline(cin, _id);
            references_count = stoi(_id);
            for(int i = 0; i<references_count; i++){
                cout << "Enter the " << i << "th reference id : ";
                getline(cin, _id);
                references.push_back(stoi(_id));
            }
            text = input();
            article A(name, date, author, article_id, text, references_count, references);
            ofstream strm(path, ios::out);      
            strm << A;                                          //Writing article in file useing overloaded operator <<
            strm.close();
            A.verify(all_articles);
            User.addArticle(A);                                
            all_articles.push_back(A);
        }
        else if(command == 3){
            int id, flag = 0;
            cout << "Enter your article id : ";
            cin >> id;
            for(auto A : User.getArticles()){
                if(A.getID() == id){                            //checks if an article is verified or not
                    flag = 1;
                    if(A.isVerified() == 1){
                        cout << "Accepted\n";
                    }
                    else{
                        cout << "Rejected\n";
                    }
                }
            }
            if(flag == 0){
                cout << "This article doesn't exist!\n";
            }
            sleep(3);
        }
        else if(command == 4){
            for(auto A : User.getArticles()){
                if(A.isVerified() == 1){                        //Checks all articles verification status
                    cout << A.getID() << " : is accepted.\n"; 
                }
                else{
                    cout << A.getID() << " : is rejected.\n";
                }
            }
            sleep(3);
        }
        else if(command == 5){
            string file_name = "./accounts/" + User.getUsername() + ".txt";
            ofstream articles_id(file_name, ios::out);
            for(auto x : User.getArticlesID()){                 //Saves users information in articles
                articles_id << x << '\n';
            }
            articles_id.close();
            for(auto x : User.getArticles()){
                file_name = "./accounts/" + to_string(x.getID()) + ".txt";
                ofstream Article(file_name, ios::out);
                Article << x;
                Article.close();
            }
            return;
        }
    }
}

void start(){
    int all = 0;
    ifstream users("users.txt");
    string name, user_name, password, _count;                   //Starting function of program
    int count;
    while(!users.eof()){
        getline(users, name);
        getline(users, user_name);
        getline(users, password);
        getline(users, _count);                                 //Loads all users information
        count = stoi(_count);
        user User(name, user_name, password, count);
        if(count > 0){
            string ID;
            ifstream articles("./accounts/" + user_name + ".txt");
            while(!articles.eof()){
                articles >> ID;
                //string path = "./accounts/" + ID + ".txt";
                User.addArticle(getArticle(ID), 0);
            }
            articles.close();
        }
        all_users.push_back(User);
    }
    users.close();
    int command;
    while(true){
        system("cls");
        cout << start_menu;
        cin >> command;
        system("cls");
        if(command == 1){
            string name, user_name, password;
            int flag = 0, count;
            cout << "Enter Username : ";
            ws(cin);
            getline(cin, user_name);
            cout << "Enter Password : ";                        //Login 
            getline(cin, password);
            for(auto U : all_users){
                if(U.getUsername() == user_name && U.getPassword() == password){
                    flag = 1;
                    main_stream(U);
                    break;
                }
            }
            if(flag == 0){
                cout << "Wrong Username or Password!\n";
                sleep(3);
            }
        }
        else if(command == 2){
            string name, user_name, password;
            int flag = 1;
            cout << "Enter your Name : ";
            ws(cin);
            getline(cin, name);
            cout << "Enter your Username : ";
            getline(cin, user_name);                            //Sign up
            cout << "Enter your Password : ";
            getline(cin, password);
            for(auto U : all_users){
                if(user_name == U.getUsername()){
                    flag = 0;
                }
            }
            if(flag == 1){
                user User(name, user_name, password, 0);
                all_users.push_back(User);
            }
            else{
                cout << "This Username already exists!\n";
                sleep(3);
            }
        }
        else if(command == 3){
            ofstream users("users.txt", ios::out);
            int flag = 0;
            for(auto U : all_users){                            //Saves users information and Exits program
                if(flag == 1){
                    users << '\n';
                }
                users << U.getName() << '\n' << U.getUsername() << '\n' << U.getPassword() << '\n' << U.getArticlesCount();
                flag = 1;
            }
            users.close();
            break;
        }
    }
}





int main(){
    start();                                                    

    return 0;
}