#include"data_in_out.h"
#include"account.h"
#include"ledger.h"
#include<mysql.h>
#include<iostream>
#include<vector>
#include<iterator>
#include<string>
#include<map>

void account_reclaim(MYSQL* conn) {
	if (mysql_query(conn, "SELECT id, name, holder, number, money FROM subaccount")) {     //��ѯ����
		std::cerr << "SELECT query failed. Error: " << mysql_error(conn) << std::endl;
	}
	MYSQL_RES* result = mysql_store_result(conn);
	if (result == NULL) {
		std::cerr << "mysql_store_result() failed. Error: " << mysql_error(conn) << std::endl;
	}
	MYSQL_ROW row;
	int id;
	std::string name;
	std::string holder;
	std::string number;
	double money;
	std::string delete_query;
	while ((row = mysql_fetch_row(result)) != NULL) {
		id = atoi(row[0]);
		name = row[1];
		holder = row[2];
		number = row[3];
		money = atof(row[4]);
		Account* ptr = new Account(name, holder, number, money);
		all_subaccount.push_back(ptr);
		delete_query = "DELETE FROM subaccount WHERE id = " + std::to_string(id);
		mysql_query(conn, delete_query.c_str());
	}
	std::cout << "�˻��������" << std::endl;
}

void account_storage(MYSQL* conn){
	std::vector<Account*>::iterator it = all_subaccount.begin();
	std::string insert_query;
	std::string name;
	std::string holder;
	std::string number;
	double money;
	while (it != all_subaccount.end()) {
		name = (*it)->get_name();
		holder = (*it)->get_holder();
		number = (*it)->get_number();
		money = (*it)->get_money();
		insert_query = "INSERT INTO subaccount(name, holder, number, money) VALUES('" + name + "', '" + holder + "', '" + number + "', " + std::to_string(money) + ")";
		mysql_query(conn, insert_query.c_str());
		delete (*it);
		it = all_subaccount.erase(it);       //���µ���������ָֹ������
	}
	std::cout << "�˻���Ϣ�ѱ���" << std::endl;
}

void ledger_reclaim(MYSQL* conn) {
	if (mysql_query(conn, "SELECT id, date1, date2, transaction_partners, account, in_or_out, transaction_amount, sle_type, note  FROM book")) {     //��ѯ����
		std::cerr << "SELECT query failed. Error: " << mysql_error(conn) << std::endl;
	}
	MYSQL_RES* result = mysql_store_result(conn);
	MYSQL_ROW row;
	int date1, date2;
	int id, year, month, day, hour, minute, in_or_out;
	std::string transaction_partners, account, sle_type, note,delete_query;
	double transaction_amount;
	while ((row = mysql_fetch_row(result)) != NULL) {
		id = atoi(row[0]);
		date1 = atoi(row[1]);
		month = date1 % 100;
		year = (date1 - month) / 100;
		date2 = atoi(row[2]);
		minute = date2 % 100;
		hour = ((date2 - minute) / 100) % 100;
		day = (((date2 - minute) / 100) - hour) / 100;
		Date d(year, month, day, hour, minute);
		transaction_partners = row[3];
		account = row[4];
		in_or_out = atoi(row[5]);
		transaction_amount = atof(row[6]);
		sle_type = row[7];
		note = row[8];
		std::vector<Account*>::iterator it;
		it = find_if(all_subaccount.begin(), all_subaccount.end(), [account](Account* temp) {
			return account == temp->get_name();
			});
		Account* ptr = (*it);
		Ledger* ledger_ptr = new Ledger(d, transaction_partners, ptr, in_or_out, transaction_amount, sle_type, note);
		Book.push_back(ledger_ptr);
		delete_query = "DELETE FROM book WHERE id = " + std::to_string(id);
		mysql_query(conn, delete_query.c_str());
	}
	std::cout << "���˱��������" << std::endl;
}

void ledger_storage(MYSQL* conn) {
	std::vector<Ledger*>::iterator it = Book.begin();
	int date1, date2;
	int in_or_out;
	std::string transaction_partners, account, sle_type, note, insert_query;
	double transaction_amount;
	while (it != Book.end()) {
		date1 = (*it)->date.code1();
		date2 = (*it)->date.code2();
		transaction_partners = (*it)->get_transaction_partners();
		account = (*it)->get_subaccount();
		in_or_out = (*it)->get_in_or_out();
		transaction_amount = (*it)->get_transaction_amount();
		sle_type = (*it)->get_sle_type();
		note = (*it)->get_note();
		insert_query = "INSERT INTO book(date1, date2, transaction_partners, account, in_or_out, transaction_amount, sle_type, note) VALUES(" + std::to_string(date1) + ", " + std::to_string(date2) 
		+ ", '"+transaction_partners + "', '" + account + "', " + std::to_string(in_or_out) + ", " + std::to_string(transaction_amount) + ", '" + sle_type + "', '" + note + "')";
		mysql_query(conn, insert_query.c_str());
		delete (*it);
		it = Book.erase(it);
	}
	std::cout << "���˱���Ϣ�ѱ���" << std::endl;
}

void plan_reclaim(MYSQL* conn) {
	if (mysql_query(conn, "SELECT id, medicine, food, accomodation, transportation, entertainment, investment, social_connect, other, sum  FROM plan_collection")) {     //��ѯ����
		std::cerr << "SELECT query failed. Error: " << mysql_error(conn) << std::endl;
	}
	MYSQL_RES* result = mysql_store_result(conn);
	MYSQL_ROW row;
	int id;
	double sum;
	std::string delete_query;
	std::map<std::string, double> plan_out_type = {
		{"ҽ��", 0.0},{"ʳƷ", 0.0},{"ס��", 0.0},
		{"��ͨ", 0.0},{"����", 0.0},{"Ͷ��", 0.0},
		{"�罻", 0.0},{"����", 0.0}
	};
	while ((row = mysql_fetch_row(result)) != NULL) {
		id = atoi(row[0]);
		plan_out_type["ҽ��"] = atof(row[1]);
		plan_out_type["ʳƷ"] = atof(row[2]);
		plan_out_type["ס��"] = atof(row[3]);
		plan_out_type["��ͨ"] = atof(row[4]);
		plan_out_type["����"] = atof(row[5]);
		plan_out_type["Ͷ��"] = atof(row[6]);
		plan_out_type["�罻"] = atof(row[7]);
		plan_out_type["����"] = atof(row[8]);
		sum = atof(row[9]);
		Plan p(sum, plan_out_type);
		plan_collection.push_back(p);
		delete_query = "DELETE FROM plan_collection WHERE id = " + std::to_string(id);
		mysql_query(conn, delete_query.c_str());
	}
	std::cout << "���ѹ滮�������" << std::endl;
}

void plan_storage(MYSQL* conn) {
	std::vector<Plan>::iterator it = plan_collection.begin();
	std::string insert_query;
	double medicine, food, accomodation, transportation, entertainment, investment, social_connect, other, sum;
	while (it != plan_collection.end()) {
		sum = it->get_plan_out_sum();
		medicine = it->plan_out_type["ҽ��"];
		food = it->plan_out_type["ʳƷ"];
		accomodation = it->plan_out_type["ס��"];
		transportation = it->plan_out_type["��ͨ"];
		entertainment = it->plan_out_type["����"];
		investment = it->plan_out_type["Ͷ��"];
		social_connect = it->plan_out_type["�罻"];
		other = it->plan_out_type["����"];
		insert_query = "INSERT INTO plan_collection(medicine, food, accomodation, transportation, entertainment, investment, social_connect, other, sum) VALUES(" 
			+ std::to_string(medicine) + ", " + std::to_string(food) + ", " + std::to_string(accomodation) + ", " + std::to_string(transportation) + ", " + std::to_string(entertainment) 
			+ ", " + std::to_string(investment) + ", " + std::to_string(social_connect) + ", " + std::to_string(other) + ", " + std::to_string(sum) + ")";
		mysql_query(conn, insert_query.c_str());
		++it;
	}
	std::cout << "���ѹ滮�ѱ���" << std::endl;
}