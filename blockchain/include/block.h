// block.h
#ifndef BLOCK_H
#define BLOCK_H
#include "transaction.h"

class Block {
 public:
  Block();
  Block(Tx tx, size_t prev_hash);
  Tx get_tx();
  size_t get_hash();
  size_t get_prev_hash();

 private:
  Tx tx;
  size_t hash;
  size_t prev_hash;
};

#endif