#include <stdio.h>
#include <stdlib.h>

//functions to swap numbers and sort arrays
void swap(int *xp, int *yp){
 int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}

void selectionSort(int arr[], int n) 
{ 
    int i, j, min_idx; 
      for (i = 0; i < n - 1; i++) { 
          min_idx = i; 
        for (j = i + 1; j < n; j++) 
            if (arr[j] < arr[min_idx]) 
                min_idx = j; 
          swap(&arr[min_idx], &arr[i]); 
    } 
} 

int main(void){
//define the deck 
int deck[53][2];
int i;
//hearts
for(i=1; i<=10; i++){
deck[i][0] = i;
deck[i][1] = 82; //R
}
deck[11][0] = 74; //J
deck[11][1] = 82; //R
deck[12][0] = 81; //Q
deck[12][1] = 82; //R
deck[13][0] = 75; //K
deck[13][1] = 82; //R
//diamonds
int j = 1;
for(i=14; i<=23; i++){
deck[i][0] = j;
deck[i][1] = 89; //Y
j++;
}
deck[24][0] = 74;//J
deck[24][1] = 89;//Y
deck[25][0] = 81;//Q
deck[25][1] = 89;//Y
deck[26][0] = 75;//K
deck[26][1] = 89;//Y
//spades
j = 1;
for(i=27; i<=36; i++){
deck[i][0] = j;
deck[i][1] = 66;
j++;
}
deck[37][0] = 74;//J
deck[37][1] = 66;//B
deck[38][0] = 81;//Q
deck[38][1] = 66;//B
deck[39][0] = 75;//K
deck[39][1] = 66;//B
//clubs
j = 1;
for(i=40; i<=49; i++){
deck[i][0] = j;
deck[i][1] = 71;//G
j++;
}
deck[50][0] = 74;//J
deck[50][1] = 71;//G
deck[51][0] = 81;//Q
deck[51][1] = 71;//G
deck[52][0] = 75;//K
deck[52][1] = 71;//G
//here I give the first hand...
int usedcards[53];
for(i=0; i<=53;i++){usedcards[i] = 0;}
int chips = 100;
int pot = 0;
printf("\e[1;1H\e[2J");
printf("\nWelcome!!\nYou have 100 chips to start playing\nGood Luck!!\n");
//variables 
int count_used = 0;
int hand1[5];
int counth = 0;
int action;
int rise;
int cpu_hand[5];
int new_hand_ans = 0;
int first_hand = 0;
int end_hand = 0;

new_hand:
end_hand = 0;
if(count_used > 42){
  printf("\nThe entire deck was used, shuffleing...\n");
  
  for(i=1;i<=52; i++){
    usedcards[i] = 0;
    count_used = 0;
  }
}
if(chips < 5){
  printf("\nYou don't have enough chips to keep playing...\nGAME OVER!.\n");
  goto end_game;
}
if(first_hand !=0){
  printf("You still have %d chips.\nDo you want to play another hand?:\n1.-yes\n2.-no\n", chips);
  scanf("%d", &new_hand_ans);
  while(new_hand_ans<1 && new_hand_ans>2){
    printf("Invalid input!.\nYou still have %d chips.\nDo you want to play another hand?:\n1.-yes\n2.-no\n", chips);
  scanf("%d", &new_hand_ans);
  }
  if(new_hand_ans == 2){
    printf("Thank you for playing with me!.\nI will miss you...\n");
    goto end_game;
  }
 printf("\e[1;1H\e[2J");
}
// computer hand using rand function and checking on used cards
do{
  int cpu_index;
  int cpu_test;

  cpu_recheck:
  cpu_test = 0;
  cpu_index = rand() % 53;
  for(i=0;i<=52;i++){
    if(usedcards[i] == cpu_index){
      cpu_test++;
    }
  }
  if(cpu_test == 0){
    usedcards[cpu_index] = cpu_index;
    cpu_hand[counth] = cpu_index;
    counth++;
    count_used++;
  }
  else{
    goto cpu_recheck;
  }
}while(counth <=4);
counth = 0;

//here I check if the cards are already used or not for the hand.
do{
  int index;
  int test;
  // here I choose a rand and check if it used
  recheck: 
  test = 0;
  index = rand() % 53;
  for(i=0; i<= 52; i++){
    if(usedcards[i] == index){
      test++;
    }
  }
  //here I add to usedcards
  if(test == 0){
   usedcards[index] = index;
   hand1[counth] = index;
   counth++;
   count_used++;
  }
  else{
   goto recheck;    
    }
  }while(counth <= 4);
  counth = 0;
chips -= 5;
pot += 10;

first_hand = 1;
//here I evaluate the cpu hand power to define reactions.
int cpu_power = 0;
//for flush or royal flush
int card_type_flush;
int flush_count = 0;
for(i=0; i<=4; i++){
    int j;
    for(j=0;j<=4;j++){
      if(deck[cpu_hand[i]][1]==deck[cpu_hand[j]][1]){
       flush_count++;
      }      
    }
    
    if(flush_count == 5){
      int flush[5];
      int k;
        for(k=0;k<=4;k++){
        flush[k] = deck[cpu_hand[k]][0];
        }
       selectionSort(flush, 5);  
       if(flush[0]==1 && flush[1]==10 && flush[2]==74 && flush[3]==75 && flush[4]==81){
         cpu_power = 10;
               }else if(flush[1]==flush[0]+1 && flush[2]==flush[1]+1 && flush[3]==flush[2]+1 && flush[4]==flush[3]+1){
                 cpu_power = 9;
                }
                else if(flush[0]==9 && flush[1]==10 && flush[2]==74 && flush[3]==75 && flush[4]==81){
                cpu_power = 9;
               }
                else if(flush[0]==8 && flush[1]==9 && flush[2]==10 && flush[3]==74 && flush[4]==81){
                 cpu_power = 9;
                }
                else if(flush[0]==7 && flush[1]==8 && flush[2]==9 && flush[3]==10 && flush[4]==74){
                cpu_power = 9;
                }
               else{
         cpu_power = 6;
         if(flush[3]==75){card_type_flush = 75;}
         else if(flush[0]==1){card_type_flush = 1;}
         else{card_type_flush = flush[4];}
        }
 
      break;      
    }
    else{
      flush_count = 0;
    }
}

//here I check for three of a kind
//the if prevents replacing a higher hand with this one
int card_type_three = 100;
if(cpu_power == 0 || cpu_power < 4){
int three_check = 0;
for(i=0;i<=4;i++){
    int j;
    for(j=0;j<=4;j++){
     if(deck[cpu_hand[i]][0]==deck[cpu_hand[j]][0]){
       three_check++;
     }
     }
     if(three_check == 3){
        cpu_power = 4;
        card_type_three = deck[cpu_hand[i]][0];
     break;
     }
     three_check = 0;
}
}
//here I check four for of a kind as this is stronger than regular flush and three of a kind there's no problem with replacing the power of a regular flush.
int card_type_four;
int four_check = 0;
for(i=0;i<=4;i++){
    int j;
    for(j=0;j<=4;j++){
     if(deck[cpu_hand[i]][0]==deck[cpu_hand[j]][0]){
       four_check++;
     }
     }
     if(four_check == 4){
     cpu_power = 8;
     card_type_four = deck[cpu_hand[i]][0];
     break;
     }
     four_check = 0;
}

//here I check for full house, as it is stronger than three of a kind and regular flush there's no problem on replacing the power value.
//the if tells me theres 3 equal cards on the hand
int card_type_full = 100;
if(cpu_power == 4 && card_type_three != 100){
  int arr_full[2];
  int index = 0;
  for(i=0;i<=4;i++){
    if(deck[cpu_hand[i]][0] != card_type_three){
      arr_full[index] = deck[cpu_hand[i]][0];
      index++;
    }
  }
  if(arr_full[0] == arr_full[1]){
    cpu_power = 7;
    card_type_full = arr_full[0];
  }
}

//here I check for straight
int card_type_straight;
if(cpu_power < 5){
  int arr_st[5];
  for(i=0;i<=4;i++){
    arr_st[i] = deck[cpu_hand[i]][0];
  }
    selectionSort(arr_st,5);

     if(arr_st[1]==arr_st[0]+1 && arr_st[2]==arr_st[1]+1 && arr_st[3]==arr_st[2]+1 && arr_st[4]==arr_st[3]+1){
       cpu_power = 5;
       card_type_straight = arr_st[4];
     }
     else if(arr_st[0]==9 && arr_st[1]==10 && arr_st[2]==74 && arr_st[3]==75 && arr_st[4]==81){
       cpu_power = 5;
       card_type_straight = 75;
     }
     else if(arr_st[0]==8 && arr_st[1]==9 && arr_st[2]==10 && arr_st[3]==74 && arr_st[4]==81){
       cpu_power = 5;
       card_type_straight = arr_st[4];
     }
     else if(arr_st[0]==7 && arr_st[1]==8 && arr_st[2]==9 &&arr_st[3]==10 && arr_st[4]==74){
       cpu_power = 5;
       card_type_straight = arr_st[4];
     }

}

//here I check for two pairs
int card_type_pair1 = 100;
if(cpu_power == 0 || cpu_power < 3){
int pair_check = 0;
for(i=0;i<=4;i++){
    int j;
    for(j=0;j<=4;j++){
     if(deck[cpu_hand[i]][0]==deck[cpu_hand[j]][0]){
       pair_check++;
     }
     }
     if(pair_check == 2){
        card_type_pair1 = deck[cpu_hand[i]][0];
     break;
    }
     pair_check = 0;
  }
}

int card_type_pair2 = 100;
int pair_check2 = 0;
for(i=0;i<=4;i++){
  if(deck[cpu_hand[i]][0] != card_type_pair1 && card_type_pair1 != 100){
    for(j=0; j<=4; j++){
      if(deck[cpu_hand[j]][0]==deck[cpu_hand[i]][0]){
        pair_check2++;
      }
    }
    if(pair_check2 == 2){
      cpu_power = 3;
      card_type_pair2 = deck[cpu_hand[i]][0];
      
    }
  }
  pair_check2 = 0;
  if(cpu_power == 3){break;}
}

//here check for one pair

if(cpu_power == 0 && card_type_pair1 != 100){
  cpu_power = 2;  
}

//here the highest card value for no hand combination
int high_card_none = 100;
if(cpu_power == 0){
  cpu_power = 1;
  int high_check[5];
  for(i=0; i<=4; i++){
     high_check[i] = deck[cpu_hand[i]][0];  
  }
  selectionSort(high_check, 5);
  if(high_check[0] == 1){high_card_none = 1;}
  else if(high_check[4] == 75){high_card_none = 75;}
  else{high_card_none = high_check[4];}
}

//here I check player power to compare at the end.
int card_type_flush_p;
int player_power = 0;
//for flush or royal flush
int flush_count_p = 0;
for(i=0; i<=4; i++){
    int j;
    for(j=0;j<=4;j++){
      if(deck[hand1[i]][1]==deck[hand1[j]][1]){
       flush_count_p++;
      }      
    }
    
    if(flush_count_p == 5){
      int flush[5];
      int k;
        for(k=0;k<=4;k++){
        flush[k] = deck[hand1[k]][0];
        }
       selectionSort(flush, 5);  
       if(flush[0]==1 && flush[1]==10 && flush[2]==74 && flush[3]==75 && flush[4]==81){
         player_power = 10;
               }else if(flush[1]==flush[0]+1 && flush[2]==flush[1]+1 && flush[3]==flush[2]+1 && flush[4]==flush[3]+1){
                 player_power = 9;
                }
                else if(flush[0]==9 && flush[1]==10 && flush[2]==74 && flush[3]==75 && flush[4]==81){
                player_power = 9;
               }
                else if(flush[0]==8 && flush[1]==9 && flush[2]==10 && flush[3]==74 && flush[4]==81){
                 player_power = 9;
                }
                else if(flush[0]==7 && flush[1]==8 && flush[2]==9 && flush[3]==10 && flush[4]==74){
                player_power = 9;
                }
               else{
         player_power = 6;
         if(flush[3]==75){card_type_flush_p = 75;}
         else if(flush[0]==1){card_type_flush_p = 1;}
         else{card_type_flush_p = flush[4];}
        }
 
      break;      
    }
    else{
      flush_count_p = 0;
    }
}

//here I check for three of a kind
//the if prevents replacing a higher hand with this one
int card_type_three_p = 100;
if(player_power == 0 || player_power < 4){
int three_check = 0;
for(i=0;i<=4;i++){
    int j;
    for(j=0;j<=4;j++){
     if(deck[hand1[i]][0]==deck[hand1[j]][0]){
       three_check++;
     }
     }
     if(three_check == 3){
        player_power = 4;
        card_type_three_p = deck[hand1[i]][0];
     break;
     }
     three_check = 0;
}
}
//here I check four for of a kind as this is stronger than regular flush and three of a kind there's no problem with replacing the power of a regular flush.
int card_type_four_p;
int four_check_p = 0;
for(i=0;i<=4;i++){
    int j;
    for(j=0;j<=4;j++){
     if(deck[hand1[i]][0]==deck[hand1[j]][0]){
       four_check_p++;
     }
     }
     if(four_check_p == 4){
     player_power = 8;
     card_type_four_p = deck[hand1[i]][0];
     break;
     }
     four_check_p = 0;
}

//here I check for full house, as it is stronger than three of a kind and regular flush there's no problem on replacing the power value.
//the if tells me theres 3 equal cards on the hand
int card_type_full_p = 100;
if(player_power == 4 && card_type_three_p != 100){
  int arr_full[2];
  int index = 0;
  for(i=0;i<=4;i++){
    if(deck[hand1[i]][0] != card_type_three_p){
      arr_full[index] = deck[hand1[i]][0];
      index++;
    }
  }
  if(arr_full[0] == arr_full[1]){
    player_power = 7;
    card_type_full_p = arr_full[0];
  }
}

//here I check for straight
int card_type_straight_p;
if(player_power < 5){
  int arr_st[5];
  for(i=0;i<=4;i++){
    arr_st[i] = deck[hand1[i]][0];
  }
    selectionSort(arr_st,5);

     if(arr_st[1]==arr_st[0]+1 && arr_st[2]==arr_st[1]+1 && arr_st[3]==arr_st[2]+1 && arr_st[4]==arr_st[3]+1){
       player_power = 5;
       card_type_straight_p = arr_st[4];
     }
     else if(arr_st[0]==9 && arr_st[1]==10 && arr_st[2]==74 && arr_st[3]==75 && arr_st[4]==81){
       player_power = 5;
       card_type_straight_p = 75;
     }
     else if(arr_st[0]==8 && arr_st[1]==9 && arr_st[2]==10 && arr_st[3]==74 && arr_st[4]==81){
       player_power = 5;
       card_type_straight_p = arr_st[4];
     }
     else if(arr_st[0]==7 && arr_st[1]==8 && arr_st[2]==9 &&arr_st[3]==10 && arr_st[4]==74){
       player_power = 5;
       card_type_straight_p = arr_st[4];
     }

}

//here I check for two pairs
int card_type_pair1_p = 100;
if(player_power == 0 || player_power < 3){
int pair_check = 0;
for(i=0;i<=4;i++){
    int j;
    for(j=0;j<=4;j++){
     if(deck[hand1[i]][0]==deck[hand1[j]][0]){
       pair_check++;
     }
     }
     if(pair_check == 2){
        card_type_pair1_p = deck[hand1[i]][0];
     break;
    }
     pair_check = 0;
  }
}

int card_type_pair2_p = 100;
int pair_check2_p = 0;
for(i=0;i<=4;i++){
  if(deck[hand1[i]][0] != card_type_pair1_p && card_type_pair1_p != 100){
    for(j=0; j<=4; j++){
      if(deck[hand1[j]][0]==deck[hand1[i]][0]){
        pair_check2_p++;
      }
    }
    if(pair_check2_p == 2){
      player_power = 3;
      card_type_pair2_p = deck[hand1[i]][0];
      
    }
  }
  pair_check2_p = 0;
  if(player_power == 3){break;}
}

//here check for one pair

if(player_power == 0 && card_type_pair1_p != 100){
  player_power = 2;  
}

//here the highest card value for no hand combination
int high_card_none_p = 100;
if(player_power == 0){
  player_power = 1;
  int high_check[5];
  for(i=0; i<=4; i++){
     high_check[i] = deck[hand1[i]][0];  
  }
  selectionSort(high_check, 5);
  if(high_check[0] == 1){high_card_none_p = 1;}
  else if(high_check[4] == 75){high_card_none_p = 75;}
  else{high_card_none_p = high_check[4];}
}

//here the game starts
int gamble;
printf("\nYou entered the game with a minimum of 5 chips!");
int rise_amount = 0;
replay:
if(rise_amount !=0){
  printf("\e[1;1H\e[2J");
printf("Computer have rised by: %d", rise_amount);
}
printf("\nyou still have: %d to play!\n", chips);
printf("The pot is: %d\n", pot);

  // showing the players hand

  printf("\nYour hand is: \n");
  for(i=0; i<=4; i++){
    //here I cahnge int values to text
       
    if(deck[hand1[i]][0] == 74 || deck[hand1[i]][0] == 81 || deck[hand1[i]][0] == 75){
          switch(deck[hand1[i]][1]){
            case 82:
             printf("%d.- %c of Hearts\n",i+1 ,deck[hand1[i]][0]);    
            break;
            case 89:
             printf("%d.- %c of Diamonds\n",i+1 ,deck[hand1[i]][0]);
            break;
            case 66:
             printf("%d.- %c of Spades\n",i+1 ,deck[hand1[i]][0]);
            break;
            case 71:
             printf("%d.- %c of Clubs\n",i+1 ,deck[hand1[i]][0]);
            break;
            default:
            break;
          }     
              
    }
      else{
        switch(deck[hand1[i]][1]){
            case 82:
             printf("%d.- %d of Hearts\n",i+1 ,deck[hand1[i]][0]);    
            break;
            case 89:
             printf("%d.- %d of Diamonds\n",i+1 ,deck[hand1[i]][0]);
            break;
            case 66:
             printf("%d.- %d of Spades\n",i+1 ,deck[hand1[i]][0]);
            break;
            case 71:
             printf("%d.- %d of Clubs\n",i+1 ,deck[hand1[i]][0]);
            break;
            default:
            break;
      }     
      
    }
  }
  
  
   
  printf("\nWhat do you want to do?\n");
  printf("1.- Rise\n2.- Pass\n3.- Pay\n4.- Fold\n");
  scanf("%d", &action);

  while(action<1 || action>4){
    printf("\nInvalid input.\nWhat do you want to do?\n");
  printf("1.- Rise\n2.- Pass\n3.- Pay\n4.- Fold\n");
  no_pass:
  scanf("%d", &action);
  }
  switch(action){
    case 1: 
    printf("How much?: ");
    scanf("%d", &rise);

    if(rise_amount == 0){
     gamble = rise;
    }
    else{
     gamble = rise+rise_amount;
    }
        
    while(chips<gamble){
      printf("Sorry, you don't have enough chips.\nkeep in mind that you need to pay for the cpu rise amount and then add your own rise amount.\nYour maximum is: %d\nHow many do you want to rise?:", chips);
      scanf("%d", &rise);   
    }
    int fold_q = 100;    
    pot += gamble;
    chips -= gamble;
    // here computer answers
    
    switch(cpu_power){
    case 10: case 9: case 8:
    rise_amount = rand() %10;
    rise_amount++;
    pot += rise+rise_amount;
    goto replay;
    break;

    case 6: case 5: case 4:
    rise_amount = rand() %5;
    rise_amount++;
    pot += rise+rise_amount;
    goto replay;
    break;

    case 3: case 2:
    if(rise>3){
    fold_q = rand()%10;
    fold_q++;
    }
    if(fold_q < 5){
      printf("Computer Folds!");
      chips += pot;
      pot = 0;
      goto new_hand;
    }
    else{
     rise_amount = rand() %3;
     rise_amount++;
    pot += rise+rise_amount;
    goto replay;
    }
    break;

    case 1:
    if(rise>2){
    fold_q = rand()%10;
    fold_q++;
    }
    if(fold_q < 6){
      printf("Computer Folds!");
      chips += pot;
      pot = 0;
      goto new_hand;
    }
    else{
     rise_amount = rand() %8;
     rise_amount++;
    pot += rise+rise_amount;
    goto replay;
    }
    break; 
    }

   case 2: 
   if(pot == 10){
   rise_amount = rand() %10;
    rise_amount++;
    pot += rise_amount;
    goto replay; 
   }
    else{
     printf("\nYou are not allowed to pass at this time!\nWhat do you want to do?:");
     goto no_pass;
   }
   break;
   int p_answer;
   case 3:
   p_answer = 0;
   if(rise_amount>chips){
     printf("\nYou don't have enough chips to pay.\nYou need %d chips.\nPress 1 to fold or 2 to All in!\n",rise_amount);
     scanf("%d", &p_answer);
     while(p_answer < 1 || p_answer > 2){
       printf("Invalid Input!\nYou don't have enough chips to pay.\nYou need %d chips.\nPress 1 to fold or 2 to All in!\n",rise_amount);
       scanf("%d", &p_answer);
     }
     if(p_answer == 1){
     pot = 0;
     goto new_hand;
     }
     else if(p_answer == 2){
     pot += chips;
     chips = 0;
     end_hand = 1;

     }
   }else{
     end_hand = 1;
   }      
   break;

   case 4:
   pot = 0;
   printf("\e[1;1H\e[2J");
   goto new_hand;
   break;   
   
  }
  if(end_hand == 1){
  int pair_def;
  int pair_def_p;
  
  //here I compare hands and decide who won!
  
   printf("\e[1;1H\e[2J");
   printf("\nyour hand is:\n");
   
   for(i=0; i<=4; i++){
    //here I cahnge int values to text
       
    if(deck[hand1[i]][0] == 74 || deck[hand1[i]][0] == 81 || deck[hand1[i]][0] == 75){
          switch(deck[hand1[i]][1]){
            case 82:
             printf("%d.- %c of Hearts\n",i+1 ,deck[hand1[i]][0]);    
            break;
            case 89:
             printf("%d.- %c of Diamonds\n",i+1 ,deck[hand1[i]][0]);
            break;
            case 66:
             printf("%d.- %c of Spades\n",i+1 ,deck[hand1[i]][0]);
            break;
            case 71:
             printf("%d.- %c of Clubs\n",i+1 ,deck[hand1[i]][0]);
            break;
            default:
            break;
          }     
              
    }
      else{
        switch(deck[hand1[i]][1]){
            case 82:
             printf("%d.- %d of Hearts\n",i+1 ,deck[hand1[i]][0]);    
            break;
            case 89:
             printf("%d.- %d of Diamonds\n",i+1 ,deck[hand1[i]][0]);
            break;
            case 66:
             printf("%d.- %d of Spades\n",i+1 ,deck[hand1[i]][0]);
            break;
            case 71:
             printf("%d.- %d of Clubs\n",i+1 ,deck[hand1[i]][0]);
            break;
            default:
            break;
      }     
      
    }
  }
 

switch(player_power){
  case 10:
  printf("\nCongrats! You have a ROYAL FLUSH!!!");
  break;
  case 9:
  printf("\nCongrats! You have a STRAIGHT FLUSH!!!");
  break;
  case 8:
  printf("\nCongrats! You have FOUR OF AKIND!!!");
  break;
  case 7:
  printf("\nYou have FULL HOUSE");
  break;
  case 6:
  printf("\nYou have a FLUSH.");
  break;
  case 5:
  printf("\nYou have STRAIGHT.");
  break;
  case 4:
  printf("\nYou have THREE OF A KIND");
  break;
  case 3:
  printf("\nYou have TWO PAIRS");
  break;
  case 2:
  printf("\nYou have ONE PAIR");
  break;
  case 1:
  printf("\nYou don't have a specific hand...\nIF the computer is on this same situation the higher card will take it all!!!");
  break;
}



//here I show the computer hand
printf("\n\nThe cpu hand is: \n");

for(i=0; i<=4; i++){
    //here I cahnge int values to text
       
    if(deck[cpu_hand[i]][0] == 74 || deck[cpu_hand[i]][0] == 81 || deck[cpu_hand[i]][0] == 75){
          switch(deck[cpu_hand[i]][1]){
            case 82:
             printf("%d.- %c of Hearts\n",i+1 ,deck[cpu_hand[i]][0]);    
            break;
            case 89:
             printf("%d.- %c of Diamonds\n",i+1 ,deck[cpu_hand[i]][0]);
            break;
            case 66:
             printf("%d.- %c of Spades\n",i+1 ,deck[cpu_hand[i]][0]);
            break;
            case 71:
             printf("%d.- %c of Clubs\n",i+1 ,deck[cpu_hand[i]][0]);
            break;
            default:
            break;
          }     
              
    }
      else{
        switch(deck[cpu_hand[i]][1]){
            case 82:
             printf("%d.- %d of Hearts\n",i+1 ,deck[cpu_hand[i]][0]);    
            break;
            case 89:
             printf("%d.- %d of Diamonds\n",i+1 ,deck[cpu_hand[i]][0]);
            break;
            case 66:
             printf("%d.- %d of Spades\n",i+1 ,deck[cpu_hand[i]][0]);
            break;
            case 71:
             printf("%d.- %d of Clubs\n",i+1 ,deck[cpu_hand[i]][0]);
            break;
            default:
            break;
      }     
      
    }
  }
 
 switch(cpu_power){
  case 10:
  printf("\nI have a ROYAL FLUSH!!!");
  break;
  case 9:
  printf("\nI have a STRAIGHT FLUSH!!!");
  break;
  case 8:
  printf("\nI have FOUR OF AKIND!!!");
  break;
  case 7:
  printf("\nI have FULL HOUSE");
  break;
  case 6:
  printf("\nI have a FLUSH.");
  break;
  case 5:
  printf("\nI have STRAIGHT.");
  break;
  case 4:
  printf("\nI have THREE OF A KIND");
  break;
  case 3:
  printf("\nI have TWO PAIRS");
  break;
  case 2:
  printf("\nI have ONE PAIR");
  break;
  case 1:
  printf("\nI don't have a specific hand -_-*");
  break;
}
//here I compare to know who won.
if(cpu_power>player_power){
  printf("\nSorry, I win this one!!");
  pot = 0;
}
else if(player_power>cpu_power){
  printf("\nRookie's luck... next time I will take it!");
  chips += pot;
  pot = 0;
}
else if(cpu_power == player_power){
  switch(player_power){
  case 1:
  if(high_card_none == 75){high_card_none = 100;}
  if(high_card_none_p == 75){high_card_none_p = 100;}
  if(high_card_none == 1){high_card_none = 110;}
  if(high_card_none_p == 1){high_card_none_p = 110;}
  if(high_card_none>high_card_none_p){
    printf("\nSorry but not sorry, I win this one!!");
    pot = 0;
  }
  else if(high_card_none == high_card_none_p){
   printf("DRAW!");
   int pot2 = 0;
   pot2 = pot/2;
   chips += pot2;
   pot = 0;
  }
  else{
    printf("\nI wanted you to win this time....");
    chips += pot;
    pot = 0;
  }
  break;
  case 2:
  if(card_type_pair1 == 75){card_type_pair1 = 100;}
  if(card_type_pair1_p == 75){card_type_pair1_p = 100;}
  if(card_type_pair1 == 1){card_type_pair1 = 110;}
  if(card_type_pair1_p == 1){card_type_pair1_p = 110;}
  if(card_type_pair1>card_type_pair1_p){
    printf("\nSorry but not sorry, I win this one!!");
    pot = 0;
  }
  else if(card_type_pair1 == card_type_pair1_p){
   printf("DRAW!");
   int pot2 = 0;
   pot2 = pot/2;
   chips += pot2;
   pot = 0;
  }
  else{
    printf("\nI wanted you to win this time....");
    chips += pot;
    pot = 0;
  }
  break;
  case 3:
  if(card_type_pair1 == 75){card_type_pair1 = 100;}
  if(card_type_pair1_p == 75){card_type_pair1_p = 100;}
  if(card_type_pair1 == 1){card_type_pair1 = 110;}
  if(card_type_pair1_p == 1){card_type_pair1_p = 110;}
  if(card_type_pair2 == 75){card_type_pair2 = 100;}
  if(card_type_pair2_p == 75){card_type_pair2_p = 100;}
  if(card_type_pair2 == 1){card_type_pair2 = 110;}
  if(card_type_pair2_p == 1){card_type_pair2_p = 110;}
  
  if(card_type_pair1>card_type_pair2){
    pair_def = card_type_pair1;
  }
  if(card_type_pair1<card_type_pair2){
    pair_def = card_type_pair2;
  }
  
  if(card_type_pair1_p>card_type_pair2_p){
    pair_def_p = card_type_pair1_p;
  }
  if(card_type_pair1_p<card_type_pair2_p){
    pair_def_p = card_type_pair2_p;
  }
  //and now to compare 
  if(pair_def>pair_def_p){
    printf("\nSorry but not sorry, I win this one!!");
    pot = 0;
  }
  else if(pair_def == pair_def_p){
   printf("DRAW!");
   int pot2 = 0;
   pot2 = pot/2;
   chips += pot2;
   pot = 0;
  }
  else{
    printf("\nI wanted you to win this time....");
    chips += pot;
    pot = 0;
  }
    
  break;
  case 4:
  if(card_type_three == 75){card_type_three = 100;}
  if(card_type_three_p == 75){card_type_three_p = 100;}
  if(card_type_three == 1){card_type_three = 110;}
  if(card_type_three_p == 1){card_type_three_p = 110;}
  
  if(card_type_three>card_type_three_p){
    printf("\nSorry but not sorry, I win this one!!");
    pot = 0;
  }
  else if(card_type_three == card_type_three_p){
   printf("DRAW!");
   int pot2 = 0;
   pot2 = pot/2;
   chips += pot2;
   pot = 0;
  }
  else{
    printf("\nI wanted you to win this time....");
    chips += pot;
    pot = 0;
  }

  break;
  case 5:
  if(card_type_straight == 75){card_type_straight = 100;}
  if(card_type_straight_p == 75){card_type_straight_p = 100;}
  if(card_type_straight == 1){card_type_straight = 110;}
  if(card_type_straight_p == 1){card_type_straight_p = 110;}
  
  if(card_type_straight>card_type_straight_p){
    printf("\nSorry but not sorry, I win this one!!");
    pot = 0;
  }
  else if(card_type_straight == card_type_straight_p){
   printf("DRAW!");
   int pot2 = 0;
   pot2 = pot/2;
   chips += pot2;
   pot = 0;
  }
  else{
    printf("\nI wanted you to win this time....");
    chips += pot;
    pot = 0;
  }
  break;
  case 6:
  if(card_type_flush == 75){card_type_flush = 100;}
  if(card_type_flush_p == 75){card_type_flush_p = 100;}
  if(card_type_flush == 1){card_type_flush = 110;}
  if(card_type_flush_p == 1){card_type_flush_p = 110;}
  
  if(card_type_flush>card_type_flush_p){
    printf("\nSorry but not sorry, I win this one!!");
    pot = 0;
  }
  else if(card_type_flush == card_type_flush_p){
   printf("DRAW!");
   int pot2 = 0;
   pot2 = pot/2;
   chips += pot2;
   pot = 0;
  }
  else{
    printf("\nI wanted you to win this time....");
    chips += pot;
    pot = 0;
  }
  break;
  case 7:
  if(card_type_full == 75){card_type_full = 100;}
  if(card_type_full_p == 75){card_type_full_p = 100;}
  if(card_type_full == 1){card_type_full = 110;}
  if(card_type_full_p == 1){card_type_full_p = 110;}
  
  if(card_type_full>card_type_full_p){
    printf("\nSorry but not sorry, I win this one!!");
    pot = 0;
  }
  else if(card_type_full == card_type_full_p){
   printf("DRAW!");
   int pot2 = 0;
   pot2 = pot/2;
   chips += pot2;
   pot = 0;
  }
  else{
    printf("\nI wanted you to win this time....");
    chips += pot;
    pot = 0;
  }
  
  break;
  case 8:
  if(card_type_four == 75){card_type_four = 100;}
  if(card_type_four_p == 75){card_type_four_p = 100;}
  if(card_type_four == 1){card_type_four = 110;}
  if(card_type_four_p == 1){card_type_four_p = 110;}
  
  if(card_type_four>card_type_four_p){
    printf("\nSorry but not sorry, I win this one!!");
    pot = 0;
  }
  else if(card_type_four == card_type_four_p){
   printf("DRAW!");
   int pot2 = 0;
   pot2 = pot/2;
   chips += pot2;
   pot = 0;
  }
  else{
    printf("\nI wanted you to win this time....");
    chips += pot;
    pot = 0;
  }
  
  break;
  case 9: case 10:
  printf("DRAW!");
   int pot2 = 0;
   pot2 = pot/2;
   chips += pot2;
   pot = 0;    

  break;
 
  }
}


// need to delay
int delay=0;
printf("\nPlease enter 1 to continue...");
scanf("%d", &delay);
while(delay !=1){
printf("\nI did said 1 ... hard time finding it?...\nLet's try angain...press O-N-E.");
scanf("%d", &delay);
}

printf("\e[1;1H\e[2J");
goto new_hand;
  }

end_game:
  return 0;
}