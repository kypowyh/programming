

#pragma once


using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Security::Cryptography;
using namespace System::Text;

public ref class Password {
public:
    String^ password = "123";
    String^ hashPassword(String^ currentPassword);
    bool check(String^ currentPassword);
};

public ref class Resident {
public:
    String^ name;
    int age;
};

public ref class House {
public:
    List<Resident^>^ residents;
    int number;
    int numResidents;

    House() {
        residents = gcnew List<Resident^>();
    }
};

public ref class Agency {
public:
    List<House^>^ houses;

    Agency() {
        houses = gcnew List<House^>();
    }
};

Agency^ ReadFromBinaryFile(String^ fileName);

void WriteToBinaryFile(String^ fileName, Agency^ agency);
