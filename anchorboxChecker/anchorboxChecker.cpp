#define LINE_SIZE 50
#define FILE_SiZE 1024
#define PATH_SIZE 1024
#include <direct.h>
#include <dirent.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

bool flag;  //Variable to check if the function performed correctly

string file_path;   //file_path:: \data\img 디렉토리 경로

vector<string> fileList, textList, errorFileList;  
     //fileList:: img 디렉토리에 있는 모든 파일명을 담고 있는 vector
     //textList:: img 디렉토리에 있는 모든 .txt 파일명을 담고 있는 vector
//errorFileList:: img 디렉토리에 있는 모든 오류가 있는 .txt 파일명을 담고 있는 vector


bool init();                                                        //전처리2:: 디렉토리 내에 있는 .txt 파일명만 textList vector로 추출하는 함수
vector<string> list_dir(const char* path);                          //전처리1:: 디렉토리 내에 있는 모든 파일명을 fileList vector로 반환하는 함수
bool check_list(vector<string>& text_list, int ANCHOR_BOX_COUNT);   //태깅한 모든 이미지 파일의 anchor box 개수와 pivot anchor box 개수를 비교하는 함수
bool delete_number(vector<string>& text_list, int number);          //태깅한 특정 anchor box number를 .txt 파일에서 지우는 함수
bool update_number(int& anchor_box_number, int val);                //Pivot anchor box 개수를 갱신하는 함수
bool print_anchorbox_number(int anchorbox_number);                  //Pivot anchor box 개수를 출력하는 함수 


int main(int argc, char** argv) {

    int ANCHOR_BOX_COUNT = 0;   //pivot anchor box number. The initial value is 0.
    char _file_path[PATH_SIZE]; //_file_path is the c string variable for the "file path" variable.

    _getcwd(_file_path, PATH_SIZE);
    string convert_to_string(_file_path);
    file_path = convert_to_string;
    file_path += "\\data\\img";
    
    while(true) {

        //  I/O
        cout << "******* Please enter commands only in English:: // 1.check // 2.delete 6 // 3.update 6 // 4.print // 5.exit *******" << endl;
        cout << "> ";
        
        string cmd;
        cin >> cmd;

        const char *cmd_c_str = cmd.c_str();

        if (strcmp(cmd_c_str, "check") && strcmp(cmd_c_str, "delete") && strcmp(cmd_c_str, "update") 
            && strcmp(cmd_c_str, "print") && strcmp(cmd_c_str, "exit")) {
            cerr << "ERROR::Incorrect command entered. Please enter it again." << endl << endl;
            continue;
        }
        else {

            fileList.clear();
            textList.clear();
            errorFileList.clear();

            flag = false;
            flag = init();

            if (!flag) {
                cerr << "The directory was not opened." << endl;
                return -1;
            }   

            if (!strcmp(cmd_c_str, "check")) {   //1. CHECK
                flag = check_list(textList, ANCHOR_BOX_COUNT);
                if (flag && ANCHOR_BOX_COUNT == 0 && errorFileList.empty()) {
                    cout << "Pivot anchor box number is zero and there is an anchor box in every file. " << endl;
                }
                else if (flag && errorFileList.empty()) {
                    cout << "All files meet the pivot anchor number. " << endl;
                }
                else if (flag && !errorFileList.empty()) {

                    cout << "********** Text files where the error were detected ********** " << endl;
                    sort(errorFileList.begin(), errorFileList.end(), [](string s1, string s2) {
                        int s1_length = s1.length();
                        int s2_length = s2.length();

                        if (s1_length == s2_length) {
                            if (s1.compare(s2) < 0) return true;
                            else return false;
                        }
                        else {
                            return (s1_length < s2_length ? true : false);
                        }
                    });

                    for (string errorFile : errorFileList) {
                        cout << errorFile << endl;
                    }

                    cout << endl;
                }
                else {
                    cerr << "check command was not performed correctly." << endl << endl;
                    continue;
                }
            }
            else if (!strcmp(cmd_c_str, "delete")) {  //2. DELETE NUMBER
                int targetNumber;
                cin >> targetNumber;

                if (targetNumber < 0) {
                    cerr << "The anchor box number you want to delete must be zero or positive." << endl << endl;
                    continue;
                }
                else {
                    flag = delete_number(textList, targetNumber);
                }

                if (flag) {
                    cout << "The anchor box number " << targetNumber<< " has been removed. " << endl;
                }
                else {
                    cerr << "delete command was not performed correctly." << endl << endl;
                    continue;
                }
            }
            else if (!strcmp(cmd_c_str, "update")) {    //3. UPDATE NUMBER
                int new_anchorbox_count;
                cin >> new_anchorbox_count;
                
                flag = update_number(ANCHOR_BOX_COUNT, new_anchorbox_count);

                if (!flag) {
                    cerr << "The pivot anchor box number must be zero or positive." << endl << endl;
                    continue;
                }
                else {
                    cout << "The pivot anchor box number has changed:: " << ANCHOR_BOX_COUNT << endl;
                }
            }
            else if (!strcmp(cmd_c_str, "print")) {     //4. PRINT NUMBER
                flag = print_anchorbox_number(ANCHOR_BOX_COUNT);
                
                if (!flag) {
                    cerr << "print command was not performed correctly." << endl << endl;
                    continue;
                }
            }      
            else if (!strcmp(cmd_c_str, "exit")) {      //5. EXIT PROGRAM
                cout<< "********** The exit command has been entered. The program has ended. **********" << endl;
                break;
            } 

            if (flag) {
                cout << "The command "<< cmd_c_str << " was performed." << endl << endl;
            }

        }
    }

    return 0;
}

bool init() {

    const char *path = file_path.c_str();
    fileList = list_dir(path);

    if (fileList.empty()) {
        return false;
    }
    else {
        for (string file : fileList) {
            if (string::npos != file.find(".txt")) {
                textList.push_back(file);
            }
        }
    }
    return true;
}

vector<string> list_dir(const char* path) {
    struct dirent *entry;
    DIR *dir = opendir(path);   //path 경로의 디렉토리 열기
    vector<string> ret;

    if (dir == NULL) {
        return ret;
    }

    while ((entry = readdir(dir)) != NULL) {
        ret.push_back(entry->d_name);
    }

    closedir(dir);
    return ret;
}

bool check_list(vector<string>& text_list, int ANCHOR_BOX_COUNT) {

    if (text_list.empty()) {
        return false;
    }

    ifstream read;

    for (string textFile : text_list) {
        
        int line_count = 0;   //Variable to compare value with ANCHOR_BOX_COUNT

        string _path = file_path + "\\" + textFile;
        read.open(_path.c_str());
        
        char line[100];

        if (!read.is_open()) {
            //Error handling
            errorFileList.push_back(textFile);
        }
        else {
            while(read.getline(line, sizeof(line))) {
                line_count++;
            }
            
            if (ANCHOR_BOX_COUNT == 0) {
                if (line_count == ANCHOR_BOX_COUNT) {
                    //Error handling
                    errorFileList.push_back(textFile);
                }
            }
            else {
                if (line_count == 0 || (line_count != ANCHOR_BOX_COUNT)) {
                    //Error handling
                    errorFileList.push_back(textFile);
                }
            }

            read.close();
        }
    }

    return true;
}

bool delete_number(vector<string>& text_list, int number) {

    if (text_list.empty()) {
        return false;
    }

    for (string textFile : text_list) {

        string _path = file_path + "\\" + textFile;

        FILE *fd;
        char line[LINE_SIZE];
        char temp[FILE_SiZE];

        fd = fopen(_path.c_str(), "rb");
        fflush(stdin);

        temp[0] = 0;
        while (!feof(fd)) {
            memset(line, 0x0, sizeof(line));
            fgets(line, LINE_SIZE, fd);
            if ((line[0] - '0') != number) {
                strcat(temp, line);
            }
        }
        fclose(fd);

        fd = fopen(_path.c_str(), "wb");
        fprintf(fd, "%s", temp);
        fclose(fd);   

    }

    return true;
}

bool update_number(int& anchor_box_number, int val) {
    if (val < 0) return false;
    else {
        anchor_box_number = val;
        return true;
    }
}

bool print_anchorbox_number(int anchorbox_number) {
    cout << "The pivot anchor box number is " << anchorbox_number << endl;
    return true;
}