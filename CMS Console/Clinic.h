#pragma once
#ifndef CLINIC_H
#define CLINIC_H
#include <iostream>
#include <filesystem>
#include <stdio.h>

using namespace std;

// Allow users to input patient details they want to add to the system.
class Clinic
{
    // Accept inputs for patient (name, age, gender, and condition.)
private:
    int PatientID;
    string PatientName;
    int PatientAge;
    char PatientGender;
    string PatientCondition;
    bool PatientStatus = 0;
    int error;

    void CreateDirectory(const std::string& path);


public:
    void AddPatient();
    void ViewPatient(int PID);
    void MarkPatient(int PID);
    void RemovePatient(int PID);
};

#endif // CLINIC_H