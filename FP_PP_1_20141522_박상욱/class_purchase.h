#ifndef __CLASS_PURCHASE__
#define __CLASS_PURCHASE__

#include<string>
#include<sstream>
#include"iobuffer.h"
#include"delim.h"

#define STDMAXBUF 512

using namespace std;

class Purchase{
private:
	string purchase_id;
	string stock_id;
	string member_id;
	string quantity;
public:
	Purchase();
	Purchase(const string& purchase_id,const string& stock_id,const string& member_id,const string& quantity);
	Purchase(const Purchase& p);
	~Purchase();

	Purchase& operator= (const Purchase& operand);
	bool operator== (const Purchase& operand);
	bool operator!= (const Purchase& operand);

	friend istream& operator>> (istream& is, Purchase& m);
	friend ostream& operator<< (ostream& os, Purchase& m);

	void setPurchaseId(const string& purchase_id);
	void setStockId(const string& stock_id);
	void setMemberId(const string& member_id);
	void setQuantity(const string& quantity);
	string getId(); 
	string getStockId(); 
	string getMemberId();

	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer&);
};

#endif