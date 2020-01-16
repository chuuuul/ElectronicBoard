# 전자 칠판
이 프로그램은 전자칠판으로 칠판에 작성한 내용을 PDF로 변환하여 서버에 저장됩니다.</br></br>

### 개발 계기
다음과 같은 계기로 개발된 어플리케이션입니다.</br>
1. 수업시간에 강사의 필기를 알아보기 힘든 적이 있다.</br>
2. 필기를 하면서 강사의 말을 놓치는 경우가 있다.</br>
3. 집중해서 청취를 하고 나중에 필기하려다가 필기가 지워져 있는 경우가 있다.</br>
4. 강의에 늦게 들어갈 경우 이전의 내용을 놓치게 된다.</br>

### 아이디어
교육기관에서 관리하는 서비스가 있으면 좋겠다.</br>
수업 시작할때 학과, 교수명, 확과명을 선택하여 서버에 올리고 파일을 관리한다.</br>
청자는 모바일 어플리케이션으로 파일을 다운로드하게 된다.</br>

### 기능
펜두께, 펜색깔 지정, undo, redo, 과목 리스트 가져오기, 이미지생성, 이미지 to pdf, 파일전송

### 컨셉
![concept](https://github.com/chuuuul/ElectronicBoard/blob/master/gitData/concept.png)

### 실행방법
Qt5로 프로젝트를 빌드한다.

### 실행화면
##### 강의시작
![main](https://github.com/chuuuul/ElectronicBoard/blob/master/gitData/main.png)

##### 강의중
![board_sw](https://github.com/chuuuul/ElectronicBoard/blob/master/gitData/board_sw.png)

##### 라즈베리파이 + 터치스크린 구동
![board_hw](https://github.com/chuuuul/ElectronicBoard/blob/master/gitData/board_hw.png)

### 환경 / 라이브러리 / 지식
임베디드, 라즈베리파이3, 리눅스, Http통신, json, C++, Qt5, QT 시그널/슬롯
