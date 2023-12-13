#include "Converter.hxx"

#include <DE_ConfigurationContext.hxx>
#include <DE_Wrapper.hxx>
#include <Message.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <OSD_SharedLibrary.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <TDocStd_Document.hxx>

using namespace Converter;

namespace
{
  static std::map<std::string, bool>& THE_COMPONENTS()
  {
    static std::map<std::string, bool> aComponentMap;
    return aComponentMap;
  }
}

//================================================================
// Function : Convert
// Purpose  :
//================================================================
bool Converter::Convert(const std::string& theFrom,
                        const std::string& theTo,
                        const bool theToTess)
{
  Handle(TDocStd_Document) aDoc = new TDocStd_Document("BinXCAF");
  auto aWrapper = DE_Wrapper::GlobalWrapper()->Copy();
  Handle(DE_ConfigurationContext) aContext = new DE_ConfigurationContext;
  aContext->LoadStr(theFrom.c_str());
  aWrapper->Load(aContext, true);
  if (!aWrapper->Read(theFrom.c_str(), aDoc))
  {
    Message::SendFail() << "Could not read: [" << theFrom << "] ";
    return false;
  }
  if (theToTess)
  {
    Handle(XCAFDoc_ShapeTool) aShTool = XCAFDoc_DocumentTool::ShapeTool(aDoc->Main());
    auto aShapes = aShTool->GetOneShape();
    BRepMesh_IncrementalMesh aMesher(aShapes, 0.5);
    aMesher.Perform();
  }
  if (!aWrapper->Write(theTo.c_str(), aDoc))
  {
    Message::SendFail() << "Could not write: [" << theTo << "] ";
    return false;
  }
  return true;
}

//================================================================
// Function : LoadConfiguration
// Purpose  :
//================================================================
bool Converter::LoadConfiguration(const std::string& theConfigPath)
{
  return DE_Wrapper::GlobalWrapper()->Load(theConfigPath.c_str());
}

//================================================================
// Function : SaveConfiguration
// Purpose  :
//================================================================
bool Converter::SaveConfiguration(const std::string& theConfigPath)
{
  return DE_Wrapper::GlobalWrapper()->Save(TCollection_AsciiString(theConfigPath.c_str()));
}

//================================================================
// Function : LoadComponent
// Purpose  :
//================================================================
bool Converter::LoadComponent(std::string theComp)
{
  Standard_Mutex::Sentry aLocker(DE_Wrapper::GlobalWrapper()->GlobalLoadMutex());
  if (THE_COMPONENTS().count(theComp) > 0)
  {
    return true;
  }
  bool aRes = true;
#ifdef _WIN32
    theComp += ".dll";
#elif defined(__APPLE__)
    theComp += ".dylib";
#else
    theComp += ".so";
#endif  
  OSD_SharedLibrary aSharedLibrary(theComp.c_str());
  if (!aSharedLibrary.DlOpen(OSD_RTLD_LAZY))
  {
    Message::SendFail() << "Could not open: [" << theComp << "] " <<
      " reason: " << aSharedLibrary.DlError();
    THE_COMPONENTS().emplace(theComp, true);
    aRes = false;
  }
  THE_COMPONENTS().emplace(theComp, aRes);
  return aRes;
}

//================================================================
// Function : Components
// Purpose  :
//================================================================
const std::map<std::string, bool>& Converter::Components()
{
  return THE_COMPONENTS();
}
