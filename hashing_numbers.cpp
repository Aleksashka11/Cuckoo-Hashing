#include "pch.h"
#include <string>
#define MAXN 8 
#define ver 2 
int hashtable[ver][MAXN];
int pos[ver];


void initTable()
{
  for (int j = 0; j < MAXN; j++)
    for (int i = 0; i < ver; i++)
      hashtable[i][j] = INT_MIN;
}

/* to get hash for a string
const int p = 31;
long long hash = 0, 
p_pow = 1;
string s = "cuckoo";
for (size_t i=0; i<s.length(); ++i)
{
	hash += (s[i] - 'a' + 1) * p_pow;
	p_pow *= p;
}*/

int hash(int function, int key)
{
  switch (function)
  {
  case 1: return key % MAXN;
  case 2: return (key / MAXN) % MAXN;
  }
}


void place(int key, int tableID, int cnt, int n)
{
  if (cnt == n)
  {
    printf("%d unpositioned\n", key);
    printf("Cycle present. REHASH.\n");
    return;
  }
  for (int i = 0; i < ver; i++)
  {
    pos[i] = hash(i + 1, key);
    if (hashtable[i][pos[i]] == key)
      return;
  }
  if (hashtable[tableID][pos[tableID]] != INT_MIN)
  {
    int dis = hashtable[tableID][pos[tableID]];
    hashtable[tableID][pos[tableID]] = key;
    place(dis, (tableID + 1) % ver, cnt + 1, n);
  }
  else 
    hashtable[tableID][pos[tableID]] = key;
}

void printTable()
{
  printf("Final hash tables:\n");

  for (int i = 0; i < ver; i++, printf("\n"))
    for (int j = 0; j < MAXN; j++)
      (hashtable[i][j] == INT_MIN) ? printf("- ") :
      printf("%d ", hashtable[i][j]);

  printf("\n");
}


void cuckoo(int keys[], int n)
{
   
  initTable();
  for (int i = 0, cnt = 0; i < n; i++, cnt = 0)
    place(keys[i], 0, cnt, n);
  printTable();
}


int main()
{

  int keys_1[] = { 30, 47, 11, 45, 26, 39, 68,
          61 };

  int n = sizeof(keys_1) / sizeof(int);

  cuckoo(keys_1, n);

  int keys_2[] = { 30, 47, 11, 45, 26, 39, 68,
          61 };

  int m = sizeof(keys_2) / sizeof(int);

  cuckoo(keys_2, m);

  return 0;
}
