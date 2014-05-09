#ifndef __FunctionGuard_H__
#define __FunctionGuard_H__

#include "CommonDefs.h"
#include "Single.h"
#include <string>
#include <vector>

BEGINNAMESPACE

#ifndef _DEBUG
#define FUNCTION_GUARD
#endif

#ifdef FUNCTION_GUARD

#define ENTER_FUNCTION_FOXNET try {
#define LEAVE_FUNCTION_FOXNET } catch(...) { SGCommon::CDebugInfoHelper::getSingleton().OnCatch(); }
#define LEAVE_FUNCTION_RETURN_0 } catch(...) { SGCommon::CDebugInfoHelper::getSingleton().OnCatch(); return 0;}
#define LEAVE_FUNCTION_RETURN_FALSE } catch(...) { SGCommon::CDebugInfoHelper::getSingleton().OnCatch(); return false;}
#define LEAVE_FUNCTION_RETURN_NULL } catch(...) { SGCommon::CDebugInfoHelper::getSingleton().OnCatch(); return NULL;}
#else

#define ENTER_FUNCTION_FOXNET {
#define LEAVE_FUNCTION_FOXNET }
#define LEAVE_FUNCTION_RETURN_0 }
#define LEAVE_FUNCTION_RETURN_FALSE }
#define LEAVE_FUNCTION_RETURN_NULL }
#endif

#pragma warning(push)
#pragma warning(disable: 4251)

class COMMON_API CDebugInfoHelper : public Single<CDebugInfoHelper>
{
public:
    CDebugInfoHelper(const char* strPath, const char* strProcessName, unsigned int nVer);
    virtual ~CDebugInfoHelper();

public:
    void OnCatch();
    void Output(const char * pszFormat, ...);
    void BugCount();

protected:
    virtual void OnOutputSelfInfo();

private:
    std::string m_strPath;
    std::string m_strProcessName;
    unsigned int m_nVer;
    FILE* m_pFile;

    typedef std::vector<unsigned int> VecStackAddr;
    std::vector< std::pair<VecStackAddr, std::pair<int, int> > > m_vecExistStackAddr;

};

#pragma warning(pop)

ENDNAMESPACE

#endif