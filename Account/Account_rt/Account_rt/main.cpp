
#include <iostream>
#include "Order_rt.h"
#include "Position_rt.h"
using namespace std;
int main() {
	//��д�õ������rt namespace
	_CrtSetBreakAlloc(154);
	rt::Position_rt pos;
	cout << pos.send_order(1,1,rt::ORDER_DIRECTION::BUY_OPEN) << endl;
	//pos.static_message();
	//pos.save();
}