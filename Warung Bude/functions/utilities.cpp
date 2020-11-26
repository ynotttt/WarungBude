void outputLocalTime() {
    time_t lctime;
    time(&lctime);
    printf("%s", ctime(&lctime));
}

void enterPrompt() {
    printf("Press enter to continue..."); getchar();
}

void detectOS() {
    #ifdef _WIN32
        #ifdef _WIN64
            printf("System: Windows 64-bit\n");
        #else
            printf("System: Windows 32-bit\n");
        #endif
    #elif __APPLE__ || __MACH__
        printf("System: MacOSX\n");
    #elif __linux__
        printf("System: Linux\n");
    #elif __ANDROID__
        printf("System: Android\n");
    #elif __APPLE__
        printf("System: Apple\n");
    #elif __FreeBSD__
        printf("System: FreeBSD\n");
    #elif __unix || __unix__
        printf("System: Unix");
    #else
        printf("System: Other\n");
    #endif
}

void delay() {
    for (int i = 0; i < 2e8; i++) ;
}

void cls() {
    for (int i = 0; i < 1e2; i++) puts("");
}

int strctr(char *str) {
    int ctr = 0;
    for (int i = 0; str[i] != '\0'; i++) ctr++;
    return ctr;
}