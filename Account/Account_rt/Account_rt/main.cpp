#include "Parameter_rt.h"
#include <iostream>
#include "Map_Any.h"
#include "EXCHANGE_CODE.h"
#include "Order_rt.h"
#include "Position_rt.h"
using namespace std;
int main() {
	//给写好的类添加rt namespace
	_CrtSetBreakAlloc(154);
	rt::Position_rt pos;
	cout << pos.send_order(1,1,rt::ORDER_DIRECTION::BUY_OPEN) << endl;
	//pos.static_message();
	//pos.save();
}