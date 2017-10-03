/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include <fstream>
#include <sys/stat.h>

#include "common/config-manager.h"
#include "common/debug.h"
#include "common/file.h"
#include "common/endian.h"
#include "common/textconsole.h"

#include "sky/disk.h"
#include "sky/logic.h"
#include "sky/sky.h"
#include "sky/skydefs.h"
#include "sky/skyscraper/sound.h"
#include "sky/struc.h"

namespace SkyScraper {

#define SOUND_FILE_BASE 60203
#define MAX_FX_NUMBER 393
#define SFXF_START_DELAY 0x80
#define SFXF_SAVE 0x20

#include "common/pack-start.h"	// START STRUCT PACKING

struct RoomList {
	uint8 room;
	uint8 adlibVolume;
	uint8 rolandVolume;
} PACKED_STRUCT;

struct Sfx {
	uint8 soundNo;
	uint8 flags;
	RoomList roomList[10];
} PACKED_STRUCT;

#include "common/pack-end.h"	// END STRUCT PACKING

uint16 Sound::_speechConvertTable[8] = {
	0,									//;Text numbers to file numbers
	600,								//; 553 lines in section 0
	600+500,							//; 488 lines in section 1
	600+500+1330,						//;1303 lines in section 2
	600+500+1330+950,					//; 922 lines in section 3
	600+500+1330+950+1150,				//;1140 lines in section 4
	600+500+1330+950+1150+550,			//; 531 lines in section 5
	600+500+1330+950+1150+550+150,		//; 150 lines in section 6
};


Sound::Sound(Disk *pDisk) {
	_skyDisk = pDisk;
	_soundData = NULL;
	//_mixer = mixer;
	_saveSounds[0] = _saveSounds[1] = 0xFFFF;
	//_mainSfxVolume = pVolume;
	_isPaused = false;
}

Sound::~Sound() {
	//_mixer->stopAll();
	free(_soundData);
}

bool Sound::startSpeech(uint16 textNum) {
	if (!(SkyEngine::_systemVars.systemFlags & SF_ALLOW_SPEECH))
		return false;
	uint16 speechFileNum = _speechConvertTable[textNum >> 12] + (textNum & 0xFFF);

	uint8 *speechData = _skyDisk->loadFile(speechFileNum + 50000);
	if (!speechData) {
		debug(9,"File %d (speechFile %d from section %d) wasn't found", speechFileNum + 50000, textNum & 0xFFF, textNum >> 12);
		return false;
	}

	uint32 speechSize = ((DataFileHeader *)speechData)->s_tot_size - sizeof(DataFileHeader);
	uint8 *playBuffer = (uint8 *)malloc(speechSize);
    memcpy(playBuffer, speechData + sizeof(DataFileHeader), speechSize);

    Common::FSNode dir(ConfMan.get("path"));
    const char* pathToSky = dir.getPath().c_str();
    char openSkyPath[300];
    sprintf(openSkyPath, "%s/opensky/", pathToSky);
    
    uint16 speechFileNumForOutput = 50000 + speechFileNum;

	char outputFileName[100];
	sprintf(outputFileName, "%s/speech-%d", openSkyPath, speechFileNumForOutput);
	struct stat buf;
	if (stat(outputFileName, &buf) == -1) { //if file does not exist, write speechData to disk
		std::ofstream file (outputFileName, std::ofstream::binary);
		file.write((char *)speechData, speechSize);
		file.close();

        free(speechData);

		debug("Saved speech: %d", speechFileNumForOutput);
    }

	return true;
}

} // End of namespace Sky
