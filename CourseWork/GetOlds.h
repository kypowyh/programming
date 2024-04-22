#pragma once

namespace course {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для GetOlds
	/// </summary>
	public ref class GetOlds : public System::Windows::Forms::Form
	{
	public:
		GetOlds(void)
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
		~GetOlds()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ olds;
	protected:

	protected:
	private: System::Windows::Forms::Button^ button1;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(GetOlds::typeid));
			this->olds = (gcnew System::Windows::Forms::RichTextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// olds
			// 
			this->olds->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->olds->Location = System::Drawing::Point(12, 13);
			this->olds->Name = L"olds";
			this->olds->Size = System::Drawing::Size(376, 243);
			this->olds->TabIndex = 0;
			this->olds->Text = L"";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Gray;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(79, 262);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(251, 26);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Выход";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &GetOlds::button1_Click);
			// 
			// GetOlds
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(69)), static_cast<System::Int32>(static_cast<System::Byte>(69)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->BackgroundImage = nullptr;
			this->ClientSize = System::Drawing::Size(400, 300);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->olds);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"GetOlds";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"GetOlds";
			this->Load += gcnew System::EventHandler(this, &GetOlds::GetOlds_Load);
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void GetOlds_Load(System::Object^ sender, System::EventArgs^ e) {
		// Загружаем данные из файла
		Agency^ agency = ReadFromBinaryFile("FileName.bin");

		// Очищаем содержимое RichTextBox
		olds->Clear();

		// Проходим по всем домам в агентстве
		for each (House ^ house in agency->houses) {
			int maxAge = -1;  // Инициализируем переменную максимального возраста

			String^ oldestName;  // Переменная для хранения имени самого старого жильца

			// Проверяем каждого жильца в доме
			for each (Resident ^ resident in house->residents) {
				// Если возраст текущего жильца больше текущего максимального возраста
				if (resident->age > maxAge) {
					maxAge = resident->age;  // Обновляем максимальный возраст
					oldestName = resident->name;  // Обновляем имя самого старого жильца
				}
			}

			// Если у дома есть жильцы, добавляем информацию в RichTextBox
			if (maxAge != -1) {
				olds->Text += "Дом " + house->number + ": Самый старый житель - " + oldestName + ", возраст - " + maxAge + "\n";
			}
		}

	}
	};
}
