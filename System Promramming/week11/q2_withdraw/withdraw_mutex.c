
// mutex를 사용한 동기화 보장 연습
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

// mutex 선언
pthread_mutex_t mutex_lock;

// 계좌 구조체
struct account{
  int balance;
};

int withdraw(struct account *accounts, int amount) {
      //pthread_mutex_lock (&account->mutex);
      pthread_mutex_lock(&mutex_lock); // 잠금
      const int vbalance = accounts->balance;

      // 잔액 검사
      if (vbalance < amount) {
            //pthread_mutex_unlock (&account->mutex);
            pthread_mutex_unlock(&mutex_lock); // 잠금 해제
            printf("잔액 부족\n");
            return -1;
      }

      // 인출 연산
      sleep(1);
      accounts->balance = vbalance - amount;
      //pthread_mutex_unlock (&account->mutex);

      printf("남은 금액 : %d\n", accounts->balance);
      pthread_mutex_unlock(&mutex_lock);
      return 0;
}

void main () {
      // thread 선언
      pthread_t p_thread1, p_thread2;

      struct account person1;
      person1.balance = 5000;

      // 뮤텍스 객체 초기화, 기본 특성으로 초기화 했음
      pthread_mutex_init(&mutex_lock, NULL);

      pthread_create(&p_thread1, NULL, withdraw, &person1, 500);
      pthread_create(&p_thread2, NULL, withdraw, &person1, 500);
      pthread_join(p_thread1, NULL);
      pthread_join(p_thread2, NULL);
      //withdraw(&person1, 100);

      return 0;
}

////////////////


// mutex를 사용한 동기화 보장 연습
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

// mutex 선언
pthread_mutex_t mutex_lock;

// 계좌 구조체
struct account{
  int balance;
};

int withdraw(struct account *accounts) {
      int amount = 500;
      //pthread_mutex_lock (&account->mutex);
      pthread_mutex_lock(&mutex_lock); // 잠금
      const int vbalance = accounts->balance;

      // 잔액 검사
      if (vbalance < amount) {
            //pthread_mutex_unlock (&account->mutex);
            pthread_mutex_unlock(&mutex_lock); // 잠금 해제
            printf("잔액 부족\n");
            return -1;
      }

      // 인출 연산
      sleep(1);
      accounts->balance = vbalance - amount;
      //pthread_mutex_unlock (&account->mutex);

      printf("남은 금액 : %d\n", accounts->balance);
      pthread_mutex_unlock(&mutex_lock);
      return 0;
}

void main () {
      // thread 선언
      pthread_t p_thread1, p_thread2;

      struct account person1;
      person1.balance = 5000;

      // 뮤텍스 객체 초기화, 기본 특성으로 초기화 했음
      pthread_mutex_init(&mutex_lock, NULL);

      pthread_create(&p_thread1, NULL, *withdraw, &person1);
      pthread_create(&p_thread2, NULL, *withdraw, &person1);
      pthread_join(p_thread1, NULL);
      pthread_join(p_thread2, NULL);
      //withdraw(&person1, 100);

      return 0;
}
