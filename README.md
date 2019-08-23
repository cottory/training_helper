# training_helper  
Program to help image training and image tagging
- video2jpg
- anchor box checker

## 1. video2jpg  
동영상에서 프레임 단위로 jpg 파일을 추출하는 프로그램

### 환경
- visual studio 2017 (Debug & x64 환경)

- opencv 3.2.0

### How to use


### step 1. project build  


1-1. program download

training_helper.zip 코드와 Opencv 홈페이지에서 opencv 3.2.0를 다운 받습니다. 

https://opencv.org/releases/page/3/
*****

1-2. program install 

C:\ 경로에 opencv 3.2.0을 extract 합니다.


*****


1-3. video2jpg.sln 실행

**프로젝트 설정 환경은 Debug모드 & x64**
*****


1-3. 추가 포함 디렉토리 설정

프로젝트 => video2jpg 속성 => C/C++ 일반 => **추가 포함 디렉토리 경로**에 아래 경로 추가

<pre><code>C:\opencv\build\include</code></pre>
*****

1-4. 추가 라이브러리 디렉토리 설정

프로젝트 => video2jpg 속성 => 링커 일반 => **추가 라이브러리 디렉토리 경로**에 아래 경로 추가

<pre><code>C:\opencv\build\x64\vc14\lib</code></pre>
*****

1-5. 추가 종속성 설정

프로젝트 => video2jpg 속성 => 링커 입력 => **추가 종속성**에 아래 파일 추가

<pre><code>opencv_world320d.lib</code></pre> 
*****

1-6. build

위 단계를 모두 마쳤다면 프로젝트 빌드가 가능합니다.
*****
*****
*****
*****
*****


### step 2. opencv 파일 복사 & video 디렉토리 생성 

<pre><code>현재 경로: \training_helper-master\training_helper-master\video2jpg\x64\Debug</code></pre>

**이제 작업하는 기본 디렉토리 경로는 video2jpg.exe 파일이 있는 경로 입니다.**

*****


2-1. opencv 파일 복사

<pre><code>opencv 파일 경로: C:\opencv\build\x64\vc14\bin </code></pre>

위 경로에 있는 opencv_world320d.dll을 포함한 8개 파일을 현재 경로에 전부 복사해줍니다.

*****


2-2. video directory 생성

현재 경로에 새로 "video"라는 디렉토리를 만듭니다.

**디렉토리명은 꼭 video 여야 합니다.**

*****

2-3. 동영상 파일 넣기

<pre><code>현재 경로: \training_helper-master\training_helper-master\video2jpg\x64\Debug\video</code></pre> 

현재 경로에 동영상 파일을 넣습니다. **동영상 파일명은 공백/한글이 없어야 합니다.**

*****
*****
*****
*****
*****


### step 3. converting video file

3-1. list.txt 생성

<pre><code>현재 cmd 경로: \training_helper-master\training_helper-master\video2jpg\x64\Debug\video</code></pre>

cmd 창을 켜고 아래 명령어를 입력해줍니다.

<pre><code>$ dir /s /b *.mp4 > list.txt</code></pre>

list.txt에는 .jpg를 만들 동영상 파일들의 경로가 들어있습니다.


*****

3-2. list.txt 복사

생성된 list.txt를 video2jpg.exe가 있는 디렉토리에 복사해줍니다.

*****

3-3. command 입력

<pre><code>현재 cmd 경로: \training_helper-master\training_helper-master\video2jpg\x64\Debug</code></pre>

cmd창에서 command를 입력해줍니다.

<pre><code>$ video2jpg.exe list.txt</code></pre>

*****

3-4. 결과 확인

video 디렉토리에 동영상 파일명과 동일한 디렉토리가 생깁니다. 

이로써 동영상으로부터 추출된 .jpg 파일을 얻을 수 있습니다.

*****
*****
*****
*****
*****





## 2. anchorboxChecker
이미지 태깅 작업 후, 태깅이 올바르게 되었는지 확인하는 프로그램

### 환경
- visual studio code

- g++ (MinGW.org GCC-6.3.0-1) 6.3.0

### How to use
*****
이 프로그램은 Yolo_mark-master를 기반으로 동작합니다.

1. 태깅을 완료하면 아래 디렉토리 경로에 태깅한 .txt 파일이 있습니다.

~~~
\Yolo_mark-master\x64\Release\data\img
~~~

2. yolo_mark.dll 파일이 있는 디렉토리 경로에 anchorboxChecker.exe를 복사해줍니다.

~~~
\Yolo_mark-master\x64\Release
~~~

3. 실행

`현재경로: \Yolo_mark-master\x64\Release`
~~~
> anchorboxChecker.exe
~~~

*****
*****
*****
*****
*****

### 기능(4가지)

**기본 기능은 두 가지**

1. **check:** PIVOT값과 txt파일에 태깅된 anchor box 개수 비교

2. **delete:** 특정 번호의 anchor box 모두 삭제

anchorboxChecker는 아래 디렉토리 경로에 있는 모든 txt 파일을 대상으로 동작합니다.
~~~
\Yolo_mark-master\x64\Release\data\img
~~~
*****

* check: PIVOT값과 다르게 태깅된 모든 txt 파일명을 출력.

`The default pivot value is 0.` 

`PIVOT 값이 0인 경우, 태깅되지 않은 모든 txt 파일명을 출력.`

<pre><code>> check </code></pre> 

* delete: txt파일에 태깅된 특정 번호 anchor box를 삭제.

<pre><code>> delete anchorbox_Number </code></pre> 

* update: PIVOT값을 갱신.

<pre><code>> update PIVOT_NUMBER </code></pre> 

* print: 현재 설정된 PIVOT값을 출력.

<pre><code>> print </code></pre> 

* exit: 프로그램 종료.

<pre><code>> exit</code></pre>
