// gcc -o name s_pipe.c
// 실행 : ./name [상대에게 보여줄 식별 이름]

// pipe를 이용한 채팅 프로그램
// <GET> aaa.txt 입력 시 aaa.txt 다운로드
// 입력 받은 값에서 strstr 함수로 <GET> 문자열 찾기
// 해당 문자열 발견 시 offset 6부터 문자열 파싱함
// 파싱한 문자열의 텍스트가 서버의 디렉토리에 있다면
// 해당 파일 복사하여 open write 모드로 저장
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

typedef enum {false, true} bool;

#define MAXLINE 256

int readline(int, char *, int); // 한줄씩 읽기 함수

int main (int argc, char * argv[]) {
  int pd, n;
  char inmsg[MAXLINE];
  char sendline[MAXLINE], line[MAXLINE];
  char filename[80];
  pid_t pid;
  int size;

  char *escapechar = "exit\n";	/* 종료문자 */

  // 부모의 경우 (쓰기)
  if(( pid = fork()) > 0) {
        // send

        // 서버가 작성할 파이프 생성
        if(mkfifo("./server_write", 0666) == -1) {
              perror("mkfifo");
              exit(1);
        }

        if ((pdw = open("./server_write", O_WRONLY)) == -1) {
              perror("open");
              exit(1);
        }

        while(readline(0, sendline, MAXLINE) != 0) { // 표준 입력 가져오기
              size = strlen(sendline);
              // 이름 추가
              sprintf(line, "%s %s", argv[1], sendline);

              n = write(pdw, line, strlen(line)+1);
              if (n == -1) {
                    perror("write");
                    exit(1);
              }

              /* 종료 문자열 입력 확인 */
              if(strncmp(sendline, escapechar, 4) == 0) {
                printf("close chat_server.\n");
                close(pdw);
                kill(pid, SIGQUIT);
                break;
              }
        }
        //close(pd);

  } else { // 자식의 경우 (읽기)
              // receive
              // 클라이언트가 작성할 파이프 생성
              if(mkfifo("./client_write", 0666) == -1) {
                    perror("mkfifo");
                    exit(1);
              }
              if ((pdr = open ("./client_write", O_RDONLY)) == -1) { // 서버에서 생성한 FIFO 열기
                    perror("open");
                    exit(1);
              }

              while ((n = read(pdr, inmsg, MAXLINE)) > 0) {
                    write(1, inmsg, n);
                    if(strstr (inmsg, "<GET>") != NULL){ // <GET> 검사
                          //printf("<GET> 감지\n"); // test
                          char *sArr[80] = { NULL, };
                          char f_name[80];
                          int i = 0;
                          char *p = NULL;
                          p = strtok(inmsg, " ");
                          bool flag = false;
                          while (p != NULL){
                                //puts(p);
                                //i++;
                                p = strtok(NULL, " ");
                                if(flag == true) {
                                      strcpy(sArr, p);
                                      printf("데이터 요청: %s\n", sArr);

                                      flag = false;

                                      // 파일 열기 절차
                                      printf("SYSTEM : open %s\n",sArr);
                                      strcpy(filename, "./");
                                      strcpy(filename, sArr);
                                      printf("경로 예제 : %s", filename);

                                      if( (FILE * fp = fopen(filename, "r")) == -1) {
                                              // 파일 없다고 메시지 전송 추가
                                              printf("파일열기 오류.");
                                      } else {
                                            // 해당 파일 열기 성공 시 진행
                                            // 파이프 디스크립터로 서버 작성공간 쓰기모드로 열고 <RDY> 메시지 날리기
                                            if ((pd_w = open("./server_write", O_WRONLY)) == -1) {
                                                  perror("open");
                                                  exit(1);
                                            }

                                            while(readline(0, sendline, MAXLINE) != 0) { // 표준 입력 가져오기
                                                  size = strlen("파일이 없습니다.\n");
                                                  // 이름 추가
                                                  char *ready = "<RDY>";
                                                  //sprintf(line, "%s %s", argv[1], "파일이 없습니다.\n");

                                                  n = write(pd_w, ready, strlen(ready)+1); // <RDY> 메시지 전송
                                                  if (n == -1) {
                                                        perror("write");
                                                        exit(1);
                                                  }
                                            } // end while
                                      } // end else

                                      // 파일 데이터 가져오기
                                      printf("파일 데이터 가져오기\n");
                                      char string[255]; // 문자열 저장할 배열
                                      fscanf(fp, "%s", string);
                                      // 가져온 데이터 전송
                                } // end if flag == true
                                if(strcmp(p, "<GET>") == 0){
                                      flag = true;
                                }
                          }
                          //printf("데이터 요청 : %s\n", sArr);
                    }
              }// 서버가 보낸 데이터 읽기


              if (n == -1) {
                    perror("read");
                    exit(1);
              }
              write(1, "\n", 1);
              close(pd);
        }
        return 0;
}

int readline(int fd, char *ptr, int maxlen) {
  int n, rc;
  char c;
  for(n = 1; n < maxlen; n++) {
    if((rc = read(fd, &c, 1)) == 1) {
      *ptr++ = c;
      if (c == '\n') break;
    } else if (rc == 0) {
      if(n == 1) return (0);
      else break;
    }
  }
  *ptr = 0;
  return (n);
}
