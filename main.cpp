#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <locale>

using pair = std::pair<std::string, size_t>;

bool ch_comp(wchar_t ch) {
    return std::iswspace(ch);
}

bool comp(wchar_t ch) {
    return std::iswpunct(ch) || ch == L'\n';
}

std::vector<pair> sort_map(std::map<std::string, size_t> &map) {
    std::vector<pair> vec;
    std::copy(map.begin(),
              map.end(),
              std::back_inserter<std::vector<pair>>(vec));

    std::sort(vec.begin(), vec.end(),
              [](const pair &l, const pair &r) {
                  if (l.second != r.second) {
                      return l.second > r.second;
                  }
                  return l.first < r.first;
              });
    return vec;
}

/// МАССИВ БАЙТИКОВ
std::vector<uint8_t> read_file(const std::string &path) {
    std::vector<uint8_t> result;
    std::ifstream f(path, std::ios::binary);
    std::streamsize size = 0;
    f.seekg(0, std::ios::end);
    /// 1277345
    size = f.tellg();
    f.seekg(0, std::ios::beg);
    result.resize(size);
    f.read(reinterpret_cast<char *>(result.data()), size);
    return result;
}

void clean_str(std::string &str) {
    str.erase(std::remove_if(str.begin(), str.end(), comp),
              str.end());
    std::replace_if(str.begin(), str.end(), ch_comp, L'_');
    if (str.size() < 3) {
        throw std::logic_error("File dont has trigrammas;(");
    }
}

std::map<std::string, size_t> map(std::string &file) {
    std::map<std::string, size_t> top_ten;
    std::string trigrama;
    for (int i = 0; i < file.length() - 2; i++) {
        trigrama = file.substr(i, 3);
        if (top_ten.find(trigrama) == top_ten.end()) {
            top_ten[trigrama] = 1;
        } else {
            top_ten[trigrama]++;
        }
    }
    return top_ten;
}


int main(int argc, char **argv) {
    if (argc > 2) {
        throw std::logic_error("Too many args");
    } else {
        auto file_bytes = read_file(argv[1]);

        int q = 5;
    }

//    clean_str(file_text);
//    std::map<std::string, size_t> top_ten = map(file_text);
//    std::vector<pair> vec = sort_map(top_ten);
//    int count = 0;
//    for (auto const &pair: vec) {
//        if (count == 10) {
//            break;
//        }
////        std::wcout << count + 1 << L") " << pair.first << ": " << pair.second << std::endl;
//        ++count;
//    }
//
//    return 0;
}