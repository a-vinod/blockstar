// Blockchain.cpp
#include <iostream>
#include <vector>

#include "block.h"

int main() {
  std::string from, to, amnt;
  std::vector<Block> chain;

  int batch_size;

  std::cout << "Batch Size: ";
  std::cin >> batch_size;
  std::cout << std::endl << "INPUT TRANSACTIONS" << std::endl;
  std::cout << "<from> <to> <amnt>" << std::endl;

  size_t tmp_hash;
  for (unsigned int i = 0; i < batch_size; i++) {
    if (i == 0) {
      // tmp_hash = DB QUERY
      tmp_hash = 0;
    }

    std::cin >> from >> to >> amnt;

    /*
    // Database call to compare prev_hash to the hash of the last
    // block on the database

    std::string last_hash = DB QUERY

    if (prev_hash != last_hash) {
        cout << "Corrupted blockchain!" << endl;
        return 1;
    }
    */

    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%YT%H:%M:%SZ", timeinfo);
    std::string t(buffer);

    Tx tx = Tx(from, to, stod(amnt), t);
    Block b = Block(tx, tmp_hash);
    chain.push_back(b);

    tmp_hash = b.get_hash();
  }

  std::cout << std::endl << "SENT TO BLOCKCHAIN:" << std::endl;
  std::cout << "<from>, <to>, <amnt>, <hash>, <prev_hash>" << std::endl;
  for (auto i = chain.begin(); i != chain.end(); ++i) {
    std::cout << i->get_tx().get_from() << ", " << i->get_tx().get_to() << ", "
              << i->get_tx().get_amnt() << ", " << i->get_hash() << ", "
              << i->get_prev_hash() << std::endl;
  }

  return 0;
}