2020/05/19
wfh1300

Account_rt::m_transfers
{
	m_event_id:{
		datetime:
		currency: CNY
		amount:
		error_id: 0
		error_msg: �ɹ�
	}
	...
}


-- ����SIM���£���ΪREAL��Ӧ��д
Account_rt::m_banks
{
	m_bank_id:{
		id: m_bank_id,
		name: m_bankname,
		bank_account:
		fetch_amount: 0.0
		qry_count: 0.0
	}
	...
}


Position_rt::m_frozen
{
	order_id: moneyneed
	...
}
Account_rt::m_frozen
{
	order_id:{
		amount: �ڻ�����/��Ʊ����
		coeff: ϵ��,  cost = coeff * amount
		money: moneyneed
	}
	...
}


Account_rt::m_events
{
	datetimenow.str: ת�˳ɹ�${money} 
	...
	-- datetimenow.str: ת��ʧ�ܣ����� left: ${m_withdrawQuota}, ask: ${money}
}



Position_rt::m_trades ��������
Account_rt::m_trades
{
	trade_id:{
		seqno: m_event_id,
		user_id:
		trade_id:
		exchange_id:
		instrument_id:
		order_id:
		exchange_trade_id:
		direction: BUY/SELL
		offset: OPEN/CLOSE
		volume:
		price:
		trade_time:
		commission:
		trade_date_time:
	}
	...
}


Account_rt::m_orders
{
	order_id:{
		account_cookie: 
		user_id 
		instrument_id
		towards
		exchange_id
		order_time
		volume
		price
		seqno: m_event_id
		direction
		offset
		volume_origin
		price_type: "LIMIT"
		limit_price
		time_condition: GFD --struct TIME_CONDITION (GFD:������Ч)
		volume_condition
		insert_date_time
		exchange_order_id
		status: ALIVE ����QUEUED
		volume_left
		last_msg: �ѱ�
	}
	...
}
Position_rt::m_orders
{
	order_id:{
		position_id
		account_cookie
		instrument_id
		towards
		exchange_id
		order_time
		volume
		price
		order_id
		status
	}
	...
}