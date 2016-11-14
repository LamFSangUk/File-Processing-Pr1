#include"class_purchase.h"

Purchase::Purchase(){

}
Purchase::Purchase(const string& purchase_id,const string& stock_id,const string& member_id,const string& quantity){
	this->purchase_id=purchase_id;
	this->stock_id=stock_id;
	this->member_id=member_id;
	this->quantity=quantity;
}
Purchase::Purchase(const Purchase& p){
	this->purchase_id=p.purchase_id;
	this->stock_id=p.stock_id;
	this->member_id=p.member_id;
	this->quantity=p.quantity;
}
Purchase::~Purchase(){

}

Purchase& Purchase::operator= (const Purchase& operand){
	this->purchase_id=operand.purchase_id;
	this->stock_id=operand.stock_id;
	this->member_id=operand.member_id;
	this->quantity=operand.quantity;
	
	return (*this);
}
bool Purchase::operator== (const Purchase& operand){
	bool det;
	det=(this->purchase_id==operand.purchase_id);
	det|=(this->stock_id==operand.stock_id);
	det|=(this->member_id==operand.member_id);
	det|=(this->quantity==operand.quantity);

	return det;
}
bool Purchase::operator!= (const Purchase& operand){
	return !((*this)==operand);
}

istream& operator>> (istream& is, Purchase& m){
	string input_str;
	
	is.exceptions(istream::failbit | istream::badbit);

	try{
		getline(is,input_str);
	}catch(istream::failure e){
		return is;
	}

	istringstream iss(input_str);

	int i=0;
	string inputdata[4];

	while(i<4){
		getline(iss,inputdata[i],'|');
		i++;
	}

	getline(iss,inputdata[3],'\n');

	m=Purchase(inputdata[0],inputdata[1],inputdata[2],inputdata[3]);

	return is;
}
ostream& operator<< (ostream& os, Purchase& m){
	
	os << " -[PURCHASE-INFO]--------------" << endl;
	os << " Purchase ID : " + m.purchase_id << endl;
	os << " Stock ID : " + m.stock_id << endl;
	os << " Member ID : " + m.member_id << endl;
	os << " Quantity : " + m.quantity << endl;
	os << " ------------------------------" << endl;
	return os;
}

void Purchase::setPurchaseId(const string& purchase_id){
	this->purchase_id=purchase_id;
}
void Purchase::setStockId(const string& stock_id){
	this->stock_id=stock_id;
}
void Purchase::setMemberId(const string& member_id){
	this->member_id=member_id;
}
void Purchase::setQuantity(const string& quantity){
	this->quantity=quantity;
}
string Purchase::getId() {
	return this->purchase_id;
}
string Purchase::getMemberId() {
	return this->member_id;
}
string Purchase::getStockId() {
	return this->stock_id;
}

bool Purchase::Pack(IOBuffer& Buffer) const {
	int numBytes;

	Buffer.Clear();

	numBytes = Buffer.Pack(this->purchase_id.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(this->stock_id.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(this->member_id.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(this->quantity.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool Purchase::Unpack(IOBuffer& Buffer) {
	int numBytes;
	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->purchase_id = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->stock_id = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->member_id = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->quantity = buf;

	return true;
}