#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;

bool repeated(int);

class account
{
	int acc_no;
	char acc_holder[50];
	int deposit;
	char type;

public:
	void create_acc();
	void deposit_acc(int);
	void show_acc();
	void modi_acc();
	void report();
	int showacc_no();
	int showacc_dep();
};

void account::create_acc()
{
	cout << "\nEnter The account Number, from 1 to 999: ";
	cin >> acc_no;
	while (cin.fail() || acc_no >999 || acc_no < 1)
	{
		cout << "\nPlease enter an valid number.";
		cin.clear();
		cin.ignore();
		cout << "\nEnter The account Number, from 1 to 999: ";
		cin >> acc_no;
	}
	while (repeated(acc_no))
	{
		cout << "\nAccount unmber existed.";
		cin.clear();
		cin.ignore();
		cout << "\nEnter The account Number, from 1 to 999: ";
		cin >> acc_no;
	}
	cin.ignore();
	cout << "\nPlease enter account holder's name: ";
	cin.getline(acc_holder, 50);
	cout << "\nPlease select account type(C/S): ";
	cin >> type;
	while (cin.fail() /*|| type != 'C' || type != 'S'*/)
	{
		cout << "\n Please enter an valid type.";
		cin.clear();
		cin.ignore();
		cout << "\nPlease select account type(C/S): ";
		cin >> type;
	}
	cin.ignore();
	cout << "\nPlease deposit an initial amount of money, not less than 500: ";
	cin >> deposit;
	while (cin.fail() || deposit < 500)
	{
		cout << "\nPlease enter an valid number.";
		cin.clear();
		cin.ignore();
		cout << "\nPlease deposit an initial amount of money, not less than 500: ";
		cin >> deposit;
	}
	cin.ignore();
	cout << "\n\n\nAccount created..." << endl;
	system("pause");
}

void account::deposit_acc(int num)
{
	deposit += num;
}

void account::show_acc()
{
	cout << "\nYour account review is as following:";
	cout << "\nAccount number: " << acc_no << endl;
	cout << "\nAccount holder: " << acc_holder << endl;
	cout << "\nAccount type: " << type << endl;
	cout << "\nAccount balance: " << deposit << endl;
}

void account::modi_acc()
{
	cout << "\nPlease enter your new username: ";
	cin.getline(acc_holder, 50);
	cout << "\nPlease enter your new account type: ";
	cin >> type;
	while (cin.fail() /*|| type != 'C' || type != 'S'*/)
	{
		cout << "\n Please enter an valid type.";
		cin.clear();
		cin.ignore();
		cout << "\nPlease select account type(C/S): ";
		cin >> type;
	}
	cin.ignore();
}

void account::report()
{
	cout << setw(3) << acc_no << setw(12) << acc_holder << setw(5) << type << setw(8) << deposit << endl;
}

int account::showacc_no()
{
	return acc_no;
}

int account::showacc_dep()
{
	return deposit;
}



void write_acc();
void bal_inquery();
void dep_acc();
void wit_acc();
void all_list();
void close_acc();
void modi_acc();

int main()
{
	int ch;
	
	do
	{
		system("cls");
		cout << "\tBanking System" << endl;
		cout << "\n01. " << setw(24) << "NEW ACCOUNT" << endl;
		cout << "\n02. " << setw(24) << "DEPOSIT AN ACCOUNT" << endl;
		cout << "\n03. " << setw(24) << "WITHDRAW AN ACCOUNT" << endl;
		cout << "\n04. " << setw(24) << "BALANCE INQUERY" << endl;
		cout << "\n05. " << setw(24) << "ALL ACCOUNTS LIST" << endl;
		cout << "\n06. " << setw(24) << "CLOSE AN ACCOUNT" << endl;
		cout << "\n07. " << setw(24) << "MODIFY AN ACCOUNT" << endl;
		cout << "\n08. " << setw(24) << "EXIT PROCESS" << endl;
		cout << "\n\n\nPlease enter the number to process: ";
		cin >> ch;
		while (cin.fail())
		{
			cout << "\nPlease enter an valid number.";
			cin.clear();
			cin.ignore();
			cout << "\nPlease enter the number to process: ";
			cin >> ch;
		}
		switch (ch)
		{
		case 1:
			write_acc();
			break;
		case 2:
			dep_acc();
			break;
		case 3:
			wit_acc();
			break;
		case 4:
			bal_inquery();
			break;
		case 5:
			all_list();
			break;
		case 6:
			close_acc();
			break;
		case 7:
			modi_acc();
			break;
		case 8:
			cout << "\nThank you for using." << endl;
			break;
		default:
			cout << "\nInvalid number." << endl;
			system("pause");
			break;
		}
	} while (ch != 8);
	
	system("pause");
	return 0;
	
}

void write_acc()
{
	account acc;
	acc.create_acc();
	ofstream acc_dat;
	acc_dat.open("Acc_dat.dat", ios::binary | ios::app);
	acc_dat.write((char*)(&acc), sizeof(acc));
	acc_dat.close();
}

void bal_inquery()
{	
	int acc_n;
	bool found = false;
	account acc;
	ifstream acc_dat;
	acc_dat.open("Acc_dat.dat", ios::binary);
	cout << "\nPlease enter your account number: ";
	cin >> acc_n;
	while (cin.fail() || acc_n >999 || acc_n < 1)
	{
		cout << "\nPlease enter an valid number.";
		cin.clear();
		cin.ignore();
		cout << "\nPlease enter your account number: ";
		cin >> acc_n;
	}
	while (!acc_dat.eof() && found == false)
	{
		acc_dat.read((char*)(&acc), sizeof(acc));
		if (acc.showacc_no() == acc_n)
		{
			found = true;
			acc.show_acc();
		}
	}
	acc_dat.close();
	if (found == false)
		cout << "Record not found." << endl;
	system("pause");
}

void dep_acc()
{
	int acc_n, dep_n;
	bool found = false;
	account acc;
	fstream acc_dat;
	acc_dat.open("Acc_dat.dat", ios::binary|ios::in|ios::out);
	cout << "\nPlease enter your account number: ";
	cin >> acc_n;
	while (cin.fail() || acc_n >999 || acc_n < 1)
	{
		cout << "\nPlease enter an valid number.";
		cin.clear();
		cin.ignore();
		cout << "\nPlease enter your account number: ";
		cin >> acc_n;
	}
	while (!acc_dat.eof() && found == false)
	{
		acc_dat.read((char*)(&acc), sizeof(acc));
		if (acc.showacc_no() == acc_n)
		{
			found = true;
			cout << "\nPlease select the amount to be deposited: ";
			cin >> dep_n;
			while (cin.fail() || dep_n <= 0)
			{
				cout << "\n Please enter an valid number.";
				cin.clear();
				cin.ignore();
				cout << "\nPlease select the amount to be deposited: ";
				cin >> dep_n;
			}
			acc.deposit_acc(dep_n);
			int pos = (-1) * int(sizeof(acc));
			acc_dat.seekp(pos, ios::cur);
			acc_dat.write((char*)(&acc), sizeof(acc));
			cout << "\n\n\nTransaction completed." << endl;
		}
	}
	acc_dat.close();
	if (found == false)
		cout << "Record not found." << endl;
	system("pause");
}

void wit_acc()
{
	int acc_n, wit_n;
	bool found = false;
	account acc;
	fstream acc_dat;
	acc_dat.open("Acc_dat.dat", ios::binary | ios::in | ios::out);
	cout << "\nPlease enter your account number: ";
	cin >> acc_n;
	while (cin.fail() || acc_n >999 || acc_n < 1)
	{
		cout << "\nPlease enter an valid number.";
		cin.clear();
		cin.ignore();
		cout << "\nPlease enter your account number: ";
		cin >> acc_n;
	}
	while (!acc_dat.eof() && found == false)
	{
		acc_dat.read((char*)(&acc), sizeof(acc));
		if (acc.showacc_no() == acc_n)
		{
			found = true;
			do
			{
				cout << "\nPlease select the amount to be withdrawed: ";
				cin >> wit_n;
				while (cin.fail() || wit_n <= 0)
				{
					cout << "\n Please enter an valid number.";
					cin.clear();
					cin.ignore();
					cout << "\nPlease select the amount to be withdrawed: ";
					cin >> wit_n;
				}
				if (wit_n > acc.showacc_dep())
					cout << "You don't have enough balance." << endl;
			} while (wit_n > acc.showacc_dep());
			acc.deposit_acc(-wit_n);
			int pos = (-1) * int(sizeof(acc));
			acc_dat.seekp(pos, ios::cur);
			acc_dat.write((char*)(&acc), sizeof(acc));
			cout << "\n\n\nTransaction completed." << endl;
		}
	}
	acc_dat.close();
	if (found == false)
		cout << "Record not found." << endl;
	system("pause");
}

void all_list()
{
	account acc;
	ifstream acc_dat;
	acc_dat.open("Acc_dat.dat", ios::binary);
	cout << setw(3) << "NO." << setw(12) << "HOLDER NAME" << setw(5) << "TYPE" << setw(8) << "DEPOSIT" << endl;
	while (acc_dat.read((char*)(&acc), sizeof(acc)))
	{
		acc.report();
	}
	acc_dat.close();
	system("pause");
}

void close_acc()
{
	int acc_n;
	bool found = false;
	account acc;
	ifstream acc_dat;
	ofstream temp;
	acc_dat.open("Acc_dat.dat", ios::binary);
	temp.open("temp.dat", ios::binary);
	if (!temp)
	{
		cout << "File temp cannot be created." << endl;
		return;
	}
	acc_dat.seekg(0, ios::beg);
	cout << "\nPlease enter your account number: ";
	cin >> acc_n;
	while (cin.fail() || acc_n >999 || acc_n < 1)
	{
		cout << "\nPlease enter an valid number.";
		cin.clear();
		cin.ignore();
		cout << "\nPlease enter your account number: ";
		cin >> acc_n;
	}
	while (acc_dat.read((char*)(&acc), sizeof(acc)))
	{
		if (acc.showacc_no() != acc_n)
		{
			temp.write((char*)(&acc), sizeof(acc));
		}
		else
		{
			found = true;
			cout << "\n\n\nAccount deleted.";
		}
	}
	acc_dat.close();
	temp.close();
	remove("Acc_dat.dat");
	rename("temp.dat", "Acc_dat.dat");
	if (found == false)
		cout << "Record not found." << endl;
	system("pause");
}

void modi_acc()
{
	int acc_n;
	bool found = false;
	account acc;
	fstream acc_dat;
	acc_dat.open("Acc_dat.dat", ios::binary | ios::in | ios::out);
	cout << "\nPlease enter your account number: ";
	cin >> acc_n;
	while (cin.fail() || acc_n >999 || acc_n < 1)
	{
		cout << "\nPlease enter an valid number.";
		cin.clear();
		cin.ignore();
		cout << "\nPlease enter your account number: ";
		cin >> acc_n;
	}
	while (!acc_dat.eof() && found == false)
	{
		acc_dat.read((char*)(&acc), sizeof(acc));
		if (acc.showacc_no() == acc_n)
		{
			found = true;
			cout << "\nPlease check your personal information." << endl;
			acc.show_acc();
			acc.modi_acc();
			int pos = (-1) * int(sizeof(acc));
			acc_dat.seekp(pos, ios::cur);
			acc_dat.write((char*)(&acc), sizeof(acc));
			cout << "\n\n\nAccount modified.";
		}
	}
	acc_dat.close();
	if (found == false)
		cout << "Record not found." << endl;
	system("pause");
}

bool repeated(int num)
{
	account acc;
	ifstream acc_dat;
	acc_dat.open("Acc_dat.dat", ios::binary | ios::in | ios::out);
	while (acc_dat.read((char*)(&acc), sizeof(acc)))
	{
		if (acc.showacc_no() == num)
			return true;
	}
	return false;
}
