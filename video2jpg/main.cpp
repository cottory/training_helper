#define MAX_FILE_NAME 400
#define MAX_PATH 400
#include <opencv/cv.h> //���� ó���� ���� ���
#include <opencv/highgui.h> //ī�޶�� ������ �Է¹ްų� �̹����� �а� ȭ�鿡 �����ֱ� ���� ���
#include <opencv2/opencv.hpp>	//opencv C++
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <direct.h>	//getcwd
using namespace cv;

int isTextFile(const char* arg) {
	
	//.txt Ȯ���ڰ� �ƴ� ���
	
	char* ext_pos;
	char ext[MAX_FILE_NAME];	//Ȯ���� check
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
		std::cerr << "ERROR:: �Է��� ���ڰ� �����մϴ�." << std::endl;
		return 1;
	}

	if (!isTextFile(argv[1])) {
		std::cerr << "ERROR:: Ȯ���ڰ� .txt ������ �ƴմϴ�." << std::endl;
		return 1;
	}

	//1. ������ ��� ��ġ ����
	char create_folder[MAX_PATH];
	char create_folder_origin[MAX_PATH];
	
	_getcwd(create_folder, MAX_PATH);
	strcpy(create_folder_origin, create_folder);

	//2. frame�� ������ ������ file_path�� ���� .txt ������ �н��ϴ�.
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
		
				//1st. ��ο��� ���� �̸��� ����
				offset = strrchr(video_path, '\\');
				strcpy(fileName, offset + 1);

				std::cout << "******************** " << fileName  << " is converting... ********************" << std::endl;

				//2nd. Ȯ���� ����
				offset = strrchr(fileName, '.');
				*offset = '\0';

				//3rd. ���� �����
				strcat_s(create_folder, "\\video");

				strcat_s(create_folder, "\\");
				strcat_s(create_folder, fileName);

				//���+���ϸ�(Ȯ���� ����)���� ���丮 ����
				_mkdir(create_folder);	

				strcat_s(create_folder, "/");
				strcat_s(create_folder, fileName);
				strcat_s(create_folder, "_%03d.jpg");

				Mat frame;

				while (true) {

					countTime++;

					capture >> frame;	//���������κ��� �� �������� �޾� frame������ ���� 
					if (frame.empty()) break;

					if (countTime % 10 == 0) {
						std::string filename;
						filename = cv::format(create_folder, countFrame++);
						imwrite(filename, frame);
						waitKey(1);
					}
				}

				//create_folder ��θ� ���������� �ʱ�ȭ
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
