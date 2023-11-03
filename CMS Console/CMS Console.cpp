// CMS Console.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include "Clinic.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <filesystem>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
void Menu() {
    cout << endl << endl;
    cout << "============================================= " << endl;
    cout << "Hi, which of the following you need to do: " << endl;
    cout << "1. Add Patient Information. " << endl;
    cout << "2. View Patient Information. " << endl;
    cout << "3. Mark Patient as Treated. " << endl;
    cout << "4. Remove Patient Information. " << endl;
    cout << "5. Close the Application! " << endl;
    cout << "============================================= " << endl;
    cout << "Insert one input (1, 2, 3, 4, or 5): ";
}
void SelectionFn(int Selection) {
    Clinic Patient;
    int PID;
    switch (Selection) {
    case 1:
        cout << endl << "Kindly insert your Patient Information: " << endl;
        Patient.AddPatient();
        cout << endl << " << A new Patient has been recorded >> " << endl;
        break;
    case 2:
        cout << endl << "Please enter Patient ID you need to display: ";
        cin >> PID;
        Patient.ViewPatient(PID);
        break;
    case 3:
        cout << endl << "Please enter Patient ID you need to Mark it as Completed: ";
        cin >> PID;
        Patient.MarkPatient(PID);
        break;
    case 4:
        cout << endl << "Please enter Patient ID you need to Delete it: ";
        cin >> PID;
        Patient.RemovePatient(PID);
        break;
    case 5:
        cout << endl << "*************************************************************** " << endl;
        cout << "Thank you for using our Clinic System (^_^), See you soon. Good Bye! ";
        cout << endl << "*************************************************************** " << endl;
        exit(0);
    }
}

int main()
{
    int Selection;
    cout << "Welcome in our Clinical Management System (CMS) " << endl;
    cout << "*********************************************** ";

    while (1) {
        Menu();
        cin >> Selection;
        SelectionFn(Selection);
    }

    return 0;
}
