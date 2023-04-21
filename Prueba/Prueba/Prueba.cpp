#include <iostream>
#include <filesystem>
#include <json/json.h>
#include <fstream>
using namespace std;
namespace fs = std::filesystem;

Json::Value folder(string path) {
    Json::Value aux;
    for (const auto& file : fs::directory_iterator(path)) {
        if (fs::is_directory(file.path().string())) {
            //cout << "Carpeta\n";
            Json::Value res = folder(file.path().string());
            aux.append(res);
        }
        else {
            //cout << "File\n";
            Json::Value aux2;
            aux2["name"] = file.path().filename().string();
            aux2["size"] = fs::file_size(file);
            aux.append(aux2);
        }
    }

    Json::Value folder;
    folder[path] = aux;
    return folder;
}

int main(int argc, char* argv[]) {

    ofstream fout("dir.json");
    string path = "D:/Documents/testFolder";
    Json::Value json;
    json["files"] = folder(path);
    //cout << json << "\n";
    fout << json;

}