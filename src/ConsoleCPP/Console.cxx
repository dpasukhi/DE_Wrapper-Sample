#pragma once

#include "../CoreDE/Converter.hxx"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

// Function to trim leading and trailing special characters and whitespace from a string
std::string trim(const std::string& str)
{
  // Remove leading whitespace and special characters
  auto start = std::find_if_not(str.begin(), str.end(), [](unsigned char c)
    {
    return std::isspace(c) || std::ispunct(c);
    });

  // Remove trailing whitespace and special characters
  auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char c)
    {
    return std::isspace(c) || std::ispunct(c);
    }).base();

    // Return the substring without leading and trailing whitespace
    return (start < end) ? std::string(start, end) : "";
}

std::string str_tolower(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), 
                   [](unsigned char c){ return std::tolower(c); } // correct
                  );
    return str;
}

void components_load(std::string theLibPath)
{
  if (theLibPath.empty())
  {
    theLibPath = "./LIBS";
  }
  std::ifstream file(theLibPath);
  if (!file.is_open())
  {
    std::cerr << "Error: Could not open the file '" << theLibPath << "'" << std::endl;
    std::exit(1);
  }
  std::string line;
  while (std::getline(file, line))
  {
    Converter::LoadComponent(trim(line));
  }
  file.close();
}

void resource_load(std::string theResPath)
{
  if (theResPath.empty())
  {
    theResPath = "./CONF";
  }
  Converter::LoadConfiguration(theResPath);
}

int main(int argc, char* argv[])
{
  if (argc < 2 || argc > 10)
  {
    std::cerr << "Error syntax" << std::endl;
    std::cout << "Available parameters: \n"
    << " [-from <path>] [-to <path>] [-lib <path>] [-config <path>] [--tess] [--dump] \n"
    << "\t -from <path>   - CAD file to convert from\n"
    << "\t -to <path>     - CAD file to convert into\n"
    << "\t -lib <path>    - path to file with list of libs, see ./data/LIB\n"
    << "\t -config <path> - path to resource file, see ./data/CONF\n"
    << "\t -dump <path>   - dump resource file of loaded libs into file\n"
    << "\t --tess         - activate tesselation for the input model before export\n";
  }
  std::string fromPath;
  std::string toPath;
  std::string libListPath;
  std::string configPath;
  std::string dumpPath;
  bool toTess = false;

  // Loop through command-line arguments
  for (int i = 1; i < argc; ++i)
  {
    std::string arg(str_tolower(argv[i]));

    if (arg == "-from" && i + 1 < argc)
    {
      fromPath = argv[i + 1];
      ++i;  // Skip the next argument (the path)
    }
    else if (arg == "-to" && i + 1 < argc)
    {
      toPath = argv[i + 1];
      ++i;  // Skip the next argument (the path)
    }
    else if (arg == "-lib" && i + 1 < argc)
    {
      libListPath = argv[i + 1];
      ++i;  // Skip the next argument (the path)
    }
    else if (arg == "-config" && i + 1 < argc)
    {
      configPath = argv[i + 1];
      ++i;  // Skip the next argument (the path)
    }
    else if (arg == "-dump" && i + 1 < argc)
    {
      dumpPath = argv[i + 1];
      ++i;  // Skip the next argument (the path)
    }
    else if (arg == "--tess")
    {
      toTess = true;
    }
    // Handle other arguments as needed
    // Add more conditions as necessary

    // You can add additional conditions or handle other parameters here.
  }
  components_load(libListPath);
  resource_load(configPath);
  if (!dumpPath.empty())
  {
    Converter::SaveConfiguration(dumpPath);
  }
  // Process the extracted paths
  if (fromPath.empty() || toPath.empty())
  {
    if (dumpPath.empty())
    {
      std::cerr << "Error: Invalid command-line arguments." << std::endl;
      return 1;
    }
    return 0;
  }
  if (!Converter::Convert(fromPath, toPath, toTess))
  {
    return 1;
  }
  return 0;
}
