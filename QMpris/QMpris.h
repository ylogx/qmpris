#include <QtGui>
 
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
