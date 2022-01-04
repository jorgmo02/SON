#ifndef MACROS
#define MACROS

#include <string>

char getinput();
bool keyboardhit();

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
static const std::string slash = "\\";
#elif defined(unix) || defined(__unix) || defined(__unix__)
static const std::string slash = "/";
#endif

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_ESC 27

static const std::string assetsPath = "." + slash + "Assets" + slash;

#define PATH(filename) (assetsPath + filename).c_str()

enum FMOD_RESULT;
// para salidas de error
void ERRCHECK(FMOD_RESULT result);

#endif // !MACROS