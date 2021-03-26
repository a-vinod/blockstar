# Blockstar Blockchain

Blockstar implements a custom blockchain that stores reviews using cryptographic hashing to secure the integrity of the blockchain for every transaction.

## Usage

To run process a batch of transactions on a local machine, build the C++ program

```bash
> make all
> ./blockchain_pusher
```

First, enter the transaction batch size.

```bash
Batch Size: 2
```

Then, enter the transactions according to the format
```bash
<from> <to> <amnt>
Gaucho Campus_Store 4.55
Employer Gaucho 200
```

If the blockchain has not been corrutped, the program will output the hashes of each block that will be added to the blockchain. Otherwise, the program will exit with an error code.

## Other Notes
This blockchain is *not* decentralized in its current implmentation. Since it's hosted on a server, if the server is shut down, then the blockchain goes down with it. However, if the database is distribued across several systems and each machine runs a blockchain_pusher instance to process transactions, the system can achieve decentralization. The trust lies with the database host. And as more nodes operate the network, the more likely that a bad actor will not be able to damange the blockchain since each good faith acting node will pick up on the hash of the last block not matching that of the majority.