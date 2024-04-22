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
    long long ModValue = 99991;

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

void createWaterMap()
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
}

void PrintWaterMap()
{
    createWaterMap();

    for(ll x = 0 ; x < 2e5 + 1 ; x++)
    {
        if(Water[x].empty())
            continue;   

        cout << "Cities Connected With : " << mapping[x] << " : - \n\n";

        for(auto i : Water[x])
            cout << mapping[i.first] << " : " << i.second << " KiloMeters." << endl;
        cout << endl;
    }

    cout << endl;

    pause;

    clear;
}

void EditWaterMap()
{
    createWaterMap();

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
    createWaterMap();

    string start, destination;

    cout << "\nEnter The Start & End Point : ";

    cin >> start >> destination;

    queue<ll> q;

    vector<bool> vis;

    vector<ll> lvl, predecessor;

    vis.assign(200001,false);

    lvl.assign(200001,0);

    predecessor.assign(200001,0);

    ll root = Encrypt(start);

    q.push(root);

    vis[root] = true;

    while(!q.empty())
    {
        ll current = q.front();

        q.pop();

        vis[current] = true;

        for(auto neighbour : Water[current])
            if(!vis[neighbour.first])
            {
                lvl[neighbour.first] = 1 + lvl[current];

                q.push(neighbour.first);

                predecessor[neighbour.first] = current;
                
                vis[neighbour.first] = true;
            }
    }

    ll endd = Encrypt(destination);
    
    cout << endl << "Shortest Distance Between " << start << " & " << destination << " covers : " << lvl[endd] + 1 << " Locations. " << endl << endl;

    vector <ll> path;

    path.push_back(endd);

    while(predecessor[endd])
    {
        path.push_back(predecessor[endd]);
        endd = predecessor[endd];
    }

    reverse(path.begin(), path.end());

    for(ll x = 0 ; x < path.size() ; x++)
        cout << x + 1 << ". " << mapping[path[x]] << endl << endl;        

    ll distanceTotal = 0;

    for(ll x = 0 ; x < path.size() - 1 ; x++)
        for(auto i : Water[path[x]])
            if(i.first == path[x + 1])
            {
                distanceTotal += i.second;
                break;
            }

    cout << "\nTotal Distance Covered : " << distanceTotal << " KiloMeters. " << endl << endl;

    pause;

    clear;
}

void createLandMap()
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

        Land[encrypt1].push_back(make_pair(encrypt2, stoi(info[x + 3])));
        Land[encrypt2].push_back(make_pair(encrypt1, stoi(info[x + 3])));
    }
}

void PrintLandMap()
{
    createLandMap();

    for(ll x = 0 ; x < 2e5 + 1 ; x++)
    {
        if(Land[x].empty())
            continue;   

        cout << "Cities Connected With : " << mapping[x] << " : - \n\n";

        for(auto i : Water[x])
            cout << mapping[i.first] << " : " << i.second << " KiloMeters." << endl;
        cout << endl;
    }

    cout << endl;

    pause;

    clear;
}

void EditLandMap()
{
    createLandMap();

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
    createLandMap();
    
    string start, destination;

    cout << "\nEnter The Start & End Point : ";

    cin >> start >> destination;

    queue<ll> q;

    vector<bool> vis;

    vector<ll> lvl, predecessor;

    vis.assign(200001,false);

    lvl.assign(200001,0);

    predecessor.assign(200001,0);

    ll root = Encrypt(start);

    q.push(root);

    vis[root] = true;

    while(!q.empty())
    {
        ll current = q.front();

        q.pop();

        vis[current] = true;

        for(auto neighbour : Land[current])
            if(!vis[neighbour.first])
            {
                lvl[neighbour.first] = 1 + lvl[current];

                q.push(neighbour.first);

                predecessor[neighbour.first] = current;
                
                vis[neighbour.first] = true;
            }
    }

    ll endd = Encrypt(destination);
    
    cout << endl << "Shortest Distance Between " << start << " & " << destination << " covers : " << lvl[endd] + 1 << " Locations. " << endl << endl;

    vector <ll> path;

    path.push_back(endd);

    while(predecessor[endd])
    {
        path.push_back(predecessor[endd]);
        endd = predecessor[endd];
    }

    reverse(path.begin(), path.end());

    for(ll x = 0 ; x < path.size() ; x++)
        cout << x + 1 << ". " << mapping[path[x]] << endl << endl;        

    ll distanceTotal = 0;

    for(ll x = 0 ; x < path.size() - 1 ; x++)
        for(auto i : Land[path[x]])
            if(i.first == path[x + 1])
            {
                distanceTotal += i.second;
                break;
            }

    cout << "\nTotal Distance Covered : " << distanceTotal << " KiloMeters. " << endl << endl;

    pause;

    clear;
}

void createAirMap()
{
    Air.assign(2e5 + 1, vector<pair<ll, ll>> ());

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

        Air[encrypt1].push_back(make_pair(encrypt2, stoi(info[x + 3])));
        Air[encrypt2].push_back(make_pair(encrypt1, stoi(info[x + 3])));
    }
}

void PrintAirMap()
{
    createAirMap();
    
    for(ll x = 0 ; x < 2e5 + 1 ; x++)
    {
        if(Air[x].empty())
            continue;   

        cout << "Cities Connected With : " << mapping[x] << " : - \n\n";

        for(auto i : Air[x])
            cout << mapping[i.first] << " : " << i.second << " KiloMeters." << endl;
        cout << endl;
    }

    cout << endl;

    pause;

    clear;
}

void EditAirMap()
{
    createAirMap();

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
    createAirMap();
    
    string start, destination;

    cout << "\nEnter The Start & End Point : ";

    cin >> start >> destination;

    queue<ll> q;

    vector<bool> vis;

    vector<ll> lvl, predecessor;

    vis.assign(200001,false);

    lvl.assign(200001,0);

    predecessor.assign(200001,0);

    ll root = Encrypt(start);

    q.push(root);

    vis[root] = true;

    while(!q.empty())
    {
        ll current = q.front();

        q.pop();

        vis[current] = true;

        for(auto neighbour : Air[current])
            if(!vis[neighbour.first])
            {
                lvl[neighbour.first] = 1 + lvl[current];

                q.push(neighbour.first);

                predecessor[neighbour.first] = current;
                
                vis[neighbour.first] = true;
            }
    }

        ll endd = Encrypt(destination);
    
    cout << endl << "Shortest Distance Between " << start << " & " << destination << " covers : " << lvl[endd] + 1 << " Locations. " << endl << endl;

    vector <ll> path;

    path.push_back(endd);

    while(predecessor[endd])
    {
        path.push_back(predecessor[endd]);
        endd = predecessor[endd];
    }

    reverse(path.begin(), path.end());

    for(ll x = 0 ; x < path.size() ; x++)
        cout << x + 1 << ". " << mapping[path[x]] << endl << endl;        

    ll distanceTotal = 0;

    for(ll x = 0 ; x < path.size() - 1 ; x++)
        for(auto i : Air[path[x]])
            if(i.first == path[x + 1])
            {
                distanceTotal += i.second;
                break;
            }

    cout << "\nTotal Distance Covered : " << distanceTotal << " KiloMeters. " << endl << endl;

    pause;

    clear;
}

void TravelLog()
{
    ;
}

void Menu();

void CustomerMenu()
{
    cout << "\n\nWelcome To Customer Menu: - \n\n";

    cout << "1. Find a Route \n\n2. Travel Log\n\n3. Quit...\n\n";

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
        TravelLog();

    else
        Menu();

    CustomerMenu();
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
            PrintWaterMap();
        
        else if(type == "Air")
            PrintAirMap();
        
        else
            PrintLandMap();
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

    AdministratorMenu();
}

void Menu()
{
    string type;

    cout << "\nWhat is Your Role? ";

    cout << "\n\n1. Customer\n\n2. Administrator\n\n3. Quit\n\n";

    cout << "\n\nEnter Your Choice : ";

    cin >> type;

    if(type == "Customer")
    {
        clear;

        CustomerMenu();
    }

    else if(type == "Administrator")
    {
        clear;

        AdministratorMenu();
    }

    else if(type == "Quit")
    {
        clear;

        MainWindow();
    }

    else
    {
        cout << "\n\nInvalid Input...\n\n";

        pause;

        clear;
    }

    Menu();
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
    cout << "\nQuitting the Program...\n\n";

    cout << "\n\nThanks For Using Our Application!\n\n";

    pause;

    abort();
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
        cout << "\nCongratulations! You have been Logged-In...\n\n";

        pause;

        clear;

        Menu();
    }

    else
    {
        cout << "\nSorry! Try Again...\n\n";

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
        cout << "\nSorry! Username is not Available...\n\n";

        pause;
    }

    else
    {
        cout << "\nCongratulations! You Have Been Successfully Signed...\n\n";

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
    MainWindow();

    return 0;
}