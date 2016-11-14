#include<iostream>
#include<conio.h>
#include<string>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include"recfile.h"

#include"class_member.h"
#include"class_stock.h"
#include"class_purchase.h"
#include"onlineshoppingsystem.h"
 
using namespace std;
 
void Menu();
void showMember(int*);
void showStock(int*);
void showPurchase(int*);
void MemberTest(int*);
void StockTest(int*);
void PurchaseTest(int*);
 
/*Main Prog*/
int main(void){
 
	Menu();
 
	return 0;
}
 
void Menu(){
	int menunum;
	
	int num_member=0, num_purchase=0, num_stock=0;

	while(1){
		system("cls");
		
		cout << "-[MENU]-----------------------"<<endl;
		cout<<" 1: showMember\n";
		cout<<" 2: showStock\n";
		cout<<" 3: showPurchase\n";
		cout<<" 4: MemberTest\n";
		cout<<" 5: StockTest\n";
		cout<<" 6: PurchaseTest\n";
		cout<<" 7: OnlineShoppingSystem\n";
		cout<<" 8: Exit\n";
		cout << "\tInput the Number" << endl;
		cout << "------------------------------"<<endl;

		cout << ">> ";
		cin>>menunum;
		switch(menunum){
			case 1: showMember(&num_member); break;
			case 2: showStock(&num_stock); break;
			case 3: showPurchase(&num_purchase); break;
			case 4: MemberTest(&num_member); break;
			case 5: StockTest(&num_stock); break;
			case 6: PurchaseTest(&num_purchase); break;
			case 7: OnlineShoppingSystem(&num_member,&num_stock,&num_purchase); break;
			case 8: return;
 
			default: 
					break;
		}
	}
}
 
void showMember(int* num_member){
	system("cls");

	ifstream ifs("listOfMember.txt");
	ifs >> *num_member;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	cout<<"Num of Records : "<<*num_member<<endl;

	for (int i = 0; i < 10; i++) {
		Member temp;
		ifs >> temp;
		cout << temp << endl;
	}

	cout << "Press any button to return to Menu" << endl;
	cout << ">> ";
	_getch();

	return;
}

void showStock(int *num_stock) {
	system("cls");
	ifstream ifs("listOfStock.txt");
	ifs >> *num_stock;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Num of Records : " << *num_stock << endl;

	for (int i = 0; i < 10; i++) {
		Stock temp;
		ifs >> temp;
		cout << temp << endl;
	}

	cout << "Press any button to return to Menu" << endl;
	cout << ">> ";
	_getch();

	return;
}

void showPurchase(int *num_purchase) {
	system("cls");
	ifstream ifs("listOfPurchase.txt");
	ifs >> *num_purchase;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Num of Records : " << *num_purchase << endl;

	for (int i = 0; i < 10; i++) {
		Purchase temp;
		ifs >> temp;
		cout << temp << endl;
	}

	cout << "Press any button to return to Menu" << endl;
	cout << ">> ";
	_getch();

	return;
}

void MemberTest(int* num_member) {

	ifstream ifs("listOfMember.txt");
	ifs >> *num_member;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Member> MemberFile(buffer);
	bool errorflag=false;


	MemberFile.Create("fileOfMember.dat", ios::out | ios::trunc);
	for (int i = 0; i < *num_member; i++) {
		Member s;
		ifs >> s;
		int recaddr;
		
	printf("1");
		if ((recaddr = MemberFile.Write(s)) == -1) {
			cout << "Write Error!" << endl;
			errorflag = true;
		}

	}
	MemberFile.Close();
	if (!errorflag) {
		cout << endl << "[Write Complete!]" << endl << endl;
	}

	MemberFile.Open("fileOfMember.dat", ios::in);
	for (int i = 0; i < 10; i++) {
		Member temp;
		MemberFile.Read(temp);
		cout << temp;
	}
	MemberFile.Close();

	cout << "Press any button to return to Menu" << endl;
	cout << ">> ";
	_getch();

	return;
}

void StockTest(int* num_stock) {

	ifstream ifs("listOfStock.txt");
	ifs >> *num_stock;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Stock> StockFile(buffer);
	bool errorflag = false;

	StockFile.Create("fileOfStock.dat", ios::out | ios::trunc);
	for (int i = 0; i < *num_stock; i++) {
		Stock s;
		ifs >> s;
		int recaddr;
		if ((recaddr = StockFile.Write(s)) == -1) {
			cout << "Write Error!" << endl;
			errorflag = true;
		}

	}
	StockFile.Close();
	if (!errorflag) {
		cout << endl << "[Write Complete!]" << endl << endl;
	}

	StockFile.Open("fileOfStock.dat", ios::in);
	for (int i = 0; i < 10; i++) {
		Stock temp;
		StockFile.Read(temp);
		cout << temp;
	}
	StockFile.Close();

	cout << "Press any button to return to Menu" << endl;
	cout << ">> ";
	_getch();

	return;
}

void PurchaseTest(int* num_purchase) {

	ifstream ifs("listOfPurchase.txt");
	ifs >> *num_purchase;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile<Purchase> PurchaseFile(buffer);
	bool errorflag = false;

	PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
	for (int i = 0; i < *num_purchase; i++) {
		Purchase s;
		ifs >> s;
		int recaddr;
		if ((recaddr = PurchaseFile.Write(s)) == -1) {
			cout << "Write Error!" << endl;
			errorflag = true;
		}

	}
	PurchaseFile.Close();
	if (!errorflag) {
		cout << endl << "[Write Complete!]" << endl << endl;
	}

	PurchaseFile.Open("fileOfPurchase.dat", ios::in);
	for (int i = 0; i < 10; i++) {
		Purchase temp;
		PurchaseFile.Read(temp);
		cout << temp;
	}
	PurchaseFile.Close();

	cout << "Press any button to return to Menu" << endl;
	cout << ">> ";
	_getch();

	return;
}