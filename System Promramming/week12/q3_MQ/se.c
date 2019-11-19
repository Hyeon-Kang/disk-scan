/*
메시지 큐를 사용해서 1:1 채팅 프로그램을 만드세요. 채팅 프로그램은 비동기 채팅을 지원해야 합니다.
즉, A => B => A => B => … 순서로만 채팅을 하는 것이 아니라, 사용자는 언제든 메시지를 전송할 수 있어야 합니다.

[Task] 1:1 채팅을 시작하고, 채팅을 하는 사용자 A와 B가 다음의 순서대로 메시지를 전송하세요. A => B => B => A => A => A.
*/

#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct mymsgbuf {
      long mtype;
      char mtext[80];
};

int main(void) {
      key_t key;
      int msgid;
      struct mymsgbuf mesg;

      key =ftok("keyfile", 1); // 키파일 정의
      msgid = msgget(key, IPC_CREAT|0644); //메시지 큐 생성 및 id 획득
      if (msgid == -1) {
            perror("msgget error");
            exit(1);
      }

      mesg.mtype = 1; // 유형을 1로 정의
      strcpy(mesg.mtext, "Message Q Test \n");

      // 메시지 전송
      if (msgsnd(msgid, (void *) &mesg, 80, IPC_NOWAIT) == -1) {
            perror("msgsnd error");
            exit(1);
      }

      return 0;
}


/*
  구상

  pid_t pid

  부모 // MQ 쓰기
  자식 // MQ 읽기

  */
