#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int htoi (char str[]) {
  int res = 0;
  
  int len = strlen(str);
  // go backwards
  for (int i = len-1; i >= 0; i--) {
    char curr = tolower(str[i]);
    
    if (curr == 'x') break;// return res;
    
    if (isdigit(curr)) {
      curr -= '0';
    } else {
      curr -= 'a' - 10;
    }

    int order = len - i - 1;
    res += curr * pow(16, order);

  }

  return res;
}

void squezze(char s1[], char s2[]) {
  int len = strlen(s1);
  char newstr[len];
  char curr;

  int i = 0;
  int l = 0;
  while ((curr = s1[i++]) != '\0') {
    int j = 0;
    char curr2;
    int skip = 0;

    while ((curr2 = s2[j++]) != '\0') {
      skip = curr2 == curr;
      if (skip) break;
    }

    if (skip) continue;

    newstr[l++] = curr;
  }

  newstr[l] = '\0';
  printf("%s\n", newstr);
}

int any(char s1[], char s2[]) {
  int i = 0;
  char curr, curr2;
  while ((curr = s1[i++]) != '\0') {
    int j = 0;
    while ((curr2 = s2[j++]) != '\0') {
      if (curr == curr2) return i-1;
    }
  }
  return -1;
}

//
/*
  11111111
  10101100
   
  p =0
  n =4
  
  11110000 & y
  00001111 & x
  = x | y
  10101111
---
  p =1  
  n =4
  
  01111000 & y
  10000111 & x
  = x | y
  11010111

 */

unsigned char gen_mask (int p, int n) {
  return ((1 << n) - 1) << p; 
} 

int setbits (unsigned char x, int p, int n, unsigned char y) {
  unsigned char maskx = gen_mask(p, n); 
  unsigned char masky = gen_mask(0, n);
  // printf("maskx = %08b\n", maskx);
  // printf("masky = %08b\n", masky);
  // printf("numx = %08b\n", x);
  // printf("numy = %08b\n", y);
  return (x & ~maskx) | (y & masky) << p; 

}


/*

  00001111
  p = 3
  n = 2

  00011000 mask 

  a = ~x & mask -> 00010000
  b = x & ~mask -> 00000111
  a | b
  =
  00010111



 */


int inverted (unsigned char x, int p, int n) {
  unsigned char mask = gen_mask(p, n);

  unsigned char a = ~x & mask;
  unsigned char b = x & ~mask;

  return a | b;
}

unsigned char rightrot (unsigned char x, int n) {
  return (x >> 8-n) | (x << n); 
}

unsigned char rmbit (unsigned char x) {
  return x &= (x - 1);
}
int bitcount (unsigned int x) {
  int count = 0;
  unsigned int num = x;
  while (num != 0) {
    num &= (num - 1);
    count += 1;
  }

  return count;
}

void to_lowercase (char arr[]) {
  int i = 0;
  int l = strlen(arr);

  char newstr[l];

  char curr;
  while ((curr = arr[i]) != '\0') {
    
    curr += curr < 'a' ? 'a'-'A' : '\0';
    newstr[i] = curr;
    i++;
  }

  newstr[l] = '\0';
  printf("%s\n", newstr);
}

int main () {
  char teststr[] = "0xbeef";
  // printf("%s = %d\n", teststr, htoi(teststr));
  // squezze(teststr, "0xebf");
  // 
  // printf("res  = %08b\n\n", setbits(55, 4, 4, 172));
  // printf("res  = %08b\n\n", setbits(1, 4, 4, 172));

  // printf("%08b\n", inverted(gen_mask(0, 4), 3, 2));
  // printf("%08b\n", inverted(gen_mask(2, 4), 3, 2));
  // printf("%08b\n", inverted(gen_mask(4, 4), 3, 2));
  // printf("%08b\n", rightrot(gen_mask(6, 2), 1));
  // printf("%08b\n", rightrot(gen_mask(6, 2), 2));
  // printf("%08b\n", rightrot(gen_mask(5, 3), 2));
  // printf("%08b\n", rightrot(gen_mask(4, 4), 2));
  // printf("%08b -> %d\n", 1, bitcount(1));
  // printf("%08b -> %d\n", 150, bitcount(150));
  // printf("%08b -> %d\n", 17, bitcount(17));
  // printf("%08b -> %d\n", 0, bitcount(0));
  to_lowercase ("AsdDDsSaA");
  return 0;
} 
