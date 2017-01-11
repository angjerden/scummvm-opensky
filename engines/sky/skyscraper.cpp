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
	_skyLogic = skyLogic;
	_skyCompact = skyCompact;
	_skyDisk = skyDisk;
	_skyText = skyText;
	_skySound = skySound;
}

SkyScraper::~SkyScraper() {
	//don't delete references to classes which other classes use
}

void SkyScraper::extractSpeechAndText() {
	debug("Scraping speech and text items for entire game.");

	memcpy(_scriptVariables, _skyLogic->_scriptVariables, NUM_SKY_SCRIPTVARS);

	//loopThroughLogicList();
}

void SkyScraper::loopThroughLogicList() {
	do {

		uint16 *logicList = (uint16 *)_skyCompact->fetchCpt(_scriptVariables[LOGIC_LIST_NO]);

		while (uint16 id = *logicList++) { // 0 means end of list
			if (id == 0xffff) {
				// Change logic data address
				logicList = (uint16 *)_skyCompact->fetchCpt(*logicList);
				continue;
			}

			_scriptVariables[CUR_ID] = id;
			_compact = _skyCompact->fetchCpt(id);

			// check the id actually wishes to be processed
			if (!(_compact->status & (1 << 6)))
				continue;

			// ok, here we process the logic bit system

			/*if (_compact->status & (1 << 7))
				_skyGrid->removeObjectFromWalk(_compact);*/

			//Debug::logic(_compact->logic);

			//(this->*_logicTable[_compact->logic]) ();
			const LogicTable *_logicTable = _skyLogic->getLogicTable();
			(_skyLogic->*_logicTable[_compact->logic]) (); //<-- must have own logic implementation in skyscraper.cpp

			/*if (_compact->status & (1 << 7))
				_skyGrid->objectToWalk(_compact);*/

			// a sync sent to the compact is available for one cycle
			// only. that cycle has just ended so remove the sync.
			// presumably the mega has just reacted to it.
			_compact->sync = 0;
		}
		// usually this loop is run only once, it'll only be run a second time if the game
		// script just asked the user to enter a copy protection code.
		// this is done to prevent the copy protection screen from flashing up.
		// (otherwise it would be visible for 1/50 second)
	} while (checkProtection());
}

bool SkyScraper::checkProtection() {
	if (_scriptVariables[ENTER_DIGITS]) {
		if (_scriptVariables[CONSOLE_TYPE] == 5) // reactor code
			_scriptVariables[FS_COMMAND] = 240;
		else									 // copy protection
			_scriptVariables[FS_COMMAND] = 337;
		_scriptVariables[ENTER_DIGITS] = 0;
		return true;
	} else
		return false;
}

} //end of namespace Sky
