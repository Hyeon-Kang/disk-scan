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

// 공유 자원
bool ready_flag = false; // <RDY> 메시지 전송
bool error_flag = false; // <err> 메시지 전송
char send_text[MAXLINE]; // 전송할 파일 내용
char filename[MAXLINE]; // 추출한 파일 제목 저장

char *token = NULL; // 스트링 토큰 리드 변수
char *sArr= {NULL,}; // 스트링 토큰화 순환 변수
char f_name[MAXLINE] = "./"; // 경로 + 추출한 파일 이름 저장용 변수

int main (int argc, char * argv[]) {
  int pdw, pdr, n; // 파이프 디스크립터, 문자열 디스크립터
  char inmsg[MAXLINE]; // 받는 메시지
  char sendline[MAXLINE], line[MAXLINE]; //보낼 메시지
  //char buffer[MAXLINE];
  pid_t pid; // pid 저장
  int size; // 메시지 사이즈

  char *ready = "<RDY>"; // 전송 준비완료 알림 메시지
  char *eof = "<EOF>"; // 전송 종료 알림 메시지

  char *err = "파일이 존재하지 않습니다.";
  char *escapechar = "exit\n";	/* 종료문자 */

      //부모 스레드 (client_write 파이프에 쓰기)

      /* 절차 설명
      부모 스레드

      파이프 쓰기모드로 열기
      문자열 읽은거 전송
      종료 키워드 감시
      <GET> 키워드 감시
      <GET> 발견 시 파싱해서 파일 이름 추출
      진행

      자식 스레드
      파이프 읽기모드로 열기
      받은 물자열 감시 <ERR> -> 파일이 없습니다 출력
      받은 문자열 감시 <RDY> -> ready_flag = true; {
            추출한 이름과 경로 조합으로
            파일 쓰기모드로 열고 준비
      sleep(1);
      send_text를 작성하고
      <EOF> 받으면
      디스크립터 닫기

      터미널 내용에서 개행 입력시 끊어서 문자열 변수로 저장
      저장 변수
      해당 문자열 변수 전송*/

      if( (pid = fork()) > 0) {
            // 서버측에서 파이프 다 만들어놓음
            // 파이프 쓰기모드로 열기
            if((pdw = open("./client_write", O_WRONLY)) == -1) {
                  perror("pipe discriptor 열기 실패");
                  exit(1);
            }

            // 반복문 수행
            while(1) {
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

                  // 입력 값에서 <GET> 감시
                  if( strstr(sendline, "<GET>") != NULL) {
                        printf("<GET> 입력 감지");      // 검사용

                        // 저장용 변수 초기화
                        //sArr = {NULL};
                        f_name = "./";

                        // 토큰화, 이름 추출
                        token =strtok(sendline, " "); // 공백 기준으로 parsing

                        // 토큰 돌리기
                        while( toekn != NULL) {
                              token = strtok(NULL, " ");
                        }

                        // 마지막 토큰 (파일 이름) 가져오기
                        printf("%s", token);
                        // 추출 확인
                        strcat(f_name, "1"); // ./ + "1" + 파일명 (클라이언트가 불러오는 파일과 차별화)
                        strcat(f_name, "token");
                        printf("경로+이름 검사 : %s", f_name);  // 경로+이름 검사
                  } // end <GET> 감시

            } // end 반복문

      } else { // 자식 스레드 (읽기모드)
              // server_write 파이프 읽기모드로 열기
              if( (pdr = open("./server_write", O_RDONLY)) == -1) {
                    perror("파이프 열기 실패");
              }

              // 반복문 수행
              while(1) {
                    // 메시지 읽어오기
                    n = (read(pdr, inmsg, MAXLINE) > 0);
                    text_check(n);
                    // 터미널에 메시지 출력
                    write(1, inmsg, n);

              }

              // <ERR>을 받으면 파일 없음 출력
              if( strstr(inmsg, "<ERR>") != NULL) {
                    printf("파일이 존재하지 않습니다.");
              }

              // <RDY>, 준비 메시지를 받는다면
              if( strstr(inmsg, "<RDY>") != NULL) {
                    printf("파일 다운로드");

                    // 파일 디스크립터 생성
                    FILE *fp;
                    if(fp = fopen(f_name, "w") == -1) {
                          n = (read(pdr, inmsg, MAXLINE) > 0);
                          text_check(n);

                          // 받은 내용 쓰기
                          fputs(inmsg, fp);

                          // 디스크립터 닫기
                          fclose(fp);
                    } // end 파일 쓰기
              } // <RDY> 처리 종료
      } // end else
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
