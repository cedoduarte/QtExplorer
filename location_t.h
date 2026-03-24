#ifndef LOCATION_T_H
#define LOCATION_T_H

#include "additionalinfo.h"
#include "globalenums.h"

#include <optional>
#include <QString>

struct Location_t
{
    LocationType locationType;
    QString displayText;
    QString iconPath;
    QString path;
    std::optional<AdditionalInfo> additionalInfo;
};

#endif // LOCATION_T_H
