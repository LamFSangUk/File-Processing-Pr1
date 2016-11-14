#include"class_stock.h"

Stock::Stock(){

}
Stock::Stock(const string& id,const string& category,const string& material,const string& price, const string& stock,const string& washing_info,const string& size){
	this->id=id;
	this->category=category;
	this->material=material;
	this->price=price;
	this->stock=stock;
	this->washing_info=washing_info;
	this->size=size;
}
Stock::Stock(const Stock& p){
	this->id=p.id;
	this->category=p.category;
	this->material=p.material;
	this->price=p.price;
	this->stock=p.stock;
	this->washing_info=p.washing_info;
	this->size=p.size;
}
Stock::~Stock(){

}

Stock& Stock::operator= (const Stock& operand){
	this->id=operand.id;
	this->category=operand.category;
	this->material=operand.material;
	this->price=operand.price;
	this->stock=operand.stock;
	this->washing_info=operand.washing_info;
	this->size=operand.size;

	return (*this);
}
bool Stock::operator== (const Stock& operand){
	bool det;

	det=(this->id==operand.id);
	det|=(this->category==operand.category);
	det|=(this->material==operand.material);
	det|=(this->price==operand.price);
	det|=(this->stock==operand.stock);
	det|=(this->washing_info==operand.washing_info);
	det|=(this->size==operand.size);

	return det;
}
bool Stock::operator!= (const Stock& operand){
	return !((*this)==operand);
}

istream & operator>> (istream& is, Stock& m){
	string input_str;
	
 
	is.exceptions(istream::failbit | istream::badbit);

	try{
		getline(is,input_str);
	}catch(istream::failure e){
		return is;
	}

	istringstream iss(input_str);
	string inputdata[7];//id,category,material,price,stock,washing_info,size

	int i=0;
 
	while(i<6){
		getline(iss,inputdata[i],'|');
		i++;
	}
 
	getline(iss,inputdata[6],'\n');
 
	m=Stock(inputdata[0],inputdata[1],inputdata[2],inputdata[3],inputdata[4], inputdata[5],inputdata[6]);
 
	return is;
}
ostream & operator<< (ostream& os, Stock& m){
	os << " -[STOCK-INFO]-----------------" << endl;
	os << " ID : "+m.id << endl;
	os << " Category : "+m.category << endl;
	os << " Material : "+m.material << endl;
	os << " Price : " + m.price << endl;
	os << " Stock : " + m.stock << endl;
	os << " Washing Info : " + m.washing_info << endl;
	os << " Size : " + m.size << endl;
	os << " ------------------------------" << endl;
	return os;
}

void Stock::setId(const string& id){
	this->id=id;
}
void Stock::setCategory(const string& category){
	this->category=category;
}
void Stock::setMaterial(const string& material){
	this->material=material;
}
void Stock::setPrice(const string& price){
	this->price=price;
}
void Stock::setStock(const string& stock){
	this->stock=stock;
}
void Stock::setWashingInfo(const string& washing_info){
	this->washing_info=washing_info;
}
void Stock::setSize(const string& size){
	this->size=size;
}
string Stock::getId() {
	return this->id;
}

bool Stock::Pack(IOBuffer& Buffer) const {
	int numBytes;

	Buffer.Clear();

	numBytes = Buffer.Pack(this->id.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(this->category.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(this->material.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(this->price.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(this->stock.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(this->washing_info.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(this->size.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool Stock::Unpack(IOBuffer& Buffer) {
	int numBytes;
	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->id = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->category = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->material = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->price = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->stock = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->washing_info = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->size = buf;

	return true;
}