#ifndef _CLUSTER_H
#define _CLUSTER_H

#include "struct.h"
#include <memory>

/* prototypes */
extern "C" {
    const char* run_qubic(const char* input_file, const char* options_str);
}
template <typename Block>
int cluster(std::ostream &fw, const std::vector<std::unique_ptr<Edge>> &edge_list);
template <typename Block>
int report_blocks(std::ostream &fw, const std::vector<std::unique_ptr<Block>> &bb,
                  std::size_t num);
template <typename Block>
void sort_block_list(std::vector<std::unique_ptr<Block>> &el);
long double get_pvalue(continuous a, int b);
std::vector<discrete> get_intersect_row(const std::vector<discrete> &colcand,
                                        discrete *g2, int cnt);
std::vector<discrete>
get_intersect_reverse_row(const std::vector<discrete> &colcand, discrete *g2,
                          int cnt);

#endif
