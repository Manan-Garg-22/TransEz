#include <bits/stdc++.h>
using namespace std;

using str = string;
using ll = long long;
using ld = long double;
const ld Pi = 3.141592653589793238462643;
const ld e = 2.718281828459045235360;
const ll MOD = 1000000007;

vector<pair<string, string>> Credentials;

vector<vector<pair<ll, ll>>> Water;

vector<vector<pair<ll, ll>>> Air;

vector<vector<pair<ll, ll>>> Land;

map<ll, string> mapping;

#define pause system("pause")

#define clear system("cls")

ll Encrypt(string data)
{
    long long ModValue = 10139;

    long long Encrypted = 0;
    
    for(int x = 0 ; x < data.size() ; x++)
    {
        ll factor = (abs(data[x] - 'a' + 1)) * pow((x+1), x);
        
        factor %= ModValue;

        Encrypted += factor;

        Encrypted %= ModValue;
    }

    return Encrypted;
}

void MainWindow();

void WaterMap()
{
    Water.assign(2e5 + 1, vector<pair<ll, ll>> ());

    ifstream file("water.txt");

    string word;

    vector<string> info;

    ll temp = 0;

    while(file >> word)
    {
        temp++;

        info.push_back(word);

        if(temp % 4 == 0)
            info.push_back("\n");
    }

    for(ll x = 0 ; x < info.size() ; x += 5)
    {
        ll encrypt1 = Encrypt(info[x + 1]);
        ll encrypt2 = Encrypt(info[x + 2]);

        mapping[encrypt1] = info[x + 1];
        mapping[encrypt2] = info[x + 2];

        Water[encrypt1].push_back(make_pair(encrypt2, stoi(info[x + 3])));
        Water[encrypt2].push_back(make_pair(encrypt1, stoi(info[x + 3])));
    }

    for(ll x = 0 ; x < 2e5 + 1 ; x++)
    {
        if(Water[x].empty())
            continue;   

        cout << "Cities Connected With : " << mapping[x] << " : - \n\n";

        for(auto i : Water[x])
            cout << mapping[i.first] << " : " << i.second << " KiloMeters." << endl;
        cout << endl;
    }
}

void EditWaterMap()
{
    string city1, city2;

    ll distance;

    cout << "\nEnter Name Of Cities which are to be connected : ";

    cin >> city1 >> city2;

    cout << "Enter Distance : ";

    cin >> distance;

    ifstream file("water.txt");

    string word;

    vector<string> info;

    ll temp = 0;

    while(file >> word)
    {
        temp++;

        info.push_back(word);

        if(temp % 4 == 0)
            info.push_back("\n");
    }


    ofstream file2("water.txt");

    for(auto i : info)
        file2 << i << ' ';

    file2 << "$ " << city1 << ' ' << city2 << ' ' << distance << "\n";
}

void WaterRoute()
{
    string start, destination;

    cout << "\nEnter The Start & End Point : ";

    cin >> start >> destination;
}

void WaterCostE()
{
    ;
}

void LandMap()
{
    Water.assign(2e5 + 1, vector<pair<ll, ll>> ());

    ifstream file("land.txt");

    string word;

    vector<string> info;

    ll temp = 0;

    while(file >> word)
    {
        temp++;

        info.push_back(word);

        if(temp % 4 == 0)
            info.push_back("\n");
    }

    for(ll x = 0 ; x < info.size() ; x += 5)
    {
        ll encrypt1 = Encrypt(info[x + 1]);
        ll encrypt2 = Encrypt(info[x + 2]);

        mapping[encrypt1] = info[x + 1];
        mapping[encrypt2] = info[x + 2];

        Water[encrypt1].push_back(make_pair(encrypt2, stoi(info[x + 3])));
        Water[encrypt2].push_back(make_pair(encrypt1, stoi(info[x + 3])));
    }

    for(ll x = 0 ; x < 2e5 + 1 ; x++)
    {
        if(Water[x].empty())
            continue;   

        cout << "Cities Connected With : " << mapping[x] << " : - \n\n";

        for(auto i : Water[x])
            cout << mapping[i.first] << " : " << i.second << " KiloMeters." << endl;
        cout << endl;
    }
}

void EditLandMap()
{
    string city1, city2;

    ll distance;

    cout << "\nEnter Name Of Cities which are to be connected : ";

    cin >> city1 >> city2;

    cout << "Enter Distance : ";

    cin >> distance;

    ifstream file("land.txt");

    string word;

    vector<string> info;

    ll temp = 0;

    while(file >> word)
    {
        temp++;

        info.push_back(word);

        if(temp % 4 == 0)
            info.push_back("\n");
    }


    ofstream file2("land.txt");

    for(auto i : info)
        file2 << i << ' ';

    file2 << "$ " << city1 << ' ' << city2 << ' ' << distance << "\n";
}

void LandRoute()
{
    ;
}

void LandCostE()
{
    ;
}

void AirMap()
{
    Water.assign(2e5 + 1, vector<pair<ll, ll>> ());

    ifstream file("air.txt");

    string word;

    vector<string> info;

    ll temp = 0;

    while(file >> word)
    {
        temp++;

        info.push_back(word);

        if(temp % 4 == 0)
            info.push_back("\n");
    }

    for(ll x = 0 ; x < info.size() ; x += 5)
    {
        ll encrypt1 = Encrypt(info[x + 1]);
        ll encrypt2 = Encrypt(info[x + 2]);

        mapping[encrypt1] = info[x + 1];
        mapping[encrypt2] = info[x + 2];

        Water[encrypt1].push_back(make_pair(encrypt2, stoi(info[x + 3])));
        Water[encrypt2].push_back(make_pair(encrypt1, stoi(info[x + 3])));
    }

    for(ll x = 0 ; x < 2e5 + 1 ; x++)
    {
        if(Water[x].empty())
            continue;   

        cout << "Cities Connected With : " << mapping[x] << " : - \n\n";

        for(auto i : Water[x])
            cout << mapping[i.first] << " : " << i.second << " KiloMeters." << endl;
        cout << endl;
    }
}

void EditAirMap()
{
    string city1, city2;

    ll distance;

    cout << "\nEnter Name Of Cities which are to be connected : ";

    cin >> city1 >> city2;

    cout << "Enter Distance : ";

    cin >> distance;

    ifstream file("air.txt");

    string word;

    vector<string> info;

    ll temp = 0;

    while(file >> word)
    {
        temp++;

        info.push_back(word);

        if(temp % 4 == 0)
            info.push_back("\n");
    }


    ofstream file2("air.txt");

    for(auto i : info)
        file2 << i << ' ';

    file2 << "$ " << city1 << ' ' << city2 << ' ' << distance << "\n";

}

void AirRoute()
{
    ;
}

void AirCostE()
{
    ;
}

void TravelLog()
{
    ;
}

void Menu();

void CustomerMenu()
{
    cout << "\n\nWelcome To Customer Menu: - \n\n";

    cout << "1. Find a Route \n\n2. Cost Estimation \n\n3. Travel Log\n\n4. Quit...\n\n";

    cout << "Enter Your Choice : ";

    ll choice;

    cin >> choice;

    if(choice == 1)
    {
        cout << "\nWhich Mode of Travel? (Water / Air / Land) : ";

        string type;

        cin >> type;

        if(type == "Water")
            WaterRoute();
        
        else if(type == "Air")
            AirRoute();
        
        else
            LandRoute();
    }

    else if(choice == 2)
    {
        cout << "\nWhich Mode of Travel? (Water / Air / Land) : ";

        string type;

        cin >> type;

        if(type == "Water")
            WaterCostE();
        
        else if(type == "Air")
            AirCostE();
        
        else
            LandCostE();
    }

    else if(choice == 3)
        TravelLog();

    else
        Menu();
}

void AdministratorMenu()
{
    cout << "\n\nWelcome To Administrator Menu: - \n\n";

    cout << "1. View Current Network \n\n2. Edit Current Network \n\n3. Quit..\n\n";

    cout << "Enter Your Choice : ";

    ll choice;

    cin >> choice;

    if(choice == 1)
    {
        cout << "\nWhich Mode of Travel? (Water / Air / Land) : ";

        string type;

        cin >> type;

        if(type == "Water")
            WaterMap();
        
        else if(type == "Air")
            AirMap();
        
        else
            LandMap();
    }

    else if(choice == 2)
    {
        cout << "\nWhich Mode of Travel? (Water / Air / Land) : ";

        string type;

        cin >> type;

        if(type == "Water")
            EditWaterMap();
        
        else if(type == "Air")
            EditAirMap();
        
        else
            EditLandMap();
    }

    else
        Menu();
}

void Menu()
{
    string type;

    cout << "\nWhat is Your Role? ";

    cout << "\n\n1. Customer\n\n2. Administrator";

    cin >> type;

    if(type == "Customer")
        CustomerMenu();

    else if(type == "Administrator")
        AdministratorMenu();

    else
        cout << "\n\nInvalid Input...";

    clear;

    Menu;
}

bool ReadCredentials(string username, string passwd)
{
    ifstream file("credentials.txt");

    string word;

    vector<string> info;

    ll temp = 0;

    while(file >> word)
    {
    	temp++;

       	info.push_back(word);

       	if(temp % 3 == 0)
       		info.push_back("\n");
    }

    for(ll x = 0 ; x < info.size() ; x += 4)
    {
    	if(info[x + 1] == username && info[x + 2] == passwd)
    		return true;
    }

    return false;
}

void WriteCredentials(string username, string passwd)
{
    ifstream file("credentials.txt");

    string word;

    vector<string> info;

    ll temp = 0;

    while(file >> word)
    {
    	temp++;

       	info.push_back(word);

       	if(temp % 3 == 0)
       		info.push_back("\n");
    }


    ofstream file2("credentials.txt");

    for(auto i : info)
    	file2 << i << ' ';

   	file2 << "$ " << username << ' ' << passwd << "\n";
}


void Quit()
{
    cout << "\nQuitting the Program...";

    cout << "\n\nThanks For Using Our Application!\n\n";

    pause;

    clear;
}

void Login()
{
    string username, passwd;

    cout << "\nEnter Username : ";

    cin >> username;

    cout << "\nEnter Password : ";

    cin >> passwd;

    bool found = ReadCredentials(username, passwd);

    if(found)
    {
        cout << "\nCongratulations! You have been Logged-In...";

        pause;

        Menu();
    }

    else
    {
        cout << "\nSorry! Try Again...";

        pause;

        clear;

        MainWindow();
    }
}

void Signup()
{
    string username, passwd;

    cout << "\nEnter Username : ";

    cin >> username;

    cout << "\nEnter Password : ";

    cin >> passwd;

    bool found = ReadCredentials(username, passwd);

    if(found)
    {
        cout << "\nSorry! Username is not Available...";

        pause;
    }

    else
    {
        cout << "\nCongratulations! You Have Been Successfully Signed...";

        WriteCredentials(username, passwd);

        pause;
    }

    clear;

    MainWindow();
}

void MainWindow()
{
    cout << "\n\nWelcome To Our Program: - \n\n";

    cout << "TransEz : Transportation Made Easy...\n\n";

    cout << "1. Log-In \n\n2. Sign-Up \n\n3. Quit..\n\n";

    cout << "Enter Your Choice : ";

    ll choice;

    cin >> choice;

    if(choice == 1)
        Login();

    else if(choice == 2)
        Signup();

    else
        Quit();
}

int main()
{
    WaterMap();

    EditWaterMap();

    MainWindow();

    return 0;
}