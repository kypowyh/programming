#pragma once

namespace course {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для DeleteForm
	/// </summary>
	public ref class DeleteForm : public System::Windows::Forms::Form
	{
	public:
		DeleteForm(void)
		{
			InitializeComponent();
			ShowInTaskbar = false;
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~DeleteForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ number;
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label1;

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(DeleteForm::typeid));
			this->number = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// number
			// 
			this->number->BackColor = System::Drawing::Color::Gray;
			this->number->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->number->ForeColor = System::Drawing::Color::White;
			this->number->Location = System::Drawing::Point(93, 112);
			this->number->Name = L"number";
			this->number->Size = System::Drawing::Size(195, 20);
			this->number->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Gray;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(93, 149);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(92, 34);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Удалить дом";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &DeleteForm::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Gray;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->ForeColor = System::Drawing::Color::White;
			this->button2->Location = System::Drawing::Point(211, 149);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(77, 34);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Выход";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &DeleteForm::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(61, 82);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(283, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Введите номер дома который хотите удалить:";
			// 
			// DeleteForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(69)), static_cast<System::Int32>(static_cast<System::Byte>(69)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->BackgroundImage = nullptr;
			this->ClientSize = System::Drawing::Size(400, 300);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->number);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"DeleteForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"DeleteForm";
			this->Load += gcnew System::EventHandler(this, &DeleteForm::DeleteForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Agency^ agency = ReadFromBinaryFile("FileName.bin");

		int houseNumber;
		if (!Int32::TryParse(number->Text, houseNumber) || houseNumber < 0) {
			MessageBox::Show("Пожалуйста, введите корректный положительный номер дома.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;  
		}

		// Находим индекс дома с заданным номером в списке домов
		int indexToRemove = -1;
		for (int i = 0; i < agency->houses->Count; i++) {
			if (agency->houses[i]->number == houseNumber) {
				indexToRemove = i;
				break;
			}
		}

		// Если дом с указанным номером найден, удаляем его
		if (indexToRemove != -1) {
			agency->houses->RemoveAt(indexToRemove);

			// Сохраняем изменения в файл
			WriteToBinaryFile("FileName.bin", agency);

			// Оповещаем пользователя об успешном удалении
			MessageBox::Show("Дом успешно удален.", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else {
			// Оповещаем пользователя о неудачном удалении
			MessageBox::Show("Дом с указанным номером не найден.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}

		this->Close();

	}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();

}
private: System::Void DeleteForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}
