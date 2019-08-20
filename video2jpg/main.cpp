#define MAX_FILE_NAME 400
#define MAX_PATH 400
#include <opencv/cv.h> //영상 처리를 위한 헤더
#include <opencv/highgui.h> //카메라로 영상을 입력받거나 이미지를 읽고 화면에 보여주기 위한 헤더
#include <opencv2/opencv.hpp>	//opencv C++
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <direct.h>	//getcwd
using namespace cv;

int isTextFile(const char* arg) {
	
	//.txt 확장자가 아닌 경우
	
	char* ext_pos;
	char ext[MAX_FILE_NAME];	//확장자 check
	strcpy(ext, arg);
	ext_pos = strrchr(ext, '.');
	strcpy(ext, ext_pos + 1);

	if (strcmp(ext, "txt")) {
		return 0;
	}
	else {
		return 1;
	}
}

int main(int argc, char** argv) {

	if (argc < 2) {
		std::cerr << "ERROR:: 입력한 인자가 부족합니다." << std::endl;
		return 1;
	}

	if (!isTextFile(argv[1])) {
		std::cerr << "ERROR:: 확장자가 .txt 형식이 아닙니다." << std::endl;
		return 1;
	}

	//1. 저장할 경로 위치 저장
	char create_folder[MAX_PATH];
	char create_folder_origin[MAX_PATH];
	
	_getcwd(create_folder, MAX_PATH);
	strcpy(create_folder_origin, create_folder);

	//2. frame을 저장할 동영상 file_path를 담은 .txt 파일을 읽습니다.
	std::ifstream readFile(argv[1]);
	
	if (readFile.is_open()) {

		std::cout << "******************** converting process is start! ********************" << std::endl;

		char fileName[MAX_FILE_NAME];
		char video_path[MAX_PATH];
		
		while (readFile.getline(video_path, sizeof(video_path))) {

			int countTime = 0;
			int countFrame = 0;
			
			std::string video_path_str = std::string(video_path);
			VideoCapture capture(video_path_str);

			if (!capture.isOpened()) {
				std::cerr << "******************** ERROR:: cv::VideoCapture is not opended ********************" << std::endl;
			}
			else {

				char *offset;
		
				//1st. 경로에서 파일 이름만 저장
				offset = strrchr(video_path, '\\');
				strcpy(fileName, offset + 1);

				std::cout << "******************** " << fileName  << " is converting... ********************" << std::endl;

				//2nd. 확장자 제거
				offset = strrchr(fileName, '.');
				*offset = '\0';

				//3rd. 폴더 만들기
				strcat_s(create_folder, "\\video");

				strcat_s(create_folder, "\\");
				strcat_s(create_folder, fileName);

				//경로+파일명(확장자 제외)으로 디렉토리 생성
				_mkdir(create_folder);	

				strcat_s(create_folder, "/");
				strcat_s(create_folder, fileName);
				strcat_s(create_folder, "_%03d.jpg");

				Mat frame;

				while (true) {

					countTime++;

					capture >> frame;	//동영상으로부터 한 프레임을 받아 frame변수에 저장 
					if (frame.empty()) break;

					if (countTime % 10 == 0) {
						std::string filename;
						filename = cv::format(create_folder, countFrame++);
						imwrite(filename, frame);
						waitKey(1);
					}
				}

				//create_folder 경로를 기존값으로 초기화
				strcpy(create_folder, create_folder_origin);	
				capture.release();

				std::cout << "******************** video_file converting is ended! ********************" << std::endl;
			}
		}

		std::cout << "******************** converting process is end! ********************" << std::endl;

	}
	else {
		std::cout << "******************** ERROR:: .txt file is not opened! ********************" << std::endl;
	}

	readFile.close();
	return 0;
}
