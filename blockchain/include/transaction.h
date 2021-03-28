// transaction.h
#ifndef TX_H
#define TX_H
#include <time.h>

#include <string>

class Tx {
 public:
  Tx();
  Tx(std::string from, std::string to, double amnt, std::string t);
  Tx(const Tx &obj);
  std::string get_from();
  std::string get_to();
  double get_amnt();
  std::string get_time();

 private:
  std::string from;
  std::string to;
  double amnt;
  std::string t;
};

#endif