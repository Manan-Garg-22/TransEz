#include <bits/stdc++.h>
using namespace std;

using str = string;
using ll = long long;
using ld = long double;
const ld Pi = 3.141592653589793238462643;
const ld e = 2.718281828459045235360;
const ll MOD = 1000000007;

//Vector to store username password pairs
vector<pair<string, string>> Credentials;    

//Vector to represent water transportation network
vector<vector<pair<ll, ll>>> Water;

//Vector to represent air transportation network
vector<vector<pair<ll, ll>>> Air;

//Vector to represent land transportation network
vector<vector<pair<ll, ll>>> Land;

//Map to link the encrypted values with their original strings
map<ll, string> mapping;

#define pause system("pause")
#define clear system("cls")

//Function to encrypt string data
ll Encrypt(string data)
{
    long long ModValue = 99991;   //Modulus value (prime) for handling overflow

    long long Encrypted = 0;

    //Loop through each character of the data string
    for(int x = 0 ; x < data.size() ; x++)
    {
        ll factor = (abs(data[x] - 'a' + 1)) * pow((x+1), x);    //calculate factor for Encryption
        
        factor %= ModValue;

        Encrypted += factor;

        Encrypted %= ModValue;  //Handling Overflow
    }

    return Encrypted;
}

void MainWindow();

//Function to create water transportation network
void createWaterMap()
{
    Water.assign(2e5 + 1, vector<pair<ll, ll>> ());

    ifstream file("water.txt");  //Open file for read operation using input file stream

    string word;

    vector<string> info;  //Vector to store words from file

    ll temp = 0;

    while(file >> word)     //Extract word from file until reach end of file
    {
        temp++;

        info.push_back(word);

        if(temp % 4 == 0)             //Add newline once 4 words are added
            info.push_back("\n");
    }

    for(ll x = 0 ; x < info.size() ; x += 5)
    {
        ll encrypt1 = Encrypt(info[x + 1]); //Encrypt city 1
        ll encrypt2 = Encrypt(info[x + 2]); //Encrypt city 2

        mapping[encrypt1] = info[x + 1]; //Map Encrypted value to city 1
        mapping[encrypt2] = info[x + 2]; //Map Encrypted value to city 2

        Water[encrypt1].push_back(make_pair(encrypt2, stoi(info[x + 3]))); //Path from encrypted city 1 to city 2 with distance
        Water[encrypt2].push_back(make_pair(encrypt1, stoi(info[x + 3]))); //Path from encrypted city 2 to city 1 with distance
    }
}

//Function to print water transportation network
void PrintWaterMap()
{
    createWaterMap();

    cout << endl << endl;

    //Loop through all elements in Water vector
    for(ll x = 0 ; x < 2e5 + 1 ; x++)
    {
        if(Water[x].empty()) //If no connections for city x, continue
            continue;   

        cout << "Cities Connected With : " << mapping[x] << " : - \n\n";

        //Loop through connections of city x and print them
        for(auto i : Water[x])
            cout << mapping[i.first] << " : " << i.second << " KiloMeters." << endl;
        cout << endl;
    }

    cout << endl;

    pause;

    clear;
}

//Function to edit water transportation network
void EditWaterMap()
{
    createWaterMap();

    string city1, city2;

    ll distance;

    cout << "\nEnter Name Of Cities which are to be connected : ";

    cin >> city1 >> city2;

    cout << "Enter Distance : ";

    cin >> distance;

    ifstream file("water.txt");  //Read file using input file stream

    string word;

    vector<string> info;

    ll temp = 0;

    while(file >> word)  //loop until reach end of file
    {
        temp++;

        info.push_back(word);

        if(temp % 4 == 0)
            info.push_back("\n");
    }


    ofstream file2("water.txt");  //open file for write operation using output file stream

    for(auto i : info)
        file2 << i << ' ';

    file2 << "$ " << city1 << ' ' << city2 << ' ' << distance << "\n";
}

//Function to ffind the shortest path and distance between two cities
void WaterRoute()
{
    createWaterMap();

    string start, destination;

    cout << "\nEnter The Start & End Point : ";

    cin >> start >> destination;

    queue<ll> q;  //Queue to perform bfs
 
    vector<bool> vis;  //Vector to mark visited nodes

    vector<ll> lvl, predecessor; //Vectors to store level and predecessor information for nodes

    vis.assign(200001,false);

    lvl.assign(200001,0);

    predecessor.assign(200001,0);

    ll root = Encrypt(start); //Convert start point to its corresponding numeric value

    q.push(root);

    vis[root] = true;

    //Performing breadth-first search until the queue is empty
    while(!q.empty())
    {
        ll current = q.front();

        q.pop();

        vis[current] = true;

        //Iterate over the neighbors of the current node in the 'Water' adjacency list
        for(auto neighbour : Water[current])
            if(!vis[neighbour.first])
            {
                lvl[neighbour.first] = 1 + lvl[current];  //Update the level of the neighbor to be one more than the current node's level

                q.push(neighbour.first);  //Add the neighbor to the queue for further exploration

                predecessor[neighbour.first] = current;  //Set the predecessor of the neighbor to be the current node
                
                vis[neighbour.first] = true;  //Mark the neighbor as visited
            }
    }

    ll endd = Encrypt(destination);  //Convert end point to its corresponding numeric value
    
    cout << endl << "Shortest Distance Between " << start << " & " << destination << " covers : " << lvl[endd] + 1 << " Locations. " << endl << endl;

    vector <ll> path; //Vector to store the shortest path from start to end points

    path.push_back(endd); //Push the end point to the path vector

    //Trace back the shortest path using predecessors
    while(predecessor[endd])
    {
        path.push_back(predecessor[endd]);
        endd = predecessor[endd];
    }

    reverse(path.begin(), path.end());  //Reverse the path vector to get the correct order

    //Output the shortest path
    for(ll x = 0 ; x < path.size() ; x++)
        cout << x + 1 << ". " << mapping[path[x]] << endl << endl;        

    //Calculate the total distance covered in the shortest path
    ll distanceTotal = 0;
 
    for(ll x = 0 ; x < path.size() - 1 ; x++)
        for(auto i : Water[path[x]])
            if(i.first == path[x + 1])
            {
                distanceTotal += i.second;
                break;
            }

    cout << "\nTotal Distance Covered : " << distanceTotal << " KiloMeters. " << endl << endl;

    cout << "Enter Your Username To Save Changes to Your Log : ";

    string name;

    cin >> name;

    name += ".txt";

    ifstream file(name);

    string word;

    vector<string> info;

    ll temp = 0;

    //Read file until reach end of file
    while(file >> word)
    {
        temp++;

        info.push_back(word);
    }


    //Write the existing information back to the file
    ofstream file2(name);
  
    for(auto i : info)
        file2 << i << ' ';

    file2 << "### Water :: ";

    //Append the new water route information to the file
    for(auto i : path)
        file2 << mapping[i] << "-> ";
    
    file2 << "Distance " << distanceTotal;

    file2 << " KiloMeters " << "### " << endl << endl;

    pause;

    clear;
}

//Function to create Land Network
void createLandMap()
{
    Water.assign(2e5 + 1, vector<pair<ll, ll>> ());

    ifstream file("land.txt"); //Open the 'land.txt' file for reading

    string word;

    vector<string> info;  //Vector to store words read from the file

    ll temp = 0;

    //Read words from the file
    while(file >> word)
    {
        temp++;

        info.push_back(word);

        if(temp % 4 == 0)          //If 4 words have been read, add a newline character to the 'info' vector
            info.push_back("\n");
    }

    for(ll x = 0 ; x < info.size() ; x += 5)
    {
        //Encrypt the city names to numeric representations
        ll encrypt1 = Encrypt(info[x + 1]);
        ll encrypt2 = Encrypt(info[x + 2]);

        //Map the numeric representations to the corresponding city names
        mapping[encrypt1] = info[x + 1];
        mapping[encrypt2] = info[x + 2];

        //Add the connection between two cities and their distance to the 'Land' vector
        Land[encrypt1].push_back(make_pair(encrypt2, stoi(info[x + 3])));
        Land[encrypt2].push_back(make_pair(encrypt1, stoi(info[x + 3])));
    }
}

//Function to print the Land Network
void PrintLandMap()
{
    createLandMap();

    cout << endl << endl;

    for(ll x = 0 ; x < 2e5 + 1 ; x++)
    {
        if(Land[x].empty())    //If connection of any city is empty, skip it
            continue;   

        cout << "Cities Connected With : " << mapping[x] << " : - \n\n";

        //Output City 1 : City 2 and distance
        for(auto i : Water[x])
            cout << mapping[i.first] << " : " << i.second << " KiloMeters." << endl;
        cout << endl;
    }

    cout << endl;

    pause;

    clear;
}

//Function to edit Land transportation Network
void EditLandMap()
{
    createLandMap();

    string city1, city2;

    ll distance;

    cout << "\nEnter Name Of Cities which are to be connected : ";

    cin >> city1 >> city2;

    cout << "Enter Distance : ";

    cin >> distance;

    ifstream file("land.txt");  //Read file using input filestream

    string word;

    vector<string> info;  //Vector to store words from the file

    ll temp = 0;

    //Read file until reach end of file
    while(file >> word)
    {
        temp++;

        info.push_back(word);

        if(temp % 4 == 0)  //Newline character once a chunk of 4 words inserted into info vector
            info.push_back("\n");
    }


    ofstream file2("land.txt");   //Write operation into file

    for(auto i : info)
        file2 << i << ' ';

    file2 << "$ " << city1 << ' ' << city2 << ' ' << distance << "\n";   //Entering data into 'land.txt' file
}

///Function to find the shortest path and distance between two cities
void LandRoute()
{
    createLandMap();
    
    string start, destination;

    cout << "\nEnter The Start & End Point : ";

    cin >> start >> destination;

    queue<ll> q;   //Queue to perform bfs

    vector<bool> vis;  //Vector to mark visited nodes

    vector<ll> lvl, predecessor;   //Vectors to store level and predecessor information for nodes
 
    vis.assign(200001,false);

    lvl.assign(200001,0);

    predecessor.assign(200001,0);

    ll root = Encrypt(start);  //Convert start point to its corresponding numeric value

    q.push(root);   //Push start node into Queue

    vis[root] = true;    //Mark start node as visited

    //Performing breadth-first search until the queue is empty
    while(!q.empty())
    {
        ll current = q.front();

        q.pop();

        vis[current] = true;

        // Iterate over the neighbors of the current node in the 'Land' adjacency list
        for(auto neighbour : Land[current])
            if(!vis[neighbour.first])
            {
                lvl[neighbour.first] = 1 + lvl[current];  //Update the level of the neighbor to be one more than the current node's level

                q.push(neighbour.first);  //Add the neighbor to the queue for further exploration

                predecessor[neighbour.first] = current;  //Set the predecessor of the neighbor to be the current node
                
                vis[neighbour.first] = true;  //Mark the neighbor as visited
            }
    }

    ll endd = Encrypt(destination);  //Convert end point to its corresponding numeric value
    
    cout << endl << "Shortest Distance Between " << start << " & " << destination << " covers : " << lvl[endd] + 1 << " Locations. " << endl << endl;

    vector <ll> path;   //Vector to store the shortest path from start to end points

    path.push_back(endd);  //Push the end point to the path vector

    //Trace back the shortest path using predecessors
    while(predecessor[endd])
    {
        path.push_back(predecessor[endd]);
        endd = predecessor[endd];
    }

    reverse(path.begin(), path.end());   //Reverse the path vector

    //Output the shortest path between two cities
    for(ll x = 0 ; x < path.size() ; x++)
        cout << x + 1 << ". " << mapping[path[x]] << endl << endl;        

    ll distanceTotal = 0;

    //Calculate the total distance covered in the shortest path
    for(ll x = 0 ; x < path.size() - 1 ; x++)
        for(auto i : Land[path[x]])
            if(i.first == path[x + 1])
            {
                distanceTotal += i.second;
                break;
            }

    cout << "\nTotal Distance Covered : " << distanceTotal << " KiloMeters. " << endl << endl;

    cout << "Enter Your Username To Save Changes to Your Log : ";

    string name;

    cin >> name;

    name += ".txt";

    ifstream file(name);

    string word;

    vector<string> info;

    ll temp = 0;

    //Read file until reach end of file
    while(file >> word)
    {
        temp++;

        info.push_back(word);
    }


    ofstream file2(name);

    //Write the existing information back to the file  
    for(auto i : info)
        file2 << i << ' ';

    file2 << "### Land :: ";

    //Append the new land route information to the file
    for(auto i : path)
        file2 << mapping[i] << "-> ";
    
    file2 << "Distance " << distanceTotal << " KiloMeters ";

    file2 << "### " << endl << endl;

    pause;

    clear;
}

//Function to create air transportation network
void createAirMap()
{
    Air.assign(2e5 + 1, vector<pair<ll, ll>> ());

    ifstream file("air.txt"); //Open file for read operation using input filestream

    string word;

    vector<string> info;  //Vector to store words from the file

    ll temp = 0;

    while(file >> word)  //Extract word from file until reach end of file
    {
        temp++;

        info.push_back(word);

        if(temp % 4 == 0)    //Add newline once 4 words are added into info vector
            info.push_back("\n");
    }

    for(ll x = 0 ; x < info.size() ; x += 5)
    {
        ll encrypt1 = Encrypt(info[x + 1]);  //Encrypted city 1
        ll encrypt2 = Encrypt(info[x + 2]);  //Encryoted city 2

        mapping[encrypt1] = info[x + 1];  //Map Encrypted value to its corresponding city 1
        mapping[encrypt2] = info[x + 2];  //Map Encrypted value to its corresponding city 2

        Air[encrypt1].push_back(make_pair(encrypt2, stoi(info[x + 3])));  //Path from Encrypted city 1 to city 2 and distance between them
        Air[encrypt2].push_back(make_pair(encrypt1, stoi(info[x + 3])));  //Path from Encrypted city 2 to city 1 and distance between them
    } 
}

//Function to print Air transportation Network
void PrintAirMap()
{
    createAirMap();
        
    cout << endl << endl;

    //Loop through all the elements in Air Vector
    for(ll x = 0 ; x < 2e5 + 1 ; x++)
    {
        if(Air[x].empty())  //If no connection for city, skip it
            continue;   

        cout << "Cities Connected With : " << mapping[x] << " : - \n\n";

        //Loop through connections of city and print them
        for(auto i : Air[x])
            cout << mapping[i.first] << " : " << i.second << " KiloMeters." << endl;
        cout << endl;
    }

    cout << endl;

    pause;

    clear;
}

//Function to edit Air Network
void EditAirMap()
{
    createAirMap();

    string city1, city2;

    ll distance;

    cout << "\nEnter Name Of Cities which are to be connected : ";

    cin >> city1 >> city2;

    cout << "Enter Distance : ";

    cin >> distance;

    ifstream file("air.txt");  //Read file

    string word;

    vector<string> info;

    ll temp = 0;

    while(file >> word)  //Loop until end of the file
    {
        temp++;

        info.push_back(word);

        if(temp % 4 == 0)
            info.push_back("\n");
    }


    ofstream file2("air.txt");  //Open file for write operation

    for(auto i : info)
        file2 << i << ' ';

    file2 << "$ " << city1 << ' ' << city2 << ' ' << distance << "\n"; //Append city1, city2 and distance into file
}

//Function to find shortest distance and path route between two cities
void AirRoute()
{
    createAirMap();
    
    string start, destination;

    cout << "\nEnter The Start & End Point : ";

    cin >> start >> destination;

    queue<ll> q;  //Queue for bfs

    vector<bool> vis; //Vector to mark visited nodes

    vector<ll> lvl, predecessor;  //Vectors to store level and predecessor information for nodes

    vis.assign(200001,false);

    lvl.assign(200001,0);

    predecessor.assign(200001,0);

    ll root = Encrypt(start);  //convert start point to its corresponding numeric value

    q.push(root);

    vis[root] = true;

    //Perform bfs until queue is empty
    while(!q.empty())
    {
        ll current = q.front();

        q.pop();

        vis[current] = true;

        //Iterate over the neighbours of the current node in the 'Air' adjacency list
        for(auto neighbour : Air[current])
            if(!vis[neighbour.first])
            {
                lvl[neighbour.first] = 1 + lvl[current]; //Update the level of the neighbor to be one more than the current node's level

                q.push(neighbour.first);  //Add the neighbor to the queue for further exploration

                predecessor[neighbour.first] = current;  //Set the predecessor of the neighbor to be the current node
                
                vis[neighbour.first] = true;  //Mark the neighbor as visited
            }
    }

        ll endd = Encrypt(destination);  //convert end point to its corresponding numeric value
    
    cout << endl << "Shortest Distance Between " << start << " & " << destination << " covers : " << lvl[endd] + 1 << " Locations. " << endl << endl;

    vector <ll> path;  //Vector to store shortest path from start to end points

    path.push_back(endd);  //Push end point to path vector

    //Trace back the shortest path using predecessors
    while(predecessor[endd])
    {
        path.push_back(predecessor[endd]);
        endd = predecessor[endd];
    }

    reverse(path.begin(), path.end());  //Reverse the path vector

    //Output the shortest path
    for(ll x = 0 ; x < path.size() ; x++)
        cout << x + 1 << ". " << mapping[path[x]] << endl << endl;        

    ll distanceTotal = 0;

    //Calculate the total distance covered in the shortest path
    for(ll x = 0 ; x < path.size() - 1 ; x++)
        for(auto i : Air[path[x]])
            if(i.first == path[x + 1])
            {
                distanceTotal += i.second;
                break;
            }

    cout << "\nTotal Distance Covered : " << distanceTotal << " KiloMeters. " << endl << endl;

    cout << "Enter Your Username To Save Changes to Your Log : ";

    string name;

    cin >> name;

    name += ".txt";

    ifstream file(name);  //Open file

    string word;

    vector<string> info;

    ll temp = 0;
    
    //Read file until end of file
    while(file >> word)
    {
        temp++;

        info.push_back(word);
    }


    ofstream file2(name);  //Open for write operation

    for(auto i : info)
        file2 << i << ' ';

    file2 << "### Air :: ";

    //Append the new Air route information to the file
    for(auto i : path)
        file2 << mapping[i] << "-> ";
    
    file2 << "Distance " << distanceTotal << " KiloMeters ";

    file2 << "### " << endl << endl;

    pause;

    clear;
}

bool ReadCredentials(string n, string p);

void TravelLog()
{
    string name, password;

    cout << "\n\nEnter The Name Of the User : ";

    cin >> name;

    cout << "\nEnter Password : ";

    cin >> password;

    if(!ReadCredentials(name, password))
    {
        cout << "Sorry! Invalid Credentials...";

        pause;

        clear;
    }

    else
    {
        cout << "\nPrinting Travel History :- \n\n";

        string filename = name;

        filename += ".txt";

        ifstream file(filename);

        string word;

        vector<string> info;

        ll temp = 0;

        while(file >> word)
        {
            temp++;

            info.push_back(word);
        }

        for(auto i : info)
        {            
            cout << i << ' ';

            if(i.find('#') != string :: npos)
                cout << endl << endl;
        }
    }
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

        fstream file;

        string filename = username;

        filename += ".txt";

        file.open(filename, ios :: out);

        file.close();

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
