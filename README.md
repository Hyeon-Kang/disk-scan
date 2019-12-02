## Disk_Scanner

## 목차
* [프로젝트 구성원](#프로젝트-구성원)
* [프로젝트 소개](#프로젝트-소개) // 개발 아키텍쳐 추가
* [프로젝트 결과](#프로젝트-결과) // 다이어그램 추가
* [사용법](#사용법)
* [활용 방안](#활용-방안)
* [Setup](#setup)





## 프로젝트 구성원
 * 강 현 : 기획 및 개발 담당
 
 
## 프로젝트 소개
 * 저장장치 물리적 스캔 프로그램. 

  이동식 드라이브의 물리적 공간 0x00000000부터 0xFFFFFFFF까지(32bit 4GB 기준) 바이트 단위로 읽어 출력해주는 프로그램입니다. 
  사용자가 파일을 제거하여도 별도의 완전삭제 프로그램을 사용하지 않는 이상 삭제한 데이터는 그저 접근 경로가 끊긴 상태로 방치 되어있을 뿐, 
  운영체제가 해당 공간에 새로운 데이터를 덮어쓰지 않으면 디스크에 그대로 남아있습니다. 
  본 프로그램은 이와 같이 디스크에 잔류한 프로그램의 흔적을 읽는 기능을 합니다.
  
  
 * 검증 방법
 
  실험을 진행할 외부저장장치에 별도의 소거 프로그램을 이용하여 완전포맷을 진행합니다.
  ![완전포맷](https://user-images.githubusercontent.com/44962939/69961262-dbf32980-154e-11ea-8d9d-92666888938b.PNG)
 
  포맷이 끝난 뒤 디스크 공간을 스캔하여 별도의 값이 있는지 검사합니다.
  ![반복중](https://user-images.githubusercontent.com/44962939/69961318-f75e3480-154e-11ea-8a7b-a387d1e6ba88.PNG)

  
  
  


## 프로젝트 결과
Project is created with:
* Lorem version: 12.3
* Ipsum version: 2.33
* Ament library version: 999


## 사용법


## 활용 방안


## Setup
To run this project, install it locally using npm:

```
$ cd ../lorem
$ npm install
$ npm start
```
