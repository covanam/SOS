void enableSysTick(void);
void* initThreadStack(void* stackPtr, void* entryAddr);
void returnToThread(void** pStackPtr, void* newStackPtr);
void idle(void);