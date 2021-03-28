// Blockchain.cpp
#include "../include/cppconn/driver.h"
#include "../include/cppconn/exception.h"
#include "../include/cppconn/prepared_statement.h"
#include "../include/cppconn/resultset.h"
#include "../include/cppconn/statement.h"
#include "../include/mysql_connection.h"
#include <stdlib.h>

#include <iostream>
#include <sstream>
#include <vector>

#include "../include/block.h"

int main() {
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;
  sql::PreparedStatement *pstmt;

  std::string prev_hash;
  unsigned int max_idx;
  try {
    std::string pass;
    std::cin >> pass;

    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", pass);
    /* Connect to the MySQL test database */
    con->setSchema("ledger");

    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM blockchain ORDER BY id");
    sql::ResultSetMetaData *res_meta = res->getMetaData();
    unsigned long long columns = res_meta->getColumnCount();

    int i = 0;

    // Validate blockchain
    while (res->next()) {
      if (i == 0) {
        prev_hash = "-1";
      }

      if (prev_hash != res->getString(columns)) {
        std::cout << "Blockchain corrupted at " << res->getInt(1) << std::endl;
        return 1;
      }

      // TODO: Recompute hash based on hash function w/ transaciton detail
      prev_hash = res->getString(columns - 1);

      i++;
      max_idx = res->getInt(1);
    }
    std::cout << max_idx << std::endl;

  } catch (sql::SQLException &e) {
    std::cout << "# ERR: SQLException in " << __FILE__;
    std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
    std::cout << "# ERR: " << e.what();
    std::cout << " (MySQL error code: " << e.getErrorCode();
    std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
  }

  std::string from, to, amnt;
  std::vector<Block> chain;

  unsigned int batch_size;

  std::cout << "Batch Size: ";
  std::cin >> batch_size;
  std::cout << std::endl << "INPUT TRANSACTIONS" << std::endl;
  std::cout << "<src> <dst> <amnt>" << std::endl;

  std::stringstream sstream(prev_hash);
  size_t tmp_hash;
  for (unsigned int i = 0; i < batch_size; i++) {
    if (i == 0) {
      sstream >> tmp_hash;
    }

    std::cin >> from >> to >> amnt;

    time_t rawtime;
    struct tm *timeinfo;
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
  std::cout << "<src>, <dst>, <amnt>, <hash>, <prev_hash>" << std::endl;

  std::string data;
  std::string insert;
  for (auto i = chain.begin(); i != chain.end(); ++i) {
    max_idx++;
    data = "(" + std::to_string(max_idx) + ",'" + i->get_tx().get_from() +
           "','" + i->get_tx().get_to() + "'," +
           std::to_string(i->get_tx().get_amnt()) + ",'" +
           std::to_string(i->get_hash()) + "','" +
           std::to_string(i->get_prev_hash()) + "')";

    std::cout << data << std::endl;

    pstmt = con->prepareStatement(
        "INSERT INTO blockchain (id, src, dst, amnt, hash, prev_hash) VALUES "
        "(?,?,?,?,?,?)");
    pstmt->setUInt(1, max_idx);
    pstmt->setString(2, i->get_tx().get_from());
    pstmt->setString(3, i->get_tx().get_to());
    pstmt->setDouble(4, i->get_tx().get_amnt());
    pstmt->setString(5, std::to_string(i->get_hash()));
    pstmt->setString(6, std::to_string(i->get_prev_hash()));
    pstmt->executeUpdate();
  }

  delete res;
  delete stmt;
  delete con;
  return 0;
}