#ifndef TOLIK_FILE_READER_HPP
#define TOLIK_FILE_READER_HPP

#include <string>

#include "Tolik/Setup.hpp"

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