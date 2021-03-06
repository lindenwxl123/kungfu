//
// Created by qlu on 2019/1/28.
//

#ifndef PROJECT_SUBSCRIPTION_H
#define PROJECT_SUBSCRIPTION_H

#include <string>
#include <vector>
#include <iostream>

#include "md_struct.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <spdlog/spdlog.h>

namespace kungfu
{
    class SubscriptionStorage
    {
    public:
        SubscriptionStorage(const std::string& file_name): file_name_(file_name) {}

        void create_table_if_not_exist(SQLite::Database& db)
        {
            try
            {
                std::string sql = "create table if not exists subscription(\"instrument_id\" char(50), \"exchange_id\" char(50), \"instrument_type\" char(1));";
                db.exec(sql);
            }
            catch (std::exception &e)
            {
                SPDLOG_ERROR("exception: {}", e.what());
            }
        }

        void add_subscription(const std::string& instrument_id)
        {
            try
            {
                SQLite::Database db(file_name_.c_str(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
                create_table_if_not_exist(db);
                SQLite::Statement insert(db, "INSERT INTO subscription(instrument_id) VALUES(?)");
                insert.bind(1, instrument_id);
                insert.exec();
            }
            catch (std::exception &e)
            {
                SPDLOG_ERROR("exception: {}", e.what());
            }
        }

        void del_subscription(const std::string& instrument_id)
        {
            try
            {
                SQLite::Database db(file_name_.c_str(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
                create_table_if_not_exist(db);
                SQLite::Statement insert(db, "DELETE FROM subscription WHERE instrument_id=?");
                insert.bind(1, instrument_id);
                insert.exec();
            }
            catch (std::exception &e)
            {
                SPDLOG_ERROR("exception: {}", e.what());
            }
        }

        std::vector<Instrument> get_subscriptions()
        {
            SPDLOG_TRACE("");
            std::vector<Instrument> result;
            try
            {
                SPDLOG_TRACE("");
                SQLite::Database db(file_name_.c_str(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
                create_table_if_not_exist(db);
                SQLite::Statement query(db, "SELECT * FROM subscription");
                SPDLOG_TRACE("");            
                Instrument inst = {};
                while (query.executeStep())
                {
                    SPDLOG_TRACE("");
                    strcpy(inst.instrument_id, query.getColumn(0));
                    strcpy(inst.exchange_id, query.getColumn(1));
                    inst.instrument_type = (kungfu::InstrumentType)query.getColumn(2).getText()[0];
                    result.push_back(inst);
                    SPDLOG_TRACE("");            
                }
            }
            catch (std::exception &e)
            {
                SPDLOG_ERROR("exception: {}", e.what());
            }
            SPDLOG_TRACE(""); 
            return result;
        }

        bool is_subscription(const std::string& instrument_id)
        {
            bool result = false;
            try
            {
                SQLite::Database db(file_name_.c_str(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
                create_table_if_not_exist(db);
                SQLite::Statement query(db, "SELECT * FROM subscription WHERE instrument_id=?");
                query.bind(1, instrument_id);
                if (query.executeStep())
                {
                    result = true;
                }
            }
            catch (std::exception &e)
            {
                SPDLOG_ERROR("exception: {}", e.what());
            }
            return result;
        }

        void add_subscription(const Instrument& instrument)
        {
            try
            {
                SQLite::Database db(file_name_.c_str(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
                create_table_if_not_exist(db);
                SQLite::Statement insert(db, "INSERT INTO subscription(instrument_id, exchange_id, instrument_type) VALUES(?, ?, ?)");
                insert.bind(1, instrument.instrument_id);
                insert.bind(2, instrument.exchange_id);
                insert.bind(3, (char)instrument.instrument_type);
                insert.exec();
            }
            catch (std::exception &e)
            {
                SPDLOG_ERROR("exception: {}", e.what());
            }
        }

        void del_subscription(const Instrument& instrument)
        {
            try
            {
                SQLite::Database db(file_name_.c_str(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
                create_table_if_not_exist(db);
                SQLite::Statement query(db, "DELETE FROM subscription WHERE instrument_id = ? and exchange_id = ? and instrument_type = ?");
                query.bind(1, instrument.instrument_id);
                query.bind(2, instrument.exchange_id);
                query.bind(3, instrument.instrument_type);
                query.exec();
            }
            catch (std::exception &e)
            {
                SPDLOG_ERROR("exception: {}", e.what());
            }
        }

    private:
        std::string file_name_;
    };
}

#endif //PROJECT_SUBSCRIPTION_H
