#ifndef AI
#define AI

typedef struct aiKnowledge Knowledge;
struct aiKnowledge{
	char * key;
    char * output;
	int count;
	double learningRate;
    double sysRate;
    double userRate;
	//TreeNode * parent; Optional but useful
    //Tree* parentTree;  Optional but gets you access to function pointers.
};


Knowledge * createKnowledge(char*key, char*output);

void setRate(Knowledge *toSet, double userRate);

int compareKnowledge(const void *first, const void*second);

void setLearning(Knowledge *toSet, double learningRate);

void setSystem(Knowledge*toSet, double newSysRate);

void setCount(Knowledge *toSet, int num);

void printKnowledge(void *a);

void printOutput(void *a);

void deleteKnowledge(void *a);

char*getOuput(Knowledge *toGet);
double getRating(Knowledge *toGet);
double getSystem(Knowledge *toGet);
double getLearningRate(Knowledge *toGet);
int getCount(Knowledge *toGet);

#endif
