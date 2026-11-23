#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

//=============main void==========

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string toLowerCase(string text) {
    for (int i = 0; i < text.length(); i++) {
        text[i] = tolower(text[i]);
    }
    return text;
}

bool searchByName(string actualName, string searchName) {

    actualName = toLowerCase(actualName);
    searchName = toLowerCase(searchName);

    if (actualName == searchName ||
        actualName.substr(0, actualName.find(' ')) == searchName) {
        return true;
        }

    return false;
}

//===================classes==================

class Patient {
    private:
    string name;
    int age;
   string phone;
    vector<string> assignDoctor;
public:
    Patient(string n, int a,string p) {
        name = n;
        age = a;
        phone=p;
    }
    string getName() {
        return name;
    }
    int getAge() {
        return age;
    }
    string getPhone() {
        return phone;
    }
    vector<string> getAssignDoctor() {
        return assignDoctor;
    }
    void addDoctor(string nameDoctor) {
        assignDoctor.push_back(nameDoctor);
    }
    void displayPatient() {
        setColor(10);
        cout << "Patient name: " << name << endl;
        cout << "Patient age: " << age << endl;
        cout << "Patient phone: " << phone << endl;
        setColor(13);
        cout<<"Names of registered doctors:"<<endl;
        setColor(14);
        if (assignDoctor.empty()) {
            setColor(12);
            cout << "Does not assigned" << endl;
        }
        else {
            setColor(13);
            for (int i = 0; i < assignDoctor.size(); i++) {
                cout << i + 1 << "-Dr. " << assignDoctor[i] << endl;
            }
        }setColor(7);
    }

    bool hasDoctor(string nameDoctor) {
        for (int i = 0; i < assignDoctor.size(); i++) {
            if (searchByName(assignDoctor[i], nameDoctor)) {
                return true;
            }
        }
        return false;
    }
};
class Doctor {
    private:
    string name;
    string specialty;
    vector<string> assignPatients;
    public:
    Doctor(string n, string a) {
        name = n;
        specialty = a;
    }
   string getName() {
        return name;
    }
    string getSpecialty() {
        return specialty;
    }
    vector<string> getAssignPatients() {
        return assignPatients;
    }

    void addPatient(string namePatient) {
        assignPatients.push_back(namePatient);
    }
    void displayDoctors() {
        setColor(10);
        cout << "Doctor name: " << name << endl;
        cout<<"Doctor specialty: "<< specialty << endl;
        setColor(13);
        cout<<"Names of registered patients:"<<endl;
        setColor(14);
        if (assignPatients.empty()) {
            setColor(12);
            cout << "No registered patients." << endl;
            setColor(7);
        }
        else {
            for (int i = 0; i < assignPatients.size(); i++) {
                cout << i + 1 << ". " << assignPatients[i] << endl;
            }setColor(7);
        }
    }
};

//===================patient function===============


void addPatient(vector<Patient>& patients) {
    string name;
    int age;
    string phone;
    bool found;
    clearInput();

    // إدخال اسم المريض والتأكد إنه مش متكرر
    do {
        found = false;

        cout << "Enter patient name: ";
        getline(cin, name);

        for (int i = 0; i < patients.size(); i++) {
            if (searchByName(patients[i].getName(), name)) {
                found = true;
                setColor(12);
                cout << "The name already exists." << endl;
                setColor(7);
                break;
            }
        }

    } while (found == true);

        cout << "Enter patient age: ";
        cin >> age;

    // إدخال رقم التليفون والتأكد إنه مش متكرر
    do {
        found = false;

        cout << "Enter patient phone: ";
        cin >> phone;

        for (int i = 0; i < patients.size(); i++) {
            if (patients[i].getPhone() == phone) {
                found = true;
                setColor(12);
                cout << "The phone already exists." << endl;
                setColor(7);
                break;
            }
        }

    } while (found == true);

    // إضافة المريض بعد التأكد من البيانات
    patients.push_back(Patient(name, age, phone));

    setColor(10);
    cout << "Patient " << name << " added." << endl;
    setColor(7);
}

void assignDoctor(vector<Patient>& patients, vector<Doctor>& doctors) {
    string namePatient;
    string nameDoctor;
    bool found = false;
    int patientIndex = -1;

    cout << "Enter Patient name: ";
    clearInput();
    getline(cin, namePatient);

    // التأكد من وجود المريض
    for (int i = 0; i < patients.size(); i++) {
        if (searchByName(patients[i].getName(), namePatient)) {
            found = true;
            patientIndex = i;
            break;
        }
    }

    if (found == false) {
        setColor(12);
        cout << namePatient << " is not a patient." << endl;
        setColor(7);
        return;
    }

    cout << "Enter doctor name: ";
    getline(cin, nameDoctor);

    found = false;

    // البحث عن الدكتور
    for (int i = 0; i < doctors.size(); i++) {
        if (searchByName(doctors[i].getName(), nameDoctor)) {
            if (patients[patientIndex].hasDoctor(doctors[i].getName())) {
                setColor(12);
                cout << "This doctor is already assigned to this patient." << endl;
                setColor(7);
                return;
            }

            found = true;
            patients[patientIndex].addDoctor(doctors[i].getName());
            doctors[i].addPatient(patients[patientIndex].getName());


            setColor(10);
            cout << namePatient << " assigned to Dr. "
                 << doctors[i].getName() << endl;
            setColor(7);

            break;
        }
    }

    // التأكد من العثور على الدكتور
    if (found == false) {
        setColor(12);
        cout << "Dr. " << nameDoctor << " is not present." << endl;
        setColor(7);
    }
}


void searchPatients(vector<Patient>& patients) {
    string namePatient;
    string phone;
    bool found = false;

    if (patients.empty()) {
        cout << "No patients available." << endl;
        return;
    }

    cout << "Enter Patient name: ";
    clearInput();
    getline(cin, namePatient);

    // البحث بالاسم
    for (int i = 0; i < patients.size(); i++) {
        if (searchByName(patients[i].getName(), namePatient)) {
            found = true;
            patients[i].displayPatient();
            break;
        }
    }

    // لو الاسم مش موجود، نبحث برقم التليفون
    if (found == false) {
        cout << namePatient << " is not a patient." << endl;

        cout << "Enter Patient phone: ";
        cin >> phone;

        for (int i = 0; i < patients.size(); i++) {
            if (patients[i].getPhone() == phone) {
                found = true;
                patients[i].displayPatient();
                break;
            }
        }
    }

    if (found == false) {
        setColor(12);
        cout << "Patient not found by name or phone." << endl;
        setColor(7);
    }
}


void displayAllPatient(vector<Patient>& patients) {

    if (patients.empty()) {
        setColor(12);
        cout << "No patients added." << endl;
        setColor(7);
        return;
    }

    for (int i = 0; i < patients.size(); i++) {
        cout << i + 1 << ". Patient:" << endl;
        patients[i].displayPatient();
        cout << "================" << endl;
    }setColor(7);
}

//===================doctor function===============

void addDoctor(vector<Doctor>& doctors) {
    string name;
    string specialty;
    bool found;
    clearInput();

    // إدخال اسم الدكتور والتأكد إنه مش متكرر
    do {
        found = false;

        cout << "Enter doctor name: ";
        getline(cin, name);

        for (int i = 0; i < doctors.size(); i++) {
            if (searchByName(doctors[i].getName(), name)) {
                found = true;
                setColor(12);
                cout << "The name already exists." << endl;
                setColor(7);
                break;
            }
        }

    } while (found == true);

    // إدخال التخصص
    cout << "Enter doctor's specialty: ";
    getline(cin, specialty);

    // إضافة الدكتور
    doctors.push_back(Doctor(name, specialty));

    setColor(10);
    cout << "Dr. " << name << " added." << endl;
    setColor(7);
}


void searchDoctors(vector<Doctor>& doctors) {
    string nameDoctor;
    string specialty;
    bool found = false;

    if (doctors.empty()) {
        cout << "No doctors available." << endl;
        return;
    }

    cout << "Enter doctor name: ";
    clearInput();
    getline(cin, nameDoctor);

    // البحث بالاسم
    for (int i = 0; i < doctors.size(); i++) {
        if (searchByName(doctors[i].getName(), nameDoctor)) {
            found = true;
            doctors[i].displayDoctors();
            break;
        }
    }

    // لو الاسم مش موجود، نبحث بالتخصص
    if (found == false) {
        cout << "Doctor name not found!" << endl;

        cout << "Enter doctor's specialty: ";
        getline(cin, specialty);

        for (int i = 0; i < doctors.size(); i++) {
            if (searchByName(doctors[i].getSpecialty(), specialty)) {
                doctors[i].displayDoctors();
                found = true;
            }
        }

        if (found == false) {
            setColor(12);
            cout << "No doctor found with this specialty." << endl;
            setColor(7);
        }
    }
}


void desplyAllDoctors(vector<Doctor>& doctors) {
    if (doctors.empty()) {
        setColor(12);
        cout << "No doctors added." << endl;
        setColor(7);
        return;
    }
    for (int i = 0; i < doctors.size(); i++) {
        cout<<i+1<<".Dr: "<<endl;
      doctors[i].displayDoctors();
        cout<<"================ "<<endl;
    }
}

int print() {
    int choice;

    cout << "\nChoose an option: ";
    cin >> choice;

    return choice;
}

int main() {
    vector<Patient> patients;
    vector<Doctor> doctors;

    int choice;

    do {
        cout << "\n=== Hospital System ===" << endl;
        cout << "1. Patient" << endl;
        cout << "2. Doctor" << endl;
        cout << "3. Exit" << endl;

        choice = print();

        if (choice == 1) {
            do {
                cout << "\n=== Patient Menu ===" << endl;
                cout << "1.  Add Patient" << endl;
                cout << "2. Assign Doctor" << endl;
                cout << "3. Search Patient" << endl;
                cout << "4.  Display All Patients" << endl;
                cout << "5. Back to Main Menu" << endl;

                choice = print();

                if (choice == 1) {
                    addPatient(patients);
                }
                else if (choice == 2) {
                    assignDoctor(patients, doctors);
                }
                else if (choice == 3) {
                  searchPatients(patients);
                }
                else if (choice == 4) {
                   displayAllPatient(patients);
                }
                else if (choice != 5) {
                    setColor(12);
                    cout << "Error! Please choose an option from 1 to 5." << endl;
                    setColor(7);
                }

            } while (choice != 5);
        }

        else if (choice == 2) {
            do {
                cout << "\n=== Doctor Menu ===" << endl;
                cout << "1. Add doctor" << endl;
                cout << "2. Search doctor" << endl;
                cout << "3. Display All doctors" << endl;
                cout << "4. Back to Main Menu" << endl;

                choice = print();

                if (choice == 1) {
                    addDoctor(doctors);
                }
                else if (choice == 2) {
                    searchDoctors(doctors);
                }
                else if (choice == 3) {
                    desplyAllDoctors(doctors);
                }
                else if (choice != 4) {
                    setColor(12);
                    cout << "Error! Please choose an option from 1 to 4." << endl;
                    setColor(7);
                }

            } while (choice != 4);
        }

        else if (choice != 3) {
            setColor(12);
            cout << "Error! Please choose an option from 1 to 3." << endl;
            setColor(7);
        }

    } while (choice != 3);

    setColor(10);
    cout << "Goodbye!" << endl;
    setColor(7);

    return 0;
}
