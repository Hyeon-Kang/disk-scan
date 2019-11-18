## Disk_Scanner
* [기술 개요](#기술-개요)
* [Technologies](#technologies)
* [Setup](#setup)

## 기술 개요
저장장치 물리적 스캔 프로그램. 

  이동식 드라이브의 물리적 공간 0x00000000부터 0xFFFFFFFF까지(32bit 4GB 기준) 바이트 단위로 읽어 출력해주는 프로그램입니다. 
  사용자가 파일을 제거하여도 별도의 완전삭제 프로그램을 사용하지 않는 이상 삭제한 데이터는 그저 접근 경로가 끊긴 상태로 방치 되어있을 뿐, 
  운영체제가 해당 공간에 새로운 데이터를 덮어쓰지 않으면 디스크에 그대로 남아있습니다. 
  본 프로그램은 이와 같이 디스크에 잔류한 프로그램의 흔적을 읽는 기능을 합니다.

	
## Technologies
Project is created with:
* Lorem version: 12.3
* Ipsum version: 2.33
* Ament library version: 999
	
## Setup
To run this project, install it locally using npm:

```
$ cd ../lorem
$ npm install
$ npm start
```
