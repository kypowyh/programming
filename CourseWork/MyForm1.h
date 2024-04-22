#pragma once
//#include "MyForm.h"
#include "EnterForm.h"
#include "myclass.h"
#include "UpdateForm.h"
#include "DeleteForm.h"
#include "GetData.h"
#include "GetOlds.h"
#include "GetMinors.h"


namespace course {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm1
	/// </summary>
	public ref class MyForm1 : public System::Windows::Forms::Form
	{
	public:
		MyForm1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm1()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::Button^ save;
	private: System::Windows::Forms::Button^ get;
	private: System::Windows::Forms::Button^ minors;
	private: System::Windows::Forms::Button^ olds;
	private: System::Windows::Forms::Button^ delet;

	private: System::Windows::Forms::Button^ update;
	private: System::Windows::Forms::Button^ exit;
	private: System::Windows::Forms::PictureBox^ pictureBox1;



	protected:

	protected:

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm1::typeid));
			this->save = (gcnew System::Windows::Forms::Button());
			this->get = (gcnew System::Windows::Forms::Button());
			this->minors = (gcnew System::Windows::Forms::Button());
			this->olds = (gcnew System::Windows::Forms::Button());
			this->delet = (gcnew System::Windows::Forms::Button());
			this->update = (gcnew System::Windows::Forms::Button());
			this->exit = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// save
			// 
			this->save->BackColor = System::Drawing::Color::Gray;
			this->save->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->save->ForeColor = System::Drawing::Color::White;
			this->save->Location = System::Drawing::Point(12, 210);
			this->save->Name = L"save";
			this->save->Size = System::Drawing::Size(129, 78);
			this->save->TabIndex = 1;
			this->save->Text = L"Добавить дом";
			this->save->UseVisualStyleBackColor = false;
			this->save->Click += gcnew System::EventHandler(this, &MyForm1::save_Click);
			// 
			// get
			// 
			this->get->BackColor = System::Drawing::Color::Gray;
			this->get->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->get->ForeColor = System::Drawing::Color::White;
			this->get->Location = System::Drawing::Point(12, 46);
			this->get->Name = L"get";
			this->get->Size = System::Drawing::Size(129, 79);
			this->get->TabIndex = 2;
			this->get->Text = L"Вывод данных";
			this->get->UseVisualStyleBackColor = false;
			this->get->Click += gcnew System::EventHandler(this, &MyForm1::get_Click);
			// 
			// minors
			// 
			this->minors->BackColor = System::Drawing::Color::Gray;
			this->minors->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->minors->ForeColor = System::Drawing::Color::White;
			this->minors->Location = System::Drawing::Point(559, 131);
			this->minors->Name = L"minors";
			this->minors->Size = System::Drawing::Size(129, 73);
			this->minors->TabIndex = 3;
			this->minors->Text = L"Данные о несовершеннолетних";
			this->minors->UseVisualStyleBackColor = false;
			this->minors->Click += gcnew System::EventHandler(this, &MyForm1::minors_Click);
			// 
			// olds
			// 
			this->olds->BackColor = System::Drawing::Color::Gray;
			this->olds->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->olds->ForeColor = System::Drawing::Color::White;
			this->olds->Location = System::Drawing::Point(559, 46);
			this->olds->Name = L"olds";
			this->olds->Size = System::Drawing::Size(129, 79);
			this->olds->TabIndex = 4;
			this->olds->Text = L"Старейшие жильцы";
			this->olds->UseVisualStyleBackColor = false;
			this->olds->Click += gcnew System::EventHandler(this, &MyForm1::olds_Click);
			// 
			// delet
			// 
			this->delet->BackColor = System::Drawing::Color::Gray;
			this->delet->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->delet->ForeColor = System::Drawing::Color::White;
			this->delet->Location = System::Drawing::Point(12, 131);
			this->delet->Name = L"delet";
			this->delet->Size = System::Drawing::Size(129, 73);
			this->delet->TabIndex = 5;
			this->delet->Text = L"Удалить данные о доме";
			this->delet->UseVisualStyleBackColor = false;
			this->delet->Click += gcnew System::EventHandler(this, &MyForm1::delet_Click);
			// 
			// update
			// 
			this->update->BackColor = System::Drawing::Color::Gray;
			this->update->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->update->ForeColor = System::Drawing::Color::White;
			this->update->Location = System::Drawing::Point(559, 210);
			this->update->Name = L"update";
			this->update->Size = System::Drawing::Size(129, 78);
			this->update->TabIndex = 6;
			this->update->Text = L"Обновить данные";
			this->update->UseVisualStyleBackColor = false;
			this->update->Click += gcnew System::EventHandler(this, &MyForm1::update_Click);
			// 
			// exit
			// 
			this->exit->BackColor = System::Drawing::Color::IndianRed;
			this->exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->exit->ForeColor = System::Drawing::Color::White;
			this->exit->Location = System::Drawing::Point(656, 11);
			this->exit->Name = L"exit";
			this->exit->Size = System::Drawing::Size(32, 29);
			this->exit->TabIndex = 7;
			this->exit->Text = L"X";
			this->exit->UseVisualStyleBackColor = false;
			this->exit->Click += gcnew System::EventHandler(this, &MyForm1::exit_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(224, 32);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(264, 256);
			this->pictureBox1->TabIndex = 8;
			this->pictureBox1->TabStop = false;
			// 
			// MyForm1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(69)), static_cast<System::Int32>(static_cast<System::Byte>(69)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->ClientSize = System::Drawing::Size(700, 300);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->exit);
			this->Controls->Add(this->update);
			this->Controls->Add(this->delet);
			this->Controls->Add(this->olds);
			this->Controls->Add(this->minors);
			this->Controls->Add(this->get);
			this->Controls->Add(this->save);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"main";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MyForm1::MyForm1_FormClosed);
			this->Load += gcnew System::EventHandler(this, &MyForm1::MyForm1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion


private: System::Void MyForm1_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void MyForm1_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
	Application::Exit();
}
private: System::Void exit_Click(System::Object^ sender, System::EventArgs^ e) {

	this->Close();
}
private: System::Void update_Click(System::Object^ sender, System::EventArgs^ e) {

	UpdateForm^ update = gcnew UpdateForm();
	update->ShowDialog();
}
private: System::Void delet_Click(System::Object^ sender, System::EventArgs^ e) {

	DeleteForm^ del = gcnew DeleteForm();
	del->ShowDialog();
}
private: System::Void olds_Click(System::Object^ sender, System::EventArgs^ e) {

	GetOlds^ olds = gcnew GetOlds();
	olds->ShowDialog();

}
private: System::Void minors_Click(System::Object^ sender, System::EventArgs^ e) {

	GetMinors^ minors = gcnew GetMinors();
	minors->ShowDialog();
}
private: System::Void get_Click(System::Object^ sender, System::EventArgs^ e) {

	GetData^ get = gcnew GetData();
	get->ShowDialog();

}
private: System::Void save_Click(System::Object^ sender, System::EventArgs^ e) {

	EnterForm^ form2 = gcnew EnterForm();
	form2->ShowDialog();

}
private: System::Void SaveHouse_Click(System::Object^ sender, System::EventArgs^ e) {

	MessageBox::Show("Данные успешно сохранены в бинарный файл!");
}
};
}
