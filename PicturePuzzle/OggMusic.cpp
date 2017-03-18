#define OGG_MUSIC
#pragma warning (disable: 4786)
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL_mixer.h"
#include "music_ogg.h"

#include "FileManager.h"
#include "Log.h"



OGG_music* OGG_new_hts(FILE* fp)
{
	OGG_music *music;

	music = (OGG_music *)malloc(sizeof *music);
	if ( music ) {
		/* Initialize the music structure */
		memset(music, 0, (sizeof *music));
		OGG_stop(music);
		OGG_setvolume(music, MIX_MAX_VOLUME);
		music->section = -1;

		if ( ov_open(fp, &music->vf, NULL, 0) < 0 ) {
			error << "Not an Ogg Vorbis audio stream: " << file << endl;
			free(music);
			fclose(fp);
			return(NULL);
		}
	} else {
		error << "Out of memory" << endl;
	}
	return(music);
}

Mix_Music* LoadOGG(FILE* fp)
{
//	FILE *fp;
	char *ext;
	Uint8 magic[5];
	Mix_Music *music;


	/* Allocate memory for the music structure */
	music = (Mix_Music *)malloc(sizeof(Mix_Music));
	if ( music == NULL ) {
		error << "Out of memory: " __FILE__ << "(" << __LINE__ << ")" << endl;
		return(NULL);
	}
	music->error = 0;

	music->type = MUS_OGG;
	music->data.ogg = OGG_new_hts(file);
	if ( music->data.ogg == NULL ) {
		music->error = 1;
	}
	

  if ( music->error ) 
  {
		free(music);
		music = NULL;
	}
	return(music);
}
