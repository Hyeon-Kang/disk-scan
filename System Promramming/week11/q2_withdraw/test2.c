// mutex를 사용한 동기화 보장 연습
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

// mutex 선언
//pthread_mutex_t mutex;

// 계좌 구조체
typedef struct{
  int balance = 0;
} account;

int withdraw(struct account *account, int amount) {
      //pthread_mutex_lock (&account->mutex);

      const int balance = account->balance;

      // 잔액 검사
      if (balance < amount) {
            //pthread_mutex_unlock (&account->mutex);
            printf("잔액 부족\n");
            return -1;
      }

      // 인출 연산
      account->balance = balance - amount;
      //pthread_mutex_unlock (&account->mutex);

      printf("남은 금액 : %d\n", account->balance);

      return 0;
}

void main () {
      account person1;
      person1->balance = 5000;

      withdraw(*person1, 100);

      return 0;
}
