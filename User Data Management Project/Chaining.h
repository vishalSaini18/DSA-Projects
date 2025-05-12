#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

using std::vector;

class Chaining : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    std::vector<Account> bankStorage1d;
    std::vector<std::vector<Account>> bankStorage2d;

    Chaining () 
    {
        
    };
    

private:
    
    // Other data members and functions specific to Chaining
};

#endif // CHAINING_H
