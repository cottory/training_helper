# training_helper
data training helper

## 1. video2jpg
동영상으로부터 프레임 별로 이미지를 추출하는 프로그램

## 환경
- visual studio 2017 (Debug & x64 환경)

- opencv 3.2.0

## How to use

step 1. project build  
======


1-1. training_helper.zip 코드와 Opencv 홈페이지에서 opencv 3.2.0를 다운로드 받습니다. 

https://opencv.org/releases/page/3/
*****

1-2. C:\ 경로에 다운받은 opencv 3.2.0을 extract 해줍니다.
*****


1-3. video2jpg.sln 실행

**프로젝트 설정 환경은 Debug모드 & x64**
*****


1-3. 추가 포함 디렉토리 설정

프로젝트 => video2jpg속성 => C/C++ 일반 => **추가 포함 디렉토리 경로**에 아래 경로 추가

C:\opencv\build\include
*****

1-4. 추가 라이브러리 디렉토리 설정

프로젝트 => video2jpg속성 => 링커 일반 => **추가 라이브러리 디렉토리 경로**에 아래 경로 추가

C:\opencv\build\x64\vc14\lib
*****

1-5. 추가 종속성 설정

프로젝트 => video2jpg속성 => 링커 입력 => **추가 종속성**에 아래 파일 추가

opencv_world320d.lib
*****

1-6. build

위의 단계를 다 하셨다면 이제 프로젝트 빌드가 가능합니다. 
*****



### step 2. next to build step  

step2에서 작업하는 경로는 build를 통해 생성된 \x64\Debug 입니다.

**\training_helper-master\training_helper-master\video2jpg\x64\Debug**




2-1. **C:\opencv\build\x64\vc14\bin 에 있는 8개의 파일을 모두 복사**

opencv_world320d.dll을 포함한 8개의 파일을 전부 위 경로에 복사해줍니다.

*****


2-2. **video directory 생성**

\training_helper-master\training_helper-master\video2jpg\x64\Debug

*****

2-3. video 디렉토리에 동영상 파일을 넣어줍니다.

*****













## 2. coming soon

