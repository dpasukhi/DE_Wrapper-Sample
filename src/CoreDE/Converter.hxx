#pragma once

#include <string>
#include <map>

#include <Standard_Macro.hxx>

namespace Converter
{
  //! Converts CAD file with loaded 
  Standard_EXPORT bool Convert(const std::string& theFrom,
                               const std::string& theTo,
                               const bool theToTess = false);

  //! Loads configuration file
  Standard_EXPORT bool LoadConfiguration(const std::string& theConfigPath);

  //! Saves configuration file
  Standard_EXPORT bool SaveConfiguration(const std::string& theConfigPath);

  //! Adds component, should be path or lib name.
  //! Lib name should be available to detect by load functionality.
  //! Means directory should be defined by PATH or LD_LIBRARY_PATH
  Standard_EXPORT bool LoadComponent(std::string theComp);

  //! Returns components list
  Standard_EXPORT const std::map<std::string, bool>& Components();
}
