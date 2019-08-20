# training_helper
data training helper

## 1. video2jpg
동영상으로부터 프레임 별로 이미지를 추출하는 프로그램

### 환경
-visual studio 2017 (Debug & x64 환경)
-opencv 3.2.0

### How to use

1. download to .zip file & opencv 3.2.0 version install 

1-1.Opencv 홈페이지에서 opencv 3.2.0를 다운로드 받습니다. 
https://opencv.org/releases/page/3/
*****

1-2.C:\ 경로에 extract 해줍니다.
*****

**프로젝트 설정 시 환경은 Debug모드 & x64 입니다.**

1-3.추가 포함 디렉토리 설정

프로젝트 => video2jpg속성 => C/C++ 일반 => **추가 포함 디렉토리 경로**에 아래 경로 추가

C:\opencv\build\include
*****

1-4.추가 라이브러리 디렉토리 설정

프로젝트 => video2jpg속성 => 링커 일반 => **추가 라이브러리 디렉토리 경로**에 아래 경로 추가

C:\opencv\build\x64\vc14\lib
*****

1-5.추가 종속성 설정

프로젝트 => video2jpg속성 => 링커 입력 => **추가 종속성**에 아래 파일 추가

opencv_world320d.lib
*****

1-6.build

위의 단계를 그대로 따라왔다면 이제 프로젝트 빌드가 가능합니다. 
*****


2. video2jpg.sln 실행 후 프로젝트 속성 setting

3.


## 2. coming soon

