__attribute__((noreturn)) void enterOs(void);
void* initThreadStack(void* stackPtr, void* entryAddr);
void returnToThread(void** pStackPtr, void* newStackPtr);
void _sleep(uint32_t duration);
