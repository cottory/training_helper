training_helper  
======
data training helper


## 1. video2jpg  
동영상에서 프레임 단위로 .jpg 파일을 추출하는 프로그램

## 환경
- visual studio 2017 (Debug & x64 환경)

- opencv 3.2.0

## How to use


### step 1. project build  


1-1. training_helper.zip 코드와 Opencv 홈페이지에서 opencv 3.2.0를 다운 받습니다. 

https://opencv.org/releases/page/3/
*****

1-2. C:\ 경로에 opencv 3.2.0을 extract 합니다.
*****


1-3. video2jpg.sln 실행

**프로젝트 설정 환경은 Debug모드 & x64**
*****


1-3. 추가 포함 디렉토리 설정

프로젝트 => video2jpg 속성 => C/C++ 일반 => **추가 포함 디렉토리 경로**에 아래 경로 추가

C:\opencv\build\include
*****

1-4. 추가 라이브러리 디렉토리 설정

프로젝트 => video2jpg 속성 => 링커 일반 => **추가 라이브러리 디렉토리 경로**에 아래 경로 추가

C:\opencv\build\x64\vc14\lib
*****

1-5. 추가 종속성 설정

프로젝트 => video2jpg 속성 => 링커 입력 => **추가 종속성**에 아래 파일 추가

opencv_world320d.lib (디버깅 모드일 경우)
*****

1-6. build

위 단계를 모두 마치셨다면 프로젝트 빌드가 가능합니다.
*****
*****
*****
*****
*****


### step 2. opencv 파일 복사 & video 디렉토리 생성 


이제 작업하는 기본 디렉토리 경로는 video2jpg.exe 파일이 있는 \x64\Debug 입니다.

**현재 경로: \training_helper-master\training_helper-master\video2jpg\x64\Debug**

*****


2-1. **C:\opencv\build\x64\vc14\bin 에 있는 8개의 파일을 모두 복사**

opencv_world320d.dll을 포함한 8개의 파일을 현재 경로에 전부 복사해줍니다.

*****


2-2. **video directory 생성**

현재 경로에 새로 video 디렉토리를 만들어줍니다.

*****

2-3. video 디렉토리에 동영상 파일을 넣어줍니다.

**동영상 파일명은 공백/한글이 없어야 합니다.**
*****
*****
*****
*****
*****


## step 3. converting video file

3-1. list.txt 생성

**현재 경로: \training_helper-master\training_helper-master\video2jpg\x64\Debug\video**

cmd 창을 켜고 아래 명령어를 입력해줍니다.


<pre><code>dir /s /b *.mp4 > list.txt</code></pre>

list.txt에는 .jpg를 만들 동영상 파일들의 경로가 들어있습니다.


*****

3-2. list.txt 복사

생성된 list.txt를 video2jpg.exe가 있는 디렉토리에 복사해줍니다.

*****

3-3. command 입력

cmd창에서 command를 입력해줍니다.

**현재 경로: \training_helper-master\training_helper-master\video2jpg\x64\Debug**


<pre><code>$ video2jpg.exe list.txt</code></pre>

*****

3-4. 결과 확인

\video 디렉토리에 동영상 파일명과 동일한 디렉토리가 생깁니다. 

이로써 동영상으로부터 추출된 .jpg 파일을 얻을 수 있습니다.

*****
*****
*****
*****
*****













## 2. anchor box utility



