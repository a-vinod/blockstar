// block.cpp
#include "../include/block.h"

// Default Constructor
Block::Block() {
  // Do nothing
}

// Constructor
Block::Block(Tx tx, size_t prev_hash) {
  this->tx = tx;
  this->prev_hash = prev_hash;

  std::string tx_detail = tx.get_time() + std::to_string(prev_hash);
  this->hash = std::hash<std::string>{}(tx_detail);
}

// Getters
Tx Block::get_tx() { return this->tx; }

size_t Block::get_hash() { return this->hash; }

size_t Block::get_prev_hash() { return this->prev_hash; }