// mutex를 사용한 동기화 보장 연습
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

// mutex 선언
pthread_mutex_t mutx;

// 계좌 구조체
typedef struct{
  int balance = 0;
} account;
// 계좌 구조체, 인출액
int withdraw(struct account *account, int amount) {
  // 인자 매핑
  account *accounts = (account *) account;

  pthread_mutex_lock (& accounts->mutex); // 잠금

  // 잔액확인
  const int balance = accounts->balance;

  // 인출여부 확인
  if (balance < amount){    // 잔액부족 사례
      pthread_mutex_unlock(& accounts->mutex); // 잠금 해제
      printf("잔액 부족\n");
      return -1;
  }

  // 통장 잔고 업데이트
  accounts->balance -= balance - amount;

  // 현금 인출
  printf("현금 %d 인출\n", amount);

  pthread_mutex_unlock(& accounts->mutex); // 잠금 해제
  return 0;
}
