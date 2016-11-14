#include"onlineshoppingsystem.h"

map<string,int> Membermap,Stockmap,Purchasemap;
map<string, vector<int> > PMwithMember, PMwithStock;

DelimFieldBuffer buffer('|', STDMAXBUF);
RecordFile<Member> MemberFile(buffer);
RecordFile<Stock> StockFile(buffer);
RecordFile<Purchase> PurchaseFile(buffer);

int TotalMemberDelSize = 0;
int TotalStockDelSize = 0;
int TotalPurchaseDelSize = 0;

void OnlineShoppingSystem(int* num_member,int* num_stock,int* num_purchase) {
	
	TotalMemberDelSize = 0;
	TotalStockDelSize = 0;
	TotalPurchaseDelSize = 0;

	if (*num_member == 0) {
		cout<< " There is No Member Data.\n Retry after executing MemberTest\n Press any Key to return menu\n";
		_getch();
		return;
	}
	if (*num_stock == 0) {
		cout << " There is No Stock Data.\n Retry after executing StockTest\n Press any Key to return menu\n";
		_getch();
		return;
	}
	if (*num_purchase == 0) {
		cout << " There is No Purchase Data.\n Retry after executing PurchaseTest\n Press any Key to return menu\n";
		_getch();
		return;
	}

	/*File Read and Make Hash Table*/
	MemberFile.Open("fileOfMember.dat", ios::in);
	for (int i = 0; i < *num_member; i++) {
		Member temp;
		int recaddr = MemberFile.Read(temp);
		Membermap.insert(make_pair(temp.getId(),recaddr));
	}
	StockFile.Open("fileOfStock.dat", ios::in);
	for (int i = 0; i < *num_stock; i++) {
		Stock temp;
		int recaddr = StockFile.Read(temp);
		Stockmap.insert(make_pair(temp.getId(), recaddr));
	}
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);
	for (int i = 0; i < *num_purchase; i++) {
		Purchase temp;
		int recaddr = PurchaseFile.Read(temp);
		Purchasemap.insert(make_pair(temp.getId(), recaddr));
		
		PMwithMember[temp.getMemberId()].push_back(recaddr);
		PMwithStock[temp.getStockId()].push_back(recaddr);
	}

	MemberFile.Close();
	StockFile.Close();
	PurchaseFile.Close();
	while (1) {
		system("cls");

		cout << " -OnlineShoppingSystem---------" << endl;
		cout << " 1. Records Search" << endl;
		cout << " 2. Records Insert" << endl;
		cout << " 3. Records Delete" << endl;
		cout << " 4. Records Update" << endl;
		cout << " 5. Exit to Menu" << endl;
		cout << " ------------------------------" << endl;
		cout << ">> ";

		int mode;
		cin >> mode;
		cin.ignore();

		switch (mode) {
			case 1: RecordSearch(); break;
			case 2: RecordInsert(num_member,num_stock,num_purchase); break;
			case 3: RecordDelete(num_member, num_stock, num_purchase); break;
			case 4: RecordUpdate();  break;
			case 5: 
				return;
			default: {
				cin.clear();
				
			}
		}
		if(TotalMemberDelSize>256){
			FileCompactionMember(num_member);
			TotalMemberDelSize=0;
		}
		if(TotalStockDelSize>256){
			FileCompactionStock(num_stock);
			TotalStockDelSize=0;
		}
		if(TotalPurchaseDelSize>256){
			FileCompactionPurchase(num_purchase);
			TotalPurchaseDelSize=0;
		}
	}
}

void RecordSearch() {
	
	while (1) {
		system("cls");

		cout << " -Record-Search----------------" << endl;
		cout << " 1. Member Records Search" << endl;
		cout << " 2. Stock Records Search" << endl;
		cout << " 3. Purchase Records Search" << endl;
		cout << " 4. Exit to OnlineShoppingSystem" << endl;
		cout << " ------------------------------" << endl;
		cout << ">> ";

		int mode;
		cin >> mode;
		cin.ignore();

		switch (mode) {
			case 1: 
				MemberResult();
				break;
			case 2: 
				StockResult();
				break;
			case 3: 
				PurchaseResult();
				break;
			case 4: return;
			default: {
				cin.clear();
				break;
			}
		}

		
	}
	return;
}

void MemberResult() {
	cout << " Please Input your Member ID : ";

	string input;
	cin >> input;

	Member result;

	MemberFile.Open("fileOfMember.dat", ios::in);

	int idx = Membermap[input];
	if (idx == 0) {
		cout << " There is Not Correct Member ID" << endl;
	}
	else {
		MemberFile.Read(result, idx);

		cout << result;
	}
	cout << " Press any button to return to Record Search" << endl;
	cout << ">> ";
	_getch();
	MemberFile.Close();

	return;
}

void StockResult() {
	cout << " Please Input the Stock ID : ";

	string input;
	cin >> input;

	Stock result;

	StockFile.Open("fileOfStock.dat", ios::in);

	int idx = Stockmap[input];
	if (idx == 0) {
		cout << " There is Not Correct Stock ID" << endl;
	}
	else {
		StockFile.Read(result, Stockmap[input]);

		cout << result;
	}
	cout << " Press any button to return to Record Search" << endl;
	cout << ">> ";
	_getch();

	StockFile.Close();

	return;
}

void PurchaseResult() {
	int searchmode;
	while (1) {
		system("cls");
		cout << " -Purchase Search--------------" << endl;
		cout << " 1. Search with Purchase ID" << endl;
		cout << " 2. Search with Stock ID" << endl;
		cout << " 3. Search with Member ID" << endl;
		cout << " 4. Exit to Search Menu" << endl;
		cout << " ------------------------------" << endl;
		cout << ">> ";

		cin >> searchmode;
		cin.ignore();

		if (searchmode == 1) {
			cout << " Please Input the Purchase ID : ";

			string input;
			cin >> input;

			Purchase result;

			PurchaseFile.Open("fileOfPurchase.dat", ios::in);

			int idx = Purchasemap[input];
			if (idx == 0) {
				cout << "There is Not Correct Purchase ID" << endl;
			}
			else {
				PurchaseFile.Read(result, Purchasemap[input]);

				cout << result;
			}
			cout << " Press any button to return to Record Search" << endl;
			cout << ">> ";
			_getch();

			PurchaseFile.Close();

			return;
		}
		else if (searchmode == 2) {
			cout << " Please Input the Stock ID : ";

			string input;
			cin >> input;

			Purchase result;

			PurchaseFile.Open("fileOfPurchase.dat", ios::in);

			int datacount = PMwithStock[input].size();
			if (datacount == 0) {
				cout << "There is Not Correct Stock ID" << endl;
			}
			else {
				for (int i = 0; i < datacount; i++) {
					PurchaseFile.Read(result, PMwithStock[input][i]);

					cout << result;
				}
			}
			cout << " Press any button to return to Record Search" << endl;
			cout << ">> ";
			_getch();

			PurchaseFile.Close();

			return;
		}
		else if (searchmode == 3) {
			cout << " Please Input the Member ID : ";

			string input;
			cin >> input;

			Purchase result;

			PurchaseFile.Open("fileOfPurchase.dat", ios::in);

			int datacount = PMwithMember[input].size();
			if (datacount == 0) {
				cout << "There is Not Correct Member ID" << endl;
			}
			else {
				for (int i = 0; i < datacount; i++) {
					PurchaseFile.Read(result, PMwithMember[input][i]);

					cout << result;
				}
			}
			cout << " Press any button to return to Record Search" << endl;
			cout << ">> ";
			_getch();

			PurchaseFile.Close();

			return;
		}
		else if (searchmode == 4) break;
		else {
			continue;
		}
	}

	return;
}

void RecordInsert(int* num_member,int*num_stock,int*num_purchase) {
	while (1) {
		system("cls");

		cout << " -Record-Insert----------------" << endl;
		cout << " 1. Member Records Insert" << endl;
		cout << " 2. Stock Records Insert" << endl;
		cout << " 3. Purchase Records Insert" << endl;
		cout << " 4. Exit to OnlineShoppingSystem" << endl;
		cout << " ------------------------------" << endl;
		cout << ">> ";

		int mode;
		cin >> mode;
		cin.ignore();

		switch (mode) {
			case 1:
				MemberInsert(num_member);
				break;
			case 2:
				StockInsert(num_stock);
				break;
			case 3:
				PurchaseInsert(num_purchase);
				break;
			case 4: return;
			default: {
				cin.clear();
				break;
			}
		}


	}
	return;
}

void MemberInsert(int* num_member) {
	cout << " Please Input Member ID : ";

	string input;
	cin >> input;
	cin.ignore();

	Member temp;

	MemberFile.Open("fileOfMember.dat", ios::out);

	int idx = Membermap[input];
	if (idx == 0) {
		string name, phonenum, addr, birth, email;
		cout << " Name : ";
		getline(cin,name);
		cout << " Phone Number : ";
		getline(cin, phonenum);
		cout << " Address : ";
		getline(cin, addr);
		cout << " Birthday : ";
		getline(cin, birth);
		cout << " Email : ";
		getline(cin, email);

		temp.setId(input);
		temp.setName(name);
		temp.setPhonenum(phonenum);
		temp.setAddress(addr);
		temp.setBirthday(birth);
		temp.setEmail(email);

		int recaddr=MemberFile.Append(temp);
		Membermap[input] = recaddr;
		(*num_member)++;
	}
	else {
		cout << " The Member ID exists already" << endl;
	}
	cout << " Press any button to return to Record Search" << endl;
	cout << ">> ";
	_getch();

	MemberFile.Close();

	return;
}

void StockInsert(int* num_stock) {
	cout << " Please Input Stock ID : ";

	string input;
	cin >> input;
	cin.ignore();

	Stock temp;

	StockFile.Open("fileOfStock.dat", ios::out);

	int idx = Stockmap[input];
	if (idx == 0) {
		string category, material, price, stock, wash_info, size;
		cout << " Category : ";
		getline(cin, category);
		cout << " Material : ";
		getline(cin, material);
		cout << " Price : ";
		getline(cin, price);
		cout << " Stock : ";
		getline(cin, stock);
		cout << " Washing Info : ";
		getline(cin, wash_info);
		cout << " Size : ";
		getline(cin, size);

		temp.setId(input);
		temp.setCategory(category);
		temp.setMaterial(material);
		temp.setPrice(price);
		temp.setStock(stock);
		temp.setWashingInfo(wash_info);
		temp.setSize(size);

		int recaddr = StockFile.Append(temp);
		Stockmap[input] = recaddr;
		(*num_stock)++;
	}
	else {
		cout << "The Stock ID exists already" << endl;
	}
	cout << " Press any button to return to Record Search" << endl;
	cout << ">> ";
	_getch();

	StockFile.Close();

	return;
}

void PurchaseInsert(int* num_purchase) {
	cout << " Please Input Purchase ID : ";

	string input;
	cin >> input;
	cin.ignore();

	Purchase temp;

	PurchaseFile.Open("fileOfPurchase.dat", ios::out);

	int idx = Purchasemap[input];
	if (idx == 0) {
		string stock_id,member_id,quantity;
		cout << "Stock ID : ";
		getline(cin, stock_id);
		cout << " Member ID : ";
		getline(cin, member_id);
		cout << " Quantity : ";
		getline(cin, quantity);

		temp.setPurchaseId(input);
		temp.setStockId(stock_id);
		temp.setMemberId(member_id);
		temp.setQuantity(quantity);

		int recaddr = PurchaseFile.Append(temp);
		Purchasemap[input] = recaddr;
		(*num_purchase)++;
	}
	else {
		cout << "The Purchase ID exists already" << endl;
	}
	cout << " Press any button to return to Record Search" << endl;
	cout << ">> ";
	_getch();

	PurchaseFile.Close();

	return;
}

void RecordDelete(int*num_member,int*num_stock,int*num_purchase) {
	while (1) {
		system("cls");

		cout << " -Record-Delete----------------" << endl;
		cout << " 1. Member Records Delete" << endl;
		cout << " 2. Stock Records Delete" << endl;
		cout << " 3. Purchase Records Delete" << endl;
		cout << " 4. Exit to OnlineShoppingSystem" << endl;
		cout << " ------------------------------" << endl;
		cout << ">> ";

		int mode;
		cin >> mode;

		switch (mode) {
			case 1:
				MemberDelete(num_member,num_purchase);
				break;
			case 2:
				StockDelete(num_stock,num_purchase);
				break;
			case 3:
				PurchaseDelete(num_purchase);
				break;
			case 4: return;
			default: {
				cin.clear();
				break;
			}
		}


	}
	return;
}

void MemberDelete(int*num_member,int*num_purchase) {
	cout << " Please Input your Member ID to Delete: ";

	string input;
	cin >> input;

	MemberFile.Open("fileOfMember.dat", ios::out);

	int delSize = 0;
	int idx = Membermap[input];
	if (idx == 0) {
		cout << " There is Not Correct Member ID" << endl;
	}
	else {
		delSize=MemberFile.Delete(idx);
		Membermap.erase(input);

		PurchaseFile.Open("fileOfPurchase.dat", ios::out);

		int delpurchasecount = PMwithMember[input].size();

		for (int i = 0; i < delpurchasecount; i++) {
			
			delSize += PurchaseFile.Delete(PMwithMember[input][i]);
			(*num_purchase)--;
		}
		PMwithMember.erase(input);

		PurchaseFile.Close();

		(*num_member)--;
		cout << " [DELETE SUCCESS!]" << endl;
	}

	
	cout << " Press any button to return to Record Delete" << endl;
	cout << ">> ";
	_getch();

	TotalMemberDelSize += delSize;
	MemberFile.Close();

	return;
}

void StockDelete(int*num_stock,int*num_purchase) {
	cout << " Please Input your Stock ID to Delete: ";

	string input;
	cin >> input;

	StockFile.Open("fileOfStock.dat", ios::out);

	int delSize = 0;
	int idx = Stockmap[input];
	if (idx == 0) {
		cout << " There is Not Correct Stock ID" << endl;
	}
	else {
		delSize = StockFile.Delete(idx);
		Stockmap.erase(input);

		PurchaseFile.Open("fileOfPurchase.dat", ios::out);

		int delpurchasecount = PMwithStock[input].size();
		for (int i = 0; i < delpurchasecount; i++) {
			delSize += PurchaseFile.Delete(PMwithStock[input][i]);
			(*num_purchase)--;
		}
		PMwithStock.erase(input);

		PurchaseFile.Close();

		(*num_stock)--;
		cout << " [DELETE SUCCESS!]" << endl;
	}

	
	cout << " Press any button to return to Record Delete" << endl;
	cout << ">> ";
	_getch();

	TotalStockDelSize += delSize;
	StockFile.Close();

	return;
}

void PurchaseDelete(int*num_purchase) {
	cout << " Please Input your Purchase ID to Delete: ";

	string input;
	cin >> input;

	PurchaseFile.Open("fileOfPurchase.dat", ios::out);

	int delSize = 0;
	int idx = Purchasemap[input];
	if (idx == 0) {
		cout << " There is Not Correct Purchase ID" << endl;
	}
	else {
		delSize = PurchaseFile.Delete(idx);
		Purchasemap.erase(input);
		//TODO:Delete PMwithMember,PMwithStock
		(*num_purchase)--;
		cout << " [DELETE SUCCESS!]" << endl;
	}

	cout << " Press any button to return to Record Delete" << endl;
	cout << ">> ";
	_getch();

	TotalPurchaseDelSize += delSize;
	PurchaseFile.Close();

	return;
}

void RecordUpdate() {
	while (1) {
		system("cls");

		cout << " -Record-Update----------------" << endl;
		cout << " 1. Member Records Update" << endl;
		cout << " 2. Stock Records Update" << endl;
		cout << " 3. Purchase Records Update" << endl;
		cout << " 4. Exit to OnlineShoppingSystem" << endl;
		cout << " ------------------------------" << endl;
		cout << ">> ";

		int mode;
		cin >> mode;

		switch (mode) {
		case 1:
			MemberUpdate();
			break;
		case 2:
			StockUpdate();
			break;
		case 3:
			PurchaseUpdate();
			break;
		case 4: return;
		default: {
			cin.clear();
			break;
		}
		}


	}
	return;
}

void MemberUpdate() {
	cout << " Please Input your Member ID to Update: ";

	string input;
	cin >> input;

	int delSize = 0;
	int idx = Membermap[input];
	if (idx == 0) {
		cout << " There is Not Correct Member ID" << endl;
	}
	else {
		cout << endl << " Which Field do you want to Update, Press the Number "<<endl;
		cout << " (1) Name\n (2) Phone Number\n (3) Address\n (4) Birthday\n (5) E-mail" << endl;

		cout << ">> ";
		int fieldnum;
		cin >> fieldnum;
		cin.ignore();

		string change;
		cout << " Input the Data : ";
		getline(cin, change);

		Member temp;
		int recaddr;

		MemberFile.Open("fileOfMember.dat", ios::in|ios::out);
		MemberFile.Read(temp, idx);

		switch (fieldnum) {
		case 1: temp.setName(change); break;
		case 2: temp.setPhonenum(change); break;
		case 3: temp.setAddress(change); break;
		case 4:	temp.setBirthday(change); break;
		case 5: temp.setEmail(change); break;
		default: break;
		}
		//MemberFile.Close();

		//MemberFile.Open("fileOfMember.dat", ios::out);
		delSize = MemberFile.Delete(idx);
		recaddr = MemberFile.Append(temp);
		Membermap[input] = recaddr;
		cout << " [UPDATE SUCCESS!]" << endl;
		MemberFile.Close();
	}

	//TODO:cascasding
	cout << " Press any button to return to Record Update" << endl;
	cout << ">> ";
	_getch();

	TotalMemberDelSize += delSize;
	
	return;
}

void StockUpdate() {
	cout << " Please Input your Member ID to Update: ";

	string input;
	cin >> input;

	int delSize = 0;
	int idx = Stockmap[input];
	if (idx == 0) {
		cout << " There is Not Correct Stock ID" << endl;
	}
	else {
		cout << endl << " Which Field do you want to Update, Press the Number " << endl;
		cout << " (1) Category\n (2) Material\n (3) Price\n (4) Stock\n (5) Washing Info\n (6) Size" << endl;

		cout << ">> ";
		int fieldnum;
		cin >> fieldnum;
		cin.ignore();

		string change;
		cout << " Input the Data : ";
		getline(cin, change);

		Stock temp;
		int recaddr;

		StockFile.Open("fileOfStock.dat", ios::in|ios::out);
		StockFile.Read(temp, idx);

		switch (fieldnum) {
		case 1: temp.setCategory(change); break;
		case 2: temp.setMaterial(change); break;
		case 3: temp.setPrice(change); break;
		case 4:	temp.setStock(change); break;
		case 5: temp.setWashingInfo(change); break;
		case 6: temp.setSize(change); break;
		default: break;
		}
		//StockFile.Close();

		//MemberFile.Open("fileOfStock.dat", ios::out);
		delSize = StockFile.Delete(idx);
		cout << delSize;
		recaddr = StockFile.Append(temp);
		Stockmap[input] = recaddr;
		cout << " [UPDATE SUCCESS!]" << endl;
		StockFile.Close();
	}

	//TODO:cascasding
	cout << " Press any button to return to Record Update" << endl;
	cout << ">> ";
	_getch();

	TotalStockDelSize += delSize;

	return;
}
void PurchaseUpdate() {
	cout << " Please Input your Purchase ID to Update: ";

	string input;
	cin >> input;

	int delSize = 0;
	int idx = Purchasemap[input];
	if (idx == 0) {
		cout << " There is Not Correct Purchase ID" << endl;
	}
	else {
		cout << endl << " Which Field do you want to Update, Press the Number " << endl;
		cout << " (1) Stock ID\n (2) Member ID\n (3) Quantity" << endl;

		cout << ">> ";
		int fieldnum;
		cin >> fieldnum;
		cin.ignore();

		string change;
		cout << " Input the Data : ";
		getline(cin, change);

		Purchase temp;
		int recaddr;

		PurchaseFile.Open("fileOfPurchase.dat", ios::in|ios::out);
		PurchaseFile.Read(temp, idx);
		
		int errflag = 0;

		switch (fieldnum) {
		case 1: 
			if(Stockmap[change]!=0) temp.setStockId(change); 
			else {
				cout << " No Stock that has the name '" << change + "'" << endl;
				errflag = 1;
			}

			break;
		case 2: 
			if (Membermap[change] != 0) temp.setMemberId(change);
			else {
				cout << " No Member that has the name '" << change + "'" << endl;
				errflag = 1;
			}
			
			break;
		case 3: temp.setQuantity(change); break;
		default: break;
		}
		//PurchaseFile.Close();

		//MemberFile.Open("fileOfMember.dat", ios::out);
		if (errflag == 0) {
			delSize = PurchaseFile.Delete(idx);
			recaddr = PurchaseFile.Append(temp);
			Purchasemap[input] = recaddr;
			cout << " [UPDATE SUCCESS!]" << endl;

			TotalPurchaseDelSize += delSize;
		}
		PurchaseFile.Close();
	}

	//TODO:cascasding
	cout << " Press any button to return to Record Update" << endl;
	cout << ">> ";
	_getch();

	return;
}

void FileCompactionMember(int *num_member) {
	vector<Member> memlist;
	Member tmp;
	MemberFile.Open("fileOfMember.dat", ios::in);
	for (int i = 0; i < *num_member; i++) {
		MemberFile.Read(tmp);

		memlist.push_back(tmp);
	}

	Membermap.clear();

	MemberFile.Close();

	MemberFile.Create("fileOfMember.dat", ios::out);

	int recaddr;
	for (int i = 0; i < *num_member; i++) {

		if ((recaddr = MemberFile.Write(memlist[i])) == -1) {
			cout << "Write Error!" << endl;
		}
		else{
			Membermap.insert(make_pair(memlist[i].getId(),recaddr));
		}
	}

	MemberFile.Close();


	return;
}

void FileCompactionStock(int* num_stock){

	vector<Stock> stocklist;
	Stock tmp;
	StockFile.Open("fileOfStock.dat", ios::in);
	for (int i = 0; i < *num_stock; i++) {
		StockFile.Read(tmp);

		stocklist.push_back(tmp);
	}
		
	Stockmap.clear();

	StockFile.Close();

	StockFile.Create("fileOfStock.dat", ios::out);

	int recaddr;
	for (int i = 0; i < *num_stock; i++) {

		if ((recaddr = StockFile.Write(stocklist[i])) == -1) {
			cout << "Write Error!" << endl;
		}
		else{
			Stockmap.insert(make_pair(stocklist[i].getId(), recaddr));
		}
	}

	StockFile.Close();

	return;
}

void FileCompactionPurchase(int* num_purchase){

	vector<Purchase> purchaselist;
	Purchase tmp;
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);
	for (int i = 0; i < *num_purchase; i++) {
		PurchaseFile.Read(tmp);

		purchaselist.push_back(tmp);
	}
	
	Purchasemap.clear();
	PMwithMember.clear();
	PMwithStock.clear();

	PurchaseFile.Close();

	PurchaseFile.Create("fileOfPurchase.dat", ios::out);

	int recaddr;
	for (int i = 0; i < *num_purchase; i++) {

		if ((recaddr = PurchaseFile.Write(purchaselist[i])) == -1) {
			cout << "Write Error!" << endl;
		}
		else{
			Purchasemap.insert(make_pair(purchaselist[i].getId(), recaddr));
			PMwithMember[purchaselist[i].getMemberId()].push_back(recaddr);
			PMwithStock[purchaselist[i].getStockId()].push_back(recaddr);
		}
	}
	
	PurchaseFile.Close();

	return;
}