#include <eosio/eosio.hpp>

class [[eosio::contract]] tictactoe : eosio::contract {
  public:
    using contract::contract;

    [[eosio::action]] void start( eosio::name host, eosio::name challenger) {
        require_auth(host);
        //require_auth(eosio::name("tictactoe"));
        //require_auth(get_self());
        //require_auth(get_self());
        //check(has_auth(host) || has_auth(challenger), "User is not authorized to perform this action.");
        print("Welcome, challengers ", host," and ",challenger,"!");
    }
};