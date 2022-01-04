#include <eosio/eosio.hpp>

using namespace eosio;

class tictactoe : eosio::contract {
  public:
    using contract::contract;

    [[eosio::action]] void start( eosio::name host, eosio::name challenger) {
        print("Welcome, challengers ", host," and ",challenger,"!");

    }
};