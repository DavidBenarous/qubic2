#ifndef _MAKE_GRAPH_H
#define _MAKE_GRAPH_H

#include "struct.h"
#include <iostream>

/* prototypes */
void make_graph(std::ostream &fw);
continuous get_spearman(discrete *s1, discrete *s2, int row_1, int row_2,
                        int cnt);
continuous get_pearson(const discrete *s1, const discrete *s2, int row_1,
                       int row_2, int cnt);
continuous get_f_socre(continuous a, continuous b, continuous c);

#endif
