#ifndef REGION_H
#define REGION_H

#define NUMBER_OF_REGIONS 5
/**
 * @enum region
 * @brief Describes a region
 * 
 * This enum descripes a region AKA it descripes a location in denmark.
 */
enum region{
    NORTH_JUTLAND = 0, 
    CENTRAL_JUTLAND, 
    SOUTHERN_DENMARK, 
    ZEALAND, 
    CAPITAL_REGION
};

struct location{
	enum region region;
	int region_importance;
};

#endif