#include <QtGui>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>
 
#if defined QMPRIS
#define QMPRIS_COMMON_DLLSPEC  Q_DECL_EXPORT
#else
#define QMPRIS_COMMON_DLLSPEC Q_DECL_IMPORT
#endif

class QMPRIS_COMMON_DLLSPEC Widget : public QWidget
{
 Q_OBJECT
public:
 Widget();
}; 


extern "C" QMPRIS_COMMON_DLLSPEC void helloWorldByLib();
extern "C" QMPRIS_COMMON_DLLSPEC QStringList discoveredMprisPlayer();
extern "C" QMPRIS_COMMON_DLLSPEC void playPause(char * destination);
extern "C" QMPRIS_COMMON_DLLSPEC void simpleOperation(char* destination, char* op);
