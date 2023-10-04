#include "Utilities/FileReader.hpp"

#include <fstream>
#include <string>

#include "Debug/Debug.hpp"

namespace Tolik
{
void FileReader::ReadTxtFile(const std::string &path, std::string &output)
{
  std::ifstream file(path);
  file.seekg(0, std::ios::end);
  output.reserve(static_cast<int>(file.tellg()) + output.length());
  file.seekg(0, std::ios::beg);
  output.insert(output.end(), (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}
};