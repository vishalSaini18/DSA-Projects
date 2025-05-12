#include "LinearProbing.h"
#include <cassert>

int prime1 = 67;

int prime2 = 100057;

int no_of_accounts = 0;


#define ull unsigned long long

ull raisetopow(ull x , int y)
{
    if(y == 0){return 1;}
    if(y == 1){return x;}
    else if(y%2 == 0){return raisetopow(x*x,y/2);}
    else if(y%2 == 1){ull k = x*(raisetopow(x*x,(y-1)/2)); return k;}
    return 0;
}


void swap_using_refrence(int &a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

int partition(std::vector <int> &vec, int start, int end)
{
 
    int pivot = vec[start];
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (vec[i] <= pivot)
            count++;
    }
 
    
    int pivotIndex = start + count;
   swap_using_refrence(vec[pivotIndex], vec[start]);
 

    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (vec[i] <= pivot) {
            i++;
        }
 
        while (vec[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap_using_refrence(vec[i++], vec[j--]);
        }
    }
 
    return pivotIndex;
}
 
void quickSort(std::vector<int> &vec, int start, int end)
{
    if (start >= end){return;}
    int p = partition(vec, start, end);
    quickSort(vec, start, p - 1);
    quickSort(vec, p + 1, end);
}




void LinearProbing::createAccount(std::string id, int count) 
{
    Account a;
    a.id = "";
    a.balance = -1;

    Account b;
    b.id = id;
    b.balance = count;

    int z = hash(id);

    if(bankStorage1d.size() == 0)
    {
        bankStorage1d.assign(prime2,a);
        bankStorage1d[z] = b;
        no_of_accounts ++;
    }
    else
    {
        for(int i = 0; i < prime2; i++)
        {
            if((bankStorage1d[(z+i)%prime2].id == (std:: string)"") or (bankStorage1d[(z+i)%prime2].id == (std:: string)"Deleted")){bankStorage1d[(z+i)%prime2] = b; no_of_accounts++; break;}
            else{continue;}
        }
    }
}

std::vector<int> LinearProbing::getTopK(int k) 
{
    std::vector<int> b;
    for(int i = 0; i < prime2; i++)
    {
        if(bankStorage1d[i].balance >= 0){b.push_back(bankStorage1d[i].balance);}
    }

    quickSort(b,0,b.size()-1);

    std::vector<int> p;
    if(b.size() >= k)
    {for(int i = 0; i < k; i++ ){p.push_back(b[b.size()-1-i]);}}
    else{for(int i = 0; i < b.size(); i++){p.push_back(b[b.size()-1-i]);}}

    return p;
}

int LinearProbing::getBalance(std::string id) 
{
    int z = hash(id);

    if(bankStorage1d.size() == 0){return -1;}
    else{
    for(int i = 0; i < prime2; i++)
    {
        if(bankStorage1d[(z+i)%prime2].id == id){return bankStorage1d[(z+i)%prime2].balance; }
        else{continue;}
    }
    return -1;
    }

}

void LinearProbing::addTransaction(std::string id, int count) {
    int z = hash(id);

    if(bankStorage1d.size() == 0){return;}
    else{
    for(int i = 0; i < prime2; i++)
    {
        if(bankStorage1d[(z+i)%prime2].id == id){bankStorage1d[(z+i)%prime2].balance += count; return; }
        else{continue;}
        
    }
    createAccount(id , count);

    }
}

bool LinearProbing::doesExist(std::string id) {
    int z = hash(id);
 
    if(bankStorage1d.size() == 0){return false;}
    else{
    for(int i = 0; i < prime2; i++)
    {
        if(bankStorage1d[(z+i)%prime2].id == id){return true; }
        else{continue;}
    }
    return false;
    }
}

bool LinearProbing::deleteAccount(std::string id) {
    int z = hash(id);
 
    if(bankStorage1d.size() == 0){return false;}
    else{
    for(int i = 0; i < prime2; i++)
    {
        if(bankStorage1d[(z+i)%prime2].id == id)
        {
            bankStorage1d[(z+i)%prime2].id = "Deleted";
            bankStorage1d[(z+i)%prime2].balance = -2;
            no_of_accounts --;
            return true;
        }
        else{continue;}
    }
    return false;
    }
}
int LinearProbing::databaseSize() {
    
    return no_of_accounts;
}

int LinearProbing::hash(std::string id) {
    ull z = 0;
    
    for(int i = 0; i <id.length(); i++)
    {
        z = z + ((char)id[i] - 47)*(raisetopow(prime1,i%11));
    }
    

    return z%prime2;

}
/*
int main(void)
{
    LinearProbing db;

    db.createAccount("Alice", 1000);


    db.createAccount("Bob", 1500);

    db.createAccount("Charlie", 2000);


    assert(db.getBalance("Alice") == 1000);
    assert(db.getBalance("Bob") == 1500);
    assert(db.getBalance("Charlie") == 2000);

    db.addTransaction("Alice", -200);
    db.addTransaction("Bob", 300);
    db.addTransaction("Charlie", -400);
    //db.addTransaction("anup",22);

    assert(db.getBalance("Alice") == 800);
    assert(db.getBalance("Bob") == 1800);
    assert(db.getBalance("Charlie") == 1600);

    std::vector<int> topBalances = db.getTopK(2);
    assert(topBalances.size() == 2);
    assert(topBalances[0] == 1800);
    assert(topBalances[1] == 1600);

    assert(db.databaseSize() == 3);

    assert(db.doesExist("Alice"));
    assert(!db.doesExist("Eve"));
    std::cout << db.getBalance("Alice");
    std::cout << db.databaseSize();
}*/