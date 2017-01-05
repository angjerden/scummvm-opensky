/*
 * skyscraper.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: anders
 */

#include "common/debug.h"

#include "sky/skyscraper.h"

namespace Sky {

SkyScraper::SkyScraper(Logic *skyLogic, SkyCompact *skyCompact, Disk *skyDisk, Text *skyText, Sound *skySound) {
	/*_skyLogic = skyLogic;
	_skyCompact = skyCompact;*/
	_skyDisk = skyDisk;
	_skyText = skyText;
	_skySound = skySound;
}

SkyScraper::~SkyScraper() {
	//don't delete references to classes which other classes use
}

void SkyScraper::extractSpeechAndText() {
	debug("Scraping speech and text items for entire game.");

	uint32 gameVersion = _skyDisk->determineGameVersion();
	debug("Game version from SkyScraper: %d", gameVersion);

	memcpy(_scriptVariables, _skyLogic->_scriptVariables, NUM_SKY_SCRIPTVARS);

	//loop through all compacts
	//uint16 *logicList = (uint16 *)_skyCompact->fetchCpt(_scriptVariables[LOGIC_LIST_NO]);

}

} //end of namespace Sky
