#include "Comp.h"

int prime1 = 67;
int prime2 = 300073;
int no_of_accounts = 0;

int collisions = 0;

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


// int hash2(std::string id)
// {
//     ull z = 0;

//     std::string numifsc = "";
//     for(int i = 0; i < 7; i++) {numifsc += id[i+4];}
 

//     for(int i = 0; i <numifsc.length(); i++)
//     {
//         z = z + ((char)numifsc[i] - '0')*(raisetopow(67,i));

//     }

//     return (z%470077);

// }


void Comp::createAccount(std::string id, int count) {

    Account b;
    b.id = id;
    b.balance = count;

    int z = hash(id);

    if(bankStorage2d.size() == 0)
    {
        bankStorage2d.assign(prime2,bankStorage1d);
        bankStorage2d[z].push_back(b);
        no_of_accounts ++;
    }
    else
    {
       // int r = hash2(id);

        // for(int i = 0; i < prime2; i++)
        // {
        //     if((bankStorage1d[(z+(i*r))%prime2].id == (std:: string)"") or (bankStorage1d[(z+(i*r))%prime2].id == (std:: string)"Deleted")){bankStorage1d[(z+(i*r))%prime2] = b; no_of_accounts++; break;}
        //     else{collisions++; continue;}
        // }
        Comp::bankStorage2d[z].push_back(b);

        no_of_accounts ++;

        
    }
}

std::vector<int> Comp::getTopK(int k) {
   
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

int Comp::getBalance(std::string id) {
    int z = hash(id);


    if(bankStorage2d.size() == 0){return -1;}
    else
    {
        for(int i = 0; i < bankStorage2d[z].size(); i++){if(bankStorage2d[z][i].id == id){return bankStorage2d[z][i].balance;} else{continue;}}
        return -1;
    }
}

void Comp::addTransaction(std::string id, int count) {
    int z = hash(id);

   
    if(bankStorage2d.size() == 0){return;}
    else
    {
        for(int i = 0; i < bankStorage2d[z].size(); i++){if(bankStorage2d[z][i].id == id){bankStorage2d[z][i].balance += count; return;} else{continue;}}
       
    }
    createAccount(id , count);
}

bool Comp::doesExist(std::string id) {
    int z = hash(id);
 
    if(bankStorage2d.size() == 0){return false;}
    else
    {
        for(int i = 0; i < bankStorage2d[z].size(); i++){if(bankStorage2d[z][i].id == id){return true;} else{continue;}}
        return false;
    }
}

bool Comp::deleteAccount(std::string id) {
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
int Comp::databaseSize() {
    return no_of_accounts;
}

int Comp::hash(std::string id) {
    ull z = 0;

    std::string caps = "";
    //std::string numifsc = "";
    std::string numacc = "";

    for(int i = 0; i < 4; i++) {caps += id[i];}
    //for(int i = 0; i < 7; i++) {numifsc += id[i+4];}
    for(int i = 0; i < 10; i++) {numacc += id[12+i];}
    
    for(int i = 0; i <caps.length(); i++)
    {
        z = z + ((char)caps[i] - 'A')*(raisetopow(33,i));
    }

    
    for(int i = 0; i <numacc.length(); i++)
    {
        z = z + ((char)numacc[i] - '9')*(raisetopow(67,i)) ;
    }
  
    return z%prime2;
    
   
    
        
    
}
