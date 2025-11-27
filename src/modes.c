#include <stdio.h>

#include "decoderaw.h"
#include "extract.h"
#include "writehex.h"
#include "regs.h"
#include "mem.h"
#include "writefstate.h"

#include "const.h"
#include "util.h"


int
interMode()
{
	return 0;
}


int
stepMode(const char *fin)
{
	FILE *rfp;

	rfp = efopen(fin, "r");
	fclose(rfp);
	
	return 0;
}


int
autoMode(const char *fin, const char *fhex, const char *ffstate)
{
	FILE *rfp, *hexfp, *fstatefp;
	int ignore;
	int ninsts;
	Rawinst rawinst;
	Inst inst;

	ninsts = 0;
	rfp = efopen(fin, "r");
	hexfp = efopen(fhex, "w");

	while ((ignore = extract(rfp, &rawinst)) != EOF){
		if (!ignore){
			decoderaw(&rawinst, &inst);
			writehex(&inst, hexfp);
			++ninsts;
		}
	}
	fclose(rfp);
	fclose(hexfp);

	hexfp = efopen(fhex, "r");
	storeinsts(hexfp);
	while (regs[PC].val != 4 * (ninsts)){
		exec(regs[PC].val);
		regs[PC].val += 4;
	}
	fclose(hexfp);

	fstatefp = efopen(ffstate, "w");
	writefstate(fstatefp);
	fclose(fstatefp);
	
	return 0;
}

