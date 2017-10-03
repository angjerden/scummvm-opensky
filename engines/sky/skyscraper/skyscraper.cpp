/*
 * skyscraper.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: anders
 */

#include "common/debug.h"

#include "skyscraper.h"

/**
 * SkyScraper - utility to extract media from Sky's data files,
 * 				like speech and text
 *
 * */

/**
 * Todos:
 *  - use _skyLogic to process logic
 *  - find out how to loop through compacts, scripts
 * 	- make own Sound::startSpeech() which doesn't play speech (send speech data to mixer)
 * 	- make own Text::getText()
 */

namespace Sky {

SkyScraper::SkyScraper() {
	//_skyLogic = new Logic();
	_skyDisk = new Disk();
	_skyCompact = new SkyCompact();
	_skyText = new Text(_skyDisk, _skyCompact);
	_skySound = new Sound(_skyDisk);
}

SkyScraper::~SkyScraper() {
	//don't delete references to classes which other classes use
}

void SkyScraper::extractSpeechAndText() {
	debug("Scraping speech and text items for entire game.");

	//do something
}

} //end of namespace Sky
