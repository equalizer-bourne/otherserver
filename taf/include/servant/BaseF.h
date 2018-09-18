// **********************************************************************
// This file was generated by a TAF parser!
// TAF version 4.6.0 by WSRD Tencent.
// Generated from `BaseF.jce'
// **********************************************************************

#ifndef __BASEF_H_
#define __BASEF_H_

#include <map>
#include <string>
#include <vector>
#include "jce/Jce.h"
using namespace std;


namespace taf
{
    const taf::Short JCEVERSION = 1;

    const taf::Short WUPVERSION = 2;

    const taf::Short WUPVERSION2 = 3;

    const taf::Char JCENORMAL = 0;

    const taf::Char JCEONEWAY = 1;

    const taf::Int32 JCESERVERSUCCESS = 0;

    const taf::Int32 JCESERVERDECODEERR = -1;

    const taf::Int32 JCESERVERENCODEERR = -2;

    const taf::Int32 JCESERVERNOFUNCERR = -3;

    const taf::Int32 JCESERVERNOSERVANTERR = -4;

    const taf::Int32 JCESERVERRESETGRID = -5;

    const taf::Int32 JCESERVERQUEUETIMEOUT = -6;

    const taf::Int32 JCEASYNCCALLTIMEOUT = -7;

    const taf::Int32 JCEPROXYCONNECTERR = -8;

    const taf::Int32 JCESERVEROVERLOAD = -9;

    const taf::Int32 JCESERVERUNKNOWNERR = -99;

    const taf::Int32 JCEMESSAGETYPENULL = 0;

    const taf::Int32 JCEMESSAGETYPEHASH = 1;

    const taf::Int32 JCEMESSAGETYPEGRID = 2;

    const taf::Int32 JCEMESSAGETYPEDYED = 4;

    const taf::Int32 JCEMESSAGETYPESAMPLE = 8;

    const taf::Int32 JCEMESSAGETYPEASYNC = 16;


}



#endif
