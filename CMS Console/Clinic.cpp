#include "Clinic.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>

using namespace std;
int Clinic::setPatientID (){
    int ID =0;
    cin >> ID;
    this->PatientID=ID;
    return ID;
}
int Clinic::getPatientID (){
    return this->PatientID;
}

string Clinic::setPatientName(){
    string Name;
    getline(cin, Name);
    this->PatientName=Name;
    return Name;
}
string Clinic::getPatientName(){
    return this->PatientName;
}

 int Clinic::setPatientAge(){
        int Age;
        cin >> Age;
        this->PatientAge=Age;
        return Age;
 }
 int Clinic::getPatientAge(){
    return this->PatientAge;
 }

char Clinic::setPatientGender(){
    char Gender;
    cin >> Gender;
    this->PatientGender=Gender;
    cin.ignore(1, '\n');
    return Gender;
}
char Clinic::getPatientGender(){
    return this->PatientGender;
}

string Clinic::setPatientCondition(){
    string Condition;
    getline(cin, Condition);
    this->PatientCondition=Condition;
    return Condition;
}
string Clinic::getPatientCondition(){
    return this->PatientCondition;
}

bool Clinic::setPatientStatus(){
    bool Status=0;
    this->PatientStatus=Status;
    return Status;
}
bool Clinic::getPatientStatus(){
    return this->PatientStatus;
}

bool ValidateName(string Name) {
    return any_of(Name.begin(), Name.end(), ::isdigit);
}

void Clinic::CreateDirectory(const string& path) {
    filesystem::create_directory(path);
}

void Clinic::AddPatient() {

// Create the directory C:\CMSDatabase if it does not already exist.
    CreateDirectory("C:\\CMSDatabase");

// Enter Patient ID
    cout << "Patient ID: ";
    setPatientID();
    cin.ignore(1, '\n');

//File Handling
    string FileName = "C:\\CMSDatabase\\PatientInfoDB-" + to_string(getPatientID()) + ".txt";

    fstream File;
    File.open(FileName, ios::app);
    File << "Patient ID: " << getPatientID() << endl;

// Enter Patient Name
    do {
        cout << "Patient Name: ";

        if (ValidateName(setPatientName()) == true)
            cout << "Please enter a valid Patient Name. " << endl;

    } while (ValidateName(getPatientName()) == true);
    File << "Patient Name: " << getPatientName() << endl;

// Enter Patient Age
    do {
        error=0;
        cout << "Patient Age: ";
        setPatientAge();
        if (cin.fail() || getPatientAge() <= 0 || getPatientAge() >= 99) {
            cout << "Please enter a valid Patient Age. " << endl;
            error = 1;
            cin.clear();
            cin.ignore(256, '\n');
        }
    } while (error == 1);
    File << "Patient Age: " << getPatientAge() << endl;

// Enter Patient Gender
    do {
        error=0;
        cout << "Patient Gender (F/M): ";

        switch (setPatientGender())
        {
        case 'M':
        case 'm':
        case 'F':
        case 'f':
            break;
        default:
            cout << "Unspecified Gender, Kindly enter Patient Gender again (F/M)." << endl;
            error = 1;
            break;
        }
    } while (error == 1);
    File << "Patient Gender: " << getPatientGender() << endl;

    // Enter Patient Condition
    cout << "Patient Condition: ";
   setPatientCondition();
    File << "Patient Condition: " << getPatientCondition() << endl;

    setPatientStatus();
    File << "Patient Status: Untreated " << endl;

    File.close();
}

void Clinic::ViewPatient(int PID) {

    fstream readFile;
    string Line = "";
    string FilePath = "C:\\CMSDatabase\\PatientInfoDB-" + to_string(PID) + ".txt";

    readFile.open(FilePath, ios::in);
    if (readFile.fail())
        cout << "This Patient ID is not exist." << endl;
    else {
        while (!readFile.eof()) {
            getline(readFile, Line);
            cout << Line << endl;
        }
    }
    readFile.close();
}

void Clinic::MarkPatient(int PID) {

    int offset;
    string line = "";
    string SearchWord = "Untreated";
    string FilePath = "C:\\CMSDatabase\\PatientInfoDB-" + to_string(PID) + ".txt";
    string ReplaceFilePath = "C:\\CMSDatabase\\PatientInfoDB-" + to_string(PID) + "-Replaced.txt";

    fstream readFile;
    readFile.open(FilePath);

    fstream writeFile;
    writeFile.open(ReplaceFilePath, ios::app);

    if (readFile.fail())
        cout << "This Patient ID is not exist." << endl;
    else {
        while (!readFile.eof()) {
            getline(readFile, line);
            offset = line.find(SearchWord, 0);
            if (offset >= 0)
            {
                line = "Patient Status: Treated ";
                writeFile << line << endl;
                cout << endl << " << Patient has been marked as treated. >> " << endl;
            }
            else {
                writeFile << line << endl;
            }

        }
    }

    writeFile.close();
    readFile.close();
    filesystem::rename(ReplaceFilePath, FilePath);
    filesystem::remove(ReplaceFilePath);

}

void Clinic::RemovePatient(int PID) {

    string FileName = "PatientInfoDB-" + to_string(PID) + ".txt";
    string FilePath = "C:\\CMSDatabase\\" + FileName;

    if (filesystem::remove(FilePath.c_str()) == 1)
        cout << "Patient File has been deleted successfully";
    else
        cout << "Patient ID is not exist!";
}
