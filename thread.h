struct Thread {
	void* stackPtr;
};

struct Thread startThread(void* entryAddr);
