
#include "myclass.h"


String^ Password::hashPassword(String^ currentPassword) {
	array<unsigned char>^ data = Encoding::UTF8->GetBytes(currentPassword);
	SHA256Managed^ sha256 = gcnew SHA256Managed();
	array<unsigned char>^ hash = sha256->ComputeHash(data);

	StringBuilder^ stringBuilder = gcnew StringBuilder();
	for each (unsigned char byte in hash) {
		stringBuilder->Append(byte.ToString("x2"));
	}

	return stringBuilder->ToString();
}

bool Password::check(String^ currentPassword) {
	String^ InputPassword = hashPassword(currentPassword);
	String^ SavedPassword = hashPassword(password);
	return InputPassword->Equals(SavedPassword);
}

Agency^ ReadFromBinaryFile(String^ fileName) {
	Agency^ agency = gcnew Agency();

	try {
		BinaryReader^ reader = gcnew BinaryReader(File::Open(fileName, FileMode::Open));

		// ������ ���������� ����� � ���������
		int numHouses = reader->ReadInt32();

		// ������ ���������� � ������ ����
		for (int i = 0; i < numHouses; i++) {
			House^ house = gcnew House();

			// ������ ����� ���� � ���������� �������
			house->number = reader->ReadInt32();
			house->numResidents = reader->ReadInt32();

			// ������ ���������� � ������ ������
			house->residents = gcnew List<Resident^>();
			for (int j = 0; j < house->numResidents; j++) {
				Resident^ resident = gcnew Resident();
				resident->name = reader->ReadString();
				resident->age = reader->ReadInt32();
				house->residents->Add(resident);
			}

			// ��������� ��� � ������ ����� ���������
			agency->houses->Add(house);
		}

		reader->Close();
		//MessageBox::Show("������ ������� ��������� �� ��������� �����.");
	}
	catch (Exception^ ex) {
		//MessageBox::Show("������ ��� ������ �� �����: " + ex->Message);
	}

	return agency;
}

void WriteToBinaryFile(String^ fileName, Agency^ agency) {
	// ���������� BinaryWriter ��� ������ ������ � �������� ����
	try {
		BinaryWriter^ writer = gcnew BinaryWriter(File::Open(fileName, FileMode::Create));

		// ���������� ���������� ����� � ���������
		writer->Write(agency->houses->Count);

		// ���������� ���������� � ������ ����
		for (int i = 0; i < agency->houses->Count; i++) {
			House^ house = agency->houses[i];

			// ���������� ����� ���� � ���������� �������
			writer->Write(house->number);
			writer->Write(house->numResidents);

			// ���������� ���������� � ������ ������
			for (int j = 0; j < house->residents->Count; j++) {
				Resident^ resident = house->residents[j];
				writer->Write(resident->name);
				writer->Write(resident->age);
			}
		}

		writer->Close();
		//MessageBox::Show("������ ������� ��������� � �������� ����.");
	}
	catch (Exception^ ex) {
		//MessageBox::Show("������ ��� ������ � ����: " + ex->Message);
	}
}

