/** @file region.h
 *  @brief Contains geographical elements
 * 
 *  This file contains the enums for different regions and the struct that symbolises a location.
*/

#ifndef REGION_H
#define REGION_H

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

/**
 *  @struct location
 *  @brief Contains information about the user's desired region to study in
 *  @var location::region 
 *  A given (enumerated) region in Denmark
 *  @var location::region_importance 
 *  A value within the interval [0;1] scanned from the user
 */
struct location{
	enum region region;
	double region_importance;
};

#endif