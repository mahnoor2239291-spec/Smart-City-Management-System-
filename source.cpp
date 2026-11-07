#include <iostream>
#include <queue>
#include <cstdlib>
#include<string>
#include <vector>
#include <cctype>

using namespace std;

void title()
{
    cout << "\n";
    cout << "=============================================================\n";
    cout << "||                                                         ||\n";
    cout << "||          SMART CITY MANAGEMENT SYSTEM                   ||\n";
    cout << "||                                                         ||\n";
    cout << "=============================================================\n";
    cout << "           Welcome to Smart City Management System\n";
    cout << "=============================================================\n\n";
}
string username = "admin";
string password = "1234";
bool isLoggedIn = false;
void loginScreen()
{
    string u, p;

    while (true)
    {
        system("cls");
        title();

        cout << "Username : ";
        cin >> u;

        cout << "Password : ";
        cin >> p;

        if (u == username && p == password)
        {
            isLoggedIn = true;

            cout << "\nLogin Successful.\n";

            system("pause");
            system("cls");
            break;
        }
        else
        {
            cout << "\nInvalid Username or Password.\n";

            system("pause");
        }
    }
}





void settingsMenu()
{
    int choice;

    do
    {
        system("cls");

        cout << "==============================\n";
        cout << "       SETTINGS MENU\n";
        cout << "==============================\n\n";

        
        cout << "1. Change Password\n";
        cout << "2. Logout\n";
        cout << "3. Back\n\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)

        {
        case 1:

            if (isLoggedIn)
            {
                string oldPass, newPass;

                cout << "Old Password : ";
                cin >> oldPass;

                if (oldPass == password)
                {
                    cout << "New Password : ";
                    cin >> newPass;

                    password = newPass;

                    cout << "\nPassword Changed Successfully.\n";
                }
                else
                {
                    cout << "\nWrong Password.\n";
                }
            }
            else
            {
                cout << "\nPlease Login First.\n";
            }

            system("pause");

            break;


        case 2:

            isLoggedIn = false;

            cout << "\nLogout Successful.\n";

            system("pause");

            loginScreen();

            break;

        case 3:

            break;
        default:
            cout << "\nInvalid Choice!";
            system("pause");
        }

    } while (choice != 3);

}
struct Area
{
    string name;
    int garbageLevel;
    int population;
    int complaints;
    int days;
    int priority;

    bool operator<(const Area& other) const
    {
        return priority < other.priority;
    }
};

priority_queue<Area> garbageQueue;
void AddArea()
{
    Area a;

    cin.ignore();

    cout << "\nArea Name : ";
    getline(cin, a.name);

    cout << "Garbage Level (%) : ";
    cin >> a.garbageLevel;

    cout << "Population : ";
    cin >> a.population;

    cout << "Complaints : ";
    cin >> a.complaints;

    cout << "Days Since Last Collection : ";
    cin >> a.days;

    a.priority = (a.garbageLevel * 5)
        + (a.population / 100)
        + (a.complaints * 10)
        + (a.days * 8);

    garbageQueue.push(a);

    cout << "\nArea Added Successfully.\n";

    system("pause");
}
void DisplayAreas()
{
    if (garbageQueue.empty())
    {
        cout << "\nNo Areas Available.\n";
        system("pause");
        return;
    }

    priority_queue<Area> temp = garbageQueue;

    while (!temp.empty())
    {
        Area a = temp.top();

        cout << "\n====================\n";

        cout << "Area : " << a.name << endl;

        cout << "Priority : " << a.priority << endl;

        cout << "Garbage Level : " << a.garbageLevel <<"%" << endl;

        cout << "Population : " << a.population << endl;

        cout << "Complaints : " << a.complaints << endl;

        cout << "Days : " << a.days << endl;

        temp.pop();
    }

    system("pause");
}
void CollectGarbage()
{
    if (garbageQueue.empty())
    {
        cout << "\nNo Garbage Requests.\n";

        system("pause");

        return;
    }

    Area a = garbageQueue.top();

    garbageQueue.pop();

    cout << "\nGarbage Collected From : " << a.name << endl;

    system("pause");
}
void garbageMenu()
{
    int choice;

    do
    {
        system("cls");

        title();

        cout << "========== Garbage Management ==========\n";

        cout << "1. Add Area\n";

        cout << "2. Display Priority List\n";

        cout << "3. Collect Garbage\n";

        cout << "4. Back\n";

        cout << "\nEnter Choice : ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            AddArea();
            break;

        case 2:
            DisplayAreas();
            break;

        case 3:
            CollectGarbage();
            break;

        case 4:
            break;

        default:

            cout << "\nInvalid Choice";

            system("pause");
        }

    } while (choice != 4);
}
struct Citizen
{
    string name;
    string cnic;
    int age;
    string address;
    string phone;

    Citizen* next;
};

Citizen* head = NULL;
bool isValidName(string name)
{
    if (name.empty())
        return false;

    for (char ch : name)
    {
        if (!(isalpha(ch) || ch == ' '))
            return false;
    }

    return true;
}

bool isValidCNIC(string cnic)
{
    if (cnic.length() != 13)
        return false;

    for (char ch : cnic)
    {
        if (!isdigit(ch))
            return false;
    }

    return true;
}

string formatCNIC(string cnic)
{
    return cnic.substr(0, 5) + "-" +
        cnic.substr(5, 7) + "-" +
        cnic.substr(12, 1);
}

bool isValidPhone(string phone)
{
    if (phone.length() != 10)
        return false;

    for (char ch : phone)
    {
        if (!isdigit(ch))
            return false;
    }

    return true;
}

string formatPhone(string phone)
{
    return  phone;
}

bool CNICExists(string cnic)
{
    Citizen* temp = head;

    while (temp != NULL)
    {
        if (temp->cnic == formatCNIC(cnic))
            return true;

        temp = temp->next;
    }

    return false;
}
void AddCitizen()
{
    Citizen* newCitizen = new Citizen;

    cin.ignore();

    while (true)
    {
        cout << "\nEnter Name : ";
        getline(cin, newCitizen->name);

        if (isValidName(newCitizen->name))
            break;

        cout << "\nInvalid Name! Only alphabets are allowed.\n";
    }

    string cnicInput;

    while (true)
    {
        cout << "\nEnter CNIC : ";
        getline(cin, cnicInput);

        if (isValidCNIC(cnicInput))
        {
            if (CNICExists(cnicInput))
            {
                cout << "\nCitizen with this CNIC already exists.\n";
            }
            else
            {
                newCitizen->cnic = formatCNIC(cnicInput);
                break;
            }
        }
        else
        {
            cout << "\nInvalid CNIC!\n";
        }

        int option;

        cout << "\n1. Try Again";
        cout << "\n2. Exit to Citizen Menu";
        cout << "\nEnter Choice : ";
        cin >> option;
        cin.ignore();

        if (option == 2)
        {
            delete newCitizen;
            return;
        }
    }

    cout << "Enter Age : ";
    cin >> newCitizen->age;

    cin.ignore();

    cout << "Enter Address : ";
    getline(cin, newCitizen->address);

    string phoneInput;

    while (true)
    {
        cout << "Enter Phone Number : +92 ";
        getline(cin, phoneInput);

        if (isValidPhone(phoneInput))
        {
            newCitizen->phone = "+92 " + phoneInput;
            break;
        }

        cout << "\nInvalid Phone Number! Please enter exactly 10 digits.\n";

        int option;

        cout << "\n1. Try Again";
        cout << "\n2. Exit to Citizen Menu";
        cout << "\nEnter Choice : ";
        cin >> option;
        cin.ignore();

        if (option == 2)
        {
            delete newCitizen;
            return;
        }
    }

    newCitizen->next = NULL;

    if (head == NULL)
    {
        head = newCitizen;
    }
    else
    {
        Citizen* temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newCitizen;
    }

    cout << "\nCitizen Added Successfully.\n";

    system("pause");
}

void DisplayCitizens()
{
    if (head == NULL)
    {
        cout << "\nNo Citizen Found.\n";
        system("pause");
        return;
    }

    Citizen* temp = head;

    cout << "\n========== Citizen List ==========\n";

    while (temp != NULL)
    {
        cout << "\nName : " << temp->name << endl;
        cout << "CNIC : " << temp->cnic << endl;
        cout << "Age : " << temp->age << endl;
        cout << "Address : " << temp->address << endl;
        cout << "Phone : " << temp->phone << endl;

        cout << "-----------------------------\n";

        temp = temp->next;
    }

    system("pause");
}
void SearchCitizen()
{
    if (head == NULL)
    {
        cout << "\nNo Citizen Found.\n";
        system("pause");
        return;
    }

    string cnic;

    cin.ignore();

    cout << "\nEnter CNIC (13 digits): ";
    getline(cin, cnic);

    if (!isValidCNIC(cnic))
    {
        cout << "\nInvalid CNIC! Please enter exactly 13 digits.\n";
        system("pause");
        return;
    }

    cnic = formatCNIC(cnic);

    Citizen* temp = head;

    while (temp != NULL)
    {
        if (temp->cnic == cnic)
        {
            cout << "\nCitizen Found\n";

            cout << "Name : " << temp->name << endl;
            cout << "CNIC : " << temp->cnic << endl; 
            cout << "Age : " << temp->age << endl;
            cout << "Address : " << temp->address << endl;
            cout << "Phone : " << temp->phone << endl;

            system("pause");
            return;
        }

        temp = temp->next;
    }

    cout << "\nCitizen Not Found.\n";

    system("pause");
}

void DeleteCitizen()
{
    if (head == NULL)
    {
        cout << "\nNo Citizen Found.\n";
        system("pause");
        return;
    }

    string cnic;

    cin.ignore();

    cout << "\nEnter CNIC : ";
    getline(cin, cnic);
    if (!isValidCNIC(cnic))
    {
        cout << "\nInvalid CNIC! Please enter exactly 13 digits.\n";
        system("pause");
        return;
    }

    cnic = formatCNIC(cnic);
    cnic = formatCNIC(cnic);

    if (head->cnic == cnic)
    {
        Citizen* del = head;

        head = head->next;

        delete del;

        cout << "\nCitizen Deleted.\n";

        system("pause");

        return;
    }

    Citizen* temp = head;

    while (temp->next != NULL)
    {
        if (temp->next->cnic == cnic)
        {
            Citizen* del = temp->next;

            temp->next = del->next;

            delete del;

            cout << "\nCitizen Deleted.\n";

            system("pause");

            return;
        }

        temp = temp->next;
    }

    cout << "\nCitizen Not Found.\n";

    system("pause");
}

void UpdateCitizen()
{
    if (head == NULL)
    {
        cout << "\nNo Citizen Found.\n";
        system("pause");
        return;
    }

    string cnicInput;

    cin.ignore();

    cout << "\nEnter CNIC of Citizen to Update (13 digits): ";
    getline(cin, cnicInput);
    if (!isValidCNIC(cnicInput))
    {
        cout << "\nInvalid CNIC! Please enter exactly 13 digits.\n";
        system("pause");
        return;
    }

    string formattedCNIC = formatCNIC(cnicInput);

    

    Citizen* temp = head;

    while (temp != NULL)
    {
        if (temp->cnic == formattedCNIC)
        {
            while (true)
            {
                cout << "Enter New Name : ";
                getline(cin, temp->name);

                if (isValidName(temp->name))
                    break;

                cout << "\nInvalid Name!\n";
            }

            cout << "Enter New Age : ";
            cin >> temp->age;

            cin.ignore();

            cout << "Enter New Address : ";
            getline(cin, temp->address);

            string phoneInput;

            while (true)
            {
                cout << "Enter New Phone Number (10 digits): ";
                getline(cin, phoneInput);

                if (isValidPhone(phoneInput))
                {
                    temp->phone = formatPhone(phoneInput);
                    break;
                }

                cout << "\nInvalid Phone Number!\n";
            }

            cout << "\nCitizen Updated Successfully.\n";

            system("pause");
            return;
        }

        temp = temp->next;
    }

    cout << "\nCitizen Not Found.\n";

    system("pause");
}
void citizenMenu()
{
    int choice;

    do
    {
        system("cls");

        title();

        cout << "========== Citizen Data ==========\n\n";

        cout << "1. Add Citizen\n";
        cout << "2. Display Citizens\n";
        cout << "3. Search Citizen\n";
        cout << "4. Update Citizen\n";
        cout << "5. Delete Citizen\n";
        cout << "6. Back\n";

        cout << "Enter Choice : ";

        cin >> choice;
        switch (choice)
        {
        case 1:
            AddCitizen();
            break;

        case 2:
            DisplayCitizens();
            break;

        case 3:
            SearchCitizen();
            break;

        case 4:
            UpdateCitizen();
            break;

        case 5:
            DeleteCitizen();
            break;

        case 6:
            break;

        default:
            cout << "\nInvalid Choice";
            system("pause");
        }

        

    } while (choice != 6);
}

struct Emergency
{
    int id;
    string category;
    string name;
    string location;
    string contact;
};

queue<Emergency> emergencyQueue;

int emergencyID = 1;


void emergencyMenu()
{
    int choice;

    do
    {
        system("cls");
        title();

        cout << "========================================\n";
        cout << "       EMERGENCY SERVICES\n";
        cout << "========================================\n\n";

        cout << "1. Accident / Health\n";
        cout << "2. Fire Brigade\n";
        cout << "3. Police\n";
        cout << "4. View All Requests\n";
        cout << "5. Process Next Request\n";
        cout << "6. Back\n\n";

        cout << "Enter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Emergency e;

            e.id = emergencyID++;
            e.category = "Accident / Health";

            cin.ignore();

            do
            {
                cout << "\nPatient Name : ";
                getline(cin, e.name);

                if (!isValidName(e.name))
                    cout << "Invalid Name!\n";

            } while (!isValidName(e.name));

            cout << "Location : ";
            getline(cin, e.location);

            string phone;

            do
            {
                cout << "Contact Number (+92) : ";
                cin >> phone;

                if (!isValidPhone(phone))
                    cout << "Invalid Number! Enter 10 digits only.\n";

            } while (!isValidPhone(phone));

            e.contact = "+92" + phone;

            emergencyQueue.push(e);

            cout << "\nEmergency Registered Successfully.\n";
            cout << "Emergency ID : " << e.id << endl;

            system("pause");

            break;
        }
        case 2:
        {
            Emergency e;

            e.id = emergencyID++;
            e.category = "Fire Brigade";

            cin.ignore();

            do
            {
                cout << "\nPlace Name : ";
                getline(cin, e.name);

                if (!isValidName(e.name))
                    cout << "Invalid Place Name! Only alphabets are allowed.\n";

            } while (!isValidName(e.name));

            cout << "Location : ";
            getline(cin, e.location);

            string phone;

            do
            {
                cout << "Contact Number (+92) : ";
                cin >> phone;

                if (!isValidPhone(phone))
                    cout << "Invalid Number! Enter exactly 10 digits.\n";

            } while (!isValidPhone(phone));

            e.contact = "+92" + phone;

            emergencyQueue.push(e);

            cout << "\n=====================================\n";
            cout << " Fire Brigade Request Registered\n";
            cout << "=====================================\n";

            cout << "Emergency ID : " << e.id << endl;
            cout << "Category     : " << e.category << endl;
            cout << "Place Name   : " << e.name << endl;
            cout << "Location     : " << e.location << endl;
            cout << "Contact      : " << e.contact << endl;

            system("pause");

            break;
        }
        case 3:
        {
            Emergency e;

            e.id = emergencyID++;
            e.category = "Police";

            cin.ignore();

            do
            {
                cout << "\nComplainant Name : ";
                getline(cin, e.name);

                if (!isValidName(e.name))
                    cout << "Invalid Name! Only alphabets are allowed.\n";

            } while (!isValidName(e.name));

            cout << "Location : ";
            getline(cin, e.location);

            string phone;

            do
            {
                cout << "Contact Number (+92) : ";
                cin >> phone;

                if (!isValidPhone(phone))
                    cout << "Invalid Number! Enter exactly 10 digits.\n";

            } while (!isValidPhone(phone));

            e.contact = "+92" + phone;

            emergencyQueue.push(e);

            cout << "\n=====================================\n";
            cout << " Police Complaint Registered\n";
            cout << "=====================================\n";

            cout << "Emergency ID : " << e.id << endl;
            cout << "Category     : " << e.category << endl;
            cout << "Name         : " << e.name << endl;
            cout << "Location     : " << e.location << endl;
            cout << "Contact      : " << e.contact << endl;

            system("pause");

            break;
        }
        case 4:
        {
            if (emergencyQueue.empty())
            {
                cout << "\nNo Emergency Requests Found.\n";
            }
            else
            {
                queue<Emergency> temp = emergencyQueue;

                cout << "\n=========================================\n";
                cout << "       ALL EMERGENCY REQUESTS\n";
                cout << "=========================================\n";

                while (!temp.empty())
                {
                    Emergency e = temp.front();

                    cout << "\nEmergency ID : " << e.id << endl;
                    cout << "Category     : " << e.category << endl;

                    if (e.category == "Fire Brigade")
                        cout << "Place Name   : " << e.name << endl;
                    else
                        cout << "Name         : " << e.name << endl;

                    cout << "Location     : " << e.location << endl;
                    cout << "Contact      : " << e.contact << endl;

                    cout << "-----------------------------------------\n";

                    temp.pop();
                }
            }

            system("pause");
            break;
        }

        case 5:
        {
            if (emergencyQueue.empty())
            {
                cout << "\nNo Pending Emergency Requests.\n";
            }
            else
            {
                Emergency e = emergencyQueue.front();

                cout << "\n=========================================\n";
                cout << "      EMERGENCY PROCESSED\n";
                cout << "=========================================\n\n";

                cout << "Emergency ID : " << e.id << endl;
                cout << "Category     : " << e.category << endl;

                if (e.category == "Fire Brigade")
                    cout << "Place Name   : " << e.name << endl;
                else
                    cout << "Name         : " << e.name << endl;

                cout << "Location     : " << e.location << endl;
                cout << "Contact      : " << e.contact << endl;

                emergencyQueue.pop();

                cout << "\nStatus : Request Processed Successfully.\n";
            }

            system("pause");
            break;
        }

        case 6:

            break;

        default:

            cout << "\nInvalid Choice!";
            system("pause");
        }

    } while (choice != 6);
}
struct Parking
{
    int bookingID;
    string area;
    string parkingPlace;
    string slotNumber;
    string ownerName;
    string vehicleNumber;
    string vehicleType;
};

vector<Parking> parkingList;

int bookingID = 1;
bool isValidVehicle(string vehicle)
{
    if (vehicle.empty())
        return false;

    for (char ch : vehicle)
    {
        if (!(isalnum(ch) || ch == '-'))
            return false;
    }

    return true;
}
void parkingMenu()
{
    int choice;

    do
    {
        system("cls");
        title();

        cout << "=========================================\n";
        cout << "     PARKING SLOT MANAGEMENT\n";
        cout << "=========================================\n\n";

        cout << "1. Book Parking Slot\n";
        cout << "2. View Booked Slots\n";
        cout << "3. Search Booking\n";
        cout << "4. Cancel Booking\n";
        cout << "5. Back\n\n";

        cout << "Enter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Parking p;

            p.bookingID = bookingID++;

            int areaChoice, parkingChoice, vehicleChoice;

            //--------------- Area ----------------

            cout << "\nSelect Area\n";
            cout << "1. Johar Town\n";
            cout << "2. DHA\n";
            cout << "3. Gulberg\n";
            cout << "4. Model Town\n";

            cout << "\nEnter Choice : ";
            cin >> areaChoice;

            switch (areaChoice)
            {
            case 1:

                p.area = "Johar Town";

                cout << "\nParking Places\n";
                cout << "1. Emporium Mall\n";
                cout << "2. Expo Center\n";
                cout << "3. UMT\n";

                cin >> parkingChoice;

                if (parkingChoice == 1)
                    p.parkingPlace = "Emporium Mall";

                else if (parkingChoice == 2)
                    p.parkingPlace = "Expo Center";

                else
                    p.parkingPlace = "UMT";

                break;

            case 2:

                p.area = "DHA";

                cout << "\nParking Places\n";
                cout << "1. Packages Mall\n";
                cout << "2. Raya\n";
                cout << "3. DHA Market\n";

                cin >> parkingChoice;

                if (parkingChoice == 1)
                    p.parkingPlace = "Packages Mall";

                else if (parkingChoice == 2)
                    p.parkingPlace = "Raya";

                else
                    p.parkingPlace = "DHA Market";

                break;

            case 3:

                p.area = "Gulberg";

                cout << "\nParking Places\n";
                cout << "1. Liberty Market\n";
                cout << "2. Hafeez Center\n";
                cout << "3. MM Alam\n";

                cin >> parkingChoice;

                if (parkingChoice == 1)
                    p.parkingPlace = "Liberty Market";

                else if (parkingChoice == 2)
                    p.parkingPlace = "Hafeez Center";

                else
                    p.parkingPlace = "MM Alam";

                break;

            case 4:

                p.area = "Model Town";

                cout << "\nParking Places\n";
                cout << "1. Model Town Park\n";
                cout << "2. Commercial Market\n";
                cout << "3. Bank Square\n";

                cin >> parkingChoice;

                if (parkingChoice == 1)
                    p.parkingPlace = "Model Town Park";

                else if (parkingChoice == 2)
                    p.parkingPlace = "Commercial Market";

                else
                    p.parkingPlace = "Bank Square";

                break;

            default:

                cout << "\nInvalid Area!\n";
                system("pause");
                break;
            }

            cout << "\nVehicle Type\n";
            cout << "1. Car\n";
            cout << "2. Bike\n";
            cout << "3. Van\n";

            cout << "\nEnter Choice : ";
            cin >> vehicleChoice;

            if (vehicleChoice == 1)
                p.vehicleType = "Car";

            else if (vehicleChoice == 2)
                p.vehicleType = "Bike";

            else
                p.vehicleType = "Van";

            cin.ignore();
            cout << "\n=========================================\n";
            cout << "        AVAILABLE SLOTS\n";
            cout << "=========================================\n";

            if (p.vehicleType == "Car")
            {
                cout << "C101  C102  C103  C104  C105\n";
            }
            else if (p.vehicleType == "Bike")
            {
                cout << "B101  B102  B103  B104  B105\n";
            }
            else
            {
                cout << "V101  V102  V103\n";
            }

            do
            {
                cout << "\nOwner Name : ";
                getline(cin, p.ownerName);

                if (!isValidName(p.ownerName))
                    cout << "Invalid Name!\n";

            } while (!isValidName(p.ownerName));

            do
            {
                cout << "Vehicle Number : ";
                getline(cin, p.vehicleNumber);

                if (!isValidVehicle(p.vehicleNumber))
                    cout << "Invalid Vehicle Number!\n";

            } while (!isValidVehicle(p.vehicleNumber));

            bool slotBooked;
            bool validSlot;

            do
            {
                slotBooked = false;
                validSlot = false;

                cout << "\nSelect Slot Number : ";
                getline(cin, p.slotNumber);

                // Valid slots according to vehicle type
                if (p.vehicleType == "Car")
                {
                    if (p.slotNumber == "C101" || p.slotNumber == "C102" ||
                        p.slotNumber == "C103" || p.slotNumber == "C104" ||
                        p.slotNumber == "C105")
                        validSlot = true;
                }
                else if (p.vehicleType == "Bike")
                {
                    if (p.slotNumber == "B101" || p.slotNumber == "B102" ||
                        p.slotNumber == "B103" || p.slotNumber == "B104" ||
                        p.slotNumber == "B105")
                        validSlot = true;
                }
                else if (p.vehicleType == "Van")
                {
                    if (p.slotNumber == "V101" || p.slotNumber == "V102" ||
                        p.slotNumber == "V103")
                        validSlot = true;
                }

                if (!validSlot)
                {
                    cout << "\nInvalid Slot Number! Please Select From Available Slots.\n";
                    continue;
                }

                for (int i = 0; i < parkingList.size(); i++)
                {
                    if (parkingList[i].area == p.area &&
                        parkingList[i].parkingPlace == p.parkingPlace &&
                        parkingList[i].vehicleType == p.vehicleType &&
                        parkingList[i].slotNumber == p.slotNumber)
                    {
                        slotBooked = true;

                        cout << "\n=========================================\n";
                        cout << " Slot Already Booked In This Parking!\n";
                        cout << " Please Select Another Slot.\n";
                        cout << "=========================================\n";

                        break;
                    }
                }

            } while (slotBooked || !validSlot);
            parkingList.push_back(p);

            cout << "\n=========================================\n";
            cout << " Parking Booked Successfully\n";
            cout << "=========================================\n";

            cout << "Booking ID     : " << p.bookingID << endl;
            cout << "Area           : " << p.area << endl;
            cout << "Parking Place  : " << p.parkingPlace << endl;
            cout << "Slot Number    : " << p.slotNumber << endl;
            cout << "Owner Name     : " << p.ownerName << endl;
            cout << "Vehicle Number : " << p.vehicleNumber << endl;
            cout << "Vehicle Type   : " << p.vehicleType << endl;

            system("pause");

            break;
        }

        case 2:
        {
            if (parkingList.empty())
            {
                cout << "\nNo Parking Slots Booked.\n";
            }
            else
            {
                cout << "\n==============================================================\n";
                cout << "                BOOKED PARKING SLOTS\n";
                cout << "==============================================================\n";

                for (int i = 0; i < parkingList.size(); i++)
                {
                    cout << "\nBooking ID     : " << parkingList[i].bookingID << endl;
                    cout << "Area           : " << parkingList[i].area << endl;
                    cout << "Parking Place  : " << parkingList[i].parkingPlace << endl;
                    cout << "Slot Number    : " << parkingList[i].slotNumber << endl;
                    cout << "Owner Name     : " << parkingList[i].ownerName << endl;
                    cout << "Vehicle Number : " << parkingList[i].vehicleNumber << endl;
                    cout << "Vehicle Type   : " << parkingList[i].vehicleType << endl;

                    cout << "--------------------------------------------------------------\n";
                }
            }

            system("pause");
            break;
        }

        case 3:
        {
            if (parkingList.empty())
            {
                cout << "\nNo Parking Bookings Available.\n";
            }
            else
            {
                string searchSlot;
                bool found = false;

                cout << "\nEnter Slot Number : ";
                cin >> searchSlot;

                for (int i = 0; i < parkingList.size(); i++)
                {
                    if (parkingList[i].slotNumber == searchSlot)
                    {
                        found = true;

                        cout << "\n=========================================\n";
                        cout << "        BOOKING FOUND\n";
                        cout << "=========================================\n";

                        cout << "Booking ID     : " << parkingList[i].bookingID << endl;
                        cout << "Area           : " << parkingList[i].area << endl;
                        cout << "Parking Place  : " << parkingList[i].parkingPlace << endl;
                        cout << "Slot Number    : " << parkingList[i].slotNumber << endl;
                        cout << "Owner Name     : " << parkingList[i].ownerName << endl;
                        cout << "Vehicle Number : " << parkingList[i].vehicleNumber << endl;
                        cout << "Vehicle Type   : " << parkingList[i].vehicleType << endl;

                        break;
                    }
                }

                if (!found)
                {
                    cout << "\nParking Slot Not Found.\n";
                }
            }

            system("pause");
            break;
        }

        case 4:
        {
            if (parkingList.empty())
            {
                cout << "\nNo Parking Bookings Available.\n";
            }
            else
            {
                string slot;
                bool found = false;

                cout << "\nEnter Slot Number to Cancel Booking : ";
                cin >> slot;

                for (int i = 0; i < parkingList.size(); i++)
                {
                    if (parkingList[i].slotNumber == slot)
                    {
                        found = true;

                        parkingList.erase(parkingList.begin() + i);

                        cout << "\n=========================================\n";
                        cout << " Booking Cancelled Successfully\n";
                        cout << "=========================================\n";

                        break;
                    }
                }

                if (!found)
                {
                    cout << "\nParking Slot Not Found.\n";
                }
            }

            system("pause");
            break;
        }

        case 5:
            break;

        default:
            cout << "\nInvalid Choice!";
            system("pause");
        }

    } while (choice != 5);
}




int main()
{
    int choice;
    loginScreen();

    do
    {
        system("cls");      // Screen Clear

        title();

        cout << "******************** MAIN MENU ********************\n\n";

        cout << "  1. Settings\n";
        cout << "  2. Garbage Management\n";
        cout << "  3. Citizen Data\n";
        cout << "  4. Emergency Services\n";
        cout << "  5. Parking  Management\n";
        cout << "  6. Exit\n\n";

        cout << "==================================================\n";
        cout << "Enter Your Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            settingsMenu();
            break;

        case 2:
            garbageMenu();
            break;

        case 3:
            citizenMenu();
            break;


                  
        case 4:
            emergencyMenu();
            break;

        case 5:
            parkingMenu();
            break;

                    case 6:
                        cout << "\n========================================\n";
                        cout << " Thank You For Using Smart City\n";
                        cout << "========================================\n";
                        break;

                    default:
                        cout << "\nInvalid Choice!";
                        system("pause");
                    }

                } while (choice != 6);

                return 0;
            }
            