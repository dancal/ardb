/*
 * table.cpp
 *
 *  Created on: 2013-4-13
 *      Author: wqy
 */
#include "ardb.hpp"
#include <string>

using namespace ardb;

void test_table_insert_get(Ardb& db)
{
	DBID dbid("0");
	db.TClear(dbid, "mytable");
	SliceArray array;
	array.push_back("key1");
	array.push_back("key2");
	array.push_back("key3");
	db.TCreate(dbid, "mytable", array);

	SliceMap keyvals;
	keyvals["key1"] = "1";
	keyvals["key2"] = "2";
	keyvals["key3"] = "3";

	SliceMap colvals;
	colvals["name"] = "ardb";
	colvals["age"] = "20";
	colvals["birth"] = "1999";
	db.TReplace(dbid, "mytable", keyvals, colvals);

	SliceArray cols;
	cols.push_back("birth");
	cols.push_back("name");
	//cols.push_back("age");
	StringArray result;
	Conditions conds;
	Condition cond("key2", CMP_LESS_EQ, "2");
	conds.push_back(cond);
	db.TGet(dbid, "mytable", cols, conds, result);

	CHECK_FATAL( result.size() != 2, "%d", result.size());
	CHECK_FATAL( result[0] != "1999", "%s", result[0].c_str());
	CHECK_FATAL( result[1] != "ardb", "%s", result[0].c_str());
}

void test_table_update(Ardb& db)
{
	DBID dbid("0");
	db.TClear(dbid, "mytable");
	SliceArray array;
	array.push_back("key1");
	array.push_back("key2");
	array.push_back("key3");
	db.TCreate(dbid, "mytable", array);

	SliceMap keyvals;
	keyvals["key1"] = "10";
	keyvals["key2"] = "20";
	keyvals["key3"] = "30";

	SliceMap colvals;
	colvals["name"] = "ardb";
	colvals["age"] = "20";
	colvals["birth"] = "1999";
	db.TReplace(dbid, "mytable", keyvals, colvals);
	Conditions conds;
	Condition cond("key2", CMP_GREATE, "5");
	conds.push_back(cond);
	colvals["name"] = "newdb";
	colvals["age"] = "30";
	colvals["birth"] = "2000";
	db.TUpdate(dbid, "mytable", colvals, conds);

	SliceArray cols;
	cols.push_back("age");
	cols.push_back("name");
	StringArray result;
	Conditions xconds;
	Condition xcond("key2", CMP_GREATE, "2");
	xconds.push_back(xcond);
	db.TGet(dbid, "mytable", cols, xconds, result);

	CHECK_FATAL( result.size() != 2, "%d", result.size());
	CHECK_FATAL( result[0] != "30", "%s", result[0].c_str());
	CHECK_FATAL( result[1] != "newdb", "%s", result[0].c_str());
}

void test_tables(Ardb& db)
{
	test_table_insert_get(db);
	test_table_update(db);
}
