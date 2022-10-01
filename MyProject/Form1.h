#pragma once

#include "stdafx.h"
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <string>
#include <msclr\marshal_cppstd.h>

#define ld long double
#define N 5
#define M 32
#define O 500
#define framesize 320

typedef struct Model
{
    ld pi[N];
    ld a[N][N];
    ld b[N][M];
} model;

int qstar[O];
ld delta[O][N];
int phi[O][N];
ld alpha[O][N];
ld beta[O][N];
ld zeta[O][N][N];
ld Gamma[O][N];
ld pstar = 0.0;
int *obs;
int T;

ld raisedSineWeight[12] = {0.0};
ld tokhuraWeight[12] = {1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};
ld PI =  3.141592653589793238;
int digit[14] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};

double samples[100000];
ld stableSamples[framesize];
ld RIS[13] = {0.0};
ld AIS[13] = {0.0};
ld CIS[13] = {0.0};

int framecount;
ld CepsArray[1000][13];
ld CodeArray[32][13];
int recording=3,y;

model lamda;
model lamda_new;
model lamda_temp;


namespace MyProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;  

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			this->default_user->Checked=true;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 

	protected: 

	protected: 

	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button4;

	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::CheckBox^  Fine;
	private: System::Windows::Forms::CheckBox^  checkop;
	private: System::Windows::Forms::CheckBox^  Scheck;



	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::RadioButton^  end_user;
	private: System::Windows::Forms::RadioButton^  default_user;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;







	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->Fine = (gcnew System::Windows::Forms::CheckBox());
			this->checkop = (gcnew System::Windows::Forms::CheckBox());
			this->Scheck = (gcnew System::Windows::Forms::CheckBox());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->end_user = (gcnew System::Windows::Forms::RadioButton());
			this->default_user = (gcnew System::Windows::Forms::RadioButton());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(178, 263);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Training";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(178, 316);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Clear";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(129, 57);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(411, 20);
			this->textBox1->TabIndex = 3;
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(178, 227);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(141, 20);
			this->textBox2->TabIndex = 4;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(324, 262);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 5;
			this->button4->Text = L"Testing";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(129, 18);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(411, 23);
			this->progressBar1->TabIndex = 7;
			this->progressBar1->Value = 100;
			this->progressBar1->Click += gcnew System::EventHandler(this, &Form1::progressBar1_Click);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker1_DoWork);
			this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::backgroundWorker1_ProgressChanged);
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(132, 115);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(54, 26);
			this->textBox3->TabIndex = 8;
			this->textBox3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &Form1::textBox3_TextChanged);
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox4->Location = System::Drawing::Point(222, 115);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(54, 26);
			this->textBox4->TabIndex = 9;
			this->textBox4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &Form1::textBox4_TextChanged);
			// 
			// textBox5
			// 
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox5->Location = System::Drawing::Point(312, 115);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(54, 26);
			this->textBox5->TabIndex = 10;
			this->textBox5->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &Form1::textBox5_TextChanged);
			// 
			// textBox6
			// 
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox6->Location = System::Drawing::Point(411, 115);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(106, 26);
			this->textBox6->TabIndex = 11;
			this->textBox6->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox6->TextChanged += gcnew System::EventHandler(this, &Form1::textBox6_TextChanged);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(324, 316);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(75, 23);
			this->button6->TabIndex = 12;
			this->button6->Text = L"Calculate";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// Fine
			// 
			this->Fine->AutoSize = true;
			this->Fine->Location = System::Drawing::Point(132, 161);
			this->Fine->Name = L"Fine";
			this->Fine->Size = System::Drawing::Size(15, 14);
			this->Fine->TabIndex = 13;
			this->Fine->UseVisualStyleBackColor = true;
			this->Fine->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
			// 
			// checkop
			// 
			this->checkop->AutoSize = true;
			this->checkop->Location = System::Drawing::Point(222, 161);
			this->checkop->Name = L"checkop";
			this->checkop->Size = System::Drawing::Size(15, 14);
			this->checkop->TabIndex = 14;
			this->checkop->UseVisualStyleBackColor = true;
			this->checkop->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged_1);
			// 
			// Scheck
			// 
			this->Scheck->AutoSize = true;
			this->Scheck->Location = System::Drawing::Point(322, 161);
			this->Scheck->Name = L"Scheck";
			this->Scheck->Size = System::Drawing::Size(15, 14);
			this->Scheck->TabIndex = 15;
			this->Scheck->UseVisualStyleBackColor = true;
			this->Scheck->CheckedChanged += gcnew System::EventHandler(this, &Form1::Scheck_CheckedChanged);
			// 
			// folderBrowserDialog1
			// 
			this->folderBrowserDialog1->HelpRequest += gcnew System::EventHandler(this, &Form1::folderBrowserDialog1_HelpRequest);
			// 
			// end_user
			// 
			this->end_user->AutoSize = true;
			this->end_user->Location = System::Drawing::Point(13, 73);
			this->end_user->Name = L"end_user";
			this->end_user->Size = System::Drawing::Size(69, 17);
			this->end_user->TabIndex = 16;
			this->end_user->TabStop = true;
			this->end_user->Text = L"End User";
			this->end_user->UseVisualStyleBackColor = true;
			// 
			// default_user
			// 
			this->default_user->AutoSize = true;
			this->default_user->Location = System::Drawing::Point(13, 123);
			this->default_user->Name = L"default_user";
			this->default_user->Size = System::Drawing::Size(84, 17);
			this->default_user->TabIndex = 17;
			this->default_user->TabStop = true;
			this->default_user->Text = L"Default User";
			this->default_user->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(136, 95);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(50, 13);
			this->label1->TabIndex = 18;
			this->label1->Text = L"First Digit";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(219, 95);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(53, 13);
			this->label2->TabIndex = 19;
			this->label2->Text = L"Operation";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(309, 95);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(68, 13);
			this->label3->TabIndex = 20;
			this->label3->Text = L"Second Digit";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(434, 95);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(37, 13);
			this->label4->TabIndex = 21;
			this->label4->Text = L"Result";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(111, 182);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(77, 13);
			this->label5->TabIndex = 22;
			this->label5->Text = L"First Checkbox";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(211, 182);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(95, 13);
			this->label6->TabIndex = 23;
			this->label6->Text = L"Second Checkbox";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(312, 182);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(82, 13);
			this->label7->TabIndex = 24;
			this->label7->Text = L"Third Checkbox";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(120, 228);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(52, 13);
			this->label8->TabIndex = 25;
			this->label8->Text = L"Accuracy";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(578, 387);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->default_user);
			this->Controls->Add(this->end_user);
			this->Controls->Add(this->Scheck);
			this->Controls->Add(this->checkop);
			this->Controls->Add(this->Fine);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"Speaking Calculator";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}


void intialize_model()
{
    for (int i = 0; i < N; i++)
        if (i == 0)
            lamda.pi[i] = 1.0;
        else
            lamda.pi[i] = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i == j && i != N - 1)
                lamda.a[i][j] = 0.8;
            else if (i == j && i == N - 1)
                lamda.a[i][j] = 1;
            else if (j == i + 1)
                lamda.a[i][j] = 0.2;
            else
                lamda.a[i][j] = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            lamda.b[i][j] = 1.0 / M;
}

void clean_model()
{
    for (int i = 0; i < N; i++)
            lamda.pi[i] = 0.0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
                lamda.a[i][j] = 0.0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            lamda.b[i][j] = 0.0;
}

void clean_model_new()
{
    for (int i = 0; i < N; i++)
            lamda_new.pi[i] = 0.0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
                lamda_new.a[i][j] = 0.0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            lamda_new.b[i][j] = 0.0;
}


void printObs(int *x,int row)
{
    int i = 0;
    for (i = 0; i < row; i++)
    {
        printf("%d ",x[i]);
    }
    printf("\n");
}


void state_sequence()
{
    printf("\n\nobserved state sequence: \n\n");
    for(int t=0;t<T;t++)
    {
        printf("%d ",qstar[t]);
    }
}

bool writeFile(const char  *fileName)
{
	errno_t err;
    FILE *fp;
	err  = fopen_s( &fp, fileName, "w" );
    if( err != 0 )
        return false;
    else
    {
        fprintf(fp,"\nObservation Sequence :");
        fprintf(fp,"\nTotal iterations :");
        fprintf(fp,"\nFinal Probability of state sequence is:");
        fprintf(fp,"\nState Sequence :");
        fprintf(fp,"\nInitial State :");
        for(int i=0;i < N;i++) 
            fprintf(fp,"%Le ",lamda.pi[i]);
        fprintf(fp,"\nA Matrix :\n");
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                fprintf(fp,"%Le ",lamda.a[i][j]);
            }
            fprintf(fp,"\n");
        }

        fprintf(fp,"\nB Matrix :\n");
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                fprintf(fp,"%Le ",lamda.b[i][j]);
            }
            fprintf(fp,"\n");
        }
        
    }
    fclose(fp);
	return true;
}

ld viterbi()
{     
    int argmax = 0;
    for (int i = 0; i < T; i++)
        qstar[i] = 0;

    for (int i = 0; i < N; i++) //initialisation
    {
        delta[0][i] = ((lamda.pi[i]) * (lamda.b[i][obs[0]]));
        phi[0][i] = -1;
    }

    for (int t = 1; t < T; t++) //recursion
    {
        for (int j = 0; j < N; j++)
        {
            argmax = 0;
            for (int i = 1; i < N; i++)
            {
                if (delta[t - 1][i]*lamda.a[i][j] > delta[t - 1][argmax]*lamda.a[argmax][j])
                    argmax = i;
            }
            delta[t][j] = delta[t - 1][argmax] * lamda.a[argmax][j] * lamda.b[j][obs[t]];
            phi[t][j] = argmax;
        }
    }
    argmax = 0;
    for (int i = 1; i < N; i++) //termination
    {
        if (delta[T - 1][i] > delta[T - 1][argmax])
            argmax = i;
    }

    pstar = delta[T - 1][argmax];
    qstar[T - 1] = argmax;

    for (int t = T - 2; t >= 0; t--) //backtracking
    {
        qstar[t] = phi[t + 1][qstar[t + 1]];
    }
    //printObs(qstar,T);
    //printf("%Le ", pstar);
    return pstar;
}

ld forward_algo()
{    
    ld sum = 0.0;

    for (int j = 0; j < N; j++) //initialisation
    {
        alpha[0][j] = lamda.pi[j] * lamda.b[j][obs[0]];        
    }

    for (int t = 1; t < T; t++) //recursion
    {
        for (int j = 0; j < N; j++)
        {            
            sum = 0.0;
            for (int i = 0; i < N; i++)
            {
                sum += alpha[t-1][i] * lamda.a[i][j] * lamda.b[j][obs[t]];
            }
            alpha[t][j] = sum;
        }
    }

    sum = 0.0;
    for (int i = 0; i < N; i++) //termination
    {
        sum += alpha[T-1][i];
    }

    //printf("%Le ", sum);
    return sum;
}

ld backward_algo()
{
    
    ld sum = 0.0;

    for (int j = 0; j < N; j++) //initialisation
    {
        beta[T-1][j] = 1;
    }

    for (int t = T-2; t >= 0; t--) //recursion
    {
        for (int j = 0; j < N; j++)
        {            
            sum = 0.0;
            for (int i = 0; i < N; i++)
            {
                sum += lamda.a[j][i] * lamda.b[i][obs[t+1]] * beta[t+1][i];
            }
            beta[t][j] = sum;
        }
    }

    sum = 0.0;
    for (int j = 0; j < N; j++) //termination
    {
        sum += beta[0][j];
    }

    //printf("%Le ", sum);
    return sum;
}

void Gamma_cal()
{
    ld sum = 0.0;
    int argmax = 0;
    int q[O];
    for (int t = 0; t < T; t++)
    {
        for (int i = 0; i < N; i++)
        {
            ld value = alpha[t][i] * beta[t][i];
            sum = 0.0;
            for (int j = 0; j < N; j++)
            {
                sum += alpha[t][j] * beta[t][j];
            }
            Gamma[t][i] = value/sum;
            if(Gamma[t][i] > Gamma[t][argmax])
                argmax = i;
        }
        q[t] = argmax;
    }
}

void zeta_cal()
{
    ld sum = 0.0;
    for (int t = 0; t < T-1; t++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {

                ld value = alpha[t][i] * lamda.a[i][j] * lamda.b[j][obs[t+1]] * beta[t+1][j];
                sum = 0.0;
                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        sum += alpha[t][i] * lamda.a[i][j] * lamda.b[j][obs[t+1]] * beta[t+1][j];
                    }
                }
                zeta[t][i][j] = value/sum;           
            }            
        }
    }
}

void Baum_Welch_reestimation()
{
    ld value, sum; 
    for (int i = 0; i < N; i++) 
        lamda.pi[i] = Gamma[0][i];
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++)
        {
            value = 0;
            sum = 0;
            for (int t = 0; t < T - 2; t++)
            {
                value += zeta[t][i][j];
                sum += Gamma[t][i];
            }
            lamda.a[i][j] = value / sum;
        }
    }
    for (int j = 0; j < N; j++) 
    {
        for (int k = 0; k < M; k++)
        {
            value = 0;
            sum = 0;
            for (int t = 0; t < T; t++)
            {
                if (obs[t] == k)
                    value += Gamma[t][j];
            }
            for (int t = 0; t < T - 1; t++)
            {
                sum += Gamma[t][j];
            }
            lamda.b[j][k] = value / sum;
        }
    }
}

model getAverageModel(int cnt)
{
    for (int i = 0; i < N; i++)
        lamda.pi[i] = lamda_new.pi[i]/cnt;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            lamda.a[i][j] = lamda_new.a[i][j]/cnt;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            lamda.b[i][j] = lamda_new.b[i][j]/cnt;
	return lamda;
}

void modify_BMatrix()
{    
      for(int i=0;i<N;i++)
    {
        int count=0;
        int max=-1;
        int maxindex=-1;
        int sum=0;
        
        for(int j=0;j<M;j++)
        {
            if(max<lamda.b[i][j])
            {
                max=lamda.b[i][j];
                maxindex=j;
            }
            if(lamda.b[i][j]<pow(10.0,-30))
            {
                count++;
                sum+=lamda.b[i][j];
                lamda.b[i][j]=pow(10.0,-30);
            }   
        }
        lamda.b[i][maxindex]-=count*pow(10.0,-30)+sum;
    }
}

void modify_model()
{
    ld maxx=0.0,sum=0.0;
    int cnt=0,index=0;

    for (int i = 0; i < N; i++)
    {
        maxx = lamda_temp.a[i][0];cnt=0;sum=0.0;index=0;
        for (int j = 0; j < N; j++)
        {
            sum += lamda_temp.a[i][j];
            if(lamda_temp.a[i][j] > maxx)
            {
                maxx = lamda_temp.a[i][j];
                index = j;
            }
        }
        if(sum > 1)
        {
            ld miss_value = sum - 1;
            lamda_temp.a[i][index] -= miss_value; 
        }
        else if(sum < 1)
        {
            ld miss_value = 1 - sum;
            lamda_temp.a[i][index] += miss_value; 
        }
    }


    for (int i = 0; i < N; i++)
    {
        maxx = lamda_temp.b[i][0];sum=0.0;index=0;
        for (int j = 0; j < M; j++)
        {
            sum += lamda_temp.b[i][j];
            if(lamda_temp.b[i][j] > maxx)
            {
                maxx = lamda_temp.b[i][j];
                index = j;
            }
        }
        if(sum > 1)
        {
            ld miss_value = sum - 1;
            lamda_temp.b[i][index] -= miss_value; 
        }
        else if(sum < 1)
        {
            ld miss_value = 1 - sum;
            lamda_temp.b[i][index] += miss_value; 
        }
    }
}

bool ReadFile(double *samples, const char  *fileName)
{
	errno_t err;
    FILE *fp;
	err  = fopen_s( &fp, fileName, "r" );
    if( err != 0 )
        return false;
    else
    {
        int i = 5, a;
        char buffer[100];
        while (i--)
        {
            fgets(buffer, 100, fp);
        }
        i = 0;
        while (fscanf_s(fp, "%d", &a) != EOF)
        {
            samples[i++] = (double)a;
        }
    }
    fclose(fp);
    return true;
}

void DCShift(double *samples, int size)
{
    int i = 0;
    double sum = 0;
    for (i = 0; i < size; i++)
    {
        sum = sum + samples[i];
    }
    sum = sum / size ;
    for (i = 0; i < size; i++)
    {
        samples[i] = samples[i] - sum ;
    }
    return;
}

void Normalization(double *samples, int size)
{

    double maxx = 0.0;
    int i = 0;

    for (; i < size; i++)
    {
        if (maxx < samples[i])
            maxx = samples[i];
    }

    for (int i = 0; i < size; i++)
    {
        samples[i] /= maxx;
        samples[i] *= 5000;
    }
    return;
}

int sizeOfFile(const char  *fileName)
{
	errno_t err;
    FILE *fp;
    int cnt = 0;    
	err  = fopen_s( &fp, fileName, "r" );
    if( err != 0 )
        return -1;
    else
    {
        int i = 5, a;
        char buffer[100];
        while (i--)
        {
            fgets(buffer, 100, fp);
        }
        while (fscanf_s(fp, "%d", &a) != EOF)
        {
            cnt++;
        }
    }
    fclose(fp);
    return cnt;
}

void ComputeRIS()
{
    int i, j, x = 320;
    ld n = (ld)x;
    for (i = 0; i <= 12; i++)
    {
        ld sum = 0.0;
        for (j = 0; j < framesize - i; j++)
        {
            sum = sum + (stableSamples[j] * stableSamples[i + j]);
        }
        sum = sum / n;

        RIS[i] = sum;
    }
    return;
}

void ComputeAIS()
{
    ld energy[13] = {0.0};
    ld K[13] = {0.0};
    ld newAlpha[13] = {0.0};
    ld prevAlpha[13] = {0.0};

    energy[0] = RIS[0];

    int i = 0, j = 0;

    for (i = 1; i <= 12; i++)
    {
        if (i == 1)
            K[i] = RIS[i] / RIS[0];
        else
        {
            ld sum = 0.0;
            for (j = 1; j < i; j++)
            {
                prevAlpha[j] = newAlpha[j];
                sum += (prevAlpha[j] * RIS[i - j]);
            }
            K[i] = (RIS[i] - sum) / energy[i - 1];
        }

        newAlpha[i] = K[i];
        for (j = 1; j < i; j++)
        {
            newAlpha[j] = prevAlpha[j] - (K[i] * prevAlpha[i - j]);
        }
        energy[i] = (1 - (K[i] * K[i])) * energy[i - 1];
    }
    for (i = 1; i <= 12; i++)
        AIS[i] = newAlpha[i];
    return;
}

void ComputeCIS()
{
    CIS[0] = logl(RIS[0]);

    int m = 0, k = 0;
    for (m = 1; m <= 12; m++)
    {
        ld sum = 0.0;

        for (k = 1; k < m; k++)
        {
            sum += ((((ld)k) * CIS[k] * AIS[m - k]) / ((ld)m));
        }

        ld value = AIS[m] + sum;
        CIS[m] = value;
    }
    return;
}

void RiasedSineWindow()
{
    for (int i = 1; i <= 12; i++)
    {
        CIS[i] = raisedSineWeight[i - 1] * CIS[i];
    }
    return;
}

void ComputeRSW()
{
    for (int i = 1; i <= 12; i++)
    {
        ld m = (ld)i;
        ld theta = (PI * m) / 12.0;
        ld value = sin(theta);
        value = 1.0 + (6.0 * value);
        raisedSineWeight[i - 1] = value;
    }
    return;
}

ld tokhura(ld *x,ld *y)
{
    ld dist = 0.0;
    for(int i=0;i<12;i++)
    {
        dist += (tokhuraWeight[i] * (x[i]-y[i]) * (x[i]-y[i])); 
    }
    ld value = dist/12.0;
    return value;
}

void getObsSeq()
{
    int i = 0, j = 0, index = 0;
    ld minDist = 0.0, tDist = 0.0;
    for (i = 0; i < T; i++)
    {
        minDist = tokhura(CepsArray[i], CodeArray[0]);
        for (j = 1; j < 32; j++)
        {
            tDist = tokhura(CepsArray[i], CodeArray[j]);
            if (tDist < minDist)
            {
                minDist = tDist;
                index = j;
            }
        }
        obs[i] = index;
    }
}

void readCodeBook()
{
	errno_t err;
    FILE *fp;    
	err  = fopen_s( &fp, "Codebook.txt", "r" );
    if( err != 0 )
    {
        printf("unable to open codebook file\n");
        return;
    }
    else
    {
        char buffer[200];
        ld val = 0.0;
        int i = 0, j = 0;		
        while (fgets(buffer, 200, fp))
        {
            j = 0;
			char *next_token = NULL;
            char* token = strtok_s(buffer, "	",&next_token);
            while (token != NULL)
            {
                val = strtod(token, NULL);
                CodeArray[i][j++] = val;
                token = strtok_s(NULL, "	",&next_token);
            }
            i++;
        }
    }
    fclose(fp);
    return;
}

bool obsGenerate(const char  *filename)
{
    T = 0;
    int row = sizeOfFile(filename);
    if (row == -1)
    {
        printf("unable to open file");
        return false;
    }
    //printf("Working on %s\n",filename);
    //printf("\nsize of file :%d\n",row);
    if (!ReadFile(samples, filename))
    {
        printf("\nunable to open input_files!..");
        return false;
    }
    DCShift(samples, row);
    Normalization(samples, row);
    framecount = row / framesize;

    T=0;
    
    for (int i = 0, k = 0; k <= (240 * 160) && k < row - 240; i++, k += 240)
    {
        T++;

        for (int j = 0; j < 320; j++)
            stableSamples[j] = (ld)samples[j + k];

        for(int j=0;j<13;j++)
        {
            RIS[j] = 0.0;
            AIS[j] = 0.0;
            CIS[j] = 0.0;
        }

        ComputeRIS();
        ComputeAIS();
        ComputeCIS();
        RiasedSineWindow();

        for(int j=0;j<13;j++)
            CepsArray[i][j] = CIS[j];
    }
    obs = new int[T];
    getObsSeq();
    return true;
}

bool writeModel(const char  *fileName)
{
	errno_t err;
    FILE *fp;    
	err  = fopen_s( &fp, fileName, "w" );
    if( err != 0 )
    {
        return false;
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            fprintf(fp, "%Le ", lamda.pi[i]);
        }
        fprintf(fp, "\n\n");

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                fprintf(fp, "%Le ", lamda.a[i][j]);
            }
            fprintf(fp, "\n");
        }
        fprintf(fp, "\n");

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                fprintf(fp, "%Le ", lamda.b[i][j]);
            }
            fprintf(fp, "\n");
        }
		printf("Model %s generated\n",fileName);
    }
    fclose(fp);
    return true;
}

bool ReadModel(const char  *fileName)
{
    errno_t err;
    FILE *fp;    
	err  = fopen_s( &fp, fileName, "r" );
    if( err != 0 )
        return false;
    else
    {
        char buffer[2000];
        ld val = 0.0;
        int i = 0, j = 0,k=0;
        while (fgets(buffer, 2000, fp))
        {
            k++;
            if(k == 1)
            {
                j=0;
				char *next_token = NULL;
                char* token = strtok_s(buffer, " ",&next_token);
                while (token != NULL)
                {
                    val = strtod(token, NULL);
                    lamda.pi[j++] = val;
                    token = strtok_s(NULL, " ",&next_token);
                }
            }
            else if(k >= 3 && k <= 7)
            {        
                j=0;
				char *next_token = NULL;
                char* token = strtok_s(buffer, " ",&next_token);
                while (token != NULL)
                {
                    val = strtod(token, NULL);
                    lamda.a[i][j++] = val;
                    token = strtok_s(NULL, " ",&next_token);
                }
                i++;
            }
            else if(k >= 9 && k <= 13)
            {
                j=0;
                if (k == 9)
                    i = 0;
				char *next_token = NULL;
                char* token = strtok_s(buffer, " ",&next_token);
                while (token != NULL)
                {
                    val = strtod(token, NULL);
                    lamda.b[i][j++] = val;
                    token = strtok_s(NULL, " ",&next_token);
                }
                i++;
            }
        }
    }
    fclose(fp);
    return true; 
}

void ModelAverage()
{
    for (int i = 0; i < N; i++)
        lamda_new.pi[i] += lamda.pi[i];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            lamda_new.a[i][j] += lamda.a[i][j];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            lamda_new.b[i][j] += lamda.b[i][j];
}

void hmm_training()
{
    int i = 0, j = 0, k = 0,iter=1;
    printf("\nTraining of hmm model starts..\n\n");
    for (i = 0; i < 14; i++)
    {
        int count = 3, k = 0;
        clean_model();
        while (count--)
        {
            clean_model_new();
            k = 0;
            for (j = 1; j <= 30; j++)
            {
				progressBar1->Value = iter * progressBar1->Maximum / 1260;
				iter++;
                T = 0;
				char filename[160];
				sprintf_s(filename,"input_files/%d_%d.txt",i,j);
                if (!obsGenerate(filename))
                    continue;
                if (count == 2)
                    intialize_model();
				else
					lamda = lamda_temp;
                int iteration = 25;
                while (iteration--)
                {
                    forward_algo();
                    backward_algo();
                    Gamma_cal();
                    viterbi();
                    zeta_cal();
                    Baum_Welch_reestimation();
                    modify_BMatrix();
                }
                modify_BMatrix();
                ModelAverage();
                delete[] obs;
            }
            lamda_temp = getAverageModel(30);
            modify_model();
        }
		char fileName[160];
		sprintf_s(fileName,"Model/%d.txt",i);
        writeModel(fileName);
    }
}

void hmm_liveTraining(const char *filePath)
{
	int i = 0, j = 0, k = 0,iter=1;
    printf("\nTraining of hmm model starts..\n\n");
    for (i = 0; i < 14; i++)
    {
        int count = 3, k = 0;
        clean_model();
        while (count--)
        {
            clean_model_new();
            k = 0;
            for (j = 1; j <= 30; j++)
            {
				progressBar1->Value = iter * progressBar1->Maximum / 1260;
				iter++;
                T = 0;
				char filename[160];
				sprintf_s(filename,"%s/%d_%d.txt",filePath,i,j);
                if (!obsGenerate(filename))
                    continue;
                if (count == 2)
                    intialize_model();
				else
					lamda = lamda_temp;
                int iteration = 25;
                while (iteration--)
                {
                    forward_algo();
                    backward_algo();
                    Gamma_cal();
                    viterbi();
                    zeta_cal();
                    Baum_Welch_reestimation();
                    modify_BMatrix();
                }
                modify_BMatrix();
                ModelAverage();
                delete[] obs;
            }
            lamda_temp = getAverageModel(30);
            modify_model();
        }
		char fileName[160];
		sprintf_s(fileName,"Models/%d.txt",i);
        writeModel(fileName);
    }
}


void hmm_testing()
{
    int accuracy = 0, total = 0;
    int i = 0, j = 0, k = 0,iter=1;
    printf("\nTesting of hmm model starts..\n\n");
    for (i = 0; i < 14; i++)
    {
        k = 0;
        for (j = 21; j <= 30 ; j++)
        {
			progressBar1->Value = iter * progressBar1->Maximum / 140;
			iter++;
            total++;
            T=0;
			char filename[160];
			sprintf_s(filename,"input_files/%d_%d.txt",i,j);
            if (!obsGenerate(filename))
                continue;
            //printObs(obs, T);
            ld maxx = 0.0;
            int index = -1;
            for (int k = 0; k < 14; k++)
            {
				char filename[160];
				sprintf_s(filename,"Model/%d.txt",k);
                clean_model();
                ReadModel(filename);
                ld value = forward_algo();
                printf("\nForward Probability for %d : %Le", digit[k], value);
                if (value > maxx)
                {
                    maxx = value;
                    index = k;
                }
            }
            if (index != -1)
			{
				this->textBox1->Text += index.ToString();
			}
            else
                printf("\nnot recognized\n\n");
            if (digit[index] == i)
                accuracy++;
            delete[] obs;
        }
    }
    double r = ((double)accuracy/total) * 100;
	this->textBox2->Text = "accuracy : "+r.ToString();
}

void hmm_livetesting(const char *filePath)
{
    int accuracy = 0, total = 0;
    int i = 0, j = 0, k = 0,iter=1;
    printf("\nTesting of hmm model starts..\n\n");
    for (i = 0; i < 14; i++)
    {
        k = 0;
        for (j = 21; j <= 30 ; j++)
        {
			progressBar1->Value = iter * progressBar1->Maximum / 140;
			iter++;
            total++;
            T=0;
			char filename[160];
			sprintf_s(filename,"%s/%d_%d.txt",filePath,i,j);
            if (!obsGenerate(filename))
                continue;
            //printObs(obs, T);
            ld maxx = 0.0;
            int index = -1;
            for (int k = 0; k < 14; k++)
            {
				char filename[160];
				sprintf_s(filename,"Model/%d.txt",k);
                clean_model();
                ReadModel(filename);
                ld value = forward_algo();
                printf("\nForward Probability for %d : %Le", digit[k], value);
                if (value > maxx)
                {
                    maxx = value;
                    index = k;
                }
            }
            if (index != -1)
			{
				this->textBox1->Text += index.ToString();
			}
            else
                printf("\nnot recognized\n\n");
            if (digit[index] == i)
                accuracy++;
            delete[] obs;
        }
    }
    double r = ((double)accuracy/total) * 100;
	this->textBox2->Text = "accuracy : "+r.ToString();
}


int liveTesting(bool flag)             
{
    system("Recording\\Recording_Module.exe 2 input_file.wav input_file.txt");

	char filename[160];
	sprintf_s(filename,"input_file.txt");

    T = 0;
    if (!obsGenerate(filename))
    {
        printf("unable to test file ");
    }
    ld maxx = 0.0;
    int index = -1;
	if(flag == true)
	{
		for (int k = 0; k < 10; k++)
		{
			char filename[160];
			sprintf_s(filename,"Model/%d.txt",k);
			clean_model();
			ReadModel(filename);
			ld value = forward_algo();
			//printf("\nForward Probability for %d : %Le", digit[k], value);
			if (value > maxx)
			{
				maxx = value;
				index = k;
			}
		}
	}
	else
	{
		for (int k = 10; k < 14; k++)
		{
			char filename[160];
			sprintf_s(filename,"Model/%d.txt",k);
			clean_model();
			ReadModel(filename);
			ld value = forward_algo();
			//printf("\nForward Probability for %d : %Le", digit[k], value);
			if (value > maxx)
			{
				maxx = value;
				index = k;
			}
		}
	}    
	delete[] obs;
	return index;    
}

bool WriteRecording(const char  *fileName)
{
	errno_t err1,err2;
    FILE *fp,*wp;    
	char filename[160];
	sprintf_s(filename,"input_file.txt");
	err1  = fopen_s( &wp, filename, "r" );
	err2  = fopen_s( &fp, fileName, "w" );
    if( err1 != 0 )
    {
        return false;
    }
    else
    {
		int i = 5, a;
        char buffer[100];
        while (fscanf_s(wp, "%d", &a) != EOF)
        {
             fprintf(fp, "%d\n", a);
        }
    }
    fclose(fp);
	fclose(wp);
    return true;
}


void generaterecording(int x,int y)
{
	int i = 0, j = 0, k = 0;
    for (i = 0; i < x; i++)
    {
        k = 0;
        for (j = 1; j <= y ; j++)
        {
			system("Recording\\Recording_Module.exe 2 input_file.wav input_file.txt");
			char filename[160];
			sprintf_s(filename,"LiveTrainRecording/%d_%d.txt",i,j);
			WriteRecording(filename);            
        }
    }
}


#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 ComputeRSW();
				 readCodeBook();
				 if(end_user->Checked)
				 {					
					 String^ folderPath = "";
					 if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
						 folderPath = folderBrowserDialog1->SelectedPath ;
						 MessageBox::Show(folderPath);
					 }
					 std::string s = msclr::interop::marshal_as<std::string>(folderPath);
					 hmm_liveTraining(s.c_str());
				 }					 
				 else if(default_user->Checked)
					hmm_training();				 
			 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 ComputeRSW();
			 readCodeBook();
			 this->textBox1->Clear();
			 int x = liveTesting(true);
			 this->textBox1->Text = x.ToString();
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->textBox1->Clear();
			 this->textBox2->Clear();
			 this->textBox3->Clear();
			 this->textBox4->Clear();
			 this->textBox5->Clear();
			 this->textBox6->Clear();
			 this->Fine->Checked==false;
			 this->checkop->Checked==false;
			 this->Scheck->Checked==false;
			  recording=3,y=10;
			 progressBar1->Value = 0;
		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 backgroundWorker1->WorkerReportsProgress = true;
			 backgroundWorker1->RunWorkerAsync(); 
			 backgroundWorker1->ReportProgress(0);  
		 }
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 ComputeRSW();
			 readCodeBook();			 
			 if(end_user->Checked)
			 {					
				 String^ folderPath = "";
				 if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
					 folderPath = folderBrowserDialog1->SelectedPath ;
					 MessageBox::Show(folderPath);
				 }
				 std::string s = msclr::interop::marshal_as<std::string>(folderPath);
				 hmm_livetesting(s.c_str());
			 }					 
			 else if(default_user->Checked)
				 hmm_testing();	
		 }
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 ComputeRSW();
			 readCodeBook();			 
		 }
private: System::Void progressBar1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {

		 }
private: System::Void backgroundWorker1_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {			  
			 progressBar1->Value = e->ProgressPercentage;			  
			 this->Text = e->ProgressPercentage.ToString();
		 }
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			 ComputeRSW();
			 readCodeBook();
			 this->textBox6->Clear();
			 int x=0,z=0;

			 if(recording==3)
			 {  
				 if(Fine->Checked==false)
				 {
					 this->textBox3->Clear();
					 int x = liveTesting(true);
					 this->textBox3->Text = x.ToString();
				 }
				 else
				 {
					 recording--;					   	
				 }
			 }

			 if(recording==2)
			 {
				 if(checkop->Checked==false)
				 {
					 this->textBox4->Clear();
					 y = liveTesting(false);
					 if(y==10)
						 this->textBox4->Text = "+";
					 else if(y==11)
						 this->textBox4->Text = "-";
					 else if(y==12)
						 this->textBox4->Text = "*";
					 else if(y==13)
						 this->textBox4->Text = "/";
				 }
				 else
				 {
					 recording--;
				 }
			 }
			 if(recording==1)
			 {
				 if(Scheck->Checked==false)
				 {
					 this->textBox5->Clear();
					 z = liveTesting(true);
					 this->textBox5->Text = z.ToString();
				 }
				 else
				 {
					 recording=-1;
				 }
			 }		 

		 }
private: System::Void textBox3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox4_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox5_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox6_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void checkBox1_CheckedChanged_1(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void Scheck_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(Scheck->Checked==true)
			 {
				 int a = Int32::Parse(this->textBox3->Text);
				 int op = y;
				 int b = Int32::Parse(this->textBox5->Text);

				 double result = 0.0;
				 bool flag = false;

				 switch(op)
				 {
				 case 10:
					 result = a+b;
					 break;
				 case 11:
					 result = a-b;
					 break;
				 case 12:
					 result = a*b;
					 break;
				 case 13:
					 if(b!=0)
						 result = (double)a/b;
					 break;
				 default:
					 flag=true;
					 break;
				 }			
				 if(flag == true)
				 {
					 MessageBox::Show("Please Record Carefully","Sorry");
				 }
				 else
					 this->textBox6->Text = result.ToString();  
			 }
		 }
private: System::Void textBox7_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void folderBrowserDialog1_HelpRequest(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

