#include "Clipboard.h"

void ClipboardIt(std::string answer) {

   const char* output = answer.c_str();
   const size_t len = strlen(output) + 1;
   HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
   memcpy(GlobalLock(hMem), output, len);
   GlobalUnlock(hMem);
   OpenClipboard(0);
   EmptyClipboard();
   SetClipboardData(CF_TEXT, hMem);
   CloseClipboard();
}