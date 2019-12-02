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
  저장장치는 전통적으로 한 섹터당 512 바이트의 공간을 가지므로 버퍼의 단위를 512 바이트로 설정했습니다.
  ```
  BYTE sector[512];
  ``` 
  
  
  
  데이터 저장 서식을 %x, %d, $c 등 어떤 것이든 관계 없습니다. 다만 바이트 단위로 데이터를 얻고 싶다면 바이트 단위로 재작성 하거나 얻은 결과를
  추가로 변환해야 합니다. 다음 자료는 %d 서식을 사용하여 10진수로 추출한 데이터 더미입니다.
  (데이터 용량이 1GB 단위로 모두 받으면 열리지 않기 때문에 데이터가 저장된 것으로 확인되는 앞 부분만 잘랐습니다.)
  ![포맷 후 데이터](https://user-images.githubusercontent.com/44962939/69962325-25dd0f00-1551-11ea-929d-951be1243823.PNG)

  
  
  
    
  데이터가 직관적이지 않기 때문에 0과 같이 불필요한 데이터는 보이지 않게 수정합니다.
  (%d -> %s)
  ```
  fprintf(pFile, "%s", sector);
  ``` 
  
  
  
  불필요한 문자가 보이지 않도록 수정한 뒤 다시 데이터를 생성합니다. 아무것도 없는 것 같지만 공백문자로 가득 찬 데이터 더미입니다.
  ![문자열처리](https://user-images.githubusercontent.com/44962939/69962767-0eeaec80-1552-11ea-9a80-f73cf450328a.PNG)
  
  
  
  
  
  텅 비어 의미 없는 값만 가득 찬 디스크에 hello.txt 를 작성합니다.
  ![hello](https://user-images.githubusercontent.com/44962939/69961520-6471ca00-154f-11ea-82e0-d63c5e486e68.png)






  다시 디스크를 스캔 후 결과를 확인합니다. (의미 없는 숫자까지 보이도록 다시 %d로 전환)
  ![hello생성후 더미](https://user-images.githubusercontent.com/44962939/69963333-5faf1500-1553-11ea-91f4-21c73dcb489e.PNG)

  
  
  
  
  역시 불필요한 문자열이 보이지 않도록 수정한 후 다시 스캔합니다.
  문자열로 출력하니 헤더로 추정되는 부분은 깨져있고 'hello world!!' 문자열이 출력됩니다.
  ![hello 발견](https://user-images.githubusercontent.com/44962939/69963827-612d0d00-1554-11ea-8797-ceda5c95968e.PNG)


  
  
  최종 목표 검증을 위해 hello.txt를 외부저장매체에서 제거합니다.
  ![hello삭제1](https://user-images.githubusercontent.com/44962939/69963966-b8cb7880-1554-11ea-85b0-efdfe29a341c.PNG)
  ![hello삭제2](https://user-images.githubusercontent.com/44962939/69963999-c97bee80-1554-11ea-93c4-fe02e2f85afa.PNG)


  
  
  삭제를 확인했습니다. 디스크 스캔을 진행해봅시다.
  
  
  

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
