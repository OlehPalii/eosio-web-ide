//#include <iostream>
#include <eosio/eosio.hpp>
#include <eosio/system.hpp> // need for eosio::time_point



//ls
//cd contract/

//cleos wallet list
//cleos wallet keys
//cleos get account table

//create account
//cleos create account eosio table EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
//cleos create account eosio a.user EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
//cleos create account eosio b.user EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

//build
//eosio-cpp table.cpp
//eosio-cpp -abigen -o table.wasm table.cpp
//eosio-cpp -abigen -o contract.wasm contract.cpp




//deploy (for help: cleos set contract --help)
//cleos set contract table ./table -p table@active
//or
//cleos set contract table ./table
//or
//cleos set code table table.wasm
//cleos set abi table table.abi

//call
//cleos push action table hi '["table"]' -p table

//show
//cleos get table table table surveillance

//:cleos get table tableacc tableacc tableName
//cleos get table table table surveillance


/*
TABLE surveillance_record{
    eosio::name subject;
    eosio::time_point  timestamp;
    uint64_t primary_key() const {return subject.value;}
    //EOSLIB_SERIALIZE (surveillance_record, (subject)(timestamp)) //call auto
};
using record_index = eosio::multi_index<eosio::name("surveillance"), surveillance_record>;
*/


struct [[eosio::table("record"), eosio::contract("table")]] record{
    eosio::name subject;
    eosio::time_point  timestamp;
    uint64_t primary_key() const {return subject.value;}

};
using record_index = eosio::multi_index<eosio::name("surveillance"), record>;

//using surveillance_index = eosio::multi_index<
//    "surveillance"_n, surveillance, eosio::indexed_by<"by.reply.to"_n, eosio::const_mem_fun<surveillance, uint64_t, &surveillance::get_name>>>;

/*
struct [[eosio::table("message"), eosio::contract("table")]] message {
    uint64_t    id       = {}; // Non-0
    uint64_t    reply_to = {}; // Non-0 if this is a reply
    eosio::name user     = {};
    std::string content  = {};
    uint64_t primary_key() const { return id; }
    uint64_t get_reply_to() const { return reply_to; }
};
using message_table = eosio::multi_index<
    "message"_n, message, eosio::indexed_by<"by.reply.to"_n, eosio::const_mem_fun<message, uint64_t, &message::get_reply_to>>>;

*/


class table : eosio::contract {
  public:
    using contract::contract;

    ACTION hi( eosio::name user){
        record_index surveillance (get_self(), get_self().value);
        //auto record = surveillance.get(user.value, "NO USER");

        auto it = surveillance.find(user.value);
        if(it == surveillance.end()){
            print("new user");
            surveillance.emplace(get_self(), [&](auto& new_row){
                new_row.subject = user;
                new_row.timestamp = eosio::current_time_point();
            });
        }else{
            print("old user");
            surveillance.modify(it, get_self(), [&](auto& new_row){
                new_row.subject = user;
                new_row.timestamp = eosio::current_time_point();
            });
        }
        
    }

    ACTION deletedata(){
        require_auth(get_self());
        record_index surveillance (get_self(), get_self().value);
        auto it = surveillance.begin();
        while(it != surveillance.end()){
            it = surveillance.erase(it);
        }
    }
};
