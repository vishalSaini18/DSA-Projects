#include "CubicProbing.h"

int prime1 = 67;
int prime2 = 302429;
int no_of_accounts = 0;

// /int collisions = 0;

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


void CubicProbing::createAccount(std::string id, int count) {
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
            if((bankStorage1d[(z+(i*i*i))%prime2].id == (std:: string)"") or (bankStorage1d[(z+(i*i*i))%prime2].id == (std:: string)"Deleted")){bankStorage1d[(z+(i*i*i))%prime2] = b; no_of_accounts++; break;}
            else{/*collisions++;*/ continue;}
        }

        
    }
}

std::vector<int> CubicProbing::getTopK(int k) {
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

int CubicProbing::getBalance(std::string id) {
    int z = hash(id);


    if(bankStorage1d.size() == 0){return -1;}
    else{
    for(ull i = 0; i < prime2; i++)
    {
        if(bankStorage1d[(z+(i*i*i))%prime2].id == (std:: string)""){return -1;}
        else if(bankStorage1d[(z+(i*i*i))%prime2].id == (std:: string)"Deleted"){continue;}
        else
        {
            if(bankStorage1d[(z+(i*i*i))%prime2].id == id){return bankStorage1d[(z+(i*i*i))%prime2].balance;}
            else{continue;}
        }

    }
    return -1;
    }
}

void CubicProbing::addTransaction(std::string id, int count) {
    int z = hash(id);

    if(bankStorage1d.size() == 0){return;}
    else{
    for(ull i = 0; i < prime2; i++)
    {
        if(bankStorage1d[(z+(i*i*i))%prime2].id == (std:: string)""){createAccount(id, count);}
        else if(bankStorage1d[(z+(i*i*i))%prime2].id == (std:: string)"Deleted"){continue;}
        else
        {
            if(bankStorage1d[(z+(i*i*i))%prime2].id == id){bankStorage1d[(z+(i*i*i))%prime2].balance += count; return;}
            else{continue;}
        }
        
    }
    return;
    }
}

bool CubicProbing::doesExist(std::string id) {
    int z = hash(id);
 
    if(bankStorage1d.size() == 0){return false;}
    else{
    for(ull i = 0; i < prime2; i++)
    {
        if(bankStorage1d[(z+(i*i*i))%prime2].id == (std:: string)""){return false; }
        else if(bankStorage1d[(z+(i*i*i))%prime2].id == (std:: string)"Deleted"){continue;}
        else
        {
            if(bankStorage1d[(z+(i*i*i))%prime2].id == id){return true;}
            else{continue;}
        }
    }
    return false;
    }
}

bool CubicProbing::deleteAccount(std::string id) {
    int z = hash(id);
 
    if(bankStorage1d.size() == 0){return false;}
    else{
    for(ull i = 0; i < prime2; i++)
    {
        if(bankStorage1d[(z+i*i*i)%prime2].id == (std:: string)""){return false;}
        else if(bankStorage1d[(z+i*i*i)%prime2].id == (std:: string)"Deleted"){continue;; }
        else
        {
            if(bankStorage1d[(z+i*i*i)%prime2].id == id)
            {
                bankStorage1d[(z+i*i*i)%prime2].id = "Deleted";
                bankStorage1d[(z+i*i*i)%prime2].balance = -2;
                no_of_accounts --;
                return true;
            }
            else{continue;}
        }
    }
    return false;
    }
}
int CubicProbing::databaseSize() {
    return no_of_accounts;
}

int CubicProbing::hash(std::string id) {
    ull z = 0;
    
    for(int i = 0; i <id.length(); i++)
    {
        z = z + ((char)id[i] - 47)*(raisetopow(prime1,i%11));
    }
    

    return z%prime2;
}


