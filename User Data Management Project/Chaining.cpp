#include "Chaining.h"



int prime1 = 67;

int prime2 = 100153;

int no_of_accounts = 0;

#define ull unsigned long long


void printvec(vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << std::endl;
    }
    
}

void swap_using_refrence(int &a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

int partition(vector <int> &vec, int start, int end)
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
 
void quickSort(vector<int> &vec, int start, int end)
{
 

    if (start >= end){return;}
 

    int p = partition(vec, start, end);
 

    quickSort(vec, start, p - 1);
 

    quickSort(vec, p + 1, end);
}


ull raisetopow(ull x , int y)
{
    if(y == 0){return 1;}
    if(y == 1){return x;}
    else if(y%2 == 0){return raisetopow(x*x,y/2);}
    else if(y%2 == 1){ull k = x*(raisetopow(x*x,(y-1)/2)); return k;}
    return 0;
}

void Chaining::createAccount(std::string id, int count) {
    Account a;
    a.id = id;
    a.balance = count;

    int z = hash(id);

    
    if(Chaining::bankStorage2d.size() == 0)
    {
        Chaining::bankStorage2d.assign(prime2,bankStorage1d);
        Chaining::bankStorage2d[z].push_back(a);
        no_of_accounts ++;

    }
    else
    {
        Chaining::bankStorage2d[z].push_back(a);

        no_of_accounts ++;
    }


    
}

std::vector<int> Chaining::getTopK(int k) 
{
    std::vector<int> a;

    for(int i = 0; i<prime2; i++)
    {
        for(int j = 0; j < bankStorage2d[i].size(); j++)
        {
            a.push_back(bankStorage2d[i][j].balance);
        }
    }
    
    quickSort(a,0,a.size()-1);

    std::vector<int> b;
    if(a.size() >= k)
    {for(int i = 0; i < k; i++ ){b.push_back(a[a.size()-1-i]);}}
    else{for(int i = 0; i < a.size(); i++){b.push_back(a[a.size()-1-i]);}}



    return b; 
}

int Chaining::getBalance(std::string id) {
    int z = hash(id);
    if(bankStorage2d.size() == 0){return -1;}
    else
    {
        for(int i = 0; i < bankStorage2d[z].size(); i++){if(bankStorage2d[z][i].id == id){return bankStorage2d[z][i].balance;} else{continue;}}
        return -1;
    }

}

void Chaining::addTransaction(std::string id, int count) {
    int z = hash(id);
    if(bankStorage2d.size() == 0){return;}
    else
    {
        for(int i = 0; i < bankStorage2d[z].size(); i++){if(bankStorage2d[z][i].id == id){bankStorage2d[z][i].balance += count; return;} else{continue;}}
       
    }
    createAccount(id , count);

}

bool Chaining::doesExist(std::string id) {
    int z = hash(id);
    if(bankStorage2d.size() == 0){return false;}
    else
    {
        for(int i = 0; i < bankStorage2d[z].size(); i++){if(bankStorage2d[z][i].id == id){return true;} else{continue;}}
        return false;
    }

    
}

bool Chaining::deleteAccount(std::string id) {
    int z = hash(id);
    if(bankStorage2d.size() == 0){return false;}
    else
    {
        for(int i =0; i <bankStorage2d[z].size(); i++)
        {
            if(bankStorage2d[z][i].id == id)
            {   bankStorage2d[z].erase(bankStorage2d[z].begin()+i); 
                no_of_accounts --;
                return true;
            }
            else{continue;}
            
        }
        return false;
    }
}
int Chaining::databaseSize() {
    
    return no_of_accounts;
}

int Chaining::hash(std::string id) {
    ull z = 0;
    
    for(int i = 0; i <id.length(); i++)
    {
        z = z + ((char)id[i] - 47)*(raisetopow(prime1,i%11));
    }
    

    return z%prime2;
}