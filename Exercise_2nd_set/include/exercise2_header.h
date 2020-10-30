/// exercise2_header.h
#include "ac_int.h"
#include "ac_fixed.h"
#include "ac_channel.h"

static const int W = 6;
static const int Wout = 14;
template <int W>

struct CSD {
    ac_int<W,false> x_p;
    ac_int<W,false> x_m;
};

// declare all functions 
void csd_encode(ac_int<W,true> &num, CSD<W> &num_csd);
//
ac_int<Wout,true> csd_mult (ac_int<W,true> &in, const CSD<W> &constant_csd);
//
void runlength_encode(ac_channel<ac_int<4,false> > &in, ac_channel<ac_int<4,false> > &out);


