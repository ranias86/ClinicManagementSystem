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
    cin >> this->PatientID;
    cin.ignore(1, '\n');

    string FileName = "C:\\CMSDatabase\\PatientInfoDB-" + to_string(this->PatientID) + ".txt";

    fstream File;
    File.open(FileName, ios::app);
    File << "Patient ID: " << this->PatientID << endl;

    // Enter Patient Name
    do {
        cout << "Patient Name: ";
        getline(cin, this->PatientName);
        if (ValidateName(this->PatientName) == true)
            cout << "Please enter a valid Patient Name. " << endl;

    } while (ValidateName(this->PatientName) == true);
    File << "Patient Name: " << this->PatientName << endl;

    // Enter Patient Age
    do {
        error = 0;
        cout << "Patient Age: ";
        cin >> PatientAge;
        if (cin.fail() || this->PatientAge <= 0 || this->PatientAge >= 99) {
            cout << "Please enter a valid Patient Age. " << endl;
            error = 1;
            cin.clear();
            cin.ignore(256, '\n');
        }
    } while (error == 1);
    File << "Patient Age: " << this->PatientAge << endl;

    // Enter Patient Gender
    do {
        cout << "Patient Gender (F/M): ";
        cin >> PatientGender;

        switch (PatientGender)
        {
        case 'M':
        case 'm':
            error = 0;
            break;
        case 'F':
        case 'f':
            error = 0;
            break;
        default:
            cout << "Unspecified Gender, Kindly enter Patient Gender again (F/M)." << endl;
            error = 1;
        }
    } while (error == 1);
    File << "Patient Gender: " << this->PatientGender << endl;

    cin.ignore(1, '\n');
    // Enter Patient Condition
    cout << "Patient Condition: ";
    getline(cin, this->PatientCondition);
    File << "Patient Condition: " << this->PatientCondition << endl;

    this->PatientStatus = 0;
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
