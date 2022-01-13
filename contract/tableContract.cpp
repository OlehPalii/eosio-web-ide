#include <eosio/eosio.hpp>
#include <eosio/system.hpp> // need for eosio::time_point



//wallet list
//cleos wallet list


//create account
//cleos create account eosio table.main EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
//cleos create account eosio a.user EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
//cleos create account eosio b.user EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

// for one line deploy
//ls
//cd contract/

//build
//eosio-cpp -abigen -o tableContract.wasm tableContract.cpp
//or
//eosio-cpp tableContract.cpp

//deploy (for help: cleos set contract --help)
//cleos set contract tableContract ./tableContract -p hello@active
//or
//cleos set contract tableContract ./tableContract

//call
//cleos push action tableContract actionName '["bob"]' -p bob@active



TABLE surveillance_record{
    eosio::name subject;
    eosio::time_point  timestamp;
    uint64_t primary_key() const {return subject.value;}
    //EOSLIB_SERIALIZE (surveillance_record, (subject)(timestamp)) //call auto
};

using surveillance_index = eosio::multi_index<eosio::name("surveillance"), surveillance_record>;


/*
struct [[eosio::table("t_record"), eosio::contract("tableContract")]] t_record{
    eosio::name subject;
    eosio::time_point  timestamp;
    uint64_t primary_key() const {return subject.value;}
};
*/


/*
struct [[eosio::table("message"), eosio::contract("tableContract")]] message {
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


class tableContract : eosio::contract {
  public:
    using contract::contract;

    //[[eosio::action]] void post(uint64_t id) {}

    ACTION hi( eosio::name user){
        surveillance_index surveillance (get_self(), get_self().value);


        surveillance.emplace(get_self(), [&](auto& new_row){
            new_row.subject = user;
            new_row.timestamp = eosio::current_time_point();
        });
    }
};
