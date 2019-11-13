
// mutex를 사용한 동기화 보장 연습
#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>
#include <unistd.h>
#include <string.h>

// mutex 선언
//pthread_mutex_t mutex;

// 계좌 구조체
struct account{
  int balance;
};

int withdraw(struct account *accounts, int amount) {
      //pthread_mutex_lock (&account->mutex);

      const int vbalance = accounts->balance;

      // 잔액 검사
      if (vbalance < amount) {
            //pthread_mutex_unlock (&account->mutex);
            printf("잔액 부족\n");
            return -1;
      }

      // 인출 연산
      accounts->balance = vbalance - amount;
      //pthread_mutex_unlock (&account->mutex);

      printf("남은 금액 : %d\n", accounts->balance);

      return 0;
}

void main () {
      struct account person1;
      person1.balance = 5000;

      withdraw(&person1, 100);

      return 0;
}
