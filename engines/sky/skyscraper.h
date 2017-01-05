/*
 * skyscraper.h
 *
 *  Created on: Dec 30, 2016
 *      Author: anders
 */

#ifndef SKY_SKYSCRAPER_H
#define SKY_SKYSCRAPER_H

#include "logic.h"
#include "compact.h"
#include "disk.h"
#include "text.h"
#include "sound.h"

//#define NUM_SKY_SCRIPTVARS 838

namespace Sky {

class SkyScraper {
public:
	SkyScraper(Logic *skyLogic, SkyCompact *skyCompact, Disk *skyDisk, Text *skyText, Sound *skySound);
	virtual ~SkyScraper();

	void extractSpeechAndText();

	uint32 _scriptVariables[NUM_SKY_SCRIPTVARS];

protected:
	Logic *_skyLogic;
	SkyCompact *_skyCompact;
	Disk *_skyDisk;
	Text *_skyText;
	Sound *_skySound;

};

} // end of namespace Sky

#endif /* SKY_SKYSCRAPER_H */

