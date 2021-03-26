// transaction.cpp
#include "transaction.h"

// Default Constructor
Tx::Tx() {
  // Do nothing
}

// Constructor
Tx::Tx(std::string from, std::string to, double amnt, std::string t) {
  this->from = from;
  this->to = to;
  this->amnt = amnt;
  this->t = t;
}

// Copy Constructor
Tx::Tx(const Tx &obj) {
  this->from = obj.from;
  this->to = obj.to;
  this->amnt = obj.amnt;
  this->t = obj.t;
}

// Getters
std::string Tx::get_from() { return this->from; }

std::string Tx::get_to() { return this->to; }

double Tx::get_amnt() { return this->amnt; }

std::string Tx::get_time() { return this->t; }