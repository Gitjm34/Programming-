#include "libxl.h"    // LibXL 헤더 파일 포함
#include <Windows.h>
#include <algorithm>    // std::shuffle
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <vector>

using namespace libxl;

// UTF-8을 UTF-16으로 변환하는 함수
std::wstring UTF8ToUTF16(const std::string& utf8)
{
    int          len = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
    std::wstring utf16(len, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &utf16[0], len);
    return utf16;
}

// 엑셀 파일에서 데이터를 읽는 함수
std::vector<std::vector<std::wstring>> readXLSXFile(const std::wstring& filename)
{
    std::vector<std::vector<std::wstring>> data;
    Book*                                  book = xlCreateXMLBook();    // XLSX 파일을 위한 LibXL 객체 생성

    if (book->load(filename.c_str())) {
        std::wcout << L"엑셀 파일 열기 성공: " << filename << std::endl;
        Sheet* sheet = book->getSheet(0);    // 첫 번째 시트 가져오기

        if (sheet) {
            int totalRows = sheet->lastRow();    // 엑셀 시트의 총 행 수 가져오기
            int totalCols = sheet->lastCol();    // 엑셀 시트의 총 열 수 가져오기
            std::wcout << L"총 행 수: " << totalRows << L", 총 열 수: " << totalCols << std::endl;

            for (int row = 0; row < totalRows; ++row) {
                std::vector<std::wstring> rowData;
                for (int col = 0; col < totalCols; ++col) {
                    CellType cellType = sheet->cellType(row, col);
                    switch (cellType) {
                        case CELLTYPE_STRING: {
                            const wchar_t* cellData = sheet->readStr(row, col);
                            rowData.push_back(cellData ? cellData : L"");
                            break;
                        }
                        case CELLTYPE_NUMBER: {
                            double cellData = sheet->readNum(row, col);
                            rowData.push_back(std::to_wstring(cellData));
                            break;
                        }
                        case CELLTYPE_BLANK:
                        default:
                            rowData.push_back(L"");
                            break;
                    }
                }
                // 빈 행이 아닌 경우 데이터를 추가
                if (!rowData.empty() && std::any_of(rowData.begin(), rowData.end(), [](const std::wstring& s) { return !s.empty(); })) {
                    data.push_back(rowData);
                }
            }
        }
    }
    else {
        std::wcout << L"엑셀 파일 열기 실패: " << filename << std::endl;
        return {};
    }

    book->release();    // LibXL 객체 해제
    return data;
}

// XLSX 파일을 작성하는 함수 (4명씩 랜덤으로 그룹화, 남은 인원은 마지막 그룹에 포함)
void writeXLSXFileRandom(const std::vector<std::vector<std::wstring>>& data, const std::wstring& filename)
{
    Book* book = xlCreateXMLBook();    // XLSX 파일 작성을 위한 LibXL 객체 생성

    if (!book) {
        std::wcerr << L"LibXL 객체 생성 실패" << std::endl;
        return;
    }

    Sheet* sheet = book->addSheet(L"Teams");
    if (!sheet) {
        std::wcerr << L"Sheet 생성 실패" << std::endl;
        return;
    }

    // 첫 번째 행은 헤더로 간주하고 그 이후의 데이터를 랜덤하게 섞음
    std::vector<std::vector<std::wstring>> students(data.begin() + 1, data.end());    // 헤더를 제외한 학생 데이터
    std::random_device                     rd;
    std::mt19937                           g(rd());
    std::shuffle(students.begin(), students.end(), g);

    // 중복 제거
    std::vector<std::vector<std::wstring>> uniqueStudents;
    std::set<std::wstring>                 studentIDs;    // ID를 기준으로 중복 확인
    for (const auto& student : students) {
        if (student.size() > 3 && !student[3].empty() && studentIDs.find(student[3]) == studentIDs.end()) {    // ID가 중복되지 않으면 추가
            uniqueStudents.push_back(student);
            studentIDs.insert(student[3]);
        }
    }

    // 헤더 추가
    for (size_t col = 0; col < data[0].size(); ++col) {
        sheet->writeStr(0, col, data[0][col].c_str());
    }

    int    row       = 1;    // 데이터는 1행부터 시작 (0행은 헤더)
    int    groupNum  = 1;
    size_t groupSize = 4;

    // 모든 학생들을 4명씩 그룹으로 나눠서 저장
    for (size_t i = 0; i < uniqueStudents.size(); i += groupSize) {
        // 그룹 번호 쓰기
        sheet->writeStr(row, 0, L"조 번호");
        sheet->writeNum(row, 1, groupNum);
        row++;

        // 현재 그룹에 학생 추가
        size_t currentGroupSize = (std::min)(groupSize, uniqueStudents.size() - i);    // 괄호로 묶어서 사용
        for (size_t j = 0; j < currentGroupSize; ++j) {
            for (size_t col = 0; col < uniqueStudents[i + j].size(); ++col) {
                sheet->writeStr(row, col, uniqueStudents[i + j][col].c_str());
            }
            row++;
        }

        groupNum++;
        row++;    // 그룹 사이에 한 줄 공백 추가
    }

    // 파일 저장
    if (book->save(filename.c_str())) {
        std::wcout << L"엑셀 파일 저장 성공: " << filename << std::endl;
    }
    else {
        std::wcerr << L"엑셀 파일 저장 실패" << std::endl;
    }

    book->release();    // LibXL 객체 해제
}


int main()
{
    // 콘솔에서 UTF-16 인코딩을 사용하도록 설정
    _setmode(_fileno(stdout), _O_U16TEXT);
    SetConsoleOutputCP(CP_UTF8);

    std::wstring inputFilename  = L"C:\\Users\\user\\Desktop\\temp\\LSP_2024_2.xlsx";
    std::wstring outputFilename = L"C:\\Users\\user\\Desktop\\temp\\test_output.xlsx";

    try {
        std::wcout << L"프로그램 시작..." << std::endl;

        // 엑셀 파일에서 데이터를 읽어들임
        std::vector<std::vector<std::wstring>> data = readXLSXFile(inputFilename);
        if (data.empty()) {
            throw std::runtime_error("파일에서 데이터를 읽을 수 없습니다.");
        }

        std::wcout << L"총 " << data.size() - 1 << L"명의 학생을 읽었습니다." << std::endl;

        // XLSX 파일로 저장 (4명씩 랜덤으로 그룹화, 남은 인원은 마지막 그룹에 포함)
        writeXLSXFileRandom(data, outputFilename);

        std::wcout << L"프로그램이 완료되었습니다. 결과는 " << outputFilename << L"에 저장되었습니다." << std::endl;
    }
    catch (const std::exception& e) {
        std::wcerr << L"오류가 발생했습니다: " << UTF8ToUTF16(e.what()) << std::endl;
        return 1;
    }

    return 0;
}
