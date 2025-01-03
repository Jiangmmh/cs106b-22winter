#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};


int main () {
    const char* imgPath = "test.jpg";

    ifstream imgFile(imgPath, ios::binary);
    if (!imgFile.is_open()) {
        cout << "Error: Could not open file " << imgPath << endl;
        return 1;
    }

    // 获取文件大小：1. 将文件定位到末尾 2. 获取文件大小 3. 将文件指针定位到文件开头
    imgFile.seekg(0, ios::end);
    streampos fileSize = imgFile.tellg();
    imgFile.seekg(0, ios::beg);

    // JPeg文件头部大小为2字节
    const int headerSize = 2;
    const int channels = 3;

    if (fileSize < headerSize) {
        cout << "Error: File " << imgPath << " is too small" << endl;
        return 1;
    }

    // 跳过JPEG头部
    imgFile.ignore(headerSize);

    // 获取图像的字节数和像素个数
    const int PixelDataSize = static_cast<int>(fileSize - imgFile.tellg());
    const int pixelsCount = PixelDataSize / channels;

    // 用vector保存像素
    vector<Pixel> pixels(pixelsCount);
    imgFile.read(reinterpret_cast<char*>(pixels.data()), PixelDataSize);
    imgFile.close();

    // 保存每个通道的像素值到文件
    for (int channel = 0; channel < channels; channel++) {
        string outputFileName = "channel_" + to_string(channel + 1) + ".txt";
        ofstream outputFile(outputFileName);
        if (!outputFile.is_open()) {
            cout << "Error: Could not open file " << outputFileName << endl;
            return 1;
        }

        for (const auto& pixel : pixels) {
            uint8_t value;
            switch (channel)
            {
            case 0:
                value = pixel.red;
                break;
            case 1:
                value = pixel.green;
                break;
            case 2:
                value = pixel.blue;
                break;
            default:
                cout << "Error: Invalid channel" << endl;
                break;
            }
            outputFile << static_cast<int>(value) << " ";
        }

        outputFile.close();
        cout << "Channel " << channel + 1 << " saved to " << outputFileName << endl;
    }
}