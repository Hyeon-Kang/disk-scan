#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char * argv[]) {
    int fd;
    caddr_t addr;
    struct stat statbuf;

    if(argc != 2) {
        fprintf(stderr, "Usage : %s filename\n", argv[0]);
        exit(1);
    }

    if(stat(argv[1], &statbuf) == -1) {
        perror("stat");
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        exit(1);
    }
    // 파일 내용을 메모리에 매핑
    addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0);

    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    close(fd);

    printf("%s", addr);

    if (munmap(addr, statbuf.st_size) == -1) { // 메모리 매핑 해제
        perror("munmap");
        exit(1);
    }

    // 메모리 접근해서 오류 발생 확인해보기
    //printf("%s", addr); // 매핑이 해제된 메모리에 접근 => 오류 발생

    return 0;
}
