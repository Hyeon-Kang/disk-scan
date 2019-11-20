#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

// 서버 프로그램

// 클라이언트는 보내는 메시지에서 <GET> 감지 되면
// 보낸 메시지를 파싱해서 파일 이름 추출

// 클라이언트로부터 메시지를 받으면
// <GET> 감지된 경우 문자열 파싱, 파일 이름 추출
// 추출한 이름으로 파일 읽기모드로 생성
// 클라이언트에게 <RDY> 메시지 전달
// 파일 내용 읽어서 변수에 저장후 디스크립터 닫기

// 클라이언트는 <RDY> 메시지를 감지한다면
// 추출한 파일 이름으로 쓰기모드로 파일 생성
// 다음에 넘어오는 데이터를 쓰고 저장, 디스크립터 닫기


typedef enum {false, true} bool;

#define MAXLINE 256
void text_check(int n); // 텍스트 전송오류 검사 함수
int readline(int, char *, int); // 터미널 입력 한줄씩 읽기 함수

int main (int argc, char * argv[]) {
      int pdw, pdr, n; // 파이프 디스크립터, 문자열 디스크립터
      char inmsg[MAXLINE]; // 받는 메시지
      char sendline[MAXLINE], line[MAXLINE]; //보낼 메시지
      char filename[80]; // 추출한 파일 제목 저장
      pid_t pid; // pid 저장
      int size; // 메시지 사이즈

      char *ready = "<RDY>"; // 전송 준비완료 알림 메시지
      char *eof = "<EOF>"; // 전송 종료 알림 메시지
      bool ready_flag = false; // <RDY> 메시지 전송
      char send_text[MAXLINE]; // 전송할 파일 내용

      bool error_flag = false;
      char *err = "파일이 존재하지 않습니다.";

      char *escapechar = "exit\n";	/* 종료문자 */

      //부모 스레드 (server_write 파이프에 쓰기)
      if( (pid = fork()) > 0) {

            // 파이프 생성
            if(mkfifo("./server_write", 0666) == -1) {
                  perror("fifo 생성 오류");
                  exit(1);
            }

            // 파이프 쓰기모드로 열기
            if((pdw = open("./server_write", O_WRONLY)) == -1) {
                  perror("pipe discriptor 열기 실패");
                  exit(1);
            }

            // 반복문 수행
            while(1) {
                  // 자식을 통해 파이프로 받은 메시지가 errror_true 인 경우 error_flag = true;
                  // 자식을 통해 파이프로 받은 메시지가 ready_true 인 경우 ready_flag = true;

                  // 파일이 존재하지 않는 경우
                  if(error_flag == true) {
                          n = write(pdw, err, strlen(err)+1); // err 메시지 전송
                          error_flag = false;
                  }

                  // 파일 전송절차 실행
                  // *** ready_flag = true 인 경우 바로 <RDY> 전송 (파일 전송절차 실행)
                  if(ready_flag == true) {
                        sleep(1); // 잠깐 쉬고
                        n = write(pdw, ready, strlen(ready)+1); // <RDY> 메시지 전송
                        // 메시지 전송 n 오류 처리
                        if (n == -1) {
                              perror("write message 오류");
                              exit(1);
                        }
                        // 이어서 send_text 전송 (EOF 포함 256자리 넘어가면 깨짐!!)
                        n = write(pdw, send_text, strlen(send_text)+1); // 읽어온 파일 내용 전송
                        text_check(n); // 파이프 작성 오류 검사
                        sleep(1); // 잠깐 쉬기 (클라이언트 처리를 위한 여유 시간)
                        n = write(pdw, eof, strlen(eof)+1); // <EOF> 메시지 전송
                        text_check(n);
                        ready_flag = false; //ready_flag = false;
                  } // 파일 전송절차 종료

                  // 터미널 입력 가져오기
                  if(readline(0, sendline, MAXLINE) != 0) {
                        // 입력할 메시지 사이즈 계산
                        size = strlen(sendline);

                        // 이름 추가 절차 (생략)

                        // 종료 입력 감시 (커맨드 : exit\n)
                        if(strcmp(sendline, escapechar, 4) == 0) {
                              printf("채팅 서버를 닫습니다.");
                              close(pdw); // 파이프 디스크립터 닫기
                              break; // 반복문 탈출
                        }

                        // 파이프에 작성 (본래 이름까지 병합하여 line이지만 테스트이므로 sendline 바로 전송)
                        n = write(pdw, sendline, strlen(sendline)+1);
                        text_check(n);

                  } // 터미널 입력 가져오기 종료
            } // end while

            // 자식스레드 종료 기다리기 추가해야 하나???

      } // 부모 스레드 종료
      else { // client_write에서 메시지를 읽어올 자식스레드
            /* 절차 설명
            서버 프로그램이므로 파이프 생성 및 열기
            메시지를 읽어온다.
            <GET>이 감지가 되면
            사용할 저장 변수 filename과 send_text를 NULL로 초기화 한다.
            파싱을 해서 파일 이름을 추출하여 filename에 저장한다.
            추출한 파일 이름이 있다면 (fopen, "r" != -1)
            파일을 열고 내용을 send_text 변수에 저장하고
            파일 디스크립터를 닫고
            ready_flag를 true로 바꾼다. -> (내부 파이프를 통해 부모에게 ready_true 전달)

            만약 -1로 존재하지 않는 경우
            아무것도 건드리지 않고
            error_flag를 true로 한다. -> 내부 파이프를 통해 부모에게 error_true 전달
             */

            // 파이프 생성
            if(mkfifo("./client_write", 0666) == -1) {
                  perror("fifo 생성 오류");
                  exit(1);
            }

            // 파이프 쓰기모드로 열기
            if((pdw = open("./client_write", O_RDONLY)) == -1) {
                  perror("pipe discriptor 열기 실패");
                  exit(1);
            }

            // 반복문 수행
            while(1) {
                  // 메시지 읽어오기
                  n =
            }// 반복문 종료
      } // 자식 스레드 종료

      return 0;
} // end main

  // 파이프에 메시지 작성이 정상적으로 됬는지 검사하는 함수
  void text_check(int n) {
        if (n == -1) {
              perror("write message 오류");
              exit(1);
        }
  }

  // 한 줄씩 읽어오는 함수
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
