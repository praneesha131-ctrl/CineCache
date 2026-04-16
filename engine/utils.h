#ifndef UTILS_H
#define UTILS_H

#include <string>

// Color definitions
#define RST "\033[0m"
#define BOLD "\033[1m"
#define DIM "\033[2m"
#define RED "\033[31m"
#define GRN "\033[32m"
#define YLW "\033[33m"
#define BLU "\033[34m"
#define MAG "\033[35m"
#define CYN "\033[36m"
#define WHT "\033[37m"
#define BBLK "\033[30m"
#define BGGRN "\033[42m"
#define BGBLU "\033[44m"
#define BGRED "\033[41m"

// Utility functions
void pauseMs(int ms);
void printLine(const std::string& ch = "-", int length = 60);
void printStep(int stepNumber, const std::string& message, const std::string& color = CYN);
void printSuccess(const std::string& message);
void printError(const std::string& message);
void printInfo(const std::string& message);

#endif // UTILS_H
