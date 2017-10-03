/*
 * skyscraper.h
 *
 *  Created on: Dec 30, 2016
 *      Author: anders
 */

#ifndef SKY_SKYSCRAPER_H
#define SKY_SKYSCRAPER_H

#include "../disk.h"
#include "../compact.h"
#include "../text.h"
#include "sky/skyscraper/sound.h"

namespace Sky {

class SkyScraper {
public:
	SkyScraper();

	virtual ~SkyScraper();

	void extractSpeechAndText();

protected:
	Disk *_skyDisk;
	SkyCompact *_skyCompact;
	Text *_skyText;
	Sound *_skySound;

};

} // end of namespace Sky

#endif /* SKY_SKYSCRAPER_H */

