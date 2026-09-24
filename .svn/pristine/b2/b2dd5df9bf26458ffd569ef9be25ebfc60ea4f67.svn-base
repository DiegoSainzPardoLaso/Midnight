#include "MessageUtils.h"

void Message::Info(const char* str)
{
	std::cout << OUT_GREEN << "INFO   " << OUT_RESET << "- " << str << '\n';
}

void Message::Info(const char* str, const char* fileName)
{
	std::cout << OUT_GREEN << "INFO   " << OUT_RESET << "- " << str << " - " << OUT_GREEN << "{ " << fileName << " } " << OUT_RESET << "\n";
}

void Message::Error(const char* str)
{
	std::cout << OUT_RED << "ERROR  " << OUT_RESET << "- " << str << '\n';
}

void Message::Error(const char* str, const char* fileName)
{
	std::cout << OUT_RED << "ERROR  " << OUT_RESET << "- " << str << " - " << OUT_YELLOW << "{ " << fileName << " } " << OUT_RESET << "\n";
}

void Message::Warning(const char* str)
{
	std::cout << OUT_YELLOW << "WARNING " << OUT_RESET << "- " << str << '\n';
}

void Message::Warning(const char* str, const char* fileName)
{
	std::cout << OUT_YELLOW << "WARNING " << OUT_RESET << "- " << str << " - " << OUT_YELLOW << "{ " << fileName << " } " << OUT_RESET << "\n";
}