#ifndef __PROG_ONLINESHOPPINGSYSTEM__
#define __PROG_ONLINESHOPPINGSYSTEM__

#include<map>
#include<vector>
#include"recfile.h"
#include"delim.h"
#include"class_member.h"
#include"class_purchase.h"
#include"class_stock.h"
#include"conio.h"

using namespace std;

void OnlineShoppingSystem(int*,int*,int*);
void RecordSearch();
void MemberResult();
void StockResult();
void PurchaseResult();
void RecordInsert(int*,int*,int*);
void MemberInsert(int*);
void StockInsert(int*);
void PurchaseInsert(int*);
void RecordDelete(int*, int*, int*);
void MemberDelete(int*,int*);
void StockDelete(int*,int*);
void PurchaseDelete(int*);
void RecordUpdate();
void MemberUpdate();
void StockUpdate();
void PurchaseUpdate();
void FileCompactionMember(int*);
void FileCompactionStock(int*);
void FileCompactionPurchase(int*);

#endif