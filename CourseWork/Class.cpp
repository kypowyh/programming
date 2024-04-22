
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

		// Читаем количество домов в агентстве
		int numHouses = reader->ReadInt32();

		// Читаем информацию о каждом доме
		for (int i = 0; i < numHouses; i++) {
			House^ house = gcnew House();

			// Читаем номер дома и количество жильцов
			house->number = reader->ReadInt32();
			house->numResidents = reader->ReadInt32();

			// Читаем информацию о каждом жильце
			house->residents = gcnew List<Resident^>();
			for (int j = 0; j < house->numResidents; j++) {
				Resident^ resident = gcnew Resident();
				resident->name = reader->ReadString();
				resident->age = reader->ReadInt32();
				house->residents->Add(resident);
			}

			// Добавляем дом в список домов агентства
			agency->houses->Add(house);
		}

		reader->Close();
		//MessageBox::Show("Данные успешно загружены из бинарного файла.");
	}
	catch (Exception^ ex) {
		//MessageBox::Show("Ошибка при чтении из файла: " + ex->Message);
	}

	return agency;
}

void WriteToBinaryFile(String^ fileName, Agency^ agency) {
	// Используем BinaryWriter для записи данных в бинарный файл
	try {
		BinaryWriter^ writer = gcnew BinaryWriter(File::Open(fileName, FileMode::Create));

		// Записываем количество домов в агентстве
		writer->Write(agency->houses->Count);

		// Записываем информацию о каждом доме
		for (int i = 0; i < agency->houses->Count; i++) {
			House^ house = agency->houses[i];

			// Записываем номер дома и количество жильцов
			writer->Write(house->number);
			writer->Write(house->numResidents);

			// Записываем информацию о каждом жильце
			for (int j = 0; j < house->residents->Count; j++) {
				Resident^ resident = house->residents[j];
				writer->Write(resident->name);
				writer->Write(resident->age);
			}
		}

		writer->Close();
		//MessageBox::Show("Данные успешно сохранены в бинарный файл.");
	}
	catch (Exception^ ex) {
		//MessageBox::Show("Ошибка при записи в файл: " + ex->Message);
	}
}

