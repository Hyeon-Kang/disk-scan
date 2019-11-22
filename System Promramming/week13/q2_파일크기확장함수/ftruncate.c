#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main (void) {
    int fd, pagesize, length;
    caddr_t addr;

    pagesize = sysconf(_sc_PAGESIZE); // 메모리의 [페이지 크기] 정보 검색
    length = 1 * pagesize;

    // 파일 생성
    if ((fd = open ("m.dat", O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1) {
        perror("open");
        exit(1);
    }

    if(ftruncate(fd, (off_t) length) == -1) { // 빈 파일의 크기 증가
        perror("ftruncate");
        exit(1);
    }
}
