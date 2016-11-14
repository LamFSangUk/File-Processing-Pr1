#ifndef __CLASS_STOCK__
#define __CLASS_STOCK__

#include<string>
#include<sstream>
#include"iobuffer.h"
#include"delim.h"

#define STDMAXBUF 512

using namespace std;

class Stock{
private:
	string id;
	string category;
	string material;
	string price;
	string stock;
	string washing_info;
	string size;
 
public:
	Stock();
	Stock(const string& id,const string& category,const string& material,const string& price, const string& stock,const string& washing_info,const string& size);
	Stock(const Stock& p);
	~Stock();

	Stock& operator= (const Stock& operand);
	bool operator== (const Stock& operand);
	bool operator!= (const Stock& operand);

	friend istream & operator>> (istream& is, Stock& m);
	friend ostream & operator<< (ostream& os, Stock& m);//Todo

	void setId(const string& id);
	void setCategory(const string& category);
	void setMaterial(const string& material);
	void setPrice(const string& price);
	void setStock(const string& stock);
	void setWashingInfo(const string& washing_info);
	void setSize(const string& size);
	string getId();

	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer&);
};

#endif