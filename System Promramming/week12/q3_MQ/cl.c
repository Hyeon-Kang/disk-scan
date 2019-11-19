#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
      key_t key;
      int msgid;

      key = ftok("keyfile", 1);
      msgid = msgget(key, IPC_CREAT|0644);
      if (msgid == -1) {
            perror("msgget error");
            exit(1);
      }

      printf("Before IPC_RMID\n");
      system("ipcs -q");
      msgctl(msgid, IPC_MRID, (struct msgid_ds *) NULL); // 메시지 큐 삭제
      printf("After IPC_RMID\n");
      system("ipcs -q");

      return 0;
}
