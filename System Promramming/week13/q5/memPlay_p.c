// 메모리 매핑을 통해 부모 프로세스와 자식 프로세스가 데이터 교환 (= 통신)

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int random_p, random_c;
    int fd;
    pid_t pid;
    caddr_t addr;
    char *temp;
    struct stat statbuf;

    // 입력 인자 개수 불 일치
    if (argc != 2) {
        fprintf(stderr, "Usage : %s filename\n", argv[0]); // 인자로 파일명 전달
        exit(1);
    }

    // 입력받은 파일 정보 조회
    if (stat(argv[1], &statbuf) == -1) {
        perror("stat error");
        exit(1);
    }

    // 파일 열기
    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror("open error");
        exit(1);
    }

    // 메모리 매핑 과정
    addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0); // 메모리 매핑 설정



    if (addr == MAP_FAILED) { // 매핑 오류처리
        perror("mmap error");
        exit(1);
    }
    close(fd);

    printf("읽어온 게임판 검사 : %s", addr);


    if((pid = fork()) > 0) { // 부모 프로세스
        srand(time(NULL)); // 자식과 달리 부모는 가변적 랜덤시드 생성

        // 100번 반복
        for(int j=0; j<100; j++){
            random_p = rand()%100; // 0~99 범위에서 임의의 값 선택(배열 탐색용)
            printf("부모 %d 접근\n", random_p);
            if(addr[random_p] != 'p'){ // 접근 한 값이 p 가 아니라면
                printf("부모 %d 수정\n", random_p);
                addr[random_p] = 'p'; // p로 수정
                //msync(addr, statbuf.st_size, MS_SYNC); // 메모리 수정사항 동기화
            }
            sleep(1);
        } // end for

        printf("게임 결과 : %s\n", addr);
        strcpy(temp, addr);
        FILE *fpp = fopen(argv[1], "w+");    // 파일을 읽기/쓰기 모드로 열기.
        fwrite(temp, strlen(temp), 1, fpp);
        fclose(fpp);

    } else if(pid == 0) { // 자식 프로세스
        for(int i=0; i<100; i++) {
            for(int a=0; a<100; a++) {
                if(addr[a] == 'p'){
                    printf("자식 %d 접근\n", a);
                    printf("자식 %d 수정\n", a);
                    addr[a] = 'c';
                    break;
                }
            } // end inner for
            sleep(1);
        } // end for
    }// end child
    //msync(addr, statbuf.st_size, MS_SYNC);


    //munmap(addr, statbuf.st_size); // 메모리 매핑 해제
    return 0;
}
