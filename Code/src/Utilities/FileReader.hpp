#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <string>

namespace Tolik
{
class Debug;

class FileReader
{
public:
  static void ReadTxtFile(const std::string &path, std::string &output);
};
}

#endif