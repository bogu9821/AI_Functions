// Disable macro redefinition warning
#pragma warning(disable: 4005)


#include <Union/Hook.h>
#include <ZenGin/zGothicAPI.h>

#ifdef __G1
#define GOTHIC_NAMESPACE Gothic_I_Classic
#define ENGINE Engine_G1
HOOKSPACE(Gothic_I_Classic, GetGameVersion() == ENGINE);
#include "oCMsgAI.hpp"
#include "Plugin_G1.hpp"
#include "Plugin.hpp"
#include "zCParser.hpp"
#endif

#ifdef __G1A
#define GOTHIC_NAMESPACE Gothic_I_Addon
#define ENGINE Engine_G1A
HOOKSPACE(Gothic_I_Addon, GetGameVersion() == ENGINE);
#include "Plugin.hpp"
#include "Plugin_G1A.hpp"
#endif

#ifdef __G2
#define GOTHIC_NAMESPACE Gothic_II_Classic
#define ENGINE Engine_G2
HOOKSPACE(Gothic_II_Classic, GetGameVersion() == ENGINE);
#include "Plugin.hpp"
#include "Plugin_G2.hpp"
#endif

#ifdef __G2A
#define GOTHIC_NAMESPACE Gothic_II_Addon
#define ENGINE Engine_G2A
HOOKSPACE(Gothic_II_Addon, GetGameVersion() == ENGINE);
#include "Plugin.hpp"
#include "Plugin_G2A.hpp"
#endif

HOOKSPACE(Global, true);
