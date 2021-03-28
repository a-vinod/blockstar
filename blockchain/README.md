# Blockstar Blockchain

Blockstar implements a custom blockchain that stores reviews using cryptographic hashing to secure the integrity of the blockchain for every transaction.

## Installation

There are a few dependencies for this program to run. Namely:

[MySQL Connector](https://dev.mysql.com/doc/connector-cpp/8.0/en/connector-cpp-introduction.html)
```bash
apt-get install libmysqlcppconn7 # libmysqlcppconn7v5 for ubuntu
apt-get install libmysqlcppconn-dev
```

[Google Cloud SQL SDK](https://cloud.google.com/sdk/docs/install) configured to connect to the instance hosting the ledger.

## Usage

To run process a batch of transactions on a local machine, build the C++ program

```bash
> make all
> ./bin/blockchain_pusher
```

Enter the GCP password and transaction batch size.

```bash
Batch Size: 2
```

Then, enter the transactions according to the format
```bash
<src> <dst> <amnt>
Gaucho Campus_Store 4.55
Employer Gaucho 200
```

If the blockchain has not been corrutped, the program will output the hashes of each block that will be added to the blockchain. Otherwise, the program will exit with an error code.

## Example

```bash
> ./bin/blockchain_pusher 
GCP PASSWORD
Batch Size: 2

INPUT TRANSACTIONS
<src> <dst> <amnt>
x y 1
y z 1

SENT TO BLOCKCHAIN:
<src>, <dst>, <amnt>, <hash>, <prev_hash>
x,y,1.000000,4186681829403008919,15663852005051641758
y,z,1.000000,18399837352518714602,4186681829403008919
```

## Other Notes
This blockchain is *not* decentralized in its current implmentation. Since it's hosted on a server, if the server is shut down, then the blockchain goes down with it. However, if the database is distribued across several systems and each machine runs a blockchain_pusher instance to process transactions, the system can achieve decentralization. The trust lies with the database host. And as more nodes operate the network, the more likely that a bad actor will not be able to damange the blockchain since each good faith acting node will pick up on the hash of the last block not matching that of the majority.
