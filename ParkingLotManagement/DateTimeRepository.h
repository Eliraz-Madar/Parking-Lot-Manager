#pragma once
#include "General.h"
#include "DateTime.h"
#include "FileHelper.h"

bool readDateTimeFromFile(DateTime* dateTime, const FileContext* fileContext);
bool writeDateTimeToFile(const DateTime* dateTime, const FileContext* fileContext);
