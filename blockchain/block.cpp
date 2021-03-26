// block.cpp
#include "block.h"

// Default Constructor
Block::Block() {
  // Do nothing
}

// Constructor
Block::Block(Tx tx, size_t prev_hash) {
  this->tx = tx;
  this->prev_hash = prev_hash;

  std::string tx_detail = tx.get_from() + tx.get_to() +
                          std::to_string(tx.get_amnt()) + tx.get_time();
  this->hash = std::hash<std::string>{}(tx_detail);
}

// Getters
Tx Block::get_tx() { return this->tx; }

size_t Block::get_hash() { return this->hash; }

size_t Block::get_prev_hash() { return this->prev_hash; }