#include "class_member.h"

Member::Member(){
 
}
Member::Member(const string& id,const string& pw,const string& name,const string& phone,const string& addr,const string& birthday,const string& email,const string& level){
	this->id=id;
	this->pw=pw;
	this->name=name;
	this->phonenum=phone;
	this->address=addr;
	this->birthday=birthday;
	this->email=email;
	this->level=level;
}
Member::Member(const Member& p){
	this->id=p.id;
	this->pw=p.pw;
	this->name=p.name;
	this->phonenum=p.phonenum;
	this->address=p.address;
	this->birthday=p.birthday;
	this->email=p.email;
	this->level=p.level;
}

Member::~Member(){

}

Member& Member::operator=(const Member& operand){
	this->id=operand.id;
	this->pw=operand.pw;
	this->name=operand.name;
	this->phonenum=operand.phonenum;
	this->address=operand.address;
	this->birthday=operand.birthday;
	this->email=operand.email;
	this->level=operand.level;
 
	return (*this);
}

bool Member::operator==(const Member& operand){
	bool det;

	det=(this->id==operand.id);
	det|=(this->name==operand.name);
	det|=(this->phonenum==operand.phonenum);
	det|=(this->address==operand.address);
	det|=(this->birthday==operand.birthday);
	det|=(this->email==operand.email);

	return det;
}

bool Member::operator!=(const Member& operand){
	return !((*this)==operand);
}

istream & operator>> (istream & is, Member &m){
	
	string input_str;
	
 
	is.exceptions(istream::failbit | istream::badbit);

	try{
		getline(is,input_str);
	}catch(istream::failure e){
		return is;
	}

	istringstream iss(input_str);
	string inputdata[8];//id,pw,name,phone,addr,birthday,email,level

	int i=0;
 
	while(i<7){
		getline(iss,inputdata[i],'|');
		i++;
	}
 
	getline(iss,inputdata[7],'\n');
 
	m=Member(inputdata[0],inputdata[1],inputdata[2],inputdata[3],inputdata[4], inputdata[5],inputdata[6],inputdata[7]);
 
	return is;
}

ostream& operator<< (ostream& os, Member& m){
	os << " -[MEMBER-INFO]----------------" << endl;
	os << " ID : " + m.id << endl;
	os << " PW : " + m.pw << endl;
	os << " Name : " + m.name << endl;
	os << " Phone Number : " + m.phonenum << endl;
	os << " Address : " + m.address << endl;
	os << " Birthday : " + m.birthday << endl;
	os << " E-mail : " + m.email << endl;
	os << " LEVEL : " + m.level << endl;
	os << " ------------------------------" << endl;
	return os;
}

void Member::setId(const string& id){
	this->id=id;
}
void Member::setName(const string& name){
	this->name=name;
}
void Member::setPhonenum(const string& phonenum){
	this->phonenum=phonenum;
}
void Member::setAddress(const string& address){
	this->address=address;
}
void Member::setBirthday(const string& birthday){
	this->birthday=birthday;
}
void Member::setEmail(const string& email){
	this->email=email;
}

bool Member::Pack(IOBuffer& Buffer) const{
	int numBytes;

	Buffer.Clear();

	numBytes=Buffer.Pack(this->id.c_str());
	if(numBytes==-1) return false;
	numBytes=Buffer.Pack(this->pw.c_str());
	if(numBytes==-1) return false;
	numBytes=Buffer.Pack(this->name.c_str());
	if(numBytes==-1) return false;
	numBytes=Buffer.Pack(this->phonenum.c_str());
	if(numBytes==-1) return false;
	numBytes=Buffer.Pack(this->address.c_str());
	if(numBytes==-1) return false;
	numBytes=Buffer.Pack(this->birthday.c_str());
	if(numBytes==-1) return false;
	numBytes=Buffer.Pack(this->email.c_str());
	if(numBytes==-1) return false;
	numBytes=Buffer.Pack(this->level.c_str());
	if(numBytes==-1) return false;

	return true;
}

bool Member::Unpack(IOBuffer& Buffer){
	int numBytes;
	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->id = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->pw = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->name = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->phonenum = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->address = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->birthday = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->email = buf;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->level = buf;

	return true;
}

string Member::getId() {
	return this->id;
}
string Member::getPw() {
	return this->pw;
}
string Member::getLevel() {
	return this->level;
}