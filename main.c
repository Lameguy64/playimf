#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

// Declare assembly routines in player.asm
extern void InstallPlayer(int rate);
extern void RemovePlayer();
extern void PlayIMF(void* imfdata, int imflen);
extern void StopIMF();
extern int GetPosIMF();
extern int GetLoopIMF();

void *loadfile(const char* filename, long* length) {

	// Very simple file loader routine
	
	void* buff;
	long size;
	FILE* fp;
	
	printf("Opening file %s...\n", filename);
	fp = fopen(filename, "rb");
	
	if (!fp) {
		printf("Cannot load %s!\n", filename);
		return NULL;
	}
	
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	printf("Loading %u bytes...\n", size);
	
	buff = malloc(size);
	fread(buff, 1, size, fp);

	fclose(fp);
	
	if ( length ) {
		*length = size;
	}		

	return buff;    
}

int main(int argc, const char* argv[]) {
	
	int i,press,rate=280,loop=-1;
	const char* file = NULL;
	void* imf;
	long imflen;

	// Little banner
	printf("PLAYIMF - Very simple IMF music player\n");
	printf("2018 - 2019 Meido-Tek Productions (Lameguy64)\n\n");
	
	if (argc == 1) {
		printf("Usage:\n");
		printf("   playimf [/r <rate>] [/l <count>] <file>\n\n");
		printf("   /r <rate>  - Music rate in Hz (default: 280).\n");
		printf("   /l <count> - Loop <count> times.\n");
		printf("   <file>     - IMF file to play.\n");
		return 0;
	}
	
	// Parse arguments
	for(i=1; i<argc; i++) {
		
		if (strcasecmp("/r", argv[i]) == 0) {
			i++;
			rate = atoi(argv[i]);
		} else if (strcasecmp("/l", argv[i]) == 0) {
			i++;
			loop = atoi(argv[i]);
			if( loop <= 0 ) {
				printf("Loop value must be greater than 0.\n");
				return 0;
			}
		} else {
			file = argv[i];
			break;
		}
		
	}
	
	if (file == NULL) {
		printf("No filename specified.\n");
		return 0;
	}
	
	// Load the file into memory
	imf = loadfile(file, &imflen);

	if (!imf) {
		return 0;
	}

	// Install the player interrupt service
	InstallPlayer(rate);
	
	// Play the IMF file
	PlayIMF(imf, (int)imflen);

	printf("Press 's' to stop, 'p' to play/restart, 'q' to quit...\n");
	
	press = 0;
	while(press != 'q') {
		
		if( kbhit() ) {

			press = getch();
			
			if (press == 's') {
				StopIMF();
				printf("Stopped.\n");
			}
			
			if (press == 'p') {
				PlayIMF(imf, (int)imflen);
				printf("Playing.\n");
			}
			
		}
		
		if(loop > 0) {
			
			if( GetLoopIMF() >= loop ) {
				break;
			}
			
		}
		
	}
	
	// Stop IMF
	StopIMF();
	
	// Remove player interrupt service
	RemovePlayer();
	
	return 0;
    
}
