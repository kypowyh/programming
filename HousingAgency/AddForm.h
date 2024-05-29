#pragma once

namespace course {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для AddForm
	/// </summary>
	public ref class AddForm : public System::Windows::Forms::Form
	{
	public:
		AddForm(void)
		{
			InitializeComponent();
			ShowInTaskbar = false;
			//
			//TODO: добавьте код конструктора
			//
		}

		String^ GetName() {
			return name->Text;
		}

		int GetAge() {
			return Convert::ToInt32(age->Text);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~AddForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ name;
	protected:
	private: System::Windows::Forms::TextBox^ age;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(AddForm::typeid));
			this->name = (gcnew System::Windows::Forms::TextBox());
			this->age = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// name
			// 
			this->name->BackColor = System::Drawing::Color::Gray;
			this->name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->name->ForeColor = System::Drawing::Color::White;
			this->name->Location = System::Drawing::Point(82, 65);
			this->name->Name = L"name";
			this->name->Size = System::Drawing::Size(220, 20);
			this->name->TabIndex = 0;
			// 
			// age
			// 
			this->age->BackColor = System::Drawing::Color::Gray;
			this->age->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->age->ForeColor = System::Drawing::Color::White;
			this->age->Location = System::Drawing::Point(79, 146);
			this->age->Name = L"age";
			this->age->Size = System::Drawing::Size(223, 20);
			this->age->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(79, 49);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(87, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Введите имя:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(79, 130);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(112, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Введите возраст:";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Gray;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(79, 197);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(99, 50);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Сохранить";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &AddForm::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Gray;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->ForeColor = System::Drawing::Color::White;
			this->button2->Location = System::Drawing::Point(200, 197);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(102, 50);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Выход";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &AddForm::button2_Click);
			// 
			// AddForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(69)), static_cast<System::Int32>(static_cast<System::Byte>(69)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->BackgroundImage = nullptr;
			this->ClientSize = System::Drawing::Size(400, 300);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->age);
			this->Controls->Add(this->name);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"AddForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"AddForm";
			this->Load += gcnew System::EventHandler(this, &AddForm::AddForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void AddForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ name = this->name->Text;

		int Age;
		if (!Int32::TryParse(age->Text, Age)) {

			MessageBox::Show("Пожалуйста, введите корректный возраст в виде числа.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;  
		}

		this->Close();
	}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();
}
};
}
