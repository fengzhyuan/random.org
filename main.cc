#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include "RdoIntegers.hh"
#include "bitmap_image.hpp"

using namespace std;

vector<long> generateRND(int len, pair<long int, long int> range) {
    RdoIntegers rdo;
    rdo.setNum(10);
    rdo.setBase("10");
    rdo.setRange(range.first, range.second);
    rdo.setInMemory(true);

    if (rdo.downloadData()) {
        cout << "failed download data\n";
        return vector<long>{}; 
    }
    vector<long int> data = rdo.cache();
    return data;
}

vector<long int> fakeRND(int len, pair<long int, long int> range) {
    vector<long int> data;
    data.reserve(len);
    srand(std::time(0));
    while (data.size() < len) {
        data.push_back(rand() % (range.second + 1 - range.first) + range.first);
    }
    return data;
}

void generateBMP(string name) {
    int width = 128, height = 128, len = width * height * 3;
    vector<long int> raw_data = fakeRND(len, {0, 255}); // generateRND(len, {0, 255});
    if (raw_data.empty() || raw_data.size() != len) {
        cout << "len:" << raw_data.size() << ",expected:" << len << endl;
        cout << "failed fetching random number\n";
        return;
    }
    bitmap_image image(width, height);
    image.clear();

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int indx = i * width + j;
            image.set_pixel(i, j, raw_data[indx], raw_data[indx+1], raw_data[indx+2]);
        }
    }

    image.save_image(name);
}
int main(int argc, char **argv) {
    generateBMP("out.bmp");


    return 0;
}
