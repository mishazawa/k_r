#include <stdio.h>
#include <string.h>


void cel_to_farh () {
  int start = -10;
  int end   = 100;
  int step  = 5;

  float _95 = 9.0 / 5.0;

  printf("Cel\tFarh\n");
  for (float curr = start; curr <= end; curr += step) {
    printf("%3.f\t%3.2f\n", curr, _95 * curr + 32.0);
  }
}

void comp_eof() {
  printf("getchar() != EOF => %d\n", getchar() != EOF);
  printf("value of EOF => %d\n", EOF);
}

void count_blanks () {
  short counter = 0;
  int character;
  while ((character = getchar()) != EOF) {
    if (character == '\n') counter += 1;
    if (character == ' ')  counter += 1;
    if (character == '\t') counter += 1;
  }
  printf("count blanks = %d\n", counter);
}

void replace_multi_blank () {
  short counter = 0;
  int character;
  while ((character = getchar()) != EOF) {
    if (character == '\n' || character == ' ' || character == '\t') {
      counter += 1;
    } else {
      counter = 0;
    }

    if (counter < 2) {
      putchar(character);
    }
  }

}

void replace_invisible () {
  int character;
  while ((character = getchar()) != EOF) {
    if (character == '\b'){
      putchar('\\'); 
      putchar('b'); 
    } else if (character == '\\') {
      putchar('\\'); 
      putchar('\\'); 
    } else if (character == '\t') {
      putchar('\\'); 
      putchar('t'); 
    } else {
      putchar(character);
    }
  }
}

#define MAX_LEN 10 
#define IN_WORD 1 
#define OUT_WORD 0 

void count_letters (int *wls) {
  int c;
  short state = OUT_WORD;
  int count = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n') {
      state = OUT_WORD;
      if (count < MAX_LEN) {
        wls[count] += 1;
      }
      count = 0; 
    } else {
      state = IN_WORD;
    }

    if (state == IN_WORD) {
      count += 1;
    }
  }
  
}

void hist_wl () {
  int wls[MAX_LEN];

  count_letters(wls);

  for (int i = 1;i < MAX_LEN; i++) {
    printf("%2d: ", i);
    for (int j = 0; j < wls[i]; j++) {
      printf("#");
    }
    printf("\n");
  }

}

/*

       #
   #   #   #
 # # # # # # #

*/
void print_hist_hor (int * arr, int cap) {
  int max_len = 0;

  for (int i = 0; i < cap; i++) {
    if (arr[i] > max_len) {
      max_len = arr[i];
    }
  }
  
  for (int j = max_len + 1; j >= 0; j--) {
    for (int i = 0; i < cap; i++) {
      if (arr[i] > j) {
        printf("# ");
      } else {
        printf("  ");
      }
    }
    printf("\n");
  }
}

void hist_wl_hor () {
  int wls[MAX_LEN];

  count_letters(wls);

  print_hist_hor (wls, MAX_LEN);
  
  for (int i = 0; i < MAX_LEN + 1; i++) {
    printf("%d ", i);
  }
  
  printf("\n");
}

#define CHAR_MAX 26

void count_char_freqs () {
  int charfreq[CHAR_MAX] = {0};
  int c;

  while ((c = getchar()) != EOF) {
    if (c >= 'a' && c <= 'z') {
      charfreq[c - 'a'] += 1;
    }
  }
  
  print_hist_hor (charfreq, CHAR_MAX);
  
  for (int i = 0; i < CHAR_MAX; i++) {
    printf("%c ", 'a' + i);
  }
  
  printf("\n");
}

int get_line(char arr[], int limit) {
  int i = 0;
  int c;
  for (;i < limit-1 && (c=getchar()) != EOF && c != '\n'; ++i) {
  // while ((c = getchar()) != EOF && i < limit - 1) {
    arr[i] = c;
  }
  
  if (c == '\n') {
    arr[i] = c;
    ++i;
  }

  arr[i] = '\0';

  return i;
}

void copy_line (char src[], char dest[]) {
  int i = 0;
  while ((dest[i] = src[i]) != '\0') {
    i++;
  }
}

#define MAX_LINE 10

void print_longest_line () {
  int curr_len = 0;
  int max_len  = 0;

  char line[MAX_LINE];
  char longest_line[MAX_LINE];

  while ((curr_len = get_line(line, MAX_LINE)) > 0) {
    if (curr_len > max_len) {
      max_len = curr_len;
      copy_line(line, longest_line);
    }
  }

  if (max_len > 0) {
    printf("Longest line(%d): %s\n", max_len-1, longest_line);
  }
}

void print_line_if_longer_n(int limit) {
  int curr_len = 0;
  char line[MAX_LINE];

  while ((curr_len = get_line(line, MAX_LINE)) > 0) {
    if (curr_len > limit) {
      printf("Output: %s\n", line);
    }
  }
}

int len(char arr[]) {
  int i = 0;
  
  while (arr[i] != '\0') {
    i++;
  }
  return i; 
}

void trim (char arr[]) {
  int l = len(arr);
  char new_str[l];

  int end_pos = 0;
  int start_pos = 0;

  // trim end
  for (int i=l-1; i >= 0; i--) {
    if (end_pos == 0 && (arr[i] == '\t' || arr[i] == ' ')) {
      continue;
    }
    end_pos = i+1;
    break;
  }

  // trim start

  for (int i = 0; i < end_pos; i++) {
    if (arr[i] == '\t' || arr[i] == ' ') {
      start_pos += 1;
      continue;
    }
    break;
  }

  for (int i = 0; i < end_pos - start_pos; i++) {
    new_str[i] = arr[i + start_pos];
  }

  new_str[end_pos - start_pos] = '\0';

  printf("\"%s\"\n", new_str);
}

void reverse (char arr[]) {
  int l = len(arr);
  char new_str[l];

  for (int i = 0; i < l; i++) {
    new_str[i] = arr[l - i - 1];
  }
  new_str[l] = '\0';

  printf("\"%s\"\n", new_str);
}

void detab (char arr[], int space_count) {

  int i = 0;
  int tab_count = 0;
  char curr;
  // count new string len
  while ((curr = arr[i]) != '\0') {
    i++;
    if (curr == '\t') {
      tab_count +=1;
    }
  }
  
  int char_count = i - tab_count + (tab_count * space_count) + 1;
  
  char new_str[char_count];
  i = 0; 
  int j = 0;

  while ((curr = arr[i]) != '\0') {
    i++;
    if (curr == '\t') {
      for (int t = 0; t < space_count; t++) new_str[j + t] = ' ';
      j += space_count;
    } else {
      new_str[j] = curr;
      j++;
    }
  }

  new_str[j] = '\0';

  printf("\"%s\"\n", new_str);
}

void entab(char arr[], int min_space_count) {
  int l = len(arr);

  char new_str[l];
  char curr;
  int i = 0;
  while ((curr = arr[i]) != '\0') {
    int seq_spaces = 0;
    while ((curr = arr[i]) == ' ') {

      if (seq_spaces == min_space_count) {
        new_str[i] = '\t';
        seq_spaces = 0;
      }
      
      i++;
      seq_spaces += 1;
    }
    new_str[i] = curr;
    i++;
  }

  new_str[i] = '\0';

  printf("\"%s\"\n", new_str);
}

int main () {
  // cel_to_farh();
  // comp_eof(); 
  // count_blanks();
  // replace_multi_blank();
  // replace_invisible();
  // hist_wl_hor ();
  // print_longest_line();
  // print_line_if_longer_n(5);
  // trim(" asd      ");
  // trim("");
  // trim("  asd     asd            ");
  // trim("       a");
  // reverse("");
  // reverse("asd");
  // reverse("asd asd qwe");
  // reverse("asd    ");
  // detab("asd\tasd", 1);
  // detab("asd\tasd", 2);
  // detab("asd\tasd", 3);
  // detab("asd\tasd", 4);
  // detab("asd\tasd", 5);
  // detab("\tasd\tasd", 1);
  // detab("\tasd\tasd", 2);
  // detab("\tasd\tasd", 3);
  // detab("asd\ta\tsd\t", 4);
  // detab("asd\tas\td", 5);
  // entab("asd  asd", 2);
  // entab("asd       asd", 2);
  // entab("asd asd", 2);
  // entab("asd   asd", 2);
  char teststr[] = "asd "
    "dsaaasd "
    "asd "
    "aaa aaa";
  printf("%d\n", strlen(teststr));
  return 0;
}
