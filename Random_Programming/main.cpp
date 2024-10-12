#include "libxl.h"    // LibXL ��� ���� ����
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

// UTF-8�� UTF-16���� ��ȯ�ϴ� �Լ�
std::wstring UTF8ToUTF16(const std::string& utf8)
{
    int          len = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
    std::wstring utf16(len, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &utf16[0], len);
    return utf16;
}

// ���� ���Ͽ��� �����͸� �д� �Լ�
std::vector<std::vector<std::wstring>> readXLSXFile(const std::wstring& filename)
{
    std::vector<std::vector<std::wstring>> data;
    Book*                                  book = xlCreateXMLBook();    // XLSX ������ ���� LibXL ��ü ����

    if (book->load(filename.c_str())) {
        std::wcout << L"���� ���� ���� ����: " << filename << std::endl;
        Sheet* sheet = book->getSheet(0);    // ù ��° ��Ʈ ��������

        if (sheet) {
            int totalRows = sheet->lastRow();    // ���� ��Ʈ�� �� �� �� ��������
            int totalCols = sheet->lastCol();    // ���� ��Ʈ�� �� �� �� ��������
            std::wcout << L"�� �� ��: " << totalRows << L", �� �� ��: " << totalCols << std::endl;

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
                // �� ���� �ƴ� ��� �����͸� �߰�
                if (!rowData.empty() && std::any_of(rowData.begin(), rowData.end(), [](const std::wstring& s) { return !s.empty(); })) {
                    data.push_back(rowData);
                }
            }
        }
    }
    else {
        std::wcout << L"���� ���� ���� ����: " << filename << std::endl;
        return {};
    }

    book->release();    // LibXL ��ü ����
    return data;
}

// XLSX ������ �ۼ��ϴ� �Լ� (4�� �������� �׷�ȭ, ���� �ο��� ������ �׷쿡 ����)
void writeXLSXFileRandom(const std::vector<std::vector<std::wstring>>& data, const std::wstring& filename)
{
    Book* book = xlCreateXMLBook();    // XLSX ���� �ۼ��� ���� LibXL ��ü ����

    if (!book) {
        std::wcerr << L"LibXL ��ü ���� ����" << std::endl;
        return;
    }

    Sheet* sheet = book->addSheet(L"Teams");
    if (!sheet) {
        std::wcerr << L"Sheet ���� ����" << std::endl;
        return;
    }

    // ù ��° ���� ����� �����ϰ� �� ������ �����͸� �����ϰ� ����
    std::vector<std::vector<std::wstring>> students(data.begin() + 1, data.end());    // ����� ������ �л� ������
    std::random_device                     rd;
    std::mt19937                           g(rd());
    std::shuffle(students.begin(), students.end(), g);

    // �ߺ� ����
    std::vector<std::vector<std::wstring>> uniqueStudents;
    std::set<std::wstring>                 studentIDs;    // ID�� �������� �ߺ� Ȯ��
    for (const auto& student : students) {
        if (student.size() > 3 && !student[3].empty() && studentIDs.find(student[3]) == studentIDs.end()) {    // ID�� �ߺ����� ������ �߰�
            uniqueStudents.push_back(student);
            studentIDs.insert(student[3]);
        }
    }

    // ��� �߰�
    for (size_t col = 0; col < data[0].size(); ++col) {
        sheet->writeStr(0, col, data[0][col].c_str());
    }

    int    row       = 1;    // �����ʹ� 1����� ���� (0���� ���)
    int    groupNum  = 1;
    size_t groupSize = 4;

    // ��� �л����� 4�� �׷����� ������ ����
    for (size_t i = 0; i < uniqueStudents.size(); i += groupSize) {
        // �׷� ��ȣ ����
        sheet->writeStr(row, 0, L"�� ��ȣ");
        sheet->writeNum(row, 1, groupNum);
        row++;

        // ���� �׷쿡 �л� �߰�
        size_t currentGroupSize = (std::min)(groupSize, uniqueStudents.size() - i);    // ��ȣ�� ��� ���
        for (size_t j = 0; j < currentGroupSize; ++j) {
            for (size_t col = 0; col < uniqueStudents[i + j].size(); ++col) {
                sheet->writeStr(row, col, uniqueStudents[i + j][col].c_str());
            }
            row++;
        }

        groupNum++;
        row++;    // �׷� ���̿� �� �� ���� �߰�
    }

    // ���� ����
    if (book->save(filename.c_str())) {
        std::wcout << L"���� ���� ���� ����: " << filename << std::endl;
    }
    else {
        std::wcerr << L"���� ���� ���� ����" << std::endl;
    }

    book->release();    // LibXL ��ü ����
}


int main()
{
    // �ֿܼ��� UTF-16 ���ڵ��� ����ϵ��� ����
    _setmode(_fileno(stdout), _O_U16TEXT);
    SetConsoleOutputCP(CP_UTF8);

    std::wstring inputFilename  = L"C:\\Users\\user\\Desktop\\temp\\LSP_2024_2.xlsx";
    std::wstring outputFilename = L"C:\\Users\\user\\Desktop\\temp\\test_output.xlsx";

    try {
        std::wcout << L"���α׷� ����..." << std::endl;

        // ���� ���Ͽ��� �����͸� �о����
        std::vector<std::vector<std::wstring>> data = readXLSXFile(inputFilename);
        if (data.empty()) {
            throw std::runtime_error("���Ͽ��� �����͸� ���� �� �����ϴ�.");
        }

        std::wcout << L"�� " << data.size() - 1 << L"���� �л��� �о����ϴ�." << std::endl;

        // XLSX ���Ϸ� ���� (4�� �������� �׷�ȭ, ���� �ο��� ������ �׷쿡 ����)
        writeXLSXFileRandom(data, outputFilename);

        std::wcout << L"���α׷��� �Ϸ�Ǿ����ϴ�. ����� " << outputFilename << L"�� ����Ǿ����ϴ�." << std::endl;
    }
    catch (const std::exception& e) {
        std::wcerr << L"������ �߻��߽��ϴ�: " << UTF8ToUTF16(e.what()) << std::endl;
        return 1;
    }

    return 0;
}
